import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "MediCore HMS"

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: LoginPage {}
    }
}