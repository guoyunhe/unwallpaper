import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root
    anchors.fill: parent

    Column {
        id: info
        anchors.centerIn: parent
        width: 500
        height: childrenRect.height
        spacing: 20

        Item {
            width: parent.width
            height: 64

            Image {
                anchors.centerIn: parent
                width: 64
                height: 64
                source: "qrc:///icons/unwallpaper-128.png"
            }
        }

        Text {
            width: parent.width
            text: "Unwallpaper v0.1.0"
            font.pixelSize: 32
            font.family: "Roboto Thin"
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            width: parent.width
            text: qsTr("Download beautiful photos from Unsplash as wallpaper")
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            width: parent.width
            text: qsTr("Copyright")
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            width: parent.width
            text: qsTr("Guo Yunhe")
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            width: parent.width
            text: "GPLv3"
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            width: parent.width
            text: qsTr("Photo credit: photographers on Unsplash, CC0")
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
