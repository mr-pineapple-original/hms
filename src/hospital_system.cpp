#include "hospital_system.hpp"
#include "char_array_functions.hpp"

void HospitalSystem::initialise()
{
    refreshh_data();
}

void HospitalSystem::refreshh_data()
{
    FileHandler::load_patients(patients, "patients.txt");
    FileHandler::load_doctors(doctors, "doctors.txt");
    FileHandler::load_admins(admins, "admins.txt");
    FileHandler::load_bills(bills, "bills.txt");
    FileHandler::load_prescriptions(prescriptions, "prescriptions.txt");
}

void HospitalSystem::run()
{
    int choice;

    do
    {
        display_main_menu();
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                login_patient();
                break;

            case 2:
                login_doctor();
                break;

            case 3:
                login_admin();
                break;

            case 4:
                std::cout << "Exiting MediCore HMS...\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } 
    while(choice != 4);
}

void HospitalSystem::login_patient()
{
    int attempts = 0;
    while(attempts < 3)
    {
        int entered_id;
        char ptr_entered_password[50];

        std::cout << "Enter Patient ID: ";
        std::cin >> entered_id;

        std::cout << "Enter Password: ";
        std::cin >> ptr_entered_password;

        Patient* ptr_patient = patients.find(entered_id);

        if(ptr_patient != nullptr)
        {
            try
            {
                if(ptr_patient->login(entered_id, ptr_entered_password))
                {
                    std::cout << "Login successful.\n";
                    patient_menu(ptr_patient);
                    return;
                }
            }
            catch(InvalidInputException& e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        attempts++;

        FileHandler::log_security_attempt("Patient", entered_id, "FAILED");

        std::cout << "Invalid ID or password.\n";
    }

    std::cout << "Account locked. Contact admin.\n";
}

void HospitalSystem::login_patient()
{
    int attempts = 0;

    while(attempts < 3)
    {
        int entered_id;
        char* ptr_entered_password = nullptr;

        std::cout << "Enter Patient ID: ";
        std::cin >> entered_id;

        std::cout << "Enter Password: ";
        safe_get_line(ptr_entered_password);  

        Patient* ptr_patient = patients.find(entered_id);

        if(ptr_patient != nullptr)
        {
            try
            {
                if(ptr_patient->login(entered_id, ptr_entered_password))
                {
                    std::cout << "Login successful.\n";

                    FileHandler::log_security_attempt("Patient", entered_id, "SUCCESS");

                    delete[] ptr_entered_password;
                    ptr_entered_password = nullptr;
                    patient_menu(ptr_patient);
                    return;
                }
            }
            catch(InvalidInputException& e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        attempts++;

        FileHandler::log_security_attempt("Patient", entered_id, "FAILED");

        std::cout << "Invalid ID or password.\n";

        delete[] ptr_entered_password;
        ptr_entered_password = nullptr;
    }

    std::cout << "Account locked. Contact admin.\n";
}


void HospitalSystem::patient_menu(Patient* ptr_patient)
{
    int choice;

    do
    {
        std::cout << "\n Welcome, " << ptr_patient->get_name() << std::endl;
        std::cout << "Balance: PKR " << ptr_patient->get_balance() << std::endl;
        std::cout << "========================" << std::endl;
        std::cout << "1. Book Appointment" << std::endl;
        std::cout << "2. Cancel Appointment" << std::endl;
        std::cout << "3. View My Appointments" << std::endl;
        std::cout << "4. View My Medical Records" << std::endl;
        std::cout << "5. View My Bills" << std::endl;
        std::cout << "6. Pay Bill" << std::endl;
        std::cout << "7. Top Up Balance" << std::endl;
        std::cout << "8. Logout" << std::endl;

        std::cin >> choice;

        switch(choice)
        {
            case 1:
                book_appointment(ptr_patient);
                break;

            case 2:
                cancel_appointment(ptr_patient);
                break;

            case 3:
                view_appointments(ptr_patient);
                break;

            case 4:
                view_medical_records(ptr_patient);
                break;

            case 5:
                view_bills(ptr_patient);
                break;

            case 6:
                pay_bill(ptr_patient);
                break;

            case 7:
                topup_balance(ptr_patient);
                break;

            case 8:
                std::cout << "Logging out...\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while(choice != 8);
}

