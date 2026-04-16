#include "WinSystemRule.h"

#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_qt.h"
#include <QSettings>
#include <QDebug>


// 注册表路径
const QString registryPath = "HKEY_CURRENT_USER\\Software\\Qycx\\misClient\\Scheduler";
const QString ucHardwareAccl_key = "ucHardwareAccl_qt";
//
WinSystemRule::WinSystemRule(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);



	CCtxQyMc* pQyMc = g_pQyMc;
	bool  bDebug = false;
	int  iVer;
	TCHAR  tBuf[128];
	//
	char verBuf[128];

	_snprintf(verBuf, sizeof(verBuf), "%s", qnmVerStr(pQyMc->iServiceId));
	if (verBuf[0] && verBuf[strlen(verBuf) - 1] == 'd')  bDebug = TRUE;
	iVer = atol(verBuf);
	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s V%d.%02d.%02d%s"  ),  appName,  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Ver: V%d.%02d.%02d%s"  ),  iVer  /  10000,  (  iVer  /  100  )  %  100,  iVer  %  100,  bDebug  ?  _T(  "Debug"  )  :  _T(  ""  )  );
	_sntprintf(tBuf, mycountof(tBuf), _T("Ver: V%d.%02d.%02d.%02d%s"), iVer / 1000000, (iVer / 10000) % 100, (iVer / 100) % 100, iVer % 100, bDebug ? _T("Debug") : _T(""));
	//
	_snprintf(verBuf, sizeof(verBuf), "%s", qnmDbVerStr(pQyMc->iServiceId));
	if (verBuf[0] && verBuf[strlen(verBuf) - 1] == 'd')  bDebug = TRUE;
	iVer = atol(verBuf);
	_sntprintf(tBuf, mycountof(tBuf), _T("%s, DbVer: %d.%02d.%02d%s"), tBuf, iVer / 10000, (iVer / 100) % 100, iVer % 100, bDebug ? _T("Debug") : _T(""));
	//SetDlgItemText(hDlg, IDC_STATIC_ver, CQyString(tBuf));

	//关于
	ui.labcp->setText(QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle));
	ui.labver->setText(QString::fromUtf16((char16_t*)tBuf));



	//显卡选择

	// 清空现有内容
	ui.displayCardBox->clear();
	ui.displayCardBox->addItem(u8"启用", 3);
	ui.displayCardBox->addItem(u8"禁用", 2);


	//
	QString displayCardValue = readRegistryValue(registryPath, ucHardwareAccl_key);
	_displayCardBox_index = displayCardValue.toInt();

	int index = ui.displayCardBox->findData(displayCardValue);


}

WinSystemRule::~WinSystemRule()
{
}

// 写入/修改注册表字符串值
void WinSystemRule::writeRegistryValue(const QString& path, const QString& key, const QString& value) {
	// 参数说明：
	// path: 注册表路径，例如 "HKEY_CURRENT_USER\\Software\\MyCompany\\MyApp"
	// key: 键名，例如 "UserName"
	// value: 要设置的字符串值

	QSettings settings(path, QSettings::NativeFormat);
	settings.setValue(key, value);

	// 检查是否成功（可选）
	if (settings.status() == QSettings::NoError) {
		qDebug() << "注册表值写入成功:" << key << "=" << value;
	}
	else {
		qDebug() << "注册表值写入失败，错误码:" << settings.status();
	}
}

// 读取注册表值
QString WinSystemRule::readRegistryValue(const QString& path, const QString& key) {
	QSettings settings(path, QSettings::NativeFormat);

	// 检查键是否存在
	if (!settings.contains(key)) {
		return NULL;
	}

	// 获取值并确保转换为字符串
	return settings.value(key).toString();
}

//点击保存
void WinSystemRule::on_saveBtn_clicked() {
	QVariant currentData = ui.displayCardBox->currentData();
	int currentId = currentData.toInt();

	writeRegistryValue(registryPath, ucHardwareAccl_key, QString::number(currentId));


	_displayCardBox_index = currentId;
	ui.save_txt->setText(u8"保存成功，重启客户端生效！");

}


void WinSystemRule::reload() {
	int index = ui.displayCardBox->findData(_displayCardBox_index);
	if (index != -1) {
		ui.displayCardBox->setCurrentIndex(index);
	}
}