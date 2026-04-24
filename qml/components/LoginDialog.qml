import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root
    modal: true
    dim: true
    closePolicy: Popup.NoAutoClose

    width: 420
    height: 320

    anchors.centerIn: parent

    property var theme: mainWindow ? mainWindow.globalTheme : null
    property string role: ""
    property int failedAttempts: 0
    property bool locked: false

    signal loginSuccess(string role, int userId, string password)
    signal loginFailed(string message)

    background: Rectangle {
        radius: theme ? theme.radiusLarge : 14
        color: "#1e293b"
        border.color: "#334155"
        border.width: 1
    }

    header: Rectangle {
        height: 55
        color: "#0f172a"
        radius: theme ? theme.radiusLarge : 14

        Text {
            text: "Login - " + root.role
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 16
            font.bold: true
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        TextField {
            id: idField
            placeholderText: "User ID"
            color: theme ? theme.text : "#2c3e50"
            Layout.fillWidth: true

            background: Rectangle {
                radius: theme ? theme.radius : 8
                color: theme ? theme.card : "#ffffff"
                border.color: theme ? theme.border : "#e0e0e0"
                border.width: 1
            }
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            color: theme ? theme.text : "#2c3e50"
            Layout.fillWidth: true

            background: Rectangle {
                radius: theme ? theme.radius : 8
                color: theme ? theme.card : "#ffffff"
                border.color: theme ? theme.border : "#e0e0e0"
                border.width: 1
            }
        }

        Text {
            id: errorText
            color: theme ? theme.danger : "#ef4444"
            visible: false
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        RowLayout {
            spacing: 10
            Layout.topMargin: 10

            Button {
                text: "Cancel"
                Layout.fillWidth: true

                background: Rectangle {
                    radius: theme ? theme.radius : 8
                    color: parent.pressed ? "#475569" : "#334155"
                }

                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }

                onClicked: root.close()
            }

            Button {
                text: "Login"
                Layout.fillWidth: true

                background: Rectangle {
                    radius: theme ? theme.radius : 8
                    color: parent.pressed ? (theme ? theme.primaryPressed : "#1c638c") :
                           parent.hovered ? (theme ? theme.primaryHover : "#2980b9") :
                           (theme ? theme.primary : "#3498db")
                }

                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }

                onClicked: {
                    if (idField.text.length > 0 && passwordField.text.length > 0) {
                        if (root.locked) {
                            root.loginFailed("Account is locked")
                            return
                        }

                        // Emit with role, userId, and password
                        root.loginSuccess(root.role, parseInt(idField.text), passwordField.text)
                        root.close()
                    } else {
                        root.failedAttempts++
                        errorText.text = "Invalid credentials (" + root.failedAttempts + "/3)"
                        errorText.visible = true

                        if (root.failedAttempts >= 3) {
                            root.locked = true
                            root.loginFailed("Account locked due to too many failed attempts")
                            root.close()
                        }
                    }
                }
            }
        }
    }
}