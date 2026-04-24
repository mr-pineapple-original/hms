import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: loginScreen
    width: parent.width
    height: parent.height
    color: "#ecf0f1"

    signal loginSuccess(string role, int userId)
    signal loginFailed(string message)

    property int failedAttempts: 0
    property bool isLocked: false
    property string selectedRole: ""

    // Login Dialog
    Dialog {
        id: loginDialog
        title: "Login - " + selectedRole
        modal: true
        width: 500
        height: 400
        background: Rectangle {
            color: "white"
            radius: 10
            border.color: "#bdc3c7"
            border.width: 1
        }

        header: Rectangle {
            height: 50
            color: "#2c3e50"
            radius: 10
            border.width: 0

            Text {
                text: "Login - " + selectedRole
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 18
                font.bold: true
            }
        }
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        onAccepted: {
            var id = parseInt(idField.text)
            var password = passwordFieldDialog.text

            if (id > 0 && password.length > 0) {
                failedAttempts = 0
                loginSuccess(selectedRole.toLowerCase(), id)
                loginDialog.close()
            } else {
                failedAttempts++
                errorMessageDialog.text = "Invalid ID or password. Attempts: " + failedAttempts + "/3"
                errorMessageDialog.visible = true

                if (failedAttempts >= 3) {
                    isLocked = true
                    errorMessageDialog.text = "Account locked. Contact admin."
                    loginFailed("Account locked")
                    loginDialog.close()
                }
            }
        }

        onRejected: {
            idField.text = ""
            passwordFieldDialog.text = ""
            errorMessageDialog.visible = false
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15

            Text {
                text: "Enter " + selectedRole + " Credentials"
                font.pixelSize: 16
                font.bold: true
                color: "#2c3e50"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "ID:"
                font.pixelSize: 14
                color: "black"
            }

            TextField {
                id: idField
                placeholderText: "Enter your ID"
                color: "black"
                Layout.fillWidth: true
                validator: IntValidator {}
                background: Rectangle {
                    border.color: parent.activeFocus ? "#3498db" : "#bdc3c7"
                    border.width: 1
                    radius: 5
                }
            }

            Text {
                text: "Password:"
                font.pixelSize: 14
                color: "black"
            }

            TextField {
                id: passwordFieldDialog
                placeholderText: "Enter your password"
                echoMode: TextInput.Password
                Layout.fillWidth: true
                color: "black"
                background: Rectangle {
                    border.color: parent.activeFocus ? "#3498db" : "#bdc3c7"
                    border.width: 1
                    radius: 5
                }
            }

            Text {
                id: errorMessageDialog
                color: "#e74c3c"
                font.pixelSize: 12
                visible: false
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
            }

            RowLayout {
                spacing: 10
                Layout.fillWidth: true
                Layout.topMargin: 20

                Button {
                    text: "Cancel"
                    Layout.fillWidth: true
                    height: 40
                    background: Rectangle {
                        radius: 5
                        color: parent.down ? "#922b21" : (parent.hovered ? "#cb4335" : "#e74c3c")
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    onClicked: {
                        idField.text = ""
                        passwordFieldDialog.text = ""
                        errorMessageDialog.visible = false
                        loginDialog.close()
                    }
                }

                Button {
                    text: "Login"
                    Layout.fillWidth: true
                    height: 40
                    background: Rectangle {
                        radius: 5
                        color: parent.down ? "#2980b9" : (parent.hovered ? "#5dade2" : "#3498db")
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    onClicked: {
                        var id = parseInt(idField.text)
                        var password = passwordFieldDialog.text

                        if (id > 0 && password.length > 0) {
                            failedAttempts = 0
                            loginSuccess(selectedRole.toLowerCase(), id)
                            loginDialog.close()
                        } else {
                            failedAttempts++
                            errorMessageDialog.text = "Invalid ID or password. Attempts: " + failedAttempts + "/3"
                            errorMessageDialog.visible = true

                            if (failedAttempts >= 3) {
                                isLocked = true
                                errorMessageDialog.text = "Account locked. Contact admin."
                                loginFailed("Account locked")
                                loginDialog.close()
                            }
                        }
                    }
                }
            }
        }
    }

    // Main content
    Rectangle {
        width: 1000
        height: 800
        anchors.centerIn: parent
        color: "white"
        radius: 10
        border.color: "#bdc3c7"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 10

            Text {
                text: "Welcome to MediCore Hospital Management System"
                font.pixelSize: 20
                font.bold: true
                color: "#2c3e50"
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
            }

            Rectangle {
                width: parent.width
                height: 2
                color: "#3498db"
                Layout.fillWidth: true
            }


            ColumnLayout {
                spacing: 8
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter

                Text {
                    text: "Login as:"
                    font.pixelSize: 16
                    font.bold: true
                    color: "#2c3e50"
                    Layout.topMargin: 10
                }

                Button {
                    text: "1. Patient"
                    Layout.fillWidth: true
                    height: 50

                    background: Rectangle {
                            radius: 5
                            color: parent.down ? "#2980b9" : (parent.hovered ? "#5dade2" : "#3498db")
                        }

                    onClicked: {
                        if (!isLocked) {
                            selectedRole = "Patient"
                            idField.text = ""
                            passwordFieldDialog.text = ""
                            errorMessageDialog.visible = false
                            loginDialog.open()
                        }
                    }
                }

                Button {
                    text: "2. Doctor"
                    Layout.fillWidth: true
                    height: 50
                    background: Rectangle {
                            radius: 5
                            color: parent.down ? "#2980b9" : (parent.hovered ? "#5dade2" : "#3498db")
                        }
                    onClicked: {
                        if (!isLocked) {
                            selectedRole = "Doctor"
                            idField.text = ""
                            passwordFieldDialog.text = ""
                            errorMessageDialog.visible = false
                            loginDialog.open()
                        }
                    }
                }

                Button {
                    text: "3. Admin"
                    Layout.fillWidth: true
                    height: 50
                    background: Rectangle {
                            radius: 5
                            color: parent.down ? "#2980b9" : (parent.hovered ? "#5dade2" : "#3498db")
                        }
                    onClicked: {
                        if (!isLocked) {
                            selectedRole = "Admin"
                            idField.text = ""
                            passwordFieldDialog.text = ""
                            errorMessageDialog.visible = false
                            loginDialog.open()
                        }
                    }
                }

                Button {
                    text: "4. Exit"
                    background: Rectangle {
                            radius: 5
                            color: parent.down ? "#922b21" : (parent.hovered ? "#cb4335" : "#e74c3c")
                        }
                    Layout.fillWidth: true
                    height: 50
                    onClicked: Qt.quit()
                }
            }

            Text {
                text: isLocked ? "ACCOUNT LOCKED - Contact Administrator" : ""
                color: "red"
                font.pixelSize: 14
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                visible: isLocked
            }
        }
    }
}