import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import Unwallpaper 1.0

Window {
    visible: true
    width: 960
    height: 640
    title: qsTr("Unwallpaper")

    Item {
        id: navbar
        width: parent.width
        height: 40
        clip: true
        z: 1

        FastBlur {
            width: parent.width
            height: latestPhotos.height
            source: latestPhotos
            radius: 32
        }

        Rectangle {
            width: parent.width
            height: parent.height
            color: "#AAFFFFFF"
        }

        Row {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 20

            Nav {
                text: qsTr("Latest")
                active: true
            }

            Nav {
                text: qsTr("Collections")
            }

            Nav {
                text: qsTr("Downloaded")
            }
        }
    }

    ScrollView {
        id: latestPhotos
        width: parent.width
        height: parent.height
        flickableItem.interactive: true // Allow touch swipe and mouse drag gestures
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        style: ScrollViewStyle {
            transientScrollBars: true
            handle: Item {
                implicitWidth: 3
                implicitHeight: 20
                Rectangle {
                    color: "black"
                    anchors.fill: parent
                }
            }
            scrollBarBackground: Item {
                implicitWidth: 3
                implicitHeight: 20
            }
        }

        Column {
            spacing: 20
            width: parent.parent.width
            height: childrenRect.height

            Column {
                property int page: 1

                id: latestPhotosList
                spacing: 40
                width: parent.parent.width
                height: childrenRect.height

                Item {
                    width: parent.width
                    height: 20
                }
            }

            // "load more" button
            Item {
                width: parent.width
                height: 30

                Button {
                    id: loadMoreButton
                    anchors.centerIn: parent
                    text: qsTr("Load more")
                    visible: false

                    onClicked: {
                        latestPhotosList.page++;
                        latestPhotosLoader.getPhotos(latestPhotosList.page)
                    }
                }
            }

            Unsplash {
                id: latestPhotosLoader

                onPhotoParsed: {
                    var component = Qt.createComponent("Photo.qml");
                    var object = component.createObject(latestPhotosList, {model: photo});
                    loadMoreButton.visible = true;
                }
            }

            Component.onCompleted: {
                latestPhotosLoader.getPhotos()
            }
        }
    }

}
