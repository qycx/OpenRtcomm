#pragma once
#include <QApplication>

class QyApplication :  public QApplication
{
    Q_OBJECT

public:
    QyApplication(int& argc, char* argv[]);
    ~QyApplication();
private:
    virtual bool notify(QObject* obj, QEvent* event);
};
