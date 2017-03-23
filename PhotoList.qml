import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import Unwallpaper 1.0

ScrollView {
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
        }

        // "load more" button
        Item {
            width: parent.width
            height: 30

            Button {
                id: loadMoreButton
                anchors.centerIn: parent
                //: Button at the end of photo list
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
