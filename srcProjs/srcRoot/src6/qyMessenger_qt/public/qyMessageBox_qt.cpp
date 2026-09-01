

#include	"stdafx.h"
#include <qmessagebox.h>
#include <qtimer.h>


__declspec(dllexport)  int  WINAPI  qyMessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType, UINT  nTimeoutInS, BOOL* pbSyncFlg)
{
	//return MessageBox(hWnd, lpText, lpCaption, uType);

	QString title;
	QString txt;
	if (lpCaption) title = QString::fromUtf16((char16_t*)lpCaption);
	if (lpText) txt = QString::fromUtf16((char16_t*)lpText);

	QWidget* pParent = QWidget::find((WId)hWnd);

	QMessageBox* box = new QMessageBox(QMessageBox::Information, title, txt,QMessageBox::Ok,pParent);
	QTimer::singleShot(nTimeoutInS *  1000, box, SLOT(accept())); //也可将accept改为close
	box->exec();//box->show();都可以

	return  0;
}