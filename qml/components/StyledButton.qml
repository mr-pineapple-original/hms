import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: control
    height: 45

    // Access theme from parent
    property var theme: mainWindow ? mainWindow.globalTheme : null

    property color normalColor: theme ? theme.primary : "#3498db"
    property color hoverColor: theme ? theme.primaryHover : "#2980b9"
    property color pressedColor: theme ? theme.primaryPressed : "#1c638c"

    // Minimum width based on content
    implicitWidth: Math.max(100, contentItem.implicitWidth + 32)

    contentItem: Text {
        text: control.text
        color: "white"
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: theme ? theme.fontSizeNormal : 14
    }

    background: Rectangle {
        radius: theme ? theme.radius : 8
        color: control.pressed ? control.pressedColor :
               control.hovered ? control.hoverColor : control.normalColor
    }
}