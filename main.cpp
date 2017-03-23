#include <Magick++.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "unsplash.h"
#include "photo.h"

using namespace Magick;

int main(int argc, char *argv[])
{
    InitializeMagick(*argv);

    QGuiApplication app(argc, argv);

    // Load translation
    QTranslator translator;
    // Look up app folder: translations/main_zh_CN.qm
    if (translator.load(QLocale(), QLatin1String("main"), QLatin1String("_"), QLatin1String("translations"), QLatin1String(".qm")))
        app.installTranslator(&translator);
    // Look up user local folder: ~/.local/share/unwallpaper/translations/main_zh_CN.qm
    else if (translator.load(QLocale(), QLatin1String("main"), QLatin1String("_"), QDir::homePath() + QLatin1String("/.local/share/unwallpaper/translations"), QLatin1String(".qm")))
        app.installTranslator(&translator);
    // Look up system local folder: ~/usr/local/share/unwallpaper/translations/main_zh_CN.qm
    else if (translator.load(QLocale(), QLatin1String("main"), QLatin1String("_"), QLatin1String("/usr/local/share/unwallpaper/translations"), QLatin1String(".qm")))
        app.installTranslator(&translator);
    // Look up system folder: ~/usr/share/unwallpaper/translations/main_zh_CN.qm
    else if (translator.load(QLocale(), QLatin1String("main"), QLatin1String("_"), QLatin1String("/usr/share/unwallpaper/translations"), QLatin1String(".qm")))
        app.installTranslator(&translator);

    // Use Flat UI style
    qputenv("QT_QUICK_CONTROLS_1_STYLE", "Flat");

    // Register C++ class in QML
    qmlRegisterType<Unsplash>("Unwallpaper", 1, 0, "Unsplash");
    qmlRegisterType<Photo>("Unwallpaper", 1, 0, "PhotoModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
