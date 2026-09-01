#include "WinSerConfig.h"
#include "ui_WinSerConfig.h"
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QUuid>
#include "CQmcLogin.h"
 
#pragma execution_character_set("gbk")

WinSerConfig::WinSerConfig(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WinSerConfig)
{
    ui->setupUi(this); 
    memset(&m_var , 0, sizeof(m_var));
    ui->uuid->setVisible(false);
    initTableWidget();
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(cancelBtnClicked()));
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addBtnClicked()));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnClicked()));
    loadStyleSheet("WinSerConfig");  
    setWindowFlags(Qt::FramelessWindowHint); 
    //
    winTitle = new WinTitle(this);
    winTitle->setButtonType(MIN_BUTTON);
    winTitle->move(0, 0);
    connect(winTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(winTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
    
    //
    
    

}

WinSerConfig::~WinSerConfig()
{
    delete ui; 
    if (winTitle) {
        delete winTitle;
        winTitle = nullptr;
    } 
}

int WinSerConfig::init() {
    
    CQmcLogin* pLogin = (CQmcLogin*)m_var.plogin;
     pLogin->m_var.cntCfgs;
     ui->tableWidget->clear();
     ui->tableWidget->setAlternatingRowColors(true);
     //隐藏垂直表头.toLocal8Bit()
     ui->tableWidget->verticalHeader()->hide();
     QStringList header;
     header
         << QStringLiteral("序号")
         << QStringLiteral("操作")
         << QStringLiteral("uuid")
         << QStringLiteral("服务器描述")
         // <<QStringLiteral("缺省IP")
         << QStringLiteral("服务器地址")
         //<<QStringLiteral("备用地址2")
         << QStringLiteral("端口")
         ;
     ui->tableWidget->setColumnCount(6);
     ui->tableWidget->setHorizontalHeaderLabels(header);
     ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
     ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
     //设置列宽
     ui->tableWidget->setColumnWidth(0, 60);
     ui->tableWidget->setColumnWidth(1, 100);
     ui->tableWidget->setColumnWidth(2, 110);
     ui->tableWidget->setColumnWidth(3, 120);
     ui->tableWidget->setColumnWidth(4, 130);
     ui->tableWidget->setColumnWidth(5, 80);
     //ui->tableWidget->setColumnWidth(6, 80);
    // ui->tableWidget->setColumnWidth(7, 80);
     ui->tableWidget->setColumnHidden(2, true);

     //初始化读取数据
     const QString&& path = QApplication::applicationDirPath() + "/" + QString("qyconf.ini");
     QSettings settings(path, QSettings::IniFormat);
     QStringList groupList = settings.childGroups();


     for (int i = 0; i < CONST_maxOfVideoConferencingServers; i++)
     {
         if (pLogin->m_var.cntCfgs.mems[i].cntName[0] == _T('\0')) {
             break;
         }
         QString serviceName =QString::fromStdWString( pLogin->m_var.cntCfgs.mems[i].cntName);
         QString addr1 =  pLogin->m_var.cntCfgs.mems[i].cntAddr;
         QString port = QString::number(pLogin->m_var.cntCfgs.mems[i].port);
         insertTableWidget(QString::number(i),serviceName, addr1, port);
     }
     //设置默认第一条
     //if (!ui->serviceName->text().trimmed().isEmpty()) 
     {

         ui->serviceName->setText( QString::fromStdWString(pLogin->m_var.cntCfgs.mems[0].cntName) );
         ui->addr1->setText( pLogin->m_var.cntCfgs.mems[0].cntAddr);
         ui->port->setText(QString::number(pLogin->m_var.cntCfgs.mems[0].port));
     }

    return 0;
}

void WinSerConfig::initTableWidget()
{
    


}


void WinSerConfig::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/Resources/QSS/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet("");
        QString qsstyleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(qsstyleSheet);
    }
    file.close();
}

void WinSerConfig::onShowClose(bool)
{
    close();
}

void WinSerConfig::onShowMin(bool)
{
    showMinimized();
}

//void WinSerConfig::insertTableWidget(QString uuid,QString serviceName,QString ipAddr,QString addr1,QString addr2,QString port){
void WinSerConfig::insertTableWidget(QString uuid,QString serviceName,QString addr1,QString port){
    int RowCont =ui->tableWidget->rowCount();  
    ui->tableWidget->insertRow(RowCont);//增加一行
    QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(RowCont));
    item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(RowCont,0,item1);
    QPushButton *editBtn = new QPushButton(QStringLiteral("修改"));
    QPushButton *delBtn = new QPushButton(QStringLiteral("删除"));
    editBtn->setStyleSheet("QPushButton{ background:transparent; font-size: 14px; color: rgb(0,148, 206); border:none; }");
    delBtn->setStyleSheet("QPushButton{ background:transparent; font-size: 14px; color: rgb(225,7, 55); border:none; }");
    editBtn->setObjectName("editBtn"+ uuid);
    delBtn->setObjectName("delBtn"+ uuid);
    connect(editBtn, SIGNAL(clicked()), this, SLOT(editBtnClicked()));
    connect(delBtn, SIGNAL(clicked()), this, SLOT(delBtnClicked()));
    QWidget *widget = new QWidget();
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(editBtn);
    hLayout->addWidget(delBtn);
    widget->setLayout(hLayout);
    ui->tableWidget->setCellWidget(RowCont,1,widget);
    QTableWidgetItem *item2 = new QTableWidgetItem(uuid);
    item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(RowCont,2,item2);
    QTableWidgetItem *item3 = new QTableWidgetItem(serviceName);
    item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(RowCont,3,item3);
    //QTableWidgetItem *item4 = new QTableWidgetItem(ipAddr);
    //item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //ui->tableWidget->setItem(RowCont,4,item4);
    QTableWidgetItem *item5 = new QTableWidgetItem(addr1);
    item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(RowCont,4,item5);
   // QTableWidgetItem *item6 = new QTableWidgetItem(addr2);
    //item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //ui->tableWidget->setItem(RowCont,6,item6);
    QTableWidgetItem *item7 = new QTableWidgetItem(port);
    item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(RowCont,5,item7);
}



//void WinSerConfig::updateTableWidget(QString uuid,QString serviceName,QString ipAddr,QString addr1,QString addr2,QString port){
void WinSerConfig::updateTableWidget(QString uuid,QString serviceName,QString addr1,QString port){

    int RowCont =ui->tableWidget->rowCount();
    for(int i=0;i<RowCont;i++){
        QString uuid_t = ui->tableWidget->item(i,2)->text();
        if(uuid_t.contains(uuid)){
            QTableWidgetItem *item2 = new QTableWidgetItem(uuid);
            item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i,2,item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(serviceName);
            item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i,3,item3);
            //QTableWidgetItem *item4 = new QTableWidgetItem(ipAddr);
            //item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            //ui->tableWidget->setItem(i,4,item4);
            QTableWidgetItem *item5 = new QTableWidgetItem(addr1);
            item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i,4,item5);
            //QTableWidgetItem *item6 = new QTableWidgetItem(addr2);
            //item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            //ui->tableWidget->setItem(i,6,item6);
            QTableWidgetItem *item7 = new QTableWidgetItem(port);
            item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i,5,item7);
            break;
        }
    }
} 


/*编辑按钮点击事件*/
void WinSerConfig::editBtnClicked(){
    CQmcLogin* pLogin = (CQmcLogin*)m_var.plogin;

    QPushButton *senderObj=qobject_cast<QPushButton*>(sender());
    QString name = senderObj->objectName();
    QStringList list = name.split("editBtn");
    QString uuid = list[1];  

    m_var.index_cntCfg = uuid.toInt();
    ui->uuid->setText(uuid);
    ui->serviceName->setText(QString::fromStdWString(pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].cntName));
    ui->addr1->setText(pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].cntAddr);
    ui->port->setText(QString::number(pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].port));
    

    /*const QString&& path = QApplication::applicationDirPath() + "/" + QString("qyconf.ini");
    QSettings settings(path, QSettings::IniFormat);
    QString serviceName = settings.value(uuid + "/serviceName").toString();
    QString addr1 = settings.value(uuid + "/addr1").toString();
    QString port = settings.value(uuid + "/port").toString();  */

   
   /* ui->serviceName->setText(serviceName);
    ui->addr1->setText(addr1);
    ui->port->setText(port); */
}

/*删除按钮点击事件*/
void WinSerConfig::delBtnClicked(){
   int result = WinMsgBox::showWinMsgBox(this, QStringLiteral("信息提示"), QStringLiteral("您确定要删除吗？"), MESSAGE_WARNNING, BUTTON_OK_AND_CANCEL, true);
   if (result == ID_OK)
   {
       QY_MC* pQymc = g_pQyMc;
       QPushButton *senderObj=qobject_cast<QPushButton*>(sender());
       QString name = senderObj->objectName();
       QStringList list = name.split("delBtn"); 
       QString uuid = list[1]; 
       CQmcLogin* pLogin = (CQmcLogin*)m_var.plogin;
       HKEY		hKeyRoot0 = HKEY_CURRENT_USER;
       TCHAR		tQnmSchedulerBuf[256] = _T("");
       TCHAR		tBuf1[256] = _T("");
       
       if (uuid.toInt() == 0) {
           _sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s"), CQyString(pQymc->cfg.pSysCfg->rootKey_qnmScheduler));
       }
       else
       {
           _sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s\\%d"), CQyString(pQymc->cfg.pSysCfg->rootKey_qnmScheduler), uuid.toInt());
       }

       tBuf1[0] = 0;
       qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_cntName), tBuf1);

       //
       safeTcsnCpy(tBuf1, pLogin->m_var.cntCfgs.mems[uuid.toInt()].cntName, mycountof(pLogin->m_var.cntCfgs.mems[uuid.toInt()].cntName));
       //myTChar2Utf8(tBuf1, pLogin->m_var.cntCfgs.mems[uuid.toInt()].cntAddr, mycountof(pLogin->m_var.cntCfgs.mems[uuid.toInt()].cntAddr));
       int RowCont = ui->tableWidget->rowCount();
       for (int i = 0;i < RowCont;i++) {
           QString uuid_t = ui->tableWidget->item(i, 2)->text();
           if (uuid_t.contains(uuid)) {
               ui->tableWidget->removeRow(i);
               break;
           }
       } 
   }
}

/*取消按钮点击事件*/
void WinSerConfig::cancelBtnClicked(){ 
    this->close();
} 

void WinSerConfig::addBtnClicked(){
    CQmcLogin* pLogin = (CQmcLogin*)m_var.plogin;
    pLogin->m_var.cntCfgs;
    QString  qstr;
    
    int i;
    for ( i = 0; i < CONST_maxOfVideoConferencingServers; i++)
    {
        if (pLogin->m_var.cntCfgs.mems[i].cntName[0] == 0) {
            m_var.index_cntCfg = i;
            break;
        }
    }
    if (i == CONST_maxOfVideoConferencingServers) {
        goto  errLabel;
    }

   
    qstr = u8"服务器" + QString::number(i);
    
    ui->uuid->setText(QString::number(i));
    ui->serviceName->setText(qstr);
    // ui->ipAddr->setText("");
    ui->addr1->setText("");
    //ui->addr2->setText("");
    ui->port->setText("8768");
    
    //
errLabel:

    return;
}

void WinSerConfig::saveBtnClicked(){

    CQmcLogin* pLogin = (CQmcLogin*)m_var.plogin;

    QY_MC* pQymc = g_pQyMc;
    HKEY		hKeyRoot0 = HKEY_CURRENT_USER;
    TCHAR		tQnmSchedulerBuf[256] = _T("");
    TCHAR		tBuf1[256] = _T("");
    TCHAR		tBuf2[256] = _T("");
    TCHAR		tBuf3[256] = _T("");

    QString serviceName = ui->serviceName->text().trimmed();
    QString addr1 = ui->addr1->text().trimmed();
    QString port = ui->port->text().trimmed();

    QString index_cnt = ui->uuid->text().trimmed();

    safeTcsnCpy((wchar_t*)serviceName.utf16() , tBuf1, mycountof( tBuf1 ));
    safeTcsnCpy((wchar_t*)addr1.utf16() , tBuf2, mycountof( tBuf2 ));
    safeTcsnCpy((wchar_t*)port.utf16() , tBuf3, mycountof( tBuf3 ));
    
    if (!m_var.index_cntCfg) {
        _sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s"), CQyString(pQymc->cfg.pSysCfg->rootKey_qnmScheduler));
    }else
    {
        _sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf) , _T("%s\\%d") , CQyString(pQymc->cfg.pSysCfg->rootKey_qnmScheduler), m_var.index_cntCfg );
    }


    


    if(addr1.isEmpty()){
        WinMsgBox::showWinMsgBox(this, QStringLiteral("信息提示"), QStringLiteral("请填写服务器地址一项!"), MESSAGE_INFORMATION, BUTTON_CLOSE, true);
        return;
    }
    if(port.isEmpty()){
        WinMsgBox::showWinMsgBox(this, QStringLiteral("信息提示"), QStringLiteral("请填写端口!"), MESSAGE_INFORMATION, BUTTON_CLOSE, true);
        return;
    }
    if(!(addr1.isEmpty() && !port.isEmpty())){
        
        qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_cntName), tBuf1);
        qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_cntAddr), tBuf2);
        qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_cntPort), tBuf3);

        
        //
        safeTcsnCpy( tBuf1 ,pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].cntName , mycountof(pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].cntName));
        myTChar2Utf8(tBuf2, pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].cntAddr, mycountof(pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].cntAddr));
        pLogin->m_var.cntCfgs.mems[m_var.index_cntCfg].port = _ttol(tBuf3);
        //
       
        onButtonCloseClicked();
#if 0
        QString uuid = ui->uuid->text().trimmed();
        if(uuid.isEmpty()){
             QUuid id = QUuid::createUuid(); 
             uuid = id.toString();
             insertTableWidget(uuid,serviceName,addr1,port);
        }
        else{
             updateTableWidget(uuid,serviceName,addr1,port);
        }
        const QString&& path = QApplication::applicationDirPath() + "/" + QString("qyconf.ini");
        QSettings settings(path, QSettings::IniFormat);
        settings.setValue(QString("/%1/%2").arg(uuid).arg("serviceName"), serviceName);
       // settings.setValue(QString("/%1/%2").arg(uuid).arg("ipAddr"), ipAddr);
        settings.setValue(QString("/%1/%2").arg(uuid).arg("addr1"), addr1);
       // settings.setValue(QString("/%1/%2").arg(uuid).arg("addr2"), addr2);
        settings.setValue(QString("/%1/%2").arg(uuid).arg("port"), port); 
        
        
        
        int res = WinMsgBox::showWinMsgBox(this, QStringLiteral("信息提示"), QStringLiteral("保存成功!"), MESSAGE_INFORMATION, BUTTON_OK, true);
        
        
        if (0==res) {
            ui->uuid->setText("");
            ui->serviceName->setText("");
           // ui->ipAddr->setText("");
            ui->addr1->setText("");
            //ui->addr2->setText("");
            ui->port->setText(""); 
        }
#endif
    }
}

void WinSerConfig::editBtnClicked(QString uuid){
    



    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    const QString&& path = QApplication::applicationDirPath() + "/" + QString("qyconf.ini");
    QSettings settings(path, QSettings::IniFormat);
    QString serviceName = settings.value(uuid+"/serviceName").toString();
    QString addr1 = settings.value(uuid+"/addr1").toString();
    QString port = settings.value(uuid+"/port").toString();
    ui->serviceName->setText(serviceName);
    ui->addr1->setText(addr1);
    ui->port->setText(port);
}

void WinSerConfig::deleteBtnClicked(QString uuid){
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();

    const QString&& path = QApplication::applicationDirPath() + "/" + QString("qyconf.ini");
    QSettings settings(path, QSettings::IniFormat);
    settings.remove(uuid);
}

void WinSerConfig::mouseMoveEvent(QMouseEvent* e)
{
    if (m_mousePressed && (e->buttons() == Qt::LeftButton)) {
        if (mousePoint != QPoint(0, 0)) {
            move(e->globalPos() - mousePoint);
        }
        e->accept();
    }
}
void WinSerConfig::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}
void WinSerConfig::mouseReleaseEvent(QMouseEvent*)
{
    m_mousePressed = false;
}

void WinSerConfig::onButtonMinClicked()
{
    showMinimized();
}

void WinSerConfig::onButtonCloseClicked()
{
    close();
}

QString WinSerConfig::getCurrent() {
 

    return "";
}