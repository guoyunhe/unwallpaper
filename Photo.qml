import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
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

        Rectangle {
            id: progressBar
            height: parent.height
            width: 0
            color: "#5544CC88"

            Behavior on width {
                SmoothedAnimation { easing.type: Easing.InOutQuad }
            }

            Timer {
                id: progressBarResetTimer
                interval: 1000
                onTriggered: {
                    progressBar.visible = false
                    progressBar.width = 0
                }
            }
        }
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
            text: model.local ? qsTr("✓ Saved") : qsTr("Download")
            enabled: !model.local

            onClicked: {
                model.download();
                downloadButton.enabled = false
            }
        }
    }

    Connections {
        target: model

        onDownloadProgress: {
            progressBar.visible = true
            progressBar.width = image.width * bytesRead / totalBytes / 2
        }

        onSaveProgress: {
            progressBar.width = image.width * (filesSaved / totalFiles / 2 + 0.5)
        }

        onSaved: {
            progressBar.width = image.width
            progressBarResetTimer.start()
        }
    }
}
