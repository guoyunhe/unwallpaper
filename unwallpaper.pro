TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    unsplash.cpp \
    photo.cpp \
    photolist.cpp \
    photosavethread.cpp \
    filesystem.cpp \
    localphotolist.cpp

RESOURCES += qml.qrc \
    icon.qrc

TRANSLATIONS = translations/main_zh_CN.ts

lupdate_only{
    SOURCES += *.qml
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    unsplash.h \
    photo.h \
    photolist.h \
    photosavethread.h \
    filesystem.h \
    localphotolist.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += Magick++

DISTFILES += \
    README.md \
    win/unwallpaper.nsi \
    linux/unwallpaper.desktop \
    linux/me.guoyunhe.unwallpaper.appdata.xml

# Windows application icon embedded in *.exe
RC_ICONS = icons/unwallpaper.ico
