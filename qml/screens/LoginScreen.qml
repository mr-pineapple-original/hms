import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components" as Components

Rectangle {
    id: loginScreen
    width: parent.width
    height: parent.height

    // Access theme from main window
    property var theme: mainWindow ? mainWindow.globalTheme : null
    color: theme ? theme.background : "#f5f5f5"

    signal loginSuccessToDashboard(string role, string userId)

    property bool isLocked: false
    property string selectedRole: ""

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainView
    }

    Components.LoginDialog {
        id: loginDialog

        onLoginSuccess: function(id, password) {
            loginScreen.loginSuccessToDashboard(loginDialog.role, id.toString())
        }

        onLoginFailed: function(msg) {
            isLocked = true
        }
    }

    Component {
        id: mainView

        Rectangle {
            anchors.fill: parent
            color: theme ? theme.background : "#f5f5f5"

            Rectangle {
                width: 450
                height: 420
                anchors.centerIn: parent

                radius: theme ? theme.radius : 8
                color: theme ? theme.card : "#ffffff"
                border.color: theme ? theme.border : "#e0e0e0"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 25
                    spacing: 15

                    Text {
                        text: "MediCore System"
                        font.pixelSize: theme ? theme.fontSizeTitle : 22
                        font.bold: true
                        color: theme ? theme.text : "#2c3e50"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 2
                        color: theme ? theme.primary : "#3498db"
                    }

                    Text {
                        text: "Login as:"
                        color: theme ? theme.text : "#2c3e50"
                        font.pixelSize: theme ? theme.fontSizeLarge : 16
                        font.bold: true
                    }

                    Components.StyledButton {
                        Layout.fillWidth: true
                        text: "Patient"
                        onClicked: {
                            selectedRole = "Patient"
                            loginDialog.role = selectedRole
                            loginDialog.open()
                        }
                    }

                    Components.StyledButton {
                        text: "Doctor"
                        Layout.fillWidth: true

                        onClicked: {
                            selectedRole = "Doctor"
                            loginDialog.role = selectedRole
                            loginDialog.open()
                        }
                    }

                    Components.StyledButton {
                        text: "Admin"
                        Layout.fillWidth: true
                        onClicked: {
                            selectedRole = "Admin"
                            loginDialog.role = selectedRole
                            loginDialog.open()
                        }
                    }

                    Components.StyledButton {
                        Layout.fillWidth: true
                        text: "Exit"
                        onClicked: Qt.quit()
                    }

                    Text {
                        text: isLocked ? "ACCOUNT LOCKED" : ""
                        color: theme ? theme.danger : "#e74c3c"
                        visible: isLocked
                        Layout.alignment: Qt.AlignHCenter
                        font.pixelSize: theme ? theme.fontSizeNormal : 14
                    }
                }
            }
        }
    }

    PatientDashboard {
        id: patientDash
        visible: false
    }

    DoctorDashboard {
        id: doctorDash
        visible: false
    }

    AdminDashboard {
        id: adminDash
        visible: false
    }
}