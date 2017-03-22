#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "unsplash.h"
#include "photo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register C++ class in QML
    qmlRegisterType<Unsplash>("Unwallpaper", 1, 0, "Unsplash");
    qmlRegisterType<Photo>("Unwallpaper", 1, 0, "PhotoModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
