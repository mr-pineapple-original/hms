import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: root

    property var theme
    property string label: ""
    property bool password: false
    property string errorText: ""
    property bool valid: true

    echoMode: password ? TextInput.Password : TextInput.Normal
    color: theme ? theme.text : "#2c3e50"
    selectByMouse: true


    // ---- BACKGROUND ----
    background: Rectangle {
        radius: theme ? theme.radius : 8
        color: theme ? theme.card : "#ffffff"

        border.width: 1
        border.color: {
            if (!root.valid && root.text.length > 0)
                return theme ? theme.danger : "#ef4444"

            if (root.activeFocus)
                return theme ? theme.primary : "#3498db"

            return theme ? theme.border : "#e0e0e0"
        }
    }

    Column {
        id: helper
        anchors.top: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 2

        Text {
            text: root.errorText
            visible: root.errorText.length > 0
            color: root.valid
                   ? (theme ? theme.success : "#22c55e")
                   : (theme ? theme.danger : "#ef4444")
            font.pixelSize: 11
            wrapMode: Text.WordWrap
        }
    }
}