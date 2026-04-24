import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: patientDashboard
    width: parent.width
    height: parent.height
    color: "#ecf0f1"

    property int userId: 0
    property string patientName: "Ahmed Ali"
    property real balance: 5000.00

    signal logout()

    // Main content
    Rectangle {
        width: 800
        height: 600
        anchors.centerIn: parent
        color: "white"
        radius: 10
        border.color: "#bdc3c7"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 15
            width: parent.width



            Text {
                text: "Welcome, " + patientName
                font.pixelSize: 20
                font.bold: true
                color: "#2c3e50"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "Balance: PKR " + balance.toFixed(2)
                font.pixelSize: 16
                font.bold: true
                color: "#27ae60"
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
                width: parent.width
                Layout.alignment: Qt.AlignHCenter

                Button {
                    text: "1. Book Appointment"
                    height: 45
                    Layout.fillWidth: true
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
                        stackView.push(bookAppointmentScreen)
                    }
                }

                Button {
                    text: "2. Cancel Appointment"
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
                        stackView.push(cancelAppointmentScreen)
                    }
                }

                Button {
                    text: "3. View My Appointments"
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
                        stackView.push(viewAppointmentsScreen)
                    }
                }

                Button {
                    text: "4. View My Medical Records"
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
                        stackView.push(viewMedicalRecordsScreen)
                    }
                }

                Button {
                    text: "5. View My Bills"
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
                        stackView.push(viewBillsScreen)
                    }
                }

                Button {
                    text: "6. Pay Bill"
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
                        stackView.push(payBillScreen)
                    }
                }

                Button {
                    text: "7. Top Up Balance"
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
                        stackView.push(topUpBalanceScreen)
                    }
                }

                Button {
                    text: "8. Logout"
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
        visible: false  // Hidden by default, push screens when needed
    }

    // Placeholder components (to be implemented later)
    Component {
        id: bookAppointmentScreen
        Rectangle {
            color: "white"
            Text { text: "Book Appointment Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: cancelAppointmentScreen
        Rectangle {
            color: "white"
            Text { text: "Cancel Appointment Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewAppointmentsScreen
        Rectangle {
            color: "white"
            Text { text: "View Appointments Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewMedicalRecordsScreen
        Rectangle {
            color: "white"
            Text { text: "View Medical Records Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: viewBillsScreen
        Rectangle {
            color: "white"
            Text { text: "View Bills Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: payBillScreen
        Rectangle {
            color: "white"
            Text { text: "Pay Bill Screen"; anchors.centerIn: parent }
        }
    }

    Component {
        id: topUpBalanceScreen
        Rectangle {
            color: "white"
            Text { text: "Top Up Balance Screen"; anchors.centerIn: parent }
        }
    }
}