import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "./screens" as Screens


ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: "MediCore Hospital Management System"

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: loginScreen
    }

    Component {
        id: loginScreen
        Screens.LoginScreen {
            onLoginSuccess: function(role, userId) {
                if (role === "patient") {
                    stackView.push(patientDashboard, { userId: userId })
                } else if (role === "doctor") {
                    stackView.push(doctorDashboard, { userId: userId })
                } else if (role === "admin") {
                    stackView.push(adminDashboard, { userId: userId })
                }
            }
        }
    }

    Component {
        id: patientDashboard
        Screens.PatientDashboard {
            onLogout: {
                stackView.pop()
            }
        }
    }

    Component {
        id: doctorDashboard
        Screens.DoctorDashboard {
            onLogout: {
                stackView.pop()
            }
        }
    }

    Component {
        id: adminDashboard
        Screens.AdminDashboard {
            onLogout: {
                stackView.pop()
            }
        }
    }
}