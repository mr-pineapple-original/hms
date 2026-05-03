#include"file_handler.hpp"
#include"parser.hpp"
#include"char_array_functions.hpp"
#include"person.hpp"
#include"file_not_found_exception.hpp"

template<typename Entity>
void FileHandler::rewrite_file(const Storage<Entity>& entity, const char* ptr_file_name)
{
    // We had to do it to avoid multiple temp.txt named files
    const char* prefix = "temp_";
    char* ptr_temp_name = concatenate_char_array(prefix, ptr_file_name);
    std::ofstream fout(ptr_temp_name);

    if(!fout)
    {
        throw FileNotFoundException();
    }

    const Entity* ptr_entity = entity.get_data();

    for(int i = 0; i < entity.size(); i++)
    {
        fout << *(ptr_entity + i) << std::endl;
    }

    fout.close();

    remove(ptr_file_name);
    rename(ptr_temp_name, ptr_file_name);

    delete[] ptr_temp_name;
    ptr_temp_name = nullptr;
}

template<typename Entity>
int FileHandler::generate_new_id(const Storage<Entity>& entity)
{
    int max_id = 0;
    const Entity* ptr_entity = entity.get_data();

    for(int i = 0; i < entity.size(); i++)
    {
        if(max_id < (*(ptr_entity + i)).get_id())
        {
            max_id = (*(ptr_entity + i)).get_id();
        }
    }
    max_id = max_id + 1;
    return max_id;
}

// The reason we cant put the loaders in the template is because the constructors of admin, doctor, prescription etc require different parameters :/

void FileHandler::load_patients(Storage<Patient>& patients, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        throw FileNotFoundException();
    }

        while (true)
    {
        
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];

        int i = 0;
        char ch;

        // reading the line manually
        while (fin.get(ch) && ch != '\n')
        {
            if (i >= size - 1)
            {
                resize_array(ptr_line, size, size * 2);
                size *= 2;
            }

            *(ptr_line + i) = ch;
            i++;
        }

        if (i == 0 && fin.eof())
        {
            delete[] ptr_line;
            ptr_line = nullptr;
            break;
        }

        *(ptr_line + i) = '\0';


        // We are gonna parse it line by line using character arrays and no built in functions or anything cause FAST hates me :(
        int index = 0;

        int id;
        int age;
        float balance;

        char* ptr_name = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_gender = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_contact = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_password = new char[DEFAULT_SIZE_CHAR_ARRAY];

        Parser::parse_int(ptr_line, index, id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_name);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_int(ptr_line, index, age);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_gender);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_contact);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_password);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_float(ptr_line, index, balance);

        Patient obj(id, ptr_password, ptr_name, ptr_gender, age, ptr_contact, balance);;

        patients.add(obj);

        delete[] ptr_line;
        delete[] ptr_name;
        delete[] ptr_contact;
        delete[] ptr_password;

        ptr_line = nullptr;
        ptr_name = nullptr;
        ptr_contact = nullptr;
        ptr_password = nullptr;
    }

    fin.close();
}

void FileHandler::load_prescriptions(Storage<Prescription>& prescriptions, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);
    if (!fin) {
        throw FileNotFoundException();
    }

    while (true) {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];
        int i = 0; char ch;

        // read line manually
        while (fin.get(ch) && ch != '\n') {
            if (i >= size - 1) {
                resize_array(ptr_line, size, size * 2);
                size *= 2;
            }
            ptr_line[i++] = ch;
        }

        if (i == 0 && fin.eof()) {
            delete[] ptr_line;
            break;
        }
        ptr_line[i] = '\0';

        int index = 0;
        int prescription_id;
        int patient_id;
        int appointment_id;
        int doctor_id;

        char* ptr_date = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_medicine = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_note = new char[DEFAULT_SIZE_CHAR_ARRAY];

        Parser::parse_int(ptr_line, index, prescription_id); Parser::skip_comma(ptr_line, index);
        Parser::parse_int(ptr_line, index, appointment_id);  Parser::skip_comma(ptr_line, index);
        Parser::parse_int(ptr_line, index, patient_id);      Parser::skip_comma(ptr_line, index);
        Parser::parse_int(ptr_line, index, doctor_id);       Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_date);     Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_medicine); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_note);

        Prescription obj(prescription_id, appointment_id, patient_id, doctor_id,
                 ptr_date, ptr_medicine, ptr_note); 
                 
        prescriptions.add(obj);

        delete[] ptr_line;
        delete[] ptr_date;
        delete[] ptr_medicine;
        delete[] ptr_note;
    }

    fin.close();
}



void FileHandler::load_admins(Storage<Admin>& admins, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        throw FileNotFoundException();
    }

    while (true)
    {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];

        int i = 0;
        char ch;

        // reading the line manually
        while (fin.get(ch) && ch != '\n')
        {
            if (i >= size - 1)
            {
                resize_array(ptr_line, size, size * 2);
                size *= 2;
            }

            *(ptr_line + i) = ch;
            i++;
        }

        if (i == 0 && fin.eof())
        {
            delete[] ptr_line;
            break;
        }

        *(ptr_line + i) = '\0';


        // We are gonna parse it line by line using character arrays and no built in functions or anything cause FAST hates me :(
        int index = 0;

        int id;
        char* ptr_name = new char[DEFAULT_SIZE_CHAR_ARRAY];   // parsed but ignored cause the admin constructor does not require it
        char* ptr_password = new char[DEFAULT_SIZE_CHAR_ARRAY];

        Parser::parse_int(ptr_line, index, id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_name);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_password);

        Admin obj(id, ptr_password);
        admins.add(obj);


        delete[] ptr_line;
        delete[] ptr_name;
        delete[] ptr_password;

        ptr_line = nullptr;
        ptr_name = nullptr;
        ptr_password = nullptr;
    }

    fin.close();
}

void FileHandler::load_appointments(Storage<Appointment>& appointments, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        throw FileNotFoundException();
    }

    while (true)
    {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];

        int i = 0;
        char ch;

        // reading the line manually
        while (fin.get(ch) && ch != '\n')
        {
            if (i >= size - 1)
            {
                resize_array(ptr_line, size, size * 2);
                size *= 2;
            }

            *(ptr_line + i) = ch;
            i++;
        }

        if (i == 0 && fin.eof())
        {
            delete[] ptr_line;
            break;
        }

        *(ptr_line + i) = '\0';

        // We are gonna parse it line by line using character arrays and no built in functions or anything cause FAST hates me :(
        int index = 0;

        int appointment_id;
        int patient_id;
        int doctor_id;

        char* ptr_date = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_time = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_status = new char[DEFAULT_SIZE_CHAR_ARRAY];

        Parser::parse_int(ptr_line, index, appointment_id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_int(ptr_line, index, patient_id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_int(ptr_line, index, doctor_id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_date);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_time);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_status);


        Appointment obj(appointment_id, patient_id, doctor_id, ptr_date, ptr_time, ptr_status);

        appointments.add(obj);

        delete[] ptr_line;
        delete[] ptr_date;
        delete[] ptr_time;
        delete[] ptr_status;

        ptr_line = nullptr;
        ptr_date = nullptr;
        ptr_time = nullptr;
        ptr_status = nullptr;
    }

    fin.close();
}

void FileHandler::load_bills(Storage<Bill>& bills, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        throw FileNotFoundException();
    }

    while (true)
    {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];

        int i = 0;
        char ch;

        // reading the line manually
        while (fin.get(ch) && ch != '\n')
        {
            if (i >= size - 1)
            {
                resize_array(ptr_line, size, size * 2);
                size *= 2;
            }

            *(ptr_line + i) = ch;
            i++;
        }

        if (i == 0 && fin.eof())
        {
            delete[] ptr_line;
            ptr_line = nullptr;
            break;
        }

        *(ptr_line + i) = '\0';

        // We are gonna parse it line by line using character arrays and no built in functions or anything cause FAST hates me :(
        int index = 0;

        int bill_id;
        int patient_id;
        int appointment_id;
        double amount;

        char* ptr_status = nullptr;
        char* ptr_date = nullptr;

        Parser::parse_int(ptr_line, index, bill_id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_int(ptr_line, index, patient_id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_int(ptr_line, index, appointment_id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_double(ptr_line, index, amount);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_status);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_date);


        Bill obj(bill_id, patient_id, appointment_id, amount, ptr_status, ptr_date);

        bills.add(obj);

        delete[] ptr_line;
        delete[] ptr_status;
        delete[] ptr_date;

        ptr_line = nullptr;
        ptr_status = nullptr;
        ptr_date = nullptr;
    }

    fin.close();
}

void FileHandler::load_doctors(Storage<Doctor>& doctors, const char* ptr_file_name)
{
    std::ifstream fin(ptr_file_name);

    if (!fin)
    {
        throw FileNotFoundException();
    }

    while (true)
    {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];

        int i = 0;
        char ch;

        // manually reading the line
        while (fin.get(ch) && ch != '\n')
        {
            if (i >= size - 1)
            {
                resize_array(ptr_line, size, size * 2);
                size *= 2;
            }

            *(ptr_line + i) = ch;
            i++;
        }

        if (i == 0 && fin.eof())
        {
            delete[] ptr_line;
            ptr_line = nullptr;
            break;
        }

        *(ptr_line + i) = '\0';

        // We are gonna parse it line by line using character arrays and no built in functions or anything cause FAST hates me :(
        int index = 0;

        int id;
        double fee;

        char* ptr_name = nullptr;
        char* ptr_specialization = nullptr;
        char* ptr_contact = nullptr;
        char* ptr_password = nullptr;

        Parser::parse_int(ptr_line, index, id);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_name);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_specialization);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_contact);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_string(ptr_line, index, ptr_password);
        Parser::skip_comma(ptr_line, index);

        Parser::parse_double(ptr_line, index, fee);

        // Where the hell is this going on
        // For some reason we have gender and age stored in the class instances but we dont have them in the file
        // If I add them in my file my TA will cut marks :(
        const char* ptr_gender = male; // We should have 
        int default_age = 18;

        Doctor obj(id, ptr_password, ptr_name,ptr_gender, default_age, ptr_specialization, ptr_contact,fee);

        doctors.add(obj);

        delete[] ptr_line;
        delete[] ptr_name;
        delete[] ptr_specialization;
        delete[] ptr_contact;
        delete[] ptr_password;

        ptr_line = nullptr;
        ptr_name = nullptr;
        ptr_specialization = nullptr;
        ptr_contact = nullptr;
        ptr_password = nullptr;
    }

    fin.close();
}

// I think it could have been done with a template skull:emoji

void FileHandler::append_patient(const Patient& patient, const char* ptr_name)
{
    std::ofstream fout(ptr_name, std::ios::app);
    if(!fout)
    {
        throw FileNotFoundException();
    }

    fout << patient << std::endl;
    fout.close();
}

void FileHandler::append_admin(const Admin& admin, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        throw FileNotFoundException();
    }

    fout << admin << std::endl;

    fout.close();
}

void FileHandler::append_appointment(const Appointment& appointment, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        throw FileNotFoundException();
    }

    fout << appointment << std::endl;

    fout.close();
}

void FileHandler::append_bill(const Bill& bill, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        throw FileNotFoundException();
    }

    fout << bill << std::endl;

    fout.close();
}

void FileHandler::append_doctor(const Doctor& doctor, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        throw FileNotFoundException();
    }

    fout << doctor << std::endl;

    fout.close();
}

void FileHandler::append_prescription(const Prescription& prescription, const char* ptr_file_name)
{
    std::ofstream fout(ptr_file_name, std::ios::app);

    if (!fout)
    {
        throw FileNotFoundException();
    }

    fout << prescription << std::endl;

    fout.close();
}

// This could also have been done with templates skull:emoji

void FileHandler::update_admins(const Storage<Admin>& admins, const char* ptr_file_name)
{
    rewrite_file(admins, ptr_file_name);
}

void FileHandler::update_appointments(const Storage<Appointment>& appointments, const char* ptr_file_name)
{
    rewrite_file(appointments, ptr_file_name);
}

void FileHandler::update_bills(const Storage<Bill>& bills, const char* ptr_file_name)
{
    rewrite_file(bills, ptr_file_name);
}

void FileHandler::update_doctors(const Storage<Doctor>& doctors, const char* ptr_file_name)
{
    rewrite_file(doctors, ptr_file_name);
}

void FileHandler::update_prescriptions(const Storage<Prescription>& prescriptions, const char* ptr_file_name)
{
    rewrite_file(prescriptions, ptr_file_name);
}



// Validator Functions need to be checked
bool FileHandler::validate_patient(const char* id, const char* password, const char* ptr_file_name) {
    std::ifstream fin(ptr_file_name);
    
    if (!fin) 
        throw FileNotFoundException();

    while (true) 
    {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];
        int i = 0; 
        char ch;

        while (fin.get(ch) && ch != '\n')
         {
            if (i >= size - 1) 
            { 
                resize_array(ptr_line, size, size * 2); size *= 2;
            }
            ptr_line[i++] = ch;
        }

        if (i == 0 && fin.eof())
         { 
            delete[] ptr_line;
            ptr_line = nullptr; 
            break; 
        }
        ptr_line[i] = '\0';

        int index = 0;
        int file_id, age; float balance;
        char* ptr_name = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_gender = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_contact = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_password = new char[DEFAULT_SIZE_CHAR_ARRAY];

        Parser::parse_int(ptr_line, index, file_id); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_name); Parser::skip_comma(ptr_line, index);
        Parser::parse_int(ptr_line, index, age); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_gender); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_contact); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_password); Parser::skip_comma(ptr_line, index);
        Parser::parse_float(ptr_line, index, balance);

        // Convert file_id to char array manually
        char id_buf[16]; int temp = file_id, pos = 0;
        if (temp == 0) id_buf[pos++] = '0';
        else 
        {
            char digits[16]; int d = 0;
            while (temp > 0) { digits[d++] = '0' + (temp % 10); temp /= 10; }
            while (d > 0) { id_buf[pos++] = digits[--d]; }
        }
        id_buf[pos] = '\0';

        bool id_match = is_char_arrays_equal(id_buf, id);
        bool pw_match = is_char_arrays_equal(ptr_password, password);

        delete[] ptr_line; delete[] ptr_name; delete[] ptr_gender; delete[] ptr_contact; delete[] ptr_password;

        if (id_match && pw_match) return true;
    }
    return false;
}

bool FileHandler::validate_doctor(const char* id, const char* password, const char* ptr_file_name) {
    std::ifstream fin(ptr_file_name);
    if (!fin) throw FileNotFoundException();

    while (true) {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];
        int i = 0; char ch;

        while (fin.get(ch) && ch != '\n') {
            if (i >= size - 1) { resize_array(ptr_line, size, size * 2); size *= 2; }
            ptr_line[i++] = ch;
        }
        if (i == 0 && fin.eof()) { delete[] ptr_line; break; }
        ptr_line[i] = '\0';

        int index = 0;
        int file_id; double fee;
        char* ptr_name = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_specialization = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_contact = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_password = new char[DEFAULT_SIZE_CHAR_ARRAY];

        Parser::parse_int(ptr_line, index, file_id); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_name); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_specialization); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_contact); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_password); Parser::skip_comma(ptr_line, index);
        Parser::parse_double(ptr_line, index, fee);

        char id_buf[16]; int temp = file_id, pos = 0;
        if (temp == 0) id_buf[pos++] = '0';
        else {
            char digits[16]; int d = 0;
            while (temp > 0) { digits[d++] = '0' + (temp % 10); temp /= 10; }
            while (d > 0) { id_buf[pos++] = digits[--d]; }
        }
        id_buf[pos] = '\0';

        bool id_match = is_char_arrays_equal(id_buf, id);
        bool pw_match = is_char_arrays_equal(ptr_password, password);

        delete[] ptr_line; delete[] ptr_name; delete[] ptr_specialization; delete[] ptr_contact; delete[] ptr_password;

        if (id_match && pw_match) return true;
    }
    return false;
}

bool FileHandler::validate_admin(const char* id, const char* password, const char* ptr_file_name) {
    std::ifstream fin(ptr_file_name);
    if (!fin) throw FileNotFoundException();

    while (true) {
        int size = DEFAULT_SIZE_CHAR_ARRAY;
        char* ptr_line = new char[size];
        int i = 0; char ch;

        while (fin.get(ch) && ch != '\n') {
            if (i >= size - 1) { resize_array(ptr_line, size, size * 2); size *= 2; }
            ptr_line[i++] = ch;
        }
        if (i == 0 && fin.eof()) { delete[] ptr_line; break; }
        ptr_line[i] = '\0';

        int index = 0;
        int file_id;
        char* ptr_name = new char[DEFAULT_SIZE_CHAR_ARRAY];
        char* ptr_password = new char[DEFAULT_SIZE_CHAR_ARRAY];

        Parser::parse_int(ptr_line, index, file_id); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_name); Parser::skip_comma(ptr_line, index);
        Parser::parse_string(ptr_line, index, ptr_password);

        char id_buf[16]; int temp = file_id, pos = 0;
        if (temp == 0) id_buf[pos++] = '0';
        else {
            char digits[16]; int d = 0;
            while (temp > 0) { digits[d++] = '0' + (temp % 10); temp /= 10; }
            while (d > 0) { id_buf[pos++] = digits[--d]; }
        }
        id_buf[pos] = '\0';

        bool id_match = is_char_arrays_equal(id_buf, id);
        bool pw_match = is_char_arrays_equal(ptr_password, password);

        delete[] ptr_line; delete[] ptr_name; delete[] ptr_password;

        if (id_match && pw_match) return true;
    }
    return false;
}


void FileHandler::log_security_attempt(const char* role, int entered_id, const char* result)
{
    std::ofstream fout("security_log.txt", std::ios::app);

    if(!fout)
    {
        throw FileNotFoundException();
    }

    time_t now = time(0);
    tm* current = localtime(&now);

    fout << current->tm_mday << "-"
         << current->tm_mon + 1 << "-"
         << current->tm_year + 1900 << " "
         << current->tm_hour << ":"
         << current->tm_min << ":"
         << current->tm_sec << ","
         << role << ","
         << entered_id << ","
         << result << std::endl;

    fout.close();
}