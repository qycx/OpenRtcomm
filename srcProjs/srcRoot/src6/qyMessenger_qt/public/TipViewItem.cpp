#include "TipViewItem.h"

TipViewItem::TipViewItem(const SessionInfo session, QStandardItem* item, QWidget *parent)
	: QWidget(parent)
{
	_sid = session.session_id;
	_sname =QString::fromStdWString( session.session_name);
	ui.setupUi(this);
	QString strName = fontMetrics().elidedText(_sname, Qt::ElideRight, 120);
	ui.lab_name->setText(strName);
	ui.lab_count->setText(QString::number(session.unread_count));
	_set_photo(QString::fromStdWString(session.header_url));
}

TipViewItem::~TipViewItem()
{
	
}

qint64 TipViewItem::sId()
{
	return _sid;
}

QString TipViewItem::sName()
{
	return _sname;
}

void TipViewItem::_set_photo(QString img)
{
	QImage	image;
	if (image.load(img))
	{
		QSize sz = ui.lab_photo->size();
		QImage img = image.scaled(sz.width(), sz.height(), Qt::KeepAspectRatioByExpanding);
		QPixmap pixmap = QPixmap::fromImage(img);
		ui.lab_photo->setPixmap(pixmap);
	}
}


//void TipViewItem::on_download_finished(QString id, QString spath, DownLoadType type)
//{
//	if (type == DownLoadType::TYPE_PHOTO)
//	{
//		_set_photo(spath);
//	}
//}
