import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import Unwallpaper 1.0

MouseArea {
    property PhotoModel model: PhotoModel {}

    width: parent.width
    height: parent.width * 0.5625

    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        source: model.regularUrl
    }

    Item {
        id: actionBar
        visible: false
        anchors.fill: parent
        anchors.margins: 10
        width: parent.width - 40
        height: 50

        Button {
            id: downloadButton
            text: "Download"

            onClicked: {
                model.download();
            }
        }
    }

    Rectangle {
        id: ifnobar
        visible: false
        color: "#88FFFFFF"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 20

        Text {
            anchors.centerIn: parent
            text: "© " + model.userFullName + " / Unsplash"
        }
    }

    hoverEnabled: true

    onEntered: {
        ifnobar.visible = true;
        actionBar.visible = true;
    }

    onExited: {
        ifnobar.visible = false;
        actionBar.visible = false;
    }

    Connections {
        target: model

        onDownloadProgress: {

        }

        onWallpaperSaved: {
            console.log("Saved!");
        }
    }
}
