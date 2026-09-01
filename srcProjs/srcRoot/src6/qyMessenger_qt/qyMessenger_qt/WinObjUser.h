#pragma once

#include <QObject>   
#include <QVariant>

struct WinObjUser {
	QString idinfo;
	QString name;
	QString bm; 
	QString dw;
	int dataType;//1 群组，2 临时组，3 好友
};
Q_DECLARE_METATYPE(WinObjUser)

 