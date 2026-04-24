import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "./components" as Components
import "./screens" as Screens

ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: "MediCore Hospital Management System"

    // Load the theme
    Components.Theme {
        id: theme
    }

    // Make theme globally accessible
    property var globalTheme: theme

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: loginScreenComponent
    }

    Component {
        id: loginScreenComponent
        Screens.LoginScreen {
            onLoginSuccessToDashboard: function(role, userId) {
                console.log("Login success:", role, userId)

                // Convert userId to integer
                var userIdInt = parseInt(userId)

                if (role === "Patient") {
                    stackView.push(patientDashboardComponent, { userId: userIdInt })
                } else if (role === "Doctor") {
                    stackView.push(doctorDashboardComponent, { userId: userIdInt })
                } else if (role === "Admin") {
                    stackView.push(adminDashboardComponent, { userId: userIdInt })
                }
            }
        }
    }

    Component {
        id: patientDashboardComponent
        Screens.PatientDashboard {
            onLogout: {
                stackView.pop() // Go back to login screen
            }
        }
    }

    Component {
        id: doctorDashboardComponent
        Screens.DoctorDashboard {
            onLogout: {
                stackView.pop() // Go back to login screen
            }
        }
    }

    Component {
        id: adminDashboardComponent
        Screens.AdminDashboard {
            onLogout: {
                stackView.pop() // Go back to login screen
            }
        }
    }
}