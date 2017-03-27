TEMPLATE = app

TARGET = unwallpaper

VERSION = 0.1.3
# Use VERSION macro in C++
DEFINES += VERSION=\\\"$$VERSION\\\"

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

TRANSLATIONS = translations/zh_CN.ts \
    translations/zh_TW.ts \
    translations/zh_HK.ts \
    translations/fi.ts \
    translations/fr.ts \
    translations/de.ts

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

# Translation compile with lrelease
lrelease.commands = lrelease $$PWD/unwallpaper.pro
QMAKE_EXTRA_TARGETS += lrelease
PRE_TARGETDEPS += lrelease

# Rules for deployment
# Install binary (default target)
unix: target.path = /usr/bin
unix: INSTALLS += target
# Install translation file
unix: trans.path = /usr/share/unwallpaper/translations
unix: trans.files = translations/*.qm
unix: trans.CONFIG += no_check_exist
unix: INSTALLS += trans
# Install desktop file
unix: desktop.path = /usr/share/applications
unix: desktop.files = linux/$${TARGET}.desktop
unix: INSTALLS += desktop
# Install appdata file
unix: appdata.path = /usr/share/metainfo
unix: appdata.files = linux/me.guoyunhe.$${TARGET}.appdata.xml
unix: INSTALLS += appdata
# Install icons
unix: icon16.path = /usr/share/icons/hicolor/16x16/apps
unix: icon16.extra = cp icons/$${TARGET}-16.png icons/$${TARGET}.png
unix: icon16.files = icons/$${TARGET}.png
unix: icon16.CONFIG += no_check_exist
unix: INSTALLS += icon16
unix: icon22.path = /usr/share/icons/hicolor/22x22/apps
unix: icon22.extra = cp icons/$${TARGET}-22.png icons/$${TARGET}.png
unix: icon22.files = icons/$${TARGET}.png
unix: icon22.CONFIG += no_check_exist
unix: INSTALLS += icon22
unix: icon32.path = /usr/share/icons/hicolor/32x32/apps
unix: icon32.extra = cp icons/$${TARGET}-32.png icons/$${TARGET}.png
unix: icon32.files = icons/$${TARGET}.png
unix: icon32.CONFIG += no_check_exist
unix: INSTALLS += icon32
unix: icon48.path = /usr/share/icons/hicolor/48x48/apps
unix: icon48.extra = cp icons/$${TARGET}-48.png icons/$${TARGET}.png
unix: icon48.files = icons/$${TARGET}.png
unix: icon48.CONFIG += no_check_exist
unix: INSTALLS += icon48
unix: icon64.path = /usr/share/icons/hicolor/64x64/apps
unix: icon64.extra = cp icons/$${TARGET}-64.png icons/$${TARGET}.png
unix: icon64.files = icons/$${TARGET}.png
unix: icon64.CONFIG += no_check_exist
unix: INSTALLS += icon64
unix: icon128.path = /usr/share/icons/hicolor/128x128/apps
unix: icon128.extra = cp icons/$${TARGET}-128.png icons/$${TARGET}.png
unix: icon128.files = icons/$${TARGET}.png
unix: icon128.CONFIG += no_check_exist
unix: INSTALLS += icon128
unix: icon256.path = /usr/share/icons/hicolor/256x256/apps
unix: icon256.extra = cp icons/$${TARGET}-256.png icons/$${TARGET}.png
unix: icon256.files = icons/$${TARGET}.png
unix: icon256.CONFIG += no_check_exist
unix: INSTALLS += icon256
unix: icon512.path = /usr/share/icons/hicolor/512x512/apps
unix: icon512.extra = cp icons/$${TARGET}-512.png icons/$${TARGET}.png
unix: icon512.files = icons/$${TARGET}.png
unix: icon512.CONFIG += no_check_exist
unix: INSTALLS += icon512

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
    LICENSE \
    win/unwallpaper.nsi \
    linux/unwallpaper.desktop \
    linux/me.guoyunhe.unwallpaper.appdata.xml

# Windows application icon embedded in *.exe
RC_ICONS = icons/unwallpaper.ico
