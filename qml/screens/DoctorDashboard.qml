import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: doctorDashboard
    width: parent.width
    height: parent.height
    color: "#ecf0f1"

    property int userId: 0
    property string doctorName: "Sarah Khan"
    property string specialization: "Cardiology"

    signal logout()

    // Main content
    Rectangle {
        width: 800
        height: 550
        anchors.centerIn: parent
        color: "white"
        radius: 10
        border.color: "#bdc3c7"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 15

            Text {
                text: "Welcome, Dr. " + doctorName
                font.pixelSize: 20
                font.bold: true
                color: "#2c3e50"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "Specialization: " + specialization
                font.pixelSize: 16
                font.bold: true
                color: "#3498db"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Rectangle {
                width: parent.width
                height: 2
                color: "#3498db"
                Layout.fillWidth: true
                Layout.topMargin: 5
                Layout.bottomMargin: 10
            }

            ColumnLayout {
                spacing: 10
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter

                Button {
                    text: "1. View Today's Appointments"
                    Layout.fillWidth: true
                    height: 45
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
                        stackView.push(viewTodaysAppointmentsScreen)
                    }
                }

                Button {
                    text: "2. Mark Appointment Complete"
                    Layout.fillWidth: true
                    height: 45
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
                        stackView.push(markCompleteScreen)
                    }
                }

                Button {
                    text: "3. Mark Appointment No-Show"
                    Layout.fillWidth: true
                    height: 45
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
                        stackView.push(markNoShowScreen)
                    }
                }

                Button {
                    text: "4. Write Prescription"
                    Layout.fillWidth: true
                    height: 45
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
                        stackView.push(writePrescriptionScreen)
                    }
                }

                Button {
                    text: "5. View Patient Medical History"
                    Layout.fillWidth: true
                    height: 45
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
                        stackView.push(viewPatientHistoryScreen)
                    }
                }

                Button {
                    text: "6. Logout"
                    Layout.fillWidth: true
                    height: 45
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
                    onClicked: logout()
                }
            }
        }
    }

    // StackView for navigation to sub-screens
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: null
        visible: false
    }

    // Placeholder components
    Component {
        id: viewTodaysAppointmentsScreen
        Rectangle {
            color: "white"
            Text { text: "Today's Appointments"; anchors.centerIn: parent }
        }
    }

    Component {
        id: markCompleteScreen
        Rectangle {
            color: "white"
            Text { text: "Mark Appointment Complete"; anchors.centerIn: parent }
        }
    }

    Component {
        id: markNoShowScreen
        Rectangle {
            color: "white"
            Text { text: "Mark Appointment No-Show"; anchors.centerIn: parent }
        }
    }

    Component {
        id: writePrescriptionScreen
        Rectangle {
            color: "white"
            Text { text: "Write Prescription"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewPatientHistoryScreen
        Rectangle {
            color: "white"
            Text { text: "View Patient Medical History"; anchors.centerIn: parent }
        }
    }
}