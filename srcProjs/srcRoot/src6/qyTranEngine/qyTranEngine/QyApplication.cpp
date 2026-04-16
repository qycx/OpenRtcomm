#include "QyApplication.h"
#include <QMenu>
#include <QLineEdit>
#include <QTextEdit>

QyApplication::QyApplication(int& argc, char* argv[])
    : QApplication(argc, argv)
{
}

QyApplication::~QyApplication()
{
}

bool QyApplication::notify(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::ContextMenu)
    {
        QString str = obj->metaObject()->className();
        if (str == "QLineEdit")
        {
			QLineEdit* edit = (QLineEdit*)obj;
			QMenu* menu = edit->createStandardContextMenu();
			QList<QAction*> actions = menu->actions();
			QList<QAction*> list;
			for (size_t i = 0; i < actions.size(); i++)
			{
				if (actions[i]->text() != u8"复制" && actions[i]->text() != u8"粘贴")
				{
					list.append(actions[i]);
				}
			}
			for (size_t i = 0; i < list.size(); i++)
			{
				menu->removeAction(list[i]);
			}
			menu->exec(QCursor::pos());
			delete menu;
			return true;
        }
    }
    return QApplication::notify(obj, event);
}
