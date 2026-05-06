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
//     FileHandler::load_admins(admins, "admin.txt");
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

// This function is to get time from the local system clock and put it on a character array in the valid format
void HospitalSystem::get_today_date(char* ptr_buffer)
{
    time_t now = time(0);
    tm* ptr_tm = localtime(&now);

    // DD
    *(ptr_buffer + 0) = '0' + (ptr_tm->tm_mday / 10);
    *(ptr_buffer + 1) = '0' + (ptr_tm->tm_mday % 10);
    *(ptr_buffer + 2) = '-';

    // MM
    int month = ptr_tm->tm_mon + 1;
    *(ptr_buffer + 3) = '0' + (month / 10);
    *(ptr_buffer + 4) = '0' + (month % 10);
    *(ptr_buffer + 5) = '-';

    // YYYY
    int year = ptr_tm->tm_year + 1900;
    *(ptr_buffer + 6)  = '0' + (year / 1000);
    *(ptr_buffer + 7)  = '0' + ((year / 100) % 10);
    *(ptr_buffer + 8)  = '0' + ((year / 10) % 10);
    *(ptr_buffer + 9)  = '0' + (year % 10);
    *(ptr_buffer + 10) = '\0';
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
    // std::cout << "\n 1. Login \n 2. Sign Up \nChoice: ";
    // int choice;
    // std::cin >> choice;
    // std::cin.ignore(CLEAR_BUFFER, '\n');

    // if (choice == 2)
    // {
    //     doctor_signup();
    //     return;
    // }

    // if (choice != 1)
    // {
    //     std::cout << "Invalid choice.\n";
    //     return;
    // }

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
    std::cout << "\n 1. Login \n 2. Sign Up \n Choice: ";
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

    // std::cout << "DEBUG: Before validation \n";
    
    try
    {
        Validator::validate_age(age);
    }
    catch(const std::exception& e)
    {
        std::cout << "\n Age cannot be negative" <<  e.what() << '\n';
    }
    
    // std::cout << "DEBUG: After validation \n";

    std::cin.ignore(CLEAR_BUFFER,'\n');
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

    std::cout << "\n --- Doctor Sign Up --- \n";

    char* ptr_name           = nullptr;
    char* ptr_specialization = nullptr;
    char* ptr_contact        = nullptr;
    char* ptr_password       = nullptr;
    double fee               = 0.0;

    std::cin.ignore(CLEAR_BUFFER,'\n');
    std::cout << "Enter Name: ";
    safe_get_line(ptr_name);

    std::cout << "Enter Password: ";
    safe_get_line(ptr_password);

    std::cout << "Enter Specialization: ";
    safe_get_line(ptr_specialization);

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
        delete[] ptr_specialization;
        delete[] ptr_contact;

        ptr_name = nullptr;
        ptr_specialization = nullptr;
        ptr_contact = nullptr;
        return;
    }


    std::cout << "Enter Fee: ";
    std::cin >> fee;
    
    if(fee == 0)
    {
        std::cout << "\n Thanks for working for free with no fee ";
    }

    try
    {
        Validator::validate_positive_double(fee);
    }

    catch(const std::exception& e)
    {
        std::cout << "\n Fee cannot be negative. Returning to menu " <<  e.what() << '\n';
                
        delete[] ptr_name;
        delete[] ptr_specialization;
        delete[] ptr_contact;

        ptr_name = nullptr;
        ptr_specialization = nullptr;
        ptr_contact = nullptr;
        return;
    }
    
    std::cin.ignore(CLEAR_BUFFER, '\n');


    const char* ptr_gender = male;   
    int default_age = 30;            

    int new_id = FileHandler::generate_new_id(doctors);

    Doctor new_doctor(new_id, ptr_password, ptr_name,
                      ptr_gender, default_age,
                      ptr_specialization, ptr_contact, fee);

    doctors.add(new_doctor);
    FileHandler::append_doctor(new_doctor, "doctors.txt");

    std::cout << "Doctor added successfully \n Doctor's ID: : " << new_id << "\n";
    std::cout << "Docotr should login with his/her credentials.\n";

    delete[] ptr_name;
    delete[] ptr_specialization;
    delete[] ptr_contact;
    delete[] ptr_password;

    ptr_name = nullptr;
    ptr_specialization = nullptr;
    ptr_contact = nullptr;
    ptr_password = nullptr;
}

void HospitalSystem::admin_signup()
{
    std::cout << "\n --- Admin Sign Up --- \n";

    char* ptr_name     = nullptr;
    char* ptr_password = nullptr;

    std::cout << "Enter Name: ";
    safe_get_line(ptr_name);

    std::cout << "Enter Password: ";
    safe_get_line(ptr_password);

    int new_id = FileHandler::generate_new_id(admins);

    Admin new_admin(new_id, ptr_password, ptr_name);

    admins.add(new_admin);
    FileHandler::append_admin(new_admin, "admin.txt");

    std::cout << "Sign up successful! Your Admin ID is: " << new_id << "\n";
    std::cout << "Please login with your credentials.\n";

    delete[] ptr_name;
    delete[] ptr_password;

    ptr_name = nullptr;
    ptr_password = nullptr;
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
            book_appointment(patient);
            break;
        case 2:
            cancel_appointment(patient);
            break;
        case 3:
            view_appointments(patient);
            break;
        case 4:
            view_medical_records(patient);
            break;
        case 5:
            view_bills(patient);
            break;
        case 6:
            pay_bill(patient);
            break;
        case 7:
            top_up_balance(patient);
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
        std::cin.ignore(CLEAR_BUFFER,'\n');
        switch (choice)
        {
        case 1:
            view_today_appointments(doctor);
            break;
        case 2:
            mark_appointment_complete(doctor);
            break;
        case 3:
            mark_appointment_no_show(doctor);
            break;
        case 4:
            write_prescription(doctor);
            break;
        case 5:
            view_patient_history(doctor);
            break;
        }
    } while (choice != 6);
}

void HospitalSystem::admin_session(Admin &admin)
{
    int choice;
    do
    {
        try
        {
            admin.menu();
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                add_doctor();
                break;
            case 2:
                remove_doctor();
                break;
            case 3:
                view_all_patients();
                break;
            case 4:
                view_all_doctors();
                break;
            case 5:
                view_all_appointments();
                break;
            case 6:
                view_unpaid_bills();
                break;
            case 7:
                discharge_patient();
                break;
            case 8:
                view_security_log();
                break;
            case 9:
                generate_daily_report();
                break;
            }
        }

        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }

    } while (choice != 10);
    
}



// -------------------------------------------------------------------------------------------------------------------

//                                      Patient's session functions

// --------------------------------------------------------------------------------------------------------------------


void HospitalSystem::book_appointment(Patient& patient)
{
    // Searching  by specialization (case insensitive)
    char* ptr_spec = nullptr;
    std::cout << "Enter specialization to search (e.g. Cardiology): ";
    std::cin.ignore(CLEAR_BUFFER,'\n');
    safe_get_line(ptr_spec);

    // Converting doctor's specialisation to lowercase manually
    for (int i = 0; *(ptr_spec + i) != '\0'; i++)
    {
        if (*(ptr_spec + i) >= 'A' && *(ptr_spec + i) <= 'Z')
            *(ptr_spec + i) = *(ptr_spec + i) + 32;
    }

    // Display matching doctors
    Doctor* ptr_doctors = doctors.get_data();
    bool found = false;

    for (int i = 0; i < doctors.size(); i++)
    {
        char* ptr_doc_spec = (ptr_doctors + i)->get_specialization();

        // Making a lowercase copy of doctor specialization for comparison
        int spec_len = get_char_arr_size(ptr_doc_spec);
        char* ptr_lower_spec = new char[spec_len + 1];

        for (int j = 0; j <= spec_len; j++)
        {
            if (*(ptr_doc_spec + j) >= 'A' && *(ptr_doc_spec + j) <= 'Z')
                *(ptr_lower_spec + j) = *(ptr_doc_spec + j) + 32;
            else
                *(ptr_lower_spec + j) = *(ptr_doc_spec + j);
        }

        if (is_char_arrays_equal(ptr_lower_spec, ptr_spec))
        {
            std::cout << "ID: " << (ptr_doctors + i)->get_id()
                      << " | Name: " << (ptr_doctors + i)->get_name()
                      << " | Fee: PKR " << (ptr_doctors + i)->get_fee() << "\n";
            found = true;
        }

        delete[] ptr_lower_spec;
        ptr_lower_spec = nullptr;
    }

    delete[] ptr_spec;
    ptr_spec = nullptr;

    if (!found)
    {
        std::cout << "No doctors available for that specialization.\n";
        return;
    }

    // Enter and validate doctor ID
    int doctor_id;
    std::cout << "Enter Doctor ID: ";
    std::cin >> doctor_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    Doctor* ptr_chosen_doctor = doctors.find(doctor_id);
    if (ptr_chosen_doctor == nullptr)
    {
        std::cout << "Doctor not found.\n";
        return;
    }

    // Enter and validate date — up to 3 attempts
    char* ptr_date = nullptr;
    bool date_valid = false;
    int date_attempts = 0;

    while (!date_valid && date_attempts < 3)
    {
        std::cout << "Enter date (DD-MM-YYYY): ";
        safe_get_line(ptr_date);

        try
        {
            Validator::validate_date(ptr_date);
            date_valid = true;
        }
        catch (...)
        {
            date_attempts++;
            std::cout << "Invalid date. Use format DD-MM-YYYY.\n";

            if (date_attempts < 3)
                std::cout << (3 - date_attempts) << " attempt(s) remaining.\n";

            delete[] ptr_date;
            ptr_date = nullptr;
        }
    }

    if (!date_valid)
    {
        std::cout << "Too many invalid attempts. Returning to menu.\n";
        return;
    }

    // Display available slots
    const char* all_slots[] = {"09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00"};

    std::cout << "Available slots for " << ptr_chosen_doctor->get_name() << " on " << ptr_date << ":\n";

    Appointment* ptr_appts = appointments.get_data();

    for (int s = 0; s < 8; s++)
    {
        bool taken = false;

        for (int i = 0; i < appointments.size(); i++)
        {
            if ((ptr_appts + i)->get_doctor_id() == doctor_id &&
                is_char_arrays_equal((ptr_appts + i)->get_date(), ptr_date) &&
                is_char_arrays_equal((ptr_appts + i)->get_time(), all_slots[s]) &&
                !is_cancelled((ptr_appts + i)->get_status()))
            {
                taken = true;
                break;
            }
        }

        if (!taken)
            std::cout << all_slots[s] << "\n";
    }

    // Enter time slot — re-prompt if taken
    char* ptr_time = nullptr;
    bool slot_booked = false;

    while (!slot_booked)
    {
        std::cout << "Enter time slot (e.g. 09:00): ";
        safe_get_line(ptr_time);

        if (!Validator::validate_time_slot(ptr_time))
        {
            std::cout << "Invalid time slot.\n";
            delete[] ptr_time;
            ptr_time = nullptr;
            continue;
        }

        try
        {
            // Checking if the slot is taken
            for (int i = 0; i < appointments.size(); i++)
            {
                if ((ptr_appts + i)->get_doctor_id() == doctor_id &&
                    is_char_arrays_equal((ptr_appts + i)->get_date(), ptr_date) &&
                    is_char_arrays_equal((ptr_appts + i)->get_time(), ptr_time) &&
                    !is_cancelled((ptr_appts + i)->get_status()))
                {
                    throw SlotUnavailableException();
                }
            }
            slot_booked = true;
        }
        catch (SlotUnavailableException& e)
        {
            std::cout << e.what() << "\n";
            std::cout << "Available slots: \n";
            // s is to move from one time slot to another
            for (int s = 0; s < 8; s++)
            {
                bool taken = false;
                for (int i = 0; i < appointments.size(); i++)
                {
                    if ((ptr_appts + i)->get_doctor_id() == doctor_id &&
                        is_char_arrays_equal((ptr_appts + i)->get_date(), ptr_date) &&
                        is_char_arrays_equal((ptr_appts + i)->get_time(), all_slots[s]) &&
                        !is_cancelled((ptr_appts + i)->get_status()))
                    {
                        taken = true;
                        break;
                    }
                }
                if (!taken)
                    std::cout << all_slots[s] << "\n";
            }

            delete[] ptr_time;
            ptr_time = nullptr;
        }
    }

    // Checking balance
    try
    {
        if (patient.get_balance() < ptr_chosen_doctor->get_fee())
            throw InsufficientFundsException();
    }
    catch (InsufficientFundsException& e)
    {
        std::cout << e.what() << "\n";
        delete[] ptr_date;
        delete[] ptr_time;
        ptr_date = nullptr;
        ptr_time = nullptr;
        return;
    }

    // Deducting fee
    patient -= ptr_chosen_doctor->get_fee();

    // Generating new IDs
    int new_appt_id = FileHandler::generate_new_id(appointments);
    int new_bill_id = FileHandler::generate_new_id(bills);

    // Building char arrays on the stack to display status 
    char pending_status[] = "pending";
    char unpaid_status[]  = "unpaid";

    // Creating and storing new appointment
    Appointment new_appt(new_appt_id, patient.get_id(), doctor_id,
                         ptr_date, ptr_time, pending_status);

    appointments.add(new_appt);
    FileHandler::append_appointment(new_appt, "appointments.txt");

    // Creating and storing new bill
    Bill new_bill(new_bill_id, patient.get_id(), new_appt_id,
                  ptr_chosen_doctor->get_fee(), unpaid_status, ptr_date);

    bills.add(new_bill);
    FileHandler::append_bill(new_bill, "bills.txt");

    // Updating the patient's balance in file
    FileHandler::update_patients(patients, "patients.txt");

    std::cout << "Appointment booked successfully. Appointment ID: " << new_appt_id << "\n";

    delete[] ptr_date;
    delete[] ptr_time;
    ptr_date = nullptr;
    ptr_time = nullptr;
}


void HospitalSystem::cancel_appointment(Patient& patient)
{
    // Displaying the pending appointments for this patient
    Appointment* ptr_appts = appointments.get_data();
    bool has_pending = false;

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_patient_id() == patient.get_id() &&
            is_char_arrays_equal((const char*)(ptr_appts + i)->get_status(), "pending"))
        {
            Doctor* ptr_doc = doctors.find((ptr_appts + i)->get_doctor_id());
            std::cout << "ID: " << (ptr_appts + i)->get_id()
                      << " | Doctor: " << (ptr_doc ? ptr_doc->get_name() : "Unknown")
                      << " | Date: " << (ptr_appts + i)->get_date()
                      << " | Time: " << (ptr_appts + i)->get_time() << "\n";
            has_pending = true;
        }
    }

    if (!has_pending)
    {
        std::cout << "You have no pending appointments.\n";
        return;
    }

    int appt_id;
    std::cout << "Enter Appointment ID to cancel: ";
    std::cin >> appt_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    Appointment* ptr_appt = appointments.find(appt_id);

    if (ptr_appt == nullptr ||
        ptr_appt->get_patient_id() != patient.get_id() ||
        !is_char_arrays_equal((const char*)ptr_appt->get_status(), "pending"))
    {
        std::cout << "Invalid appointment ID.\n";
        return;
    }

    // Finding the doctor fee for refund
    Doctor* ptr_doc = doctors.find(ptr_appt->get_doctor_id());
    double fee = ptr_doc ? ptr_doc->get_fee() : 0.0;

    // Updating the appointment status to cancelled
    char cancelled[] = "cancelled";
    ptr_appt->set_appointment(ptr_appt->get_id(), ptr_appt->get_patient_id(),
                              ptr_appt->get_doctor_id(), ptr_appt->get_date(),
                              ptr_appt->get_time(), cancelled);

    FileHandler::update_appointments(appointments, "appointments.txt");

    // Refunding the fee using += operator
    patient += fee;
    FileHandler::update_patients(patients, "patients.txt");

    // Canceling the corresponding bill
    Bill* ptr_bills = bills.get_data();
    for (int i = 0; i < bills.size(); i++)
    {
        if ((ptr_bills + i)->get_appointment_id() == appt_id)
        {
            (ptr_bills + i)->set_bill((ptr_bills + i)->get_id(),
                                      (ptr_bills + i)->get_patient_id(),
                                      (ptr_bills + i)->get_appointment_id(),
                                      (ptr_bills + i)->get_amount(),
                                      cancelled,
                                      (ptr_bills + i)->get_date());
            break;
        }
    }

    // Updating it in the bill files which we can't escape irl too :/
    FileHandler::update_bills(bills, "bills.txt");

    std::cout << "Appointment cancelled. PKR " << fee << " refunded to your balance.\n";
}

//  We are gonna sort the appointments by using bubble_sort here

void HospitalSystem::view_appointments(Patient& patient)
{
    // Collecting the patient's appointments into a temp array
    Appointment* ptr_appts = appointments.get_data();
    int count = 0;

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_patient_id() == patient.get_id())
            count++;
    }

    if (count == 0)
    {
        std::cout << "No appointments found.\n";
        return;
    }

    // Building the index array for sorting without copying objects
    int* ptr_indices = new int[count];
    int index = 0;

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_patient_id() == patient.get_id())
        {
            *(ptr_indices + index) = i;
            index++;
        }
    }

    // Bubble sort by date in the ascending order (DD-MM-YYYY — sort by YYYY then MM then DD)
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            char* ptr_d1 = (ptr_appts + *(ptr_indices + j))->get_date();
            char* ptr_d2 = (ptr_appts + *(ptr_indices + j + 1))->get_date();

            // Comparing YYYY (chars 6-9), then MM (3-4), then DD (0-1)
            bool swap = false;
            int year1  = (*(ptr_d1+6)-'0')*1000 + (*(ptr_d1+7)-'0')*100 + (*(ptr_d1+8)-'0')*10 + (*(ptr_d1+9)-'0');
            int year2  = (*(ptr_d2+6)-'0')*1000 + (*(ptr_d2+7)-'0')*100 + (*(ptr_d2+8)-'0')*10 + (*(ptr_d2+9)-'0');
            int month1 = (*(ptr_d1+3)-'0')*10 + (*(ptr_d1+4)-'0');
            int month2 = (*(ptr_d2+3)-'0')*10 + (*(ptr_d2+4)-'0');
            int day1   = (*(ptr_d1+0)-'0')*10 + (*(ptr_d1+1)-'0');
            int day2   = (*(ptr_d2+0)-'0')*10 + (*(ptr_d2+1)-'0');

            if (year1 > year2)
                swap = true;
            else if (year1 == year2 && month1 > month2) 
                swap = true;
            else if (year1 == year2 && month1 == month2 && day1 > day2)
                swap = true;

            if (swap)
            {
                int temp = *(ptr_indices + j);
                *(ptr_indices + j) = *(ptr_indices + j + 1);
                *(ptr_indices + j + 1) = temp;
            }
        }
    }

    std::cout << "ID | Doctor Name | Specialization | Date | Time Slot | Status\n";
    std::cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        Appointment* ptr_appoint = ptr_appts + *(ptr_indices + i);
        Doctor* ptr_doc    = doctors.find(ptr_appoint->get_doctor_id());

        std::cout << ptr_appoint->get_id() << " | "
                  << (ptr_doc ? ptr_doc->get_name() : "Unknown") << " | "
                  << (ptr_doc ? ptr_doc->get_specialization() : "Unknown") << " | "
                  << ptr_appoint->get_date() << " | "
                  << ptr_appoint->get_time() << " | "
                  << ptr_appoint->get_status() << "\n";
    }

    delete[] ptr_indices;
    ptr_indices = nullptr;
}

//  We are gonna sort the medical records by bubble sort here by date in the descending order
void HospitalSystem::view_medical_records(Patient& patient)
{
    Prescription* ptr_prescriptions = prescriptions.get_data();
    int count = 0;

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if ((ptr_prescriptions + i)->get_patient_id() == patient.get_id())
            count++;
    }

    if (count == 0)
    {
        std::cout << "No medical records found.\n";
        return;
    }

    int* ptr_indices = new int[count];
    int idx = 0;

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if ((ptr_prescriptions + i)->get_patient_id() == patient.get_id())
        {
            *(ptr_indices + idx) = i;
            idx++;
        }
    }

    // Bubble sort by date descending
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            char* ptr_d1 = (ptr_prescriptions + *(ptr_indices + j))->get_date();
            char* ptr_d2 = (ptr_prescriptions + *(ptr_indices + j + 1))->get_date();

            int year1  = (*(ptr_d1+6)-'0')*1000 + (*(ptr_d1+7)-'0')*100 + (*(ptr_d1+8)-'0')*10 + (*(ptr_d1+9)-'0');
            int year2  = (*(ptr_d2+6)-'0')*1000 + (*(ptr_d2+7)-'0')*100 + (*(ptr_d2+8)-'0')*10 + (*(ptr_d2+9)-'0');
            int month1 = (*(ptr_d1+3)-'0')*10 + (*(ptr_d1+4)-'0');
            int month2 = (*(ptr_d2+3)-'0')*10 + (*(ptr_d2+4)-'0');
            int day1   = (*(ptr_d1+0)-'0')*10 + (*(ptr_d1+1)-'0');
            int day2   = (*(ptr_d2+0)-'0')*10 + (*(ptr_d2+1)-'0');

            bool swap = false;
            if (year1 < year2) swap = true;
            else if (year1 == year2 && month1 < month2) swap = true;
            else if (year1 == year2 && month1 == month2 && day1 < day2) swap = true;

            if (swap)
            {
                int temp = *(ptr_indices + j);
                *(ptr_indices + j) = *(ptr_indices + j + 1);
                *(ptr_indices + j + 1) = temp;
            }
        }
    }

    std::cout << "Date | Doctor Name | Medicines | Notes\n";
    std::cout << "---------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        Prescription* ptr_p = ptr_prescriptions + *(ptr_indices + i);
        Doctor* ptr_doc     = doctors.find(ptr_p->get_doctor_id());

        std::cout << ptr_p->get_date() << " | "
                  << (ptr_doc ? ptr_doc->get_name() : "Unknown") << " | "
                  << ptr_p->get_medicine() << " | "
                  << ptr_p->get_doctor_note() << "\n";
    }

    delete[] ptr_indices;
    ptr_indices = nullptr;
}

void HospitalSystem::view_bills(Patient& patient)
{
    Bill* ptr_bills = bills.get_data();
    bool found = false;
    double total_unpaid = 0.0;

    std::cout << "Bill ID | Appointment ID | Amount (PKR) | Status | Date\n";
    std::cout << "---------------------------------------------------------\n";

    for (int i = 0; i < bills.size(); i++)
    {
        if ((ptr_bills + i)->get_patient_id() == patient.get_id())
        {
            std::cout << (ptr_bills + i)->get_id() << " | "
                      << (ptr_bills + i)->get_appointment_id() << " | "
                      << (ptr_bills + i)->get_amount() << " | "
                      << (ptr_bills + i)->get_status() << " | "
                      << (ptr_bills + i)->get_date() << "\n";

            if (is_char_arrays_equal((const char*)(ptr_bills + i)->get_status(), "unpaid"))
                total_unpaid += (ptr_bills + i)->get_amount();

            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No bills found.\n";
        return;
    }

    std::cout << "Total outstanding unpaid: PKR " << total_unpaid << "\n";
}

void HospitalSystem::pay_bill(Patient& patient)
{
    Bill* ptr_bills = bills.get_data();
    bool has_unpaid = false;

    std::cout << "Unpaid Bills:\n";
    for (int i = 0; i < bills.size(); i++)
    {
        if ((ptr_bills + i)->get_patient_id() == patient.get_id() &&
            is_char_arrays_equal((const char*)(ptr_bills + i)->get_status(), "unpaid"))
        {
            std::cout << "Bill ID: " << (ptr_bills + i)->get_id()
                      << " | Amount: PKR " << (ptr_bills + i)->get_amount()
                      << " | Date: " << (ptr_bills + i)->get_date() << "\n";
            has_unpaid = true;
        }
    }

    if (!has_unpaid)
    {
        std::cout << "No unpaid bills.\n";
        return;
    }

    int bill_id;
    std::cout << "Enter Bill ID to pay: ";
    std::cin >> bill_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    Bill* ptr_bill = bills.find(bill_id);

    if (ptr_bill == nullptr ||
        ptr_bill->get_patient_id() != patient.get_id() ||
        !is_char_arrays_equal((const char*)ptr_bill->get_status(), "unpaid"))
    {
        std::cout << "Invalid Bill ID.\n";
        return;
    }

    try
    {
        if (patient.get_balance() < ptr_bill->get_amount())
            throw InsufficientFundsException();
    }
    catch (InsufficientFundsException& e)
    {
        std::cout << e.what() << "\n";
        return;
    }

    // Deducting the patient's bills using the -= operator
    patient -= ptr_bill->get_amount();

    // Updateing the bill status to paid
    char paid[] = "paid";
    ptr_bill->set_bill(ptr_bill->get_id(), ptr_bill->get_patient_id(),
                       ptr_bill->get_appointment_id(), ptr_bill->get_amount(),
                       paid, ptr_bill->get_date());

    FileHandler::update_bills(bills, "bills.txt");
    FileHandler::update_patients(patients, "patients.txt");

    std::cout << "Bill paid successfully. Remaining balance: PKR " << patient.get_balance() << "\n";
}

void HospitalSystem::top_up_balance(Patient& patient)
{
    int attempts = 0;

    while (attempts < 3)
    {
        double amount;
        std::cout << "Enter amount to add (PKR): ";
        std::cin >> amount;
        std::cin.ignore(CLEAR_BUFFER, '\n');

        try
        {
            if (amount <= 0)
                throw InvalidInputException();

            // Add using += operator
            patient += amount;
            FileHandler::update_patients(patients, "patients.txt");

            std::cout << "Balance updated. New balance: PKR " << patient.get_balance() << "\n";
            return;
        }
        catch (InvalidInputException& e)
        {
            attempts++;
            std::cout << e.what() << "\n";

            if (attempts < 3)
                std::cout << (3 - attempts) << " attempt(s) remaining.\n";
        }
    }

    std::cout << "Too many invalid attempts. Returning to menu.\n";
}


// -------------------------------------------------------------------------------------------------------------------

//                                      Doctor's session functions

// --------------------------------------------------------------------------------------------------------------------


void HospitalSystem::view_today_appointments(Doctor& doctor)
{
    // DD-MM-YYYY + '\0' is stored in this static character array mate
    char today[11];
    get_today_date(today);

    Appointment* ptr_appts = appointments.get_data();

    // Getting the count of the doctor's appointments to see how many appointmnents he has on this day
    int count = 0;
    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_doctor_id() == doctor.get_id() &&
            is_char_arrays_equal((ptr_appts + i)->get_date(), today))
        {
            count++;
        }
    }

    if (count == 0)
    {
        std::cout << "No appointments scheduled for today.\n";
        return;
    }

    // Building an array to store the indexes
    int* ptr_indices = new int[count];
    int index = 0;

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_doctor_id() == doctor.get_id() &&
            is_char_arrays_equal((ptr_appts + i)->get_date(), today))
        {
            *(ptr_indices + index) = i;
            index++;
        }
    }

    // Sorting the time slot by bubble_sort in an ascending order (HH:MM — just compare char by char)
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            char* ptr_t1 = (ptr_appts + *(ptr_indices + j))->get_time();
            char* ptr_t2 = (ptr_appts + *(ptr_indices + j + 1))->get_time();

            // HH:MM — compare hours then minutes
            int h1 = (*(ptr_t1 + 0) - '0') * 10 + (*(ptr_t1 + 1) - '0');
            int h2 = (*(ptr_t2 + 0) - '0') * 10 + (*(ptr_t2 + 1) - '0');
            int m1 = (*(ptr_t1 + 3) - '0') * 10 + (*(ptr_t1 + 4) - '0');
            int m2 = (*(ptr_t2 + 3) - '0') * 10 + (*(ptr_t2 + 4) - '0');

            bool swap = false;
            if (h1 > h2) 
                swap = true;
            else if (h1 == h2 && m1 > m2) 
                swap = true;

            if (swap)
            {
                int temp = *(ptr_indices + j);
                *(ptr_indices + j) = *(ptr_indices + j + 1);
                *(ptr_indices + j + 1) = temp;
            }
        }
    }

    std::cout << "Appointment ID | Patient Name | Time Slot | Status\n";
    std::cout << "----------------------------------------------------\n";

    // ptr_appoint is respectively storing the doctor's appointments of today
    for (int i = 0; i < count; i++)
    {
        Appointment* ptr_appoint = ptr_appts + *(ptr_indices + i);
        Patient* ptr_pat   = patients.find(ptr_appoint->get_patient_id());

        std::cout << ptr_appoint->get_id() << " | "
                  << (ptr_pat ? ptr_pat->get_name() : "Unknown") << " | "
                  << ptr_appoint->get_time() << " | "
                  << ptr_appoint->get_status() << "\n";
    }

    delete[] ptr_indices;
    ptr_indices = nullptr;
}

void HospitalSystem::mark_appointment_complete(Doctor& doctor)
{
    // DD-MM-YYYY + '\0' is stored in this static character array mate
    char today[11];
    get_today_date(today);

    // To show today's pending appointments
    // Poor doc still has work to do mate
    Appointment* ptr_appts = appointments.get_data();
    bool has_pending = false;

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_doctor_id() == doctor.get_id() &&
            is_char_arrays_equal((ptr_appts + i)->get_date(), today) &&
            is_char_arrays_equal((const char*)(ptr_appts + i)->get_status(), "pending"))
        {
            Patient* ptr_pat = patients.find((ptr_appts + i)->get_patient_id());
            std::cout << "ID: " << (ptr_appts + i)->get_id()
                      << " | Patient: " << (ptr_pat ? ptr_pat->get_name() : "Unknown")
                      << " | Time: " << (ptr_appts + i)->get_time() << "\n";
            has_pending = true;
        }
    }

    if (!has_pending)
    {
        std::cout << "No pending appointments for today.\n";
        return;
    }

    int appt_id;
    std::cout << "Enter Appointment ID: ";
    std::cin >> appt_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    Appointment* ptr_appt = appointments.find(appt_id);

    if (ptr_appt == nullptr ||
        ptr_appt->get_doctor_id() != doctor.get_id() ||
        !is_char_arrays_equal((const char*)ptr_appt->get_status(), "pending") ||
        !is_char_arrays_equal(ptr_appt->get_date(), today))
    {
        std::cout << "Invalid appointment ID.\n";
        return;
    }

    char completed[] = "completed";
    ptr_appt->set_appointment(ptr_appt->get_id(), ptr_appt->get_patient_id(),
                               ptr_appt->get_doctor_id(), ptr_appt->get_date(),
                               ptr_appt->get_time(), completed);

    FileHandler::update_appointments(appointments, "appointments.txt");
    std::cout << "Appointment marked as completed.\n";
}


void HospitalSystem::mark_appointment_no_show(Doctor& doctor)
{
    // DD-MM-YYYY + '\0' is stored in this static character array mate
    char today[11];
    get_today_date(today);

    Appointment* ptr_appts = appointments.get_data();
    bool has_pending = false;

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_doctor_id() == doctor.get_id() &&
            is_char_arrays_equal((ptr_appts + i)->get_date(), today) &&
            is_char_arrays_equal((const char*)(ptr_appts + i)->get_status(), "pending"))
        {
            Patient* ptr_pat = patients.find((ptr_appts + i)->get_patient_id());
            std::cout << "ID: " << (ptr_appts + i)->get_id()
                      << " | Patient: " << (ptr_pat ? ptr_pat->get_name() : "Unknown")
                      << " | Time: " << (ptr_appts + i)->get_time() << "\n";
            has_pending = true;
        }
    }

    if (!has_pending)
    {
        std::cout << "No pending appointments for today.\n";
        return;
    }

    int appointment_id;
    std::cout << "Enter Appointment ID: ";
    std::cin >> appointment_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    Appointment* ptr_appt = appointments.find(appointment_id);

    if (ptr_appt == nullptr ||
        ptr_appt->get_doctor_id() != doctor.get_id() ||
        !is_char_arrays_equal((const char*)ptr_appt->get_status(), "pending") ||
        !is_char_arrays_equal(ptr_appt->get_date(), today))
    {
        std::cout << "Invalid appointment ID.\n";
        return;
    }

    // Updaing the appointment to no-show
    char noshow[] = "no-show";
    ptr_appt->set_appointment(ptr_appt->get_id(), ptr_appt->get_patient_id(),
                               ptr_appt->get_doctor_id(), ptr_appt->get_date(),
                               ptr_appt->get_time(), noshow);

    FileHandler::update_appointments(appointments, "appointments.txt");

    // Cancelling the bill with no refund cause it is a bad hospital 
    //                                                               \ |
    //                                                               / |
    // I even added the angry emoji here if you can see it  
    Bill* ptr_bills = bills.get_data();
    char cancelled[] = "cancelled";

    for (int i = 0; i < bills.size(); i++)
    {
        if ((ptr_bills + i)->get_appointment_id() == appointment_id)
        {
            (ptr_bills + i)->set_bill((ptr_bills + i)->get_id(),
                                      (ptr_bills + i)->get_patient_id(),
                                      (ptr_bills + i)->get_appointment_id(),
                                      (ptr_bills + i)->get_amount(),
                                      cancelled,
                                      (ptr_bills + i)->get_date());
            break;
        }
    }

    // Updates it with the file handler and makrs it as no show
    FileHandler::update_bills(bills, "bills.txt");
    std::cout << "Appointment marked as no-show.\n";
}

void HospitalSystem::write_prescription(Doctor& doctor)
{
    int appointment_id;
    std::cout << "Enter Appointment ID: ";
    std::cin >> appointment_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    // Validating if it belongs to the docotr and is it already completed or not
    Appointment* ptr_appt = appointments.find(appointment_id);

    if (ptr_appt == nullptr ||
        ptr_appt->get_doctor_id() != doctor.get_id() ||
        !is_char_arrays_equal((const char*)ptr_appt->get_status(), "completed"))
    {
        std::cout << "Invalid appointment ID.\n";
        return;
    }

    // Checking if the prescription already exists in this appointment
    Prescription* ptr_prescriptions = prescriptions.get_data();

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if ((ptr_prescriptions + i)->get_appointment_id() == appointment_id)
        {
            std::cout << "Prescription already written for this appointment.\n";
            return;
        }
    }

    // Taking input medicines — max 499 chars cause TA said so :/ ( TA told us to truncate silently :/ )
    char* ptr_medicines = new char[500];
    std::cout << "Enter medicines (e.g. Paracetamol 500mg;Amoxicillin 250mg): ";
    std::cin.getline(ptr_medicines, 500);

    // Taking input notes — max 299 chars cause TA said so :/  ( TA also told us to truncate silently :/ )
    char* ptr_notes = new char[300];
    std::cout << "Enter notes (max 300 chars): ";
    std::cin.getline(ptr_notes, 300);

    // Get today's date for the prescription
    char today[11];
    get_today_date(today);

    int new_id = FileHandler::generate_new_id(prescriptions);

    Prescription new_prescription(new_id, appointment_id,
                                  ptr_appt->get_patient_id(),
                                  doctor.get_id(),
                                  today,
                                  ptr_medicines,
                                  ptr_notes);

    prescriptions.add(new_prescription);
    FileHandler::append_prescription(new_prescription, "prescriptions.txt");

    // The only reason we have this is because I can't believe I had to wake till 11:40 to debug things so it is better to display if it has been completed or not
    std::cout << "Prescription saved.\n";

    delete[] ptr_medicines;
    delete[] ptr_notes;
    ptr_medicines = nullptr;
    ptr_notes = nullptr;

}

void HospitalSystem::view_patient_history(Doctor& doctor)
{

    int patient_id;
    std::cout << "Enter Patient ID: ";
    std::cin >> patient_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    // Validating if the patient exists or not
    Patient* ptr_patient = patients.find(patient_id);
    if (ptr_patient == nullptr)
    {
        std::cout << "Access denied. You can only view records of your own patients.\n";
        return;
    }

    // Validating if the doctor has at least one completed appointment with this patient
    Appointment* ptr_appts = appointments.get_data();
    bool has_completed = false;

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_patient_id() == patient_id &&
            (ptr_appts + i)->get_doctor_id() == doctor.get_id() &&
            is_char_arrays_equal((const char*)(ptr_appts + i)->get_status(), "completed"))
        {
            has_completed = true;
            break;
        }
    }

    // It helps us to avoid doctor creeping up to the innoncent patients
    if (!has_completed)
    {
        std::cout << "Access denied. You can only view records of your own patients.\n";
        return;
    }

    // Collecting prescriptions for this patient by the doctor
    Prescription* ptr_prescriptions = prescriptions.get_data();
    int count = 0;

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if ((ptr_prescriptions + i)->get_patient_id() == patient_id &&
            (ptr_prescriptions + i)->get_doctor_id() == doctor.get_id())
        {
            count++;
        }
    }

    if (count == 0)
    {
        std::cout << "No medical records found for this patient.\n";
        return;
    }

    // Building an array to store the indexes
    int* ptr_indices = new int[count];
    int index = 0;

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if ((ptr_prescriptions + i)->get_patient_id() == patient_id &&
            (ptr_prescriptions + i)->get_doctor_id() == doctor.get_id())
        {
            *(ptr_indices + index) = i;
            index++;
        }
    }

    // Sorting by date by bubble_sort in descending order
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            char* ptr_d1 = (ptr_prescriptions + *(ptr_indices + j))->get_date();
            char* ptr_d2 = (ptr_prescriptions + *(ptr_indices + j + 1))->get_date();

            int year1  = (*(ptr_d1+6)-'0')*1000 + (*(ptr_d1+7)-'0')*100 + (*(ptr_d1+8)-'0')*10 + (*(ptr_d1+9)-'0');
            int year2  = (*(ptr_d2+6)-'0')*1000 + (*(ptr_d2+7)-'0')*100 + (*(ptr_d2+8)-'0')*10 + (*(ptr_d2+9)-'0');
            int month1 = (*(ptr_d1+3)-'0')*10 + (*(ptr_d1+4)-'0');
            int month2 = (*(ptr_d2+3)-'0')*10 + (*(ptr_d2+4)-'0');
            int day1   = (*(ptr_d1+0)-'0')*10 + (*(ptr_d1+1)-'0');
            int day2   = (*(ptr_d2+0)-'0')*10 + (*(ptr_d2+1)-'0');

            bool swap = false;
            if (year1 < year2)
                swap = true;
            else if (year1 == year2 && month1 < month2)
                swap = true;
            else if (year1 == year2 && month1 == month2 && day1 < day2)
                swap = true;

            if (swap)
            {
                int temp = *(ptr_indices + j);
                *(ptr_indices + j) = *(ptr_indices + j + 1);
                *(ptr_indices + j + 1) = temp;
            }
        }
    }

    std::cout << "Date | Medicines | Notes\n";
    std::cout << "-------------------------\n";

    for (int i = 0; i < count; i++)
    {
        Prescription* ptr_p = ptr_prescriptions + *(ptr_indices + i);
        std::cout << ptr_p->get_date() << " | "
                  << ptr_p->get_medicine() << " | "
                  << ptr_p->get_doctor_note() << "\n";
    }

    delete[] ptr_indices;
    ptr_indices = nullptr;
}


// -------------------------------------------------------------------------------------------------------------------

//                                      Admin's session functions

// --------------------------------------------------------------------------------------------------------------------

void HospitalSystem::add_doctor()
{
    doctor_signup();
}


void HospitalSystem::remove_doctor()
{
    // Displaying all the doctors so that the admin can remove the doctor
    Doctor* ptr_doctors = doctors.get_data();

    std::cout << "ID | Name | Specialization | Fee\n";
    std::cout << "-----------------------------------\n";

    for (int i = 0; i < doctors.size(); i++)
    {
        std::cout << (ptr_doctors + i)->get_id() << " | "
                  << (ptr_doctors + i)->get_name() << " | "
                  << (ptr_doctors + i)->get_specialization() << " | "
                  << (ptr_doctors + i)->get_fee() << "\n";
    }

    int doctor_id;
    std::cout << "Enter Doctor ID to remove: ";
    std::cin >> doctor_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    Doctor* ptr_doc = doctors.find(doctor_id);
    if (ptr_doc == nullptr)
    {
        std::cout << "Doctor not found.\n";
        return;
    }

    // Checking for pending appointments
    Appointment* ptr_appts = appointments.get_data();

    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_doctor_id() == doctor_id &&
            is_char_arrays_equal((const char*)(ptr_appts + i)->get_status(), "pending"))
        {
            std::cout << "Cannot remove doctor with pending appointments. Cancel or reassign them first.\n";
            return;
        }
    }

    doctors.remove(doctor_id);
    FileHandler::update_doctors(doctors, "doctors.txt");

    std::cout << "Doctor removed.\n";
}

void HospitalSystem::view_all_patients()
{
    Patient* ptr_patients = patients.get_data();
    Bill*    ptr_bills    = bills.get_data();

    std::cout << "ID | Name | Age | Gender | Contact | Balance | Unpaid Bills\n";
    std::cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < patients.size(); i++)
    {
        int unpaid_count = 0;

        for (int j = 0; j < bills.size(); j++)
        {
            if ((ptr_bills + j)->get_patient_id() == (ptr_patients + i)->get_id() &&
                is_char_arrays_equal((const char*)(ptr_bills + j)->get_status(), "unpaid"))
            {
                unpaid_count++;
            }
        }

        std::cout << (ptr_patients + i)->get_id()      << " | "
                  << (ptr_patients + i)->get_name()     << " | "
                  << (ptr_patients + i)->get_age()      << " | "
                  << (ptr_patients + i)->get_gender()   << " | "
                  << (ptr_patients + i)->get_contact()  << " | "
                  << (ptr_patients + i)->get_balance()  << " | "
                  << unpaid_count                        << "\n";
    }
}

void HospitalSystem::view_all_doctors()
{
    Doctor* ptr_doctors = doctors.get_data();

    std::cout << "ID | Name | Specialization | Contact | Fee \n";
    std::cout << "-------------------------------------------- \n";

    for (int i = 0; i < doctors.size(); i++)
    {
        std::cout << (ptr_doctors + i)->get_id()             << " | "
                  << (ptr_doctors + i)->get_name()            << " | "
                  << (ptr_doctors + i)->get_specialization()  << " | "
                  << (ptr_doctors + i)->get_contact()         << " | "
                  << (ptr_doctors + i)->get_fee()             << "\n";
    }
}

void HospitalSystem::view_all_appointments()
{
    int count = appointments.size();

    if (count == 0)
    {
        std::cout << "No appointments found.\n";
        return;
    }

    Appointment* ptr_appts = appointments.get_data();

    // Building the index array
    int* ptr_indices = new int[count];
    for (int i = 0; i < count; i++)
        *(ptr_indices + i) = i;

    // Sorring the appointments by date by bubble_sort by in descending_order
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            char* ptr_d1 = (ptr_appts + *(ptr_indices + j))->get_date();
            char* ptr_d2 = (ptr_appts + *(ptr_indices + j + 1))->get_date();

            int year1  = (*(ptr_d1+6)-'0')*1000+(*(ptr_d1+7)-'0')*100+(*(ptr_d1+8)-'0')*10+(*(ptr_d1+9)-'0');
            int year2  = (*(ptr_d2+6)-'0')*1000+(*(ptr_d2+7)-'0')*100+(*(ptr_d2+8)-'0')*10+(*(ptr_d2+9)-'0');
            int month1 = (*(ptr_d1+3)-'0')*10+(*(ptr_d1+4)-'0');
            int month2 = (*(ptr_d2+3)-'0')*10+(*(ptr_d2+4)-'0');
            int day1   = (*(ptr_d1+0)-'0')*10+(*(ptr_d1+1)-'0');
            int day2   = (*(ptr_d2+0)-'0')*10+(*(ptr_d2+1)-'0');

            bool swap = false;
            if (year1 < year2) 
                swap = true;
            else if (year1 == year2 && month1 < month2)
                swap = true;
            else if (year1 == year2 && month1 == month2 && day1 < day2)
                swap = true;

            if (swap)
            {
                int temp = *(ptr_indices + j);
                *(ptr_indices + j) = *(ptr_indices + j + 1);
                *(ptr_indices + j + 1) = temp;
            }
        }
    }

    std::cout << "ID | Patient Name | Doctor Name | Date | Time Slot | Status\n";
    std::cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        Appointment* ptr_a  = ptr_appts + *(ptr_indices + i);
        Patient*     ptr_p  = patients.find(ptr_a->get_patient_id());
        Doctor*      ptr_d  = doctors.find(ptr_a->get_doctor_id());

        std::cout << ptr_a->get_id()                          << " | "
                  << (ptr_p ? ptr_p->get_name() : "Unknown")  << " | "
                  << (ptr_d ? ptr_d->get_name() : "Unknown")  << " | "
                  << ptr_a->get_date()                         << " | "
                  << ptr_a->get_time()                         << " | "
                  << ptr_a->get_status()                       << "\n";
    }

    delete[] ptr_indices;
    ptr_indices = nullptr;
}

void HospitalSystem::view_unpaid_bills()
{
    Bill* ptr_bills = bills.get_data();
    bool found = false;

    // DD-MM-YYYY + '\0' is stored in this static character array mate
    char today[11];
    get_today_date(today);

    int today_day   = (today[0]-'0')*10 + (today[1]-'0');
    int today_month = (today[3]-'0')*10 + (today[4]-'0');
    int today_year  = (today[6]-'0')*1000+(today[7]-'0')*100+(today[8]-'0')*10+(today[9]-'0');

    std::cout << "Bill ID | Patient Name | Amount (PKR) | Date\n";
    std::cout << "----------------------------------------------\n";

    for (int i = 0; i < bills.size(); i++)
    {
        if (!is_char_arrays_equal((const char*)(ptr_bills + i)->get_status(), "unpaid"))
            continue;

        Patient* ptr_pat = patients.find((ptr_bills + i)->get_patient_id());
        char*    ptr_date = (ptr_bills + i)->get_date();

        // Parsing bill date
        int bill_day   = (*(ptr_date+0)-'0')*10+(*(ptr_date+1)-'0');
        int bill_month = (*(ptr_date+3)-'0')*10+(*(ptr_date+4)-'0');
        int bill_year  = (*(ptr_date+6)-'0')*1000+(*(ptr_date+7)-'0')*100
                        +(*(ptr_date+8)-'0')*10+(*(ptr_date+9)-'0');

        // Calculating rough day difference using difftime on mktime structs
        tm bill_tm = {};
        bill_tm.tm_mday = bill_day;
        bill_tm.tm_mon  = bill_month - 1;
        bill_tm.tm_year = bill_year - 1900;

        tm today_tm = {};
        today_tm.tm_mday = today_day;
        today_tm.tm_mon  = today_month - 1;
        today_tm.tm_year = today_year - 1900;

        time_t bill_time  = mktime(&bill_tm);
        time_t today_time = mktime(&today_tm);

        double diff_seconds = difftime(today_time, bill_time);
        double diff_days    = diff_seconds / 86400.0;

        std::cout << (ptr_bills + i)->get_id() << " | "
                  << (ptr_pat ? ptr_pat->get_name() : "Unknown") << " | "
                  << (ptr_bills + i)->get_amount() << " | "
                  << ptr_date;

        if (diff_days > 7.0)
            std::cout << " [OVERDUE]";

        std::cout << "\n";
        found = true;
    }

    if (!found)
        std::cout << "No unpaid bills.\n";
}

void HospitalSystem::discharge_patient()
{
    int patient_id;
    std::cout << "Enter Patient ID: ";
    std::cin >> patient_id;
    std::cin.ignore(CLEAR_BUFFER, '\n');

    Patient* ptr_patient = patients.find(patient_id);
    if (ptr_patient == nullptr)
    {
        std::cout << "Patient not found.\n";
        return;
    }

    // Checking for unpaid bills
    Bill* ptr_bills = bills.get_data();
    for (int i = 0; i < bills.size(); i++)
    {
        if ((ptr_bills + i)->get_patient_id() == patient_id &&
            is_char_arrays_equal((const char*)(ptr_bills + i)->get_status(), "unpaid"))
        {
            std::cout << "Cannot discharge patient with unpaid bills.\n";
            return;
        }
    }

    // Checking for pending appointments
    Appointment* ptr_appts = appointments.get_data();
    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_patient_id() == patient_id &&
            is_char_arrays_equal((const char*)(ptr_appts + i)->get_status(), "pending"))
        {
            std::cout << "Cannot discharge patient with pending appointments.\n";
            return;
        }
    }

    // Storing this to discharged.txt
    std::ofstream fout("discharged.txt", std::ios::app);
    
    if (!fout.is_open())
    {
        std::cout << "Error opening discharged.txt.\n";
        throw FileNotFoundException();
    }

    // Writing the patient's record
    fout << *ptr_patient << "\n";

    // Writing their appointments
    for (int i = 0; i < appointments.size(); i++)
    {
        if ((ptr_appts + i)->get_patient_id() == patient_id)
            fout << *(ptr_appts + i) << "\n";
    }

    // Writing their bills
    for (int i = 0; i < bills.size(); i++)
    {
        if ((ptr_bills + i)->get_patient_id() == patient_id)
            fout << *(ptr_bills + i) << "\n";
    }

    // Writing their prescriptions
    Prescription* ptr_prescriptions = prescriptions.get_data();
    for (int i = 0; i < prescriptions.size(); i++)
    {
        if ((ptr_prescriptions + i)->get_patient_id() == patient_id)
            fout << *(ptr_prescriptions + i) << "\n";
    }

    fout.close();

    // Removing from all the storages and updating the files

    patients.remove(patient_id);
    FileHandler::update_patients(patients, "patients.txt");

    // Removing appointments
    for (int i = appointments.size() - 1; i >= 0; i--)
    {
        if ((ptr_appts + i)->get_patient_id() == patient_id)
            appointments.remove((ptr_appts + i)->get_id());
    }
    FileHandler::update_appointments(appointments, "appointments.txt");

    // Removing bills
    for (int i = bills.size() - 1; i >= 0; i--)
    {
        if ((ptr_bills + i)->get_patient_id() == patient_id)
            bills.remove((ptr_bills + i)->get_id());
    }
    FileHandler::update_bills(bills, "bills.txt");

    // Removing prescriptions
    for (int i = prescriptions.size() - 1; i >= 0; i--)
    {
        if ((ptr_prescriptions + i)->get_patient_id() == patient_id)
            prescriptions.remove((ptr_prescriptions + i)->get_id());
    }
    FileHandler::update_prescriptions(prescriptions, "prescriptions.txt");

    std::cout << "Patient discharged and archived successfully.\n";
}


void HospitalSystem::view_security_log()
{
    std::ifstream fin("security_log.txt");
    if (!fin.is_open())
    {
        std::cout << "No security events logged.\n";
        throw FileNotFoundException();
    }

    FileHandler::read_security_log(fin);

    fin.close();
}

void HospitalSystem::generate_daily_report()
{
    // DD-MM-YYYY + '\0' is stored in this static character array mate
    char today[11];
    get_today_date(today);

    std::cout << "\n --------- Daily Report: " << today << " ---------- \n";

    // Appointment counts
    int total = 0, pending = 0, completed = 0, noshow = 0, cancelled = 0;
    Appointment* ptr_appts = appointments.get_data();

    for (int i = 0; i < appointments.size(); i++)
    {
        if (!is_char_arrays_equal((ptr_appts + i)->get_date(), today))
            continue;

        total++;
        char* ptr_status = (ptr_appts + i)->get_status();

        if      (is_char_arrays_equal((const char*)ptr_status, "pending"))
                    pending++;
        else if (is_char_arrays_equal((const char*)ptr_status, "completed")) 
                    completed++;
        else if (is_char_arrays_equal((const char*)ptr_status, "no-show"))  
                    noshow++;
        else if (is_char_arrays_equal((const char*)ptr_status, "cancelled"))
                    cancelled++;
    }

    std::cout << "Total appointments today: " << total
              << " (Pending: "   << pending
              << " Completed: "  << completed
              << " No-show: "    << noshow
              << " Cancelled: "  << cancelled << ")\n";

    // Calculating the revenue from paid bills today
    double revenue = 0.0;
    Bill* ptr_bills = bills.get_data();

    for (int i = 0; i < bills.size(); i++)
    {
        if (is_char_arrays_equal((const char*)(ptr_bills + i)->get_date(), today) &&
            is_char_arrays_equal((const char*)(ptr_bills + i)->get_status(), "paid"))
        {
            revenue += (ptr_bills + i)->get_amount();
        }
    }

    std::cout << "Revenue collected today (paid bills): PKR " << revenue << "\n";

    // Patients with outstanding unpaid bills
    std::cout << "\n Patients with unpaid bills: \n";
    std::cout << "Patient Name | Total Owed \n";
    std::cout << "---------------------------\n";

    Patient* ptr_patients = patients.get_data();
    bool any_unpaid = false;

    for (int i = 0; i < patients.size(); i++)
    {
        double total_owed = 0.0;
        int patient_id = (ptr_patients + i)->get_id();

        for (int j = 0; j < bills.size(); j++)
        {
            if ((ptr_bills + j)->get_patient_id() == patient_id &&
                is_char_arrays_equal((const char*)(ptr_bills + j)->get_status(), "unpaid"))
            {
                total_owed += (ptr_bills + j)->get_amount();
            }
        }

        if (total_owed > 0.0)
        {
            std::cout << (ptr_patients + i)->get_name() << " | PKR " << total_owed << "\n";
            any_unpaid = true;
        }
    }

    if (!any_unpaid)
        std::cout << "None.\n";

    // Doctor-wise summary for today
    std::cout << "\n Doctor-wise summary for today: \n";
    std::cout << "Doctor Name | Completed | Pending | No-show \n";
    std::cout << "---------------------------------------------\n";

    Doctor* ptr_doctors = doctors.get_data();

    for (int i = 0; i < doctors.size(); i++)
    {
        int doctor_id = (ptr_doctors + i)->get_id();
        int doc_completed = 0, doc_pending = 0, doc_noshow = 0;

        for (int j = 0; j < appointments.size(); j++)
        {
            if ((ptr_appts + j)->get_doctor_id() != doctor_id)
                continue;
            if (!is_char_arrays_equal((ptr_appts + j)->get_date(), today))
                continue;

            char* ptr_status = (ptr_appts + j)->get_status();
            if      (is_char_arrays_equal((const char*)ptr_status, "completed")) doc_completed++;
            else if (is_char_arrays_equal((const char*)ptr_status, "pending"))   doc_pending++;
            else if (is_char_arrays_equal((const char*)ptr_status, "no-show"))   doc_noshow++;
        }

        if (doc_completed + doc_pending + doc_noshow > 0)
        {
            std::cout << (ptr_doctors + i)->get_name() << " | "
                      << doc_completed << " | "
                      << doc_pending   << " | "
                      << doc_noshow    << "\n";
        }
    }
}
