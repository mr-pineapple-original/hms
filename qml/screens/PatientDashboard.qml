import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components" as Components
import "../patient" as Patient

Rectangle {
    id: patientDashboard
    width: parent.width
    height: parent.height

    // Access theme from main window
    property var theme: mainWindow ? mainWindow.globalTheme : null

    property int userId: 0
    property string patientName: "Ahmed Ali"
    property real balance: 5000.00

    signal logout()

    // Use theme colors
    color: theme ? theme.background : "#ecf0f1"

    // Main content
    Rectangle {
        width: 600
        height: 650
        anchors.centerIn: parent
        color: theme ? theme.card : "white"
        radius: theme ? theme.radiusLarge : 10
        border.color: theme ? theme.border : "#bdc3c7"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 15

            Text {
                text: "Welcome, " + patientName
                font.pixelSize: theme ? theme.fontSizeTitle : 20
                font.bold: true
                color: theme ? theme.text : "#2c3e50"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "Balance: PKR " + balance.toFixed(2)
                font.pixelSize: theme ? theme.fontSizeLarge : 16
                font.bold: true
                color: theme ? theme.success : "#27ae60"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Rectangle {
                width: parent.width
                height: 2
                color: theme ? theme.primary : "#3498db"
                Layout.fillWidth: true
                Layout.topMargin: 5
                Layout.bottomMargin: 10
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true

                ColumnLayout {
                    spacing: 10
                    width: parent.width - 20

                    Components.StyledButton {
                        text: "1. Book Appointment"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(bookAppointmentScreen)
                            stackView.visible = true
                            patientDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "2. Cancel Appointment"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(cancelAppointmentScreen)
                            stackView.visible = true
                            patientDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "3. View My Appointments"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewAppointmentsScreen)
                            stackView.visible = true
                            patientDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "4. View My Medical Records"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewMedicalRecordsScreen)
                            stackView.visible = true
                            patientDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "5. View My Bills"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewBillsScreen)
                            stackView.visible = true
                            patientDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "6. Pay Bill"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(payBillScreen)
                            stackView.visible = true
                            patientDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "7. Top Up Balance"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(topUpBalanceScreen)
                            stackView.visible = true
                            patientDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "8. Logout"
                        Layout.fillWidth: true
                        normalColor: theme ? theme.danger : "#e74c3c"
                        hoverColor: theme ? theme.dangerHover : "#c0392b"
                        pressedColor: theme ? theme.dangerPressed : "#a93226"
                        onClicked: logout()
                    }
                }
            }
        }
    }

    // StackView for navigation to sub-screens
    StackView {
        id: stackView
        anchors.fill: parent

        // Handle when we pop back to this view
        onCurrentItemChanged: {
            if (stackView.depth === 0) {
                stackView.visible = false
                patientDashboard.visible = true
            }
        }
    }

    // Screen Components - These will be separate files in the patient/ folder
    Component {
        id: bookAppointmentScreen
        Patient.BookAppointmentScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: cancelAppointmentScreen
        Patient.CancelAppointmentScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewAppointmentsScreen
        Patient.ViewAppointmentsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewMedicalRecordsScreen
        Patient.ViewMedicalRecordsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewBillsScreen
        Patient.ViewBillsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: payBillScreen
        Patient.PayBillScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: topUpBalanceScreen
        Patient.TopUpBalanceScreen {
            onGoBack: {
                stackView.pop()
            }
            onBalanceUpdated: {
                balance = newBalance
            }
        }
    }
}