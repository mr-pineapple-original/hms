import QtQuick 2.15

Item {
    property var theme: Theme

    Component.onCompleted: {
        // Make theme available globally
        if (typeof globalTheme === "undefined") {
            globalTheme = theme
        }
    }
}