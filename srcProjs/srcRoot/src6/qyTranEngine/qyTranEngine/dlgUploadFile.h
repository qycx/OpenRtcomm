#pragma once

#include <QWidget>
#include "ui_dlgUploadFile.h"

//#include <dlgOfflineResProc.h>
struct DlgOfflineRes_var_DEF;

class dlgUploadFile : public QWidget
{
	Q_OBJECT

public:
	dlgUploadFile(QWidget *parent = nullptr);
	~dlgUploadFile();

	struct DlgOfflineRes_varEx_DEF*  m_var;


protected:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	void SendFile(QString fullFileName, HWND hWnd);

public slots:
	void slot_upload_click();

private:
	Ui::dlgUploadFileClass ui;
};
