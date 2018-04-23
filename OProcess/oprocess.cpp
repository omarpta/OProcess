#include "oprocess.h"

OProcess::OProcess(QObject *parent) : QObject(parent)
{
    setObjectName(QStringLiteral("From QAxFactory"));
    process = Q_NULLPTR;
}

bool OProcess::StartProcess(QString cmd)
{
    try {
        //log("** Starting");
        if (process != Q_NULLPTR) {
            //log("** Killed");
            process->kill();
        }
        process = new QProcess();
        process->setProcessChannelMode(QProcess::MergedChannels);
        process->start(cmd,QIODevice::ReadWrite);
        //log("** Done");
        return true;
    } catch (...) {
        return false;
    }
}

bool OProcess::WaitStart(int msecs)
{
    return process->waitForStarted(msecs);
}

bool OProcess::WaitForReadyRead(int msecs)
{
    return process->waitForReadyRead(msecs);
}

QString OProcess::ReadAll()
{
    QString data = QString(process->readAll().data());
    return data;
}

qint64 OProcess::Write(QString msg)
{
    return process->write(msg.toLatin1().data());
}

void OProcess::Kill()
{
    process->kill();
}

bool OProcess::WaitFinish(int msecs)
{
    return process->waitForFinished(msecs);
}

bool OProcess::IsOpen()
{
    if (process != Q_NULLPTR) {
        return process->isOpen();
    } else {
        return false;
    }

}

void OProcess::log(QString msg)
{
    QString filename="c:\\temp\\Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << msg << endl;
    }
}

void OProcess::quit()
{
    QTimer::singleShot(0 /*ms*/, qApp, &QCoreApplication::quit);
}
