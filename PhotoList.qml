import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import Unwallpaper 1.0

Item {
    property PhotoListModel model: PhotoListModel {}
    width: parent.width
    height: parent.height

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
                id: list
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
                    //visible: false

                    onClicked: {
                        model.nextPage()
                        visible = false
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        model.fetch();
    }

    Connections {
        target: model

        onDownloadProgress: {
            //
        }

        onPhotoParsed: {
            var component = Qt.createComponent("Photo.qml");
            var object = component.createObject(list, {model: photo});
        }

        onAllPhotosParsed: {
            loadMoreButton.visible = true;
        }
    }
}
