import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: adminDashboard
    width: parent.width
    height: parent.height
    color: "#ecf0f1"

    property int userId: 0
    property string adminName: "Admin"

    signal logout()

    // Main content
    Rectangle {
        width: 800
        height: 650
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
                text: "Admin Panel — MediCore"
                font.pixelSize: 20
                font.bold: true
                color: "#2c3e50"
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
                    text: "1. Add Doctor"
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
                        stackView.push(addDoctorScreen)
                    }
                }

                Button {
                    text: "2. Remove Doctor"
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
                        stackView.push(removeDoctorScreen)
                    }
                }

                Button {
                    text: "3. View All Patients"
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
                        stackView.push(viewAllPatientsScreen)
                    }
                }

                Button {
                    text: "4. View All Doctors"
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
                        stackView.push(viewAllDoctorsScreen)
                    }
                }

                Button {
                    text: "5. View All Appointments"
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
                        stackView.push(viewAllAppointmentsScreen)
                    }
                }

                Button {
                    text: "6. View Unpaid Bills"
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
                        stackView.push(viewUnpaidBillsScreen)
                    }
                }

                Button {
                    text: "7. Discharge Patient"
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
                        stackView.push(dischargePatientScreen)
                    }
                }

                Button {
                    text: "8. View Security Log"
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
                        stackView.push(viewSecurityLogScreen)
                    }
                }

                Button {
                    text: "9. Generate Daily Report"
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
                        stackView.push(generateDailyReportScreen)
                    }
                }

                Button {
                    text: "10. Logout"
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
        id: addDoctorScreen
        Rectangle {
            color: "white"
            Text { text: "Add Doctor Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: removeDoctorScreen
        Rectangle {
            color: "white"
            Text { text: "Remove Doctor Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewAllPatientsScreen
        Rectangle {
            color: "white"
            Text { text: "View All Patients Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewAllDoctorsScreen
        Rectangle {
            color: "white"
            Text { text: "View All Doctors Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewAllAppointmentsScreen
        Rectangle {
            color: "white"
            Text { text: "View All Appointments Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewUnpaidBillsScreen
        Rectangle {
            color: "white"
            Text { text: "View Unpaid Bills Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: dischargePatientScreen
        Rectangle {
            color: "white"
            Text { text: "Discharge Patient Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewSecurityLogScreen
        Rectangle {
            color: "white"
            Text { text: "View Security Log Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: generateDailyReportScreen
        Rectangle {
            color: "white"
            Text { text: "Generate Daily Report Screen"; anchors.centerIn: parent }
        }
    }
}