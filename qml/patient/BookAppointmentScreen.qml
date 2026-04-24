import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components" as Components

Rectangle {
    id: screen
    width: parent.width
    height: parent.height

    property var theme: mainWindow ? mainWindow.globalTheme : null
    signal goBack()

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
        width: 500

        Text {
            text: "Book Appointment"
            font.pixelSize: theme ? theme.fontSizeTitle : 20
            font.bold: true
            color: theme ? theme.text : "#2c3e50"
            Layout.alignment: Qt.AlignHCenter
        }

        // TODO: Add appointment booking form here
        Text {
            text: "Coming Soon..."
            color: theme ? theme.textSecondary : "#7f8c8d"
            Layout.alignment: Qt.AlignHCenter
        }
    }
}