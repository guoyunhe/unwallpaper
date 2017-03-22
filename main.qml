import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import Unwallpaper 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("unwallpaper")

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
                spacing: 20
                width: parent.parent.width
                height: childrenRect.height
            }

            // "load more" button
            Item {
                width: parent.width
                height: 30

                MouseArea {
                    anchors.centerIn: parent
                    implicitWidth: 100
                    implicitHeight: 30

                    Rectangle {
                        anchors.centerIn: parent
                        color: "black"
                        implicitWidth: 100
                        implicitHeight: 30

                        Text {
                            anchors.centerIn: parent
                            text: qsTr("load more")
                            color: "white"
                        }
                    }

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
                }
            }

            Component.onCompleted: {
                latestPhotosLoader.getPhotos()
            }
        }
    }


}
