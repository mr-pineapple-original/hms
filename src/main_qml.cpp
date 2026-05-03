#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QStringLiteral>


#include "person.hpp"
#include "doctor.hpp"
#include "admin.hpp"
#include "appointment.hpp"
#include "bill.hpp"
#include "prescription.hpp"
#include "patient.hpp"

#include "storage.hpp"
#include "invalid_input_exception.hpp"
#include "validator.hpp"
#include "file_handler.hpp"

Storage<Patient> patients;
Storage<Doctor> doctors;
Storage<Admin> admins;
Storage<Appointment> appointments;
Storage<Bill> bills;
Storage<Prescription> prescriptions;


void refresh_vars()
{
    FileHandler::load_doctors(doctors, "doctors.txt");
    FileHandler::load_admins(admins, "admin.txt");
    FileHandler::load_appointments(appointments, "appointments.txt");
    FileHandler::load_bills(bills, "bills.txt");
    FileHandler::load_prescriptions(prescriptions, "prescriptions.txt");
}

int main(int argc, char *argv[])
{
    refresh_vars();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qt/qml/hms/qml/Main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();

 

}

