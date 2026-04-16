#include "WinSystemOther.h"

#include <QFileDialog>
#include <QMessageBox>

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include "ctxQmc.h"

WinSystemOther::WinSystemOther(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WinSystemOtherClass())
{
    ui->setupUi(this);

    connect(this->ui->pushButton_select, &QPushButton::clicked, this, &WinSystemOther::selectDirectory);
    connect(this->ui->pushButton_save, &QPushButton::clicked, this, &WinSystemOther::save);

    Init();
}


void WinSystemOther::reload() {
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    ui->checkBox_save->setChecked(pProcInfo->cfg.policy.isSaveICFile);
}

void WinSystemOther::Init() {

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    //QY_REG				reg;
    //TCHAR* pRegVal = NULL;

    //memset(&reg, 0, sizeof(reg));
    //reg.hKeyRoot0 = HKEY_CURRENT_USER;
    //lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

    //pRegVal = (TCHAR*)_T(CONST_regValName_dirToSaveICFile);
    //if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)pProcInfo->cfg.policy.dirToSaveICFile,
    //    sizeof(pProcInfo->cfg.policy.dirToSaveICFile), 0))  pProcInfo->cfg.policy.dirToSaveICFile[0] = 0;
    //tTrim(pProcInfo->cfg.policy.dirToSaveICFile);
    //if (pProcInfo->cfg.policy.dirToSaveICFile[0]) {
    //    if (tTrailDir(pProcInfo->cfg.policy.dirToSaveICFile, mycountof(pProcInfo->cfg.policy.dirToSaveICFile)))  /*goto  errLabel*/;
    //}

    QString dir = QString::fromWCharArray(pProcInfo->cfg.policy.dirToSaveICFile);

    ui->lineEdit_ic_path->setText(dir);
    
    ui->checkBox_save->setChecked(pProcInfo->cfg.policy.isSaveICFile);
    m_isSave = pProcInfo->cfg.policy.isSaveICFile;
}

WinSystemOther::~WinSystemOther()
{
	delete ui;
}


void WinSystemOther::selectDirectory() 
{
    QString orgDir = ui->lineEdit_ic_path->text();

    if (orgDir.isEmpty())
        orgDir = QDir::homePath();

    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("选择目录"),
        orgDir,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (!dir.isEmpty()) {
        // 处理选择的目录
        //QMessageBox::information(this, "目录选择", "你选择的目录是: " + dir);
        ui->lineEdit_ic_path->setText(dir);
    }   


    

}

void WinSystemOther::save()
{
    QString dir = ui->lineEdit_ic_path->text();

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

   /* if (lstrcmpi(dir.toStdWString().c_str(), pProcInfo->cfg.policy.dirToSaveICFile) == 0) {
        return;
    }   */

    safeTcsnCpy(dir.toStdWString().c_str(), pProcInfo->cfg.policy.dirToSaveICFile,
        mycountof(pProcInfo->cfg.policy.dirToSaveICFile));

    tTrim(pProcInfo->cfg.policy.dirToSaveICFile);
    if (pProcInfo->cfg.policy.dirToSaveICFile[0]) {
        if (!bDir(pProcInfo->cfg.policy.dirToSaveICFile)) {
            //qyShowHint(_T("The directory to save ic file does not exist"));  return;
        }
    }

    QY_REG reg;
    TCHAR* pRegVal = NULL;

    memset(&reg, 0, sizeof(reg));
    reg.hKeyRoot0 = HKEY_CURRENT_USER;
    lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));
     
    //pRegVal = (TCHAR*)_T(CONST_regValName_dirToSaveICFile);
    qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_dirToSaveICFile), pProcInfo->cfg.policy.dirToSaveICFile);   
    
    if (ui->checkBox_save->isChecked())
        pProcInfo->cfg.policy.isSaveICFile = true;
    else 
        pProcInfo->cfg.policy.isSaveICFile = false;

    qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_isSaveICFile), pProcInfo->cfg.policy.isSaveICFile ? _T("1") : _T(""));
}