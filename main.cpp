#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "filesystem.h"
#include "unsplash.h"
#include "photo.h"
#include "photolist.h"
#include "localphotolist.h"

#ifdef Q_OS_LINUX
#include <Magick++.h>
using namespace Magick;
#endif // Q_OS_LINUX

int main(int argc, char *argv[])
{
#ifdef Q_OS_LINUX
    InitializeMagick(*argv);
#endif // Q_OS_LINUX

    QGuiApplication app(argc, argv);

    app.setApplicationName(QString("unwallpaper"));
    app.setApplicationDisplayName(QString("Unwallpaper"));
    app.setApplicationVersion(QString("0.1.0"));

    FileSystem::init();

    // Load translation
    QTranslator translator;
    foreach (QString path , FileSystem::getTranslationPaths()) {
        if (translator.load(QLocale(), QLatin1String("main"), QLatin1String("_"), path, QLatin1String(".qm"))) {
            app.installTranslator(&translator);
            break;
        }
    }

    // Use Flat UI style
    qputenv("QT_QUICK_CONTROLS_1_STYLE", "Flat");

    // Register C++ class in QML
    qmlRegisterType<Unsplash>("Unwallpaper", 1, 0, "Unsplash");
    qmlRegisterType<Photo>("Unwallpaper", 1, 0, "PhotoModel");
    qmlRegisterType<PhotoList>("Unwallpaper", 1, 0, "PhotoListModel");
    qmlRegisterType<LocalPhotoList>("Unwallpaper", 1, 0, "LocalPhotoListModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
