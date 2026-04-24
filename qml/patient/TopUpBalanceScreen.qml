import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components" as Components

Rectangle {
    id: screen
    width: parent.width
    height: parent.height

    property var theme: mainWindow ? mainWindow.globalTheme : null
    property real currentBalance: 0

    signal goBack()
    signal balanceUpdated(real newBalance)

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

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20
        width: 400

        Text {
            text: "Top Up Balance"
            font.pixelSize: theme ? theme.fontSizeTitle : 20
            font.bold: true
            color: theme ? theme.text : "#2c3e50"
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            text: "Current Balance: PKR " + currentBalance.toFixed(2)
            font.pixelSize: theme ? theme.fontSizeLarge : 16
            color: theme ? theme.text : "#2c3e50"
            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            id: amountField
            placeholderText: "Enter amount"
            Layout.fillWidth: true
            validator: DoubleValidator { bottom: 0; decimals: 2 }
        }

        Components.StyledButton {
            text: "Add Balance"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                var amount = parseFloat(amountField.text) || 0
                if (amount > 0) {
                    balanceUpdated(currentBalance + amount)
                    goBack()
                }
            }
        }
    }
}