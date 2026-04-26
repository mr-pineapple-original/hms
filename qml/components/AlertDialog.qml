import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: alertDialog
    modal: true
    anchors.centerIn: parent
    width: 400

    // Public properties
    property var theme: parent ? parent.theme : null
    property string dialogTitle: "Confirm Action"
    property string dialogMessage: "Are you sure?"
    property string confirmText: "Confirm"
    property string cancelText: "Cancel"
    property bool showCancelButton: true
    property string dialogType: "confirm" // "confirm", "warning", "error", "success", "info"
    property var onConfirm: function() {}
    property var onCancel: function() {}
    property var onClose: function() {}

    // Internal properties
    property color dialogColor: getDialogColor()

    function getDialogColor() {
        switch(dialogType) {
            case "warning": return theme ? theme.warning : "#f59e0b"
            case "error": return theme ? theme.danger : "#ef4444"
            case "success": return theme ? theme.success : "#10b981"
            case "info": return theme ? theme.info : "#3b82f6"
            default: return theme ? theme.primary : "#3b82f6"
        }
    }

    // Dialog styling
    background: Rectangle {
        color: theme ? theme.card : "#1e293b"
        radius: theme ? theme.radiusLarge : 12
        border.color: theme ? theme.border : "#334155"
        border.width: 1
    }

    header: Rectangle {
        height: 60
        color: dialogColor
        radius: (theme ? theme.radiusLarge : 12)

        RowLayout {
            anchors.fill: parent
            anchors.margins: 15

            // Icon based on dialog type
            Text {
                text: getIcon()
                font.pixelSize: 24
                color: "white"
                visible: dialogType !== "confirm"
            }

            Text {
                text: dialogTitle
                color: "white"
                font.bold: true
                font.pixelSize: 16
                Layout.fillWidth: true
            }

            Button {
                text: "✕"
                flat: true
                onClicked: {
                    alertDialog.close()
                    if (onClose) onClose()
                }

                background: Rectangle {
                    color: parent.pressed ? Qt.rgba(255,255,255,0.2) : "transparent"
                    radius: 20
                }

                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.pixelSize: 18
                }
            }
        }
    }

    function getIcon() {
        switch(dialogType) {
            case "warning": return "⚠️"
            case "error": return "❌"
            case "success": return "✓"
            case "info": return "ℹ️"
            default: return ""
        }
    }

    contentItem: ColumnLayout {
        spacing: 20

        Text {
            text: dialogMessage
            color: theme ? theme.text : "white"
            font.pixelSize: 14
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
        }
    }

    footer: RowLayout {
        Layout.fillWidth: true
        Layout.margins: 15
        spacing: 10

        Item { Layout.fillWidth: true }

        Button {
            text: cancelText
            visible: showCancelButton
            onClicked: {
                alertDialog.close()
                if (onCancel) onCancel()
            }

            background: Rectangle {
                color: parent.pressed ? Qt.rgba(100,100,100,0.2) : "transparent"
                radius: theme ? theme.radius : 6
                border.color: theme ? theme.border : "#334155"
                border.width: 1
            }

            contentItem: Text {
                text: parent.text
                color: theme ? theme.text : "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            text: confirmText
            onClicked: {
                alertDialog.close()
                if (onConfirm) onConfirm()
            }

            background: Rectangle {
                color: dialogColor
                radius: theme ? theme.radius : 6
            }

            contentItem: Text {
                text: parent.text
                color: "white"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}