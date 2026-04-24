import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components" as Components

Rectangle {
    id: screen
    width: parent.width
    height: parent.height

    property var theme: mainWindow ? mainWindow.globalTheme : null
    signal goBack()  // Signal to go back to dashboard

    color: theme ? theme.background : "#ecf0f1"

    // Back button
    Button {
        text: "← Back to Dashboard"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 20
        onClicked: goBack()

        background: Rectangle {
            radius: theme ? theme.radius : 5
            color: theme ? theme.primary : "#3498db"
        }

        contentItem: Text {
            text: parent.text
            color: "white"
        }
    }

    // Your screen content here
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20
        width: 400

        Text {
            text: "Add Doctor"
            font.pixelSize: theme ? theme.fontSizeTitle : 22
            font.bold: true
            color: theme ? theme.text : "#2c3e50"
            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            placeholderText: "Doctor Name"
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Specialization"
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Phone Number"
            Layout.fillWidth: true
        }

        TextField {
            placeholderText: "Email"
            Layout.fillWidth: true
        }

        Components.StyledButton {
            text: "Add Doctor"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                // TODO: Add doctor logic
                goBack()  // Go back after adding
            }
        }
    }
}