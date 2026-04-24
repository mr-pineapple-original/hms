import QtQuick 2.15

QtObject {
    // Current mode: "light" or "dark"
    property string currentMode: "light"

    // Mode colors
    readonly property var lightMode: QtObject {
        readonly property color primary: "#3498db"
        readonly property color primaryHover: "#2980b9"
        readonly property color primaryPressed: "#1c638c"

        readonly property color danger: "#e74c3c"
        readonly property color dangerHover: "#c0392b"
        readonly property color dangerPressed: "#a93226"

        readonly property color success: "#27ae60"
        readonly property color warning: "#f39c12"

        readonly property color background: "#f5f5f5"
        readonly property color card: "#ffffff"
        readonly property color border: "#e0e0e0"
        readonly property color text: "#2c3e50"
        readonly property color textSecondary: "#7f8c8d"

        readonly property color header: "#ecf0f1"
        readonly property color hover: "#f8f9fa"
    }

    readonly property var darkMode: QtObject {
        readonly property color primary: "#3498db"
        readonly property color primaryHover: "#5dade2"
        readonly property color primaryPressed: "#1c638c"

        readonly property color danger: "#e74c3c"
        readonly property color dangerHover: "#cb4335"
        readonly property color dangerPressed: "#922b21"

        readonly property color success: "#2ecc71"
        readonly property color warning: "#f39c12"

        readonly property color background: "#1a1a2e"
        readonly property color card: "#16213e"
        readonly property color border: "#2c3e50"
        readonly property color text: "#ecf0f1"
        readonly property color textSecondary: "#bdc3c7"

        readonly property color header: "#0f3460"
        readonly property color hover: "#1f2937"
    }

    // Dynamic properties that change based on currentMode
    readonly property color primary: currentMode === "dark" ? darkMode.primary : lightMode.primary
    readonly property color primaryHover: currentMode === "dark" ? darkMode.primaryHover : lightMode.primaryHover
    readonly property color primaryPressed: currentMode === "dark" ? darkMode.primaryPressed : lightMode.primaryPressed

    readonly property color danger: currentMode === "dark" ? darkMode.danger : lightMode.danger
    readonly property color dangerHover: currentMode === "dark" ? darkMode.dangerHover : lightMode.dangerHover
    readonly property color dangerPressed: currentMode === "dark" ? darkMode.dangerPressed : lightMode.dangerPressed

    readonly property color success: currentMode === "dark" ? darkMode.success : lightMode.success
    readonly property color warning: currentMode === "dark" ? darkMode.warning : lightMode.warning

    readonly property color background: currentMode === "dark" ? darkMode.background : lightMode.background
    readonly property color card: currentMode === "dark" ? darkMode.card : lightMode.card
    readonly property color border: currentMode === "dark" ? darkMode.border : lightMode.border
    readonly property color text: currentMode === "dark" ? darkMode.text : lightMode.text
    readonly property color textSecondary: currentMode === "dark" ? darkMode.textSecondary : lightMode.textSecondary

    readonly property color header: currentMode === "dark" ? darkMode.header : lightMode.header
    readonly property color hover: currentMode === "dark" ? darkMode.hover : lightMode.hover

    // Sizes (same for both modes)
    readonly property int radius: 8
    readonly property int radiusLarge: 14

    // Font sizes (same for both modes)
    readonly property int fontSizeSmall: 12
    readonly property int fontSizeNormal: 14
    readonly property int fontSizeLarge: 16
    readonly property int fontSizeTitle: 22

    // Helper function to toggle mode
    function toggleMode() {
        currentMode = currentMode === "light" ? "dark" : "light"
    }

    // Helper function to set mode explicitly
    function setMode(mode) {
        if (mode === "light" || mode === "dark") {
            currentMode = mode
        }
    }
}