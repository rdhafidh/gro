#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <utilqml.h>
#include <cameraimageproviderloop.h>
#include <qmlappengine.h>
#include <QQuickWindow> 
#include <imageitem.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName ("grpc_camera_client1"); 
    qputenv ("QML_DISABLE_DISK_CACHE","true");
    qputenv ("QML_FORCE_DISK_CACHE","false");
    qmlRegisterType<ImageItem>("ImageItemQML",1,0,"ImageItem");
    UtilQML util;
    CameraImageProviderLoop prov;
    QMLAppEngine engine;
    engine.rootContext ()->setContextProperty ("utilqml",&util);
    engine.rootContext ()->setContextProperty ("camera",&prov);
    engine.rootContext ()->setContextProperty ("qmlengine",&engine); 
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
