import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components" as Components
import "../doctor" as Doctor

Rectangle {
    id: doctorDashboard
    width: parent.width
    height: parent.height

    // Access theme from main window
    property var theme: mainWindow ? mainWindow.globalTheme : null

    property int userId: 0
    property string doctorName: "Sarah Khan"
    property string specialization: "Cardiology"

    signal logout()

    // Use theme colors
    color: theme ? theme.background : "#ecf0f1"

    // Main content
    Rectangle {
        width: 600
        height: 550
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
                text: "Welcome, Dr. " + doctorName
                font.pixelSize: theme ? theme.fontSizeTitle : 20
                font.bold: true
                color: theme ? theme.text : "#2c3e50"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "Specialization: " + specialization
                font.pixelSize: theme ? theme.fontSizeLarge : 16
                font.bold: true
                color: theme ? theme.primary : "#3498db"
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
                        text: "1. View Today's Appointments"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewTodaysAppointmentsScreen)
                            stackView.visible = true
                            doctorDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "2. Mark Appointment Complete"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(markCompleteScreen)
                            stackView.visible = true
                            doctorDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "3. Mark Appointment No-Show"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(markNoShowScreen)
                            stackView.visible = true
                            doctorDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "4. Write Prescription"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(writePrescriptionScreen)
                            stackView.visible = true
                            doctorDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "5. View Patient Medical History"
                        Layout.fillWidth: true
                        onClicked: {
                            stackView.push(viewPatientHistoryScreen)
                            stackView.visible = true
                            doctorDashboard.visible = false
                        }
                    }

                    Components.StyledButton {
                        text: "6. Logout"
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
                doctorDashboard.visible = true
            }
        }
    }

    // Screen Components - These will be separate files in the doctor/ folder
    Component {
        id: viewTodaysAppointmentsScreen
        Doctor.ViewTodaysAppointmentsScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: markCompleteScreen
        Doctor.MarkAppointmentCompleteScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: markNoShowScreen
        Doctor.MarkAppointmentNoShowScreen{
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: writePrescriptionScreen
        Doctor.WritePrescriptionScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }

    Component {
        id: viewPatientHistoryScreen
        Doctor.ViewPatientMedicalHistoryScreen {
            onGoBack: {
                stackView.pop()
            }
        }
    }
}