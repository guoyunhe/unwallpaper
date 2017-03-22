import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import Unwallpaper 1.0

MouseArea {
    property PhotoModel model: PhotoModel {}

    width: parent.width
    height: parent.width * 0.5625 + 40

    Image {
        id: image
        width: parent.width
        height: parent.height - 40
        fillMode: Image.PreserveAspectCrop
        source: model.regularUrl
    }

    Row {
        id: footer
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        height: 30
        spacing: 20

        Text {
            width: footer.width - downloadButton.width - footer.spacing
            text: "© " + model.userFullName + " / Unsplash"
            verticalAlignment: Text.AlignVCenter
        }

        Button {
            id: downloadButton
            text: qsTr("Download")

            onClicked: {
                model.download();
            }
        }
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
