import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components" as Components
import "../admin" as Admin

Rectangle {
    id: adminDashboard
    width: parent.width
    height: parent.height

    // Access theme from main window
    property var theme: mainWindow ? mainWindow.globalTheme : null

    property int userId: 0
    property string adminName: "Admin"

    signal logout()

    // Use theme colors
    color: theme ? theme.background : "#ecf0f1"

    // Main content
    Rectangle {
        width: 500
        height: 600
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
                text: "Admin Panel — MediCore"
                font.pixelSize: theme ? theme.fontSizeTitle : 20
                font.bold: true
                color: theme ? theme.text : "#2c3e50"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "Welcome, " + adminName
                font.pixelSize: theme ? theme.fontSizeLarge : 16
                color: theme ? theme.primary : "#3498db"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                visible: adminName !== "Admin"
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
                        text: "1. Add Doctor"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(addDoctorScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "2. Remove Doctor"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(removeDoctorScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "3. View All Patients"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewAllPatientsScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "4. View All Doctors"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewAllDoctorsScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "5. View All Appointments"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewAllAppointmentsScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "6. View Unpaid Bills"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewUnpaidBillsScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "7. Discharge Patient"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(dischargePatientScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "8. View Security Log"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewSecurityLogScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "9. Generate Daily Report"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(generateDailyReportScreen)
                            stackView.visible = true
                            adminDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "10. Logout"
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
                adminDashboard.visible = true
            }
        }
    }

    // Screen Components
    Component {
        id: addDoctorScreen
        Admin.AddDoctorScreen {
            onGoBack:  {
                stackView.pop()
            }
        }
    }

    Component {
        id: removeDoctorScreen
        Admin.RemoveDoctorScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewAllPatientsScreen
        Admin.ViewAllPatientsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewAllDoctorsScreen
        Admin.ViewAllDoctorsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewAllAppointmentsScreen
        Admin.ViewAllAppointmentsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewUnpaidBillsScreen
        Admin.ViewUnpaidBillsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: dischargePatientScreen
        Admin.DischargePatientScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewSecurityLogScreen
        Admin.ViewSecurityLogScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: generateDailyReportScreen
        Admin.GenerateDailyReportScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }
}