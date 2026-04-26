import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components"

Rectangle {
    id: screen
    width: parent.width
    height: parent.height

    property var theme: mainWindow ? mainWindow.globalTheme : null
    property bool isLoading: false
    property string statusMessage: ""
    property bool statusSuccess: false

    // 🔹 model comes from C++
    property var doctorsModel: mainWindow ? mainWindow.doctorsModel : null

    signal goBack()
    signal removeDoctorRequested(int doctorId)

    color: theme ? theme.background : "#0f172a"

    ColumnLayout {
        anchors.fill: parent

        // HEADER
        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 20

            StyledButton {
                text: "← Back"
                theme: theme
                onClicked: goBack()
            }

            Text {
                text: "Remove Doctor"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                color: theme.text
                font.pixelSize: theme.fontSizeLarge
                font.bold: true
            }

            Item { width: 80 }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 20

            ColumnLayout {
                width: ScrollView.view.width
                spacing: 20

                Rectangle {
                    Layout.fillWidth: true
                    Layout.maximumWidth: 1000
                    Layout.alignment: Qt.AlignHCenter

                    radius: theme.radiusLarge
                    color: theme.card
                    border.color: theme.border

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.margins: 20
                        spacing: 15

                        // HEADER ROW
                        Rectangle {
                            Layout.fillWidth: true
                            height: 45
                            radius: 6
                            color: theme.primary

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 10

                                Text { text: "ID"; Layout.preferredWidth: 60; color: "white"; font.bold: true }
                                Text { text: "Name"; Layout.fillWidth: true; color: "white"; font.bold: true }
                                Text { text: "Specialization"; Layout.preferredWidth: 180; color: "white"; font.bold: true }
                                Text { text: "Fee"; Layout.preferredWidth: 100; color: "white"; font.bold: true }
                                Text { text: "Action"; Layout.preferredWidth: 100; color: "white"; font.bold: true }
                            }
                        }

                        // LIST
                        ListView {
                            Layout.fillWidth: true
                            Layout.preferredHeight: contentHeight
                            model: doctorsModel
                            clip: true

                            delegate: Rectangle {
                                width: ListView.view.width
                                height: 55
                                color: index % 2 === 0 ? theme.surface : theme.card

                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 10

                                    Text { text: model.id; Layout.preferredWidth: 60; color: theme.primary }
                                    Text { text: model.name; Layout.fillWidth: true; color: theme.text }
                                    Text { text: model.specialization; Layout.preferredWidth: 180; color: theme.text }
                                    Text { text: "$" + model.fee; Layout.preferredWidth: 100; color: theme.success }

                                    StyledButton {
                                        text: "Remove"
                                        theme: theme
                                        normalColor: theme.danger
                                        hoverColor: theme.dangerHover
                                        pressedColor: theme.dangerPressed

                                        onClicked: {
                                            confirmDialog.doctorId = model.id
                                            confirmDialog.doctorName = model.name
                                            confirmDialog.open()
                                        }
                                    }
                                }
                            }
                        }

                        // STATUS
                        Text {
                            visible: statusMessage.length > 0
                            text: statusMessage
                            color: statusSuccess ? theme.success : theme.danger
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }

    // CONFIRM DIALOG
    AlertDialog {
        id: confirmDialog
        theme: theme
        dialogTitle: "Remove Doctor"
        dialogType: "warning"
        confirmText: "Remove"

        property int doctorId: 0
        property string doctorName: ""

        onOpened: {
            dialogMessage = "Remove doctor:\n" + doctorName + " (ID: " + doctorId + ")?"
        }

        onConfirm: {
            isLoading = true
            removeDoctorRequested(doctorId)
        }
    }

    // LOADING
    Rectangle {
        anchors.fill: parent
        visible: isLoading
        color: "#80000000"

        BusyIndicator {
            anchors.centerIn: parent
            running: isLoading
        }
    }

    // 🔹 called from C++
    function showResult(success, message) {
        isLoading = false
        statusSuccess = success
        statusMessage = message
    }
}