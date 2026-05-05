// #include "hospital_system.hpp"
// #include "char_array_functions.hpp"

// void HospitalSystem::initialise()
// {
//     refreshh_data();
// }

// void HospitalSystem::refreshh_data()
// {
//     FileHandler::load_patients(patients, "patients.txt");
//     FileHandler::load_doctors(doctors, "doctors.txt");
//     FileHandler::load_admins(admins, "admins.txt");
//     FileHandler::load_bills(bills, "bills.txt");
//     FileHandler::load_prescriptions(prescriptions, "prescriptions.txt");
// }

// void HospitalSystem::run()
// {
//     int choice;

//     do
//     {
//         display_main_menu();
//         std::cin >> choice;

//         switch(choice)
//         {
//             case 1:
//                 login_patient();
//                 break;

//             case 2:
//                 login_doctor();
//                 break;

//             case 3:
//                 login_admin();
//                 break;

//             case 4:
//                 std::cout << "Exiting MediCore HMS...\n";
//                 break;

//             default:
//                 std::cout << "Invalid choice.\n";
//         }

//     }
//     while(choice != 4);
// }

// void HospitalSystem::login_patient()
// {
//     int attempts = 0;
//     while(attempts < 3)
//     {
//         int entered_id;
//         char ptr_entered_password[50];

//         std::cout << "Enter Patient ID: ";
//         std::cin >> entered_id;

//         std::cout << "Enter Password: ";
//         std::cin >> ptr_entered_password;

//         Patient* ptr_patient = patients.find(entered_id);

//         if(ptr_patient != nullptr)
//         {
//             try
//             {
//                 if(ptr_patient->login(entered_id, ptr_entered_password))
//                 {
//                     std::cout << "Login successful.\n";
//                     patient_menu(ptr_patient);
//                     return;
//                 }
//             }
//             catch(InvalidInputException& e)
//             {
//                 std::cout << e.what() << std::endl;
//             }
//         }

//         attempts++;

//         FileHandler::log_security_attempt("Patient", entered_id, "FAILED");

//         std::cout << "Invalid ID or password.\n";
//     }

//     std::cout << "Account locked. Contact admin.\n";
// }

// void HospitalSystem::login_patient()
// {
//     int attempts = 0;

//     while(attempts < 3)
//     {
//         int entered_id;
//         char* ptr_entered_password = nullptr;

//         std::cout << "Enter Patient ID: ";
//         std::cin >> entered_id;

//         std::cout << "Enter Password: ";
//         safe_get_line(ptr_entered_password);

//         Patient* ptr_patient = patients.find(entered_id);

//         if(ptr_patient != nullptr)
//         {
//             try
//             {
//                 if(ptr_patient->login(entered_id, ptr_entered_password))
//                 {
//                     std::cout << "Login successful.\n";

//                     FileHandler::log_security_attempt("Patient", entered_id, "SUCCESS");

//                     delete[] ptr_entered_password;
//                     ptr_entered_password = nullptr;
//                     patient_menu(ptr_patient);
//                     return;
//                 }
//             }
//             catch(InvalidInputException& e)
//             {
//                 std::cout << e.what() << std::endl;
//             }
//         }

//         attempts++;

//         FileHandler::log_security_attempt("Patient", entered_id, "FAILED");

//         std::cout << "Invalid ID or password.\n";

//         delete[] ptr_entered_password;
//         ptr_entered_password = nullptr;
//     }

//     std::cout << "Account locked. Contact admin.\n";
// }

// void HospitalSystem::patient_menu(Patient* ptr_patient)
// {
//     int choice;

//     do
//     {
//         std::cout << "\n Welcome, " << ptr_patient->get_name() << std::endl;
//         std::cout << "Balance: PKR " << ptr_patient->get_balance() << std::endl;
//         std::cout << "========================" << std::endl;
//         std::cout << "1. Book Appointment" << std::endl;
//         std::cout << "2. Cancel Appointment" << std::endl;
//         std::cout << "3. View My Appointments" << std::endl;
//         std::cout << "4. View My Medical Records" << std::endl;
//         std::cout << "5. View My Bills" << std::endl;
//         std::cout << "6. Pay Bill" << std::endl;
//         std::cout << "7. Top Up Balance" << std::endl;
//         std::cout << "8. Logout" << std::endl;

//         std::cin >> choice;

//         switch(choice)
//         {
//             case 1:
//                 book_appointment(ptr_patient);
//                 break;

//             case 2:
//                 cancel_appointment(ptr_patient);
//                 break;

//             case 3:
//                 view_appointments(ptr_patient);
//                 break;

//             case 4:
//                 view_medical_records(ptr_patient);
//                 break;

//             case 5:
//                 view_bills(ptr_patient);
//                 break;

//             case 6:
//                 pay_bill(ptr_patient);
//                 break;

//             case 7:
//                 topup_balance(ptr_patient);
//                 break;

//             case 8:
//                 std::cout << "Logging out...\n";
//                 break;

//             default:
//                 std::cout << "Invalid choice.\n";
//         }

//     } while(choice != 8);
// }

#include "hospital_system.hpp"
#include <iostream>

HospitalSystem::HospitalSystem()
{

}

void HospitalSystem::load_data()
{
    try
    {
        FileHandler::load_patients(patients, "patients.txt");
        FileHandler::load_doctors(doctors, "doctors.txt");
        FileHandler::load_admins(admins, "admin.txt");
        FileHandler::load_appointments(appointments, "appointments.txt");
        FileHandler::load_bills(bills, "bills.txt");
        FileHandler::load_prescriptions(prescriptions, "prescriptions.txt");        
    }
    catch(const std::exception& e)
    {
        std::cout << "\n Error failed to open file " <<  e.what() << '\n';
    }
    
}

void HospitalSystem::save_data()
{
    FileHandler::update_patients(patients, "patients.txt");
    FileHandler::update_doctors(doctors, "doctors.txt");
    FileHandler::update_admins(admins, "admin.txt");
    FileHandler::update_appointments(appointments, "appointments.txt");
    FileHandler::update_bills(bills, "bills.txt");
    FileHandler::update_prescriptions(prescriptions, "prescriptions.txt");
}

void HospitalSystem::run()
{
    load_data(); 
    login_menu();
    save_data();
}

// void HospitalSystem::login_menu()
// {
//     int choice;
//     do
//     {
//         std::cout << "\nWelcome to MediCore Hospital Management System\n";
//         std::cout << "===============================================\n";
//         std::cout << "Login as:\n1. Patient\n2. Doctor\n3. Admin\n4. Exit\n";
//         std::cin >> choice;

//         if (choice == 1)
//         {
//             int id;
//             char *password = nullptr;
//             std::cout << "Enter Patient ID: ";
//             std::cin >> id;
//             std::cin.ignore(CLEAR_BUFFER,'\n');
//             std::cout << "Enter Password: ";
//             safe_get_line(password);

//             const Patient *data = patients.get_data();
//             for (int i = 0; i < patients.size(); i++)
//             {
//                 if (data[i].get_id() == id && data[i].login(id, password))
//                 {
//                     patient_session(patients.get_data()[i]);
//                 }
//             }
//             delete[] password;
//         }

//         else if (choice == 2)
//         {
//             int id;
//             char *password = nullptr;
//             std::cout << "Enter Doctor ID: ";
//             std::cin >> id;
//             std::cout << "Enter Password: ";
//             safe_get_line(password);

//             const Doctor *data = doctors.get_data();
//             for (int i = 0; i < doctors.size(); i++)
//             {
//                 if (data[i].get_id() == id && data[i].login(id, password))
//                 {
//                     doctor_session(doctors.get_data()[i]);
//                 }
//             }

//             delete[] password;
//         }

//         else if (choice == 3)
//         {
//             int id;
//             char *password = nullptr;
//             std::cout << "Enter Admin ID: ";
//             std::cin >> id;
//             std::cout << "Enter Password: ";
//             safe_get_line(password);

//             const Admin *data = admins.get_data();
//             for (int i = 0; i < admins.size(); i++)
//             {
//                 if (data[i].get_id() == id && data[i].authenticate(id, password))
//                 {
//                     admin_session(admins.get_data()[i]);
//                 }
//             }

//             delete[] password;
//         }
//     } while (choice != 4);
// }


void HospitalSystem::login_menu()
{
    int choice = 0;
    do
    {
        std::cout << "\n Welcome to MediCore Hospital Management System \n";
        std::cout << "\n =============================================== \n";
        std::cout << "Login as: \n";
        std::cout << "1. Patient \n";
        std::cout << "2. Doctor \n";
        std::cout << "3. Admin \n";
        std::cout << "4. Exit \n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(CLEAR_BUFFER, '\n');

        if      (choice == 1) 
            patient_login();
        else if (choice == 2)
             doctor_login();
        else if (choice == 3)
             admin_login();
        else if (choice != 4)
             std::cout << "Invalid choice. Try again.\n";

    } while (choice != 4);

    std::cout << "Goodbye! \n";
}

void HospitalSystem::patient_login()
{
    std::cout << "\n 1. Login \n 2. Sign Up \nChoice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    if (choice == 2)
    {
        patient_signup();
        return;
    }

    if (choice != 1)
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    int id;
    char* ptr_password = nullptr;

    std::cout << "Enter Patient ID: ";
    std::cin >> id;
    std::cin.ignore(CLEAR_BUFFER, '\n');
    std::cout << "Enter Password: ";
    safe_get_line(ptr_password);

    int fail_count = 0;
    bool logged_in = false;

    Patient* ptr_data = patients.get_data();

    for (int i = 0; i < patients.size(); i++)
    {
        if ((ptr_data + i)->get_id() == id)
        {
            if ((ptr_data + i)->login(id, ptr_password))
            {
                logged_in = true;
                patient_session(*(ptr_data + i));
            }
            else
            {
                fail_count++;
            }
            break;
        }
    }

    if (!logged_in)
    {
        fail_count++;
        std::cout << "Invalid ID or password.\n";

        // Re-prompt up to 3 total attempts
        while (fail_count < 3 && !logged_in)
        {
            std::cout << "Enter Patient ID: ";
            std::cin >> id;
            std::cin.ignore(CLEAR_BUFFER, '\n');
            std::cout << "Enter Password: ";

            delete[] ptr_password;
            ptr_password = nullptr;
            safe_get_line(ptr_password);

            for (int i = 0; i < patients.size(); i++)
            {
                if ((ptr_data + i)->get_id() == id &&
                    (ptr_data + i)->login(id, ptr_password))
                {
                    logged_in = true;
                    patient_session(*(ptr_data + i));
                    break;
                }
            }

            if (!logged_in)
            {
                fail_count++;
                if (fail_count < 3)
                    std::cout << "Invalid ID or password. " << (3 - fail_count) << " attempt(s) remaining.\n";
            }
        }

        if (!logged_in && fail_count >= 3)
        {
            std::cout << "Account locked. Contact admin.\n";
            FileHandler::log_security_attempt("Patient", id, "LOCKED");
        }
    }

    delete[] ptr_password;
    ptr_password = nullptr;
}


void HospitalSystem::doctor_login()
{
    std::cout << "\n 1. Login \n 2. Sign Up \nChoice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    if (choice == 2)
    {
        doctor_signup();
        return;
    }

    if (choice != 1)
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    int id;
    char* ptr_password = nullptr;

    std::cout << "Enter Doctor ID: ";
    std::cin >> id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    std::cout << "Enter Password: ";
    safe_get_line(ptr_password);

    int fail_count = 0;
    bool logged_in = false;

    Doctor* ptr_data = doctors.get_data();

    for (int i = 0; i < doctors.size(); i++)
    {
        if ((ptr_data + i)->get_id() == id)
        {
            if ((ptr_data + i)->login(id, ptr_password))
            {
                logged_in = true;
                doctor_session(*(ptr_data + i));
            }
            else
            {
                fail_count++;
            }
            break;
        }
    }

    if (!logged_in)
    {
        fail_count++;
        std::cout << "Invalid ID or password.\n";

        while (fail_count < 3 && !logged_in)
        {
            std::cout << "Enter Doctor ID: ";
            std::cin >> id;
            std::cin.ignore(CLEAR_BUFFER, '\n');

            std::cout << "Enter Password: ";

            delete[] ptr_password;
            ptr_password = nullptr;
            safe_get_line(ptr_password);

            for (int i = 0; i < doctors.size(); i++)
            {
                if ((ptr_data + i)->get_id() == id &&
                    (ptr_data + i)->login(id, ptr_password))
                {
                    logged_in = true;
                    doctor_session(*(ptr_data + i));
                    break;
                }
            }

            if (!logged_in)
            {
                fail_count++;
                if (fail_count < 3)
                    std::cout << "Invalid ID or password. " 
                              << (3 - fail_count) 
                              << " attempt(s) remaining.\n";
            }
        }

        if (!logged_in && fail_count >= 3)
        {
            std::cout << "Account locked. Contact admin.\n";
            FileHandler::log_security_attempt("Doctor", id, "LOCKED");
        }
    }

    delete[] ptr_password;
    ptr_password = nullptr;
}

void HospitalSystem::admin_login()
{
    std::cout << "\n 1. Login \n 2.Sign Up \n Choice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    if (choice == 2)
    {
        admin_signup();
        return;
    }

    if (choice != 1)
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    int id;
    char* ptr_password = nullptr;

    std::cout << "Enter Admin ID: ";
    std::cin >> id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    std::cout << "Enter Password: ";
    safe_get_line(ptr_password);

    int fail_count = 0;
    bool logged_in = false;

    Admin* ptr_data = admins.get_data();

    for (int i = 0; i < admins.size(); i++)
    {
        if ((ptr_data + i)->get_id() == id)
        {
            if ((ptr_data + i)->authenticate(id, ptr_password))
            {
                logged_in = true;
                admin_session(*(ptr_data + i));
            }
            else
            {
                fail_count++;
            }
            break;
        }
    }

    if (!logged_in)
    {
        fail_count++;
        std::cout << "Invalid ID or password.\n";

        while (fail_count < 3 && !logged_in)
        {
            std::cout << "Enter Admin ID: ";
            std::cin >> id;
            std::cin.ignore(CLEAR_BUFFER, '\n');

            std::cout << "Enter Password: ";

            delete[] ptr_password;
            ptr_password = nullptr;
            safe_get_line(ptr_password);

            for (int i = 0; i < admins.size(); i++)
            {
                if ((ptr_data + i)->get_id() == id &&
                    (ptr_data + i)->authenticate(id, ptr_password))
                {
                    logged_in = true;
                    admin_session(*(ptr_data + i));
                    break;
                }
            }

            if (!logged_in)
            {
                fail_count++;
                if (fail_count < 3)
                    std::cout << "Invalid ID or password. "
                              << (3 - fail_count)
                              << " attempt(s) remaining.\n";
            }
        }

        if (!logged_in && fail_count >= 3)
        {
            std::cout << "Account locked. Contact super admin.\n";
            FileHandler::log_security_attempt("Admin", id, "LOCKED");
        }
    }

    delete[] ptr_password;
    ptr_password = nullptr;
}

void HospitalSystem::patient_signup()
{
    std::cout << "\n --- Patient Sign Up --- \n";

    char* ptr_name     = nullptr;
    char* ptr_password = nullptr;
    char* ptr_contact  = nullptr;
    const char* ptr_gender   = nullptr;
    int   age          = 0;
    double balance     = 0.0;

    std::cout << "Enter Name: ";
    safe_get_line(ptr_name);

    std::cout << "Enter Password ";
    safe_get_line(ptr_password);

    std::cout << "Enter Contact (11 digits): ";
    safe_get_line(ptr_contact);

    try 
    { 
        Validator::validate_contact(ptr_contact);
    }

    catch(...)
    {
        std::cout << "Invalid contact number. Returning to menu.\n";
        delete[] ptr_name;
        delete[] ptr_password;
        delete[] ptr_contact;

        ptr_name = nullptr;
        ptr_password = nullptr;
        ptr_contact = nullptr;
        return;
    }

    std::cout << "Enter Age: ";
    std::cin >> age;

    try
    {
        Validator::validate_age(age);
    }
    catch(const std::exception& e)
    {
        std::cout << "\n Age cannot be negative" <<  e.what() << '\n';
    }
    
    std::cout << "Enter Gender (M/F): ";
    char gender;
    std::cin >> gender;
    if (gender == 'M' || gender == 'm')
    {
    ptr_gender = male;
    }
    else if (gender == 'F' || gender == 'f')
    {
    ptr_gender = female;
    }
    else
    {
    std::cout << "Invalid gender. Returning to menu.\n";
    delete[] ptr_name;
    delete[] ptr_password;
    delete[] ptr_contact;
    return;
    }

    std:: cout << "\n Enter balance: ";
    std::cin >> balance;


    int new_id = FileHandler::generate_new_id(patients);

    Patient new_patient(new_id, ptr_password, ptr_name,
                        ptr_gender, age, ptr_contact, balance);

    patients.add(new_patient);
    FileHandler::append_patient(new_patient, "patients.txt");

    std::cout << "Sign up successful! Your Patient ID is: " << new_id << "\n";
    std::cout << "Please login with your new credentials.\n";

    delete[] ptr_name;
    delete[] ptr_password;
    delete[] ptr_contact;

    ptr_name = nullptr;
    ptr_password = nullptr;
    ptr_contact = nullptr;
    ptr_gender = nullptr;
}

void HospitalSystem::doctor_signup()
{

}
void HospitalSystem::admin_signup()
{

}

// To execute after the user successfully logs in 

void HospitalSystem::patient_session(Patient &patient)
{
    int choice;
    do
    {
        patient.menu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Book Appointment (hook into appointment_service) \n";
            break;
        case 2:
            std::cout << "Cancel Appointment (update appointments + bills) \n";
            break;
        case 3:
            std::cout << "View My Appointments \n";
            break;
        case 4:
            std::cout << "View Medical Records \n";
            break;
        case 5:
            std::cout << "View Bills \n";
            break;
        case 6:
            std::cout << "Pay Bill \n";
            break;
        case 7:
            std::cout << "Top Up Balance \n";
            break;
        }
    } while (choice != 8);
}

void HospitalSystem::doctor_session(Doctor &doctor)
{
    int choice;
    do
    {
        doctor.menu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "View Today's Appointments\n";
            break;
        case 2:
            std::cout << "Mark Appointment Complete\n";
            break;
        case 3:
            std::cout << "Mark No-Show\n";
            break;
        case 4:
            std::cout << "Write Prescription\n";
            break;
        case 5:
            std::cout << "View Patient History\n";
            break;
        }
    } while (choice != 6);
}

void HospitalSystem::admin_session(Admin &admin)
{
    int choice;
    do
    {
        admin.menu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Add Doctor\n";
            break;
        case 2:
            std::cout << "Remove Doctor\n";
            break;
        case 3:
            std::cout << "View All Patients\n";
            break;
        case 4:
            std::cout << "View All Doctors\n";
            break;
        case 5:
            std::cout << "View All Appointments\n";
            break;
        case 6:
            std::cout << "View Unpaid Bills\n";
            break;
        case 7:
            std::cout << "Discharge Patient\n";
            break;
        case 8:
            std::cout << "View Security Log\n";
            break;
        case 9:
            std::cout << "Generate Daily Report\n";
            break;
        }
    } while (choice != 10);
}
