import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components"

Rectangle {
    id: screen
    width: parent.width
    height: parent.height

    property var theme: mainWindow ? mainWindow.globalTheme : null
    property string successMessage: ""
    property string errorMessage: ""
    property bool isLoading: false

    signal goBack()
    signal doctorAdded(string message)

    color: theme ? theme.background : "#0f172a"

    ColumnLayout {
        anchors.fill: parent

        // HEADER
        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 20

            StyledButton {
                text: "← Back"
                theme: screen.theme
                onClicked: goBack()
            }

            Item { Layout.fillWidth: true }
        }

        // CONTENT
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 20

            ColumnLayout {
                width: ScrollView.view.width
                spacing: 20

                Text {
                    text: "Add New Doctor"
                    color: theme ? theme.text : "white"
                    font.pixelSize: theme ? theme.fontSizeLarge : 20
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                // CARD
                Rectangle {
                    Layout.fillWidth: true
                    Layout.maximumWidth: 550
                    Layout.alignment: Qt.AlignHCenter

                    radius: theme ? theme.radiusLarge : 14
                    color: theme ? theme.card : "#1e293b"
                    border.color: theme ? theme.border : "#334155"

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.margins: 25
                        spacing: 18

                        // NAME
                        Text { text: "Doctor Name *"; color: theme.text }
                        StyledField {
                            id: nameField
                            Layout.fillWidth: true
                            theme: theme
                            placeholderText: "Full name"
                        }

                        // SPECIALIZATION
                        Text { text: "Specialization *"; color: theme.text }
                        StyledField {
                            id: specializationField
                            Layout.fillWidth: true
                            theme: theme
                            placeholderText: "Cardiologist"
                        }

                        // CONTACT
                        Text { text: "Contact *"; color: theme.text }
                        StyledField {
                            id: contactField
                            Layout.fillWidth: true
                            theme: theme
                            placeholderText: "11 digits"
                            inputMethodHints: Qt.ImhDigitsOnly

                            valid: text.length === 11
                            errorText: {
                                if (text.length === 0) return ""
                                return text.length === 11
                                       ? "✓ Valid number"
                                       : "Must be 11 digits"
                            }
                        }

                        // PASSWORD
                        Text { text: "Password *"; color: theme.text }
                        StyledField {
                            id: passwordField
                            Layout.fillWidth: true
                            theme: theme
                            placeholderText: "Minimum 6 characters"
                            password: true

                            valid: text.length >= 6
                            errorText: {
                                if (text.length === 0) return ""
                                return text.length >= 6
                                       ? "✓ Valid password"
                                       : "At least 6 characters"
                            }
                        }

                        // FEE
                        Text { text: "Consultation Fee"; color: theme.text }
                        StyledField {
                            id: feeField
                            Layout.fillWidth: true
                            theme: theme
                            placeholderText: "Enter fee"

                            valid: !text || !isNaN(parseFloat(text))
                            errorText: {
                                if (text.length === 0) return ""
                                return isNaN(parseFloat(text))
                                       ? "Enter a valid number"
                                       : "✓ Valid fee"
                            }
                        }

                        // MESSAGE
                        Text {
                            text: successMessage || errorMessage
                            visible: successMessage || errorMessage
                            color: successMessage ? theme.success : theme.danger
                            Layout.fillWidth: true
                            wrapMode: Text.WordWrap
                        }

                        // ACTION BUTTON
                        StyledButton {
                            Layout.fillWidth: true
                            theme: theme
                            text: isLoading ? "Adding..." : "Add Doctor"
                            enabled: isFormValid() && !isLoading
                            onClicked: addDoctor()
                        }
                    }
                }

                Item { Layout.fillHeight: true }
            }
        }
    }

    // LOADING OVERLAY
    Rectangle {
        anchors.fill: parent
        visible: isLoading
        color: "#80000000"

        BusyIndicator {
            anchors.centerIn: parent
            running: isLoading
        }
    }

    function isFormValid() {
        return nameField.text.length &&
               specializationField.text.length &&
               contactField.text.length === 11 &&
               passwordField.text.length >= 6 &&
               feeField.text.length &&
               !isNaN(parseFloat(feeField.text))
    }

    function addDoctor() {
        successMessage = ""
        errorMessage = ""

        if (!isFormValid()) {
            errorMessage = "Invalid input"
            return
        }

        isLoading = true

        let result = mainWindow.addDoctor(
            nameField.text,
            specializationField.text,
            contactField.text,
            passwordField.text,
            parseFloat(feeField.text)
        )

        isLoading = false

        if (result.success) {
            successMessage = "Doctor added (ID: " + result.id + ")"
            doctorAdded(successMessage)
            clearForm()
        } else {
            errorMessage = result.message
        }
    }

    function clearForm() {
        nameField.text = ""
        specializationField.text = ""
        contactField.text = ""
        passwordField.text = ""
        feeField.text = ""
    }
}