import QtQuick 2.0

MouseArea {
    id: nav
    width: childrenRect.width
    height: childrenRect.height
    property bool active: false
    property string text: "Nav"

    Text {
        text: parent.text
        color: parent.active ? "#000000" : "#555555"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}
