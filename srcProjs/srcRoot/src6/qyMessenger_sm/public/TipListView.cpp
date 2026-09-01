#include "TipListView.h"
#include "TipViewItem.h"



TipListView::TipListView(QWidget *parent)
	: QListView(parent)
{
	this->setFocusPolicy(Qt::NoFocus);
	_item_module = new QStandardItemModel(this);
	this->setModel(_item_module);
	connect(this, &QListView::clicked, this, &TipListView::slot_list_activated);
}

TipListView::~TipListView()
{
}


void TipListView::setTipSession(const QList<SessionInfo> sessions)
{
    //for each (auto session in sessions)
    for(int i=0;i<sessions.size();i++)
	{
        auto session=sessions[i];

		QStandardItem *item = new QStandardItem(session.session_id);
		TipViewItem* s_item = new TipViewItem(session, item);
		QSize size = item->sizeHint();
		item->setSizeHint(QSize(size.width(), s_item->size().height()));
		_item_module->appendRow(item);
		QModelIndex index = _item_module->indexFromItem(item);
		this->setIndexWidget(index, s_item);
	}
}

void TipListView::slot_list_activated(QModelIndex current)
{
	if (current.row() >= 0)
	{
		TipViewItem* item = (TipViewItem*)(this->indexWidget(current));
		if (item)
		{
			emit open_session(item->sId(),item->sName());
		}
		_item_module->removeRow(current.row());
	}
}

