#ifndef OPROCESS_H
#define OPROCESS_H

#include <QApplication>
#include <QAxFactory>
#include <QTabWidget>
#include <QScopedPointer>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QProcess>
class OProcess : public QObject
{
    Q_OBJECT

       Q_CLASSINFO("ClassID", "{8e217673-70e6-4ef1-9aaf-cde30bb10277}")
       Q_CLASSINFO("InterfaceID", "{09e8cc89-e08d-45af-b8d1-a30c08f445b9}")
       Q_CLASSINFO("RegisterObject", "yes")

        Q_PROPERTY(QString id READ id)
       //Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
public:
    explicit OProcess(QObject *parent = nullptr);
    QString id() const { return objectName(); }




signals:

public slots:
    void quit();
    bool StartProcess(QString cmd);
    bool WaitStart(int msecs = 30000);
    bool WaitForReadyRead(int msecs = 30000);
    QString ReadAll();
    qint64 Write(QString msg);
    void Kill();
    bool WaitFinish(int msecs = 30000);
    bool IsOpen();


private:
    void log(QString msg);
    QProcess *process;
};

#endif // OPROCESS_H
