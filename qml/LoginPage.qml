import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Welcome to MediCore Hospital Management System"
            font.bold: true
            font.pixelSize: 18
            styleColor:  white
        }

        Button {
            text: "1. Patient"
            onClicked: stack.push("PatientPage.qml")
        }

        Button {
            text: "2. Doctor"
            onClicked: stack.push("DoctorPage.qml")
        }

        Button {
            text: "3. Admin"
            onClicked: stack.push("AdminPage.qml")
        }

        Button {
            text: "4. Exit"
            onClicked: Qt.quit()
        }
    }
}