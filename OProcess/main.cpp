#include <QApplication>
#include <QAxFactory>
#include "oprocess.h"

QAXFACTORY_BEGIN("{bca4e011-c1d0-4cc8-841e-1e393eb4e105}", "{32ab5069-067d-42f6-ab19-87ce23957851}")
   QAXCLASS(OProcess)
QAXFACTORY_END()

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qInstallMessageHandler(myMessageOutput);
    app.setQuitOnLastWindowClosed(false);

    // started by COM - don't do anything
    if (QAxFactory::isServer())
        return app.exec();

    // started by user
    OProcess appobject;
    appobject.setObjectName(QStringLiteral("From Application"));

    QAxFactory::startServer();
    QAxFactory::registerActiveObject(&appobject);

    //appobject.window()->setMinimumSize(300, 100);
    //appobject.setVisible(true);

    QObject::connect(&app, &QGuiApplication::lastWindowClosed, &appobject, &OProcess::quit);

    return app.exec();
}
//! [7]
