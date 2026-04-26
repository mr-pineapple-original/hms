
// file_handler.cpp
#include "file_handler.hpp"
#include "parser.hpp"
// ======================================================
// PRIVATE TEMPLATE HELPER FUNCTION
// ======================================================

// Rewrites entire file safely using temp file replacement
template<typename Entity>
void FileHandler::rewrite_file(const Storage<Entity>& entity, const char* ptr_file_name)
{
    std::ofstream fout("temp.txt");

    if (!fout)
    {
        std::cout << "\nError creating temporary file.";
        return;
    }

    for (int i = 0; i < entity.size(); i++)
    {
        fout << entity.get_all()[i] << std::endl;
    }

    fout.close();

    remove(ptr_file_name);
    rename("temp.txt", ptr_file_name);
}

// ======================================================
// TEMPLATE FUNCTION FOR GENERATING NEW IDS
// ======================================================

template<typename Entity>
int FileHandler::generate_new_id(const Storage<Entity>& entity)
{
    int max_id = 0;

    for (int i = 0; i < entity.size(); i++)
    {
        if (entity.get_all()[i].get_id() > max_id)
        {
            max_id = entity.get_all()[i].get_id();
        }
    }

    return max_id + 1;
}

// ======================================================
// LOAD FUNCTIONS
// ======================================================

// Reads all patient records from file into storage

// Fixed in the real file
// Goated Riyal ???

// void FileHandler::load_patients(Storage<Patient>& patients, const char* file)
// {
//     std::ifstream fin(file);

//     if (!fin)
//     {
//         std::cout << "Error opening file\n";
//         return;
//     }

//     char line[500];

//     while (fin.getline(line, 500))
//     {
//         int i = 0;

//         int id;
//         char name[50];
//         int age;
//         char* ptr_gender;
//         char contact[20];
//         char password[50];
//         float balance;

//         Parser::parse_int(line, i, id);
//         Parser::skip_comma(line, i);

//         Parser::parse_string(line, i, name);
//         Parser::skip_comma(line, i);

//         Parser::parse_int(line, i, age);
//         Parser::skip_comma(line, i);

//         Parser::parse_string(line, i, ptr_gender);
//         Parser::skip_comma(line, i);

//         Parser::parse_string(line, i, contact);
//         Parser::skip_comma(line, i);

//         Parser::parse_string(line, i, password);
//         Parser::skip_comma(line, i);

//         Parser::parse_float(line, i, balance);

//         Patient p(id, name, age, ptr_gender, contact, password, balance);
//         patients.add(p);
//     }

//     fin.close();
// }

// Reads all admin records
void FileHandler::load_admins(Storage<Admin>& admins, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        std::cout << "\nError opening admins file.";
        return;
    }

    fin.close();
}

// Reads all appointments
void FileHandler::load_appointments(Storage<Appointment>& appointments, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        std::cout << "\nError opening appointments file.";
        return;
    }

    fin.close();
}

// Reads all bills
void FileHandler::load_bills(Storage<Bill>& bills, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        std::cout << "\nError opening bills file.";
        return;
    }

    fin.close();
}

// Reads all doctors
void FileHandler::load_doctors(Storage<Doctor>& doctors, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        std::cout << "\nError opening doctors file.";
        return;
    }

    fin.close();
}

// Reads all prescriptions
void FileHandler::load_prescriptions(Storage<Prescription>& prescriptions, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        std::cout << "\nError opening prescriptions file.";
        return;
    }

    fin.close();
}

// ======================================================
// APPEND FUNCTIONS
// ======================================================

// Adds one patient to file
void FileHandler::append_patient(const Patient& patient, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        std::cout << "\nError appending patient.";
        return;
    }

    fout << patient << std::endl;

    fout.close();
}

// Adds one admin
void FileHandler::append_admin(const Admin& admin, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        std::cout << "\nError appending admin.";
        return;
    }

    fout << admin << std::endl;

    fout.close();
}

// Adds one appointment
void FileHandler::append_appointment(const Appointment& appointment, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        std::cout << "\nError appending appointment.";
        return;
    }

    fout << appointment << std::endl;

    fout.close();
}

// Adds one bill
void FileHandler::append_bill(const Bill& bill, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        std::cout << "\nError appending bill.";
        return;
    }

    fout << bill << std::endl;

    fout.close();
}

// Adds one doctor
void FileHandler::append_doctor(const Doctor& doctor, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        std::cout << "\nError appending doctor.";
        return;
    }

    fout << doctor << std::endl;

    fout.close();
}

// Adds one prescription
void FileHandler::append_prescription(const Prescription& prescription, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        std::cout << "\nError appending prescription.";
        return;
    }

    fout << prescription << std::endl;

    fout.close();
}

// ======================================================
// UPDATE FUNCTIONS
// ======================================================

// Rewrites patients file
void FileHandler::update_patients(const Storage<Patient>& patients, const char* ptr_file_name)
{
    rewrite_file(patients, ptr_file_name);
}

// Rewrites admins file
void FileHandler::update_admins(const Storage<Admin>& admins, const char* ptr_file_name)
{
    rewrite_file(admins, ptr_file_name);
}

// Rewrites appointments file
void FileHandler::update_appointments(const Storage<Appointment>& appointments, const char* ptr_file_name)
{
    rewrite_file(appointments, ptr_file_name);
}

// Rewrites bills file
void FileHandler::update_bills(const Storage<Bill>& bills, const char* ptr_file_name)
{
    rewrite_file(bills, ptr_file_name);
}

// Rewrites doctors file
void FileHandler::update_doctors(const Storage<Doctor>& doctors, const char* ptr_file_name)
{
    rewrite_file(doctors, ptr_file_name);
}

// Rewrites prescriptions file
void FileHandler::update_prescriptions(const Storage<Prescription>& prescriptions, const char* ptr_file_name)
{
    rewrite_file(prescriptions, ptr_file_name);
}
