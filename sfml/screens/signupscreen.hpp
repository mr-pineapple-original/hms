// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"

// // ── SignupScreen ──────────────────────────────────────────────────────────
// // Patient self-registration.
// // TODO: connect FileHandler::append_patient() and Validator when ready.
// // ─────────────────────────────────────────────────────────────────────────
// class SignupScreen : public Screen {
// private:
//     Label      heading;
//     Label      divider;

//     Label      name_label;       TextField name_field;
//     Label      age_label;        TextField age_field;
//     Label      gender_label;     TextField gender_field;    // M or F
//     Label      contact_label;    TextField contact_field;   // 11 digits
//     Label      pass_label;       TextField pass_field;      // min 6 chars

//     Button     signup_btn;
//     Button     back_btn;
//     ColorLabel status_label;

// public:
//     SignupScreen()
//         : heading("Patient Signup"),
//           divider("===================="),
//           name_label("Name:"),
//           age_label("Age:"),
//           gender_label("Gender (M/F):"),
//           contact_label("Contact (11 digits):"),
//           pass_label("Password: "),
//           signup_btn("Create Account", 180, 40),
//           back_btn("Back", 100, 40),
//           status_label("")
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);

//         float lx = 50, fx = 280, y = 90, step = 60;
//         name_label.set_position   (lx, y);  name_field.set_position   (fx, y - 8);  y += step;
//         age_label.set_position    (lx, y);  age_field.set_position    (fx, y - 8);  y += step;
//         gender_label.set_position (lx, y);  gender_field.set_position (fx, y - 8);  y += step;
//         contact_label.set_position(lx, y);  contact_field.set_position(fx, y - 8);  y += step;
//         pass_label.set_position   (lx, y);  pass_field.set_position   (fx, y - 8);  y += step;

//         signup_btn.set_position(160, y + 10);
//         back_btn.set_position  (360, y + 10);
//         status_label.set_position(50, y + 70);

//         signup_btn.set_on_click([this]() {
//             if (name_field.get_text().isEmpty()    || age_field.get_text().isEmpty()    ||
//                 gender_field.get_text().isEmpty()  || contact_field.get_text().isEmpty() ||
//                 pass_field.get_text().isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("All fields are required.");
//                 return;
//             }
//             // TODO: Validator::validate_contact(contact_buf)  → 11 digits
//             // TODO: Validator::validate_password(pass_buf)    → min 6 chars
//             // TODO: Validator::validate_age(age_buf)          → positive int
//             // TODO: Validator::validate_gender(gender_buf)    → 'M' or 'F'
//             // TODO: generate new patient ID (read max ID from patients.txt, +1)
//             // TODO: FileHandler::append_patient(id, name, age, gender, contact, password,
//             //                                   balance=0, "patients.txt")
//             status_label.set_color(sf::Color::Green);
//             status_label.set_text("Account created successfully! Please login. (stub)");
//             name_field.clear(); age_field.clear(); gender_field.clear();
//             contact_field.clear(); pass_field.clear();
//         });

//         back_btn.set_on_click([this]() {
//             UIManager::instance().set_screen(new LoginDialog(PATIENT));
//         });
//     }

//     void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
//         name_field.handle_event   (event, window);
//         age_field.handle_event    (event, window);
//         gender_field.handle_event (event, window);
//         contact_field.handle_event(event, window);
//         pass_field.handle_event   (event, window);
//         signup_btn.handle_event   (event, window);
//         back_btn.handle_event     (event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow& window) override {
//         heading.render(window);
//         divider.render(window);
//         name_label.render(window);    name_field.render(window);
//         age_label.render(window);     age_field.render(window);
//         gender_label.render(window);  gender_field.render(window);
//         contact_label.render(window); contact_field.render(window);
//         pass_label.render(window);    pass_field.render(window);
//         signup_btn.render(window);
//         back_btn.render(window);
//         status_label.render(window);
//     }
// };


#pragma once
#include "screen.hpp"
#include "logindialog.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "../components/sf_string_utils.hpp"
#include "../components/userrole.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/file_handler.hpp"
#include "../../src/validator.hpp"
#include "../../src/patient.hpp"
#include "../../src/char_array_functions.hpp"

class SignupScreen : public Screen {
private:
    Label      heading;
    Label      divider;

    Label      name_label;      TextField  name_field;
    Label      age_label;       TextField  age_field;
    Label      gender_label;    TextField  gender_field;
    Label      contact_label;   TextField  contact_field;
    Label      pass_label;      TextField  pass_field;

    Button     signup_btn;
    Button     back_btn;
    ColorLabel status_label;

public:
    SignupScreen()
        : heading("Patient Signup"),
          divider("===================="),
          name_label("Name:"),
          age_label("Age:"),
          gender_label("Gender (M/F):"),
          contact_label("Contact (11 digits):"),
          pass_label("Password:"),
          signup_btn("Create Account", 180, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);

        float lx = 50, fx = 280, y = 90, step = 60;
        name_label.set_position   (lx, y);  name_field.set_position   (fx, y - 8);  y += step;
        age_label.set_position    (lx, y);  age_field.set_position    (fx, y - 8);  y += step;
        gender_label.set_position (lx, y);  gender_field.set_position (fx, y - 8);  y += step;
        contact_label.set_position(lx, y);  contact_field.set_position(fx, y - 8);  y += step;
        pass_label.set_position   (lx, y);  pass_field.set_position   (fx, y - 8);  y += step;

        signup_btn.set_position  (160, y + 10);
        back_btn.set_position    (360, y + 10);
        status_label.set_position(50,  y + 70);

        signup_btn.set_on_click([this]() {

            // ── Step 1: check no field is empty ───────────────────────────
            if (name_field.get_text().isEmpty()    ||
                age_field.get_text().isEmpty()     ||
                gender_field.get_text().isEmpty()  ||
                contact_field.get_text().isEmpty() ||
                pass_field.get_text().isEmpty())
            {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("All fields are required.");
                return;
            }

            // ── Step 2: convert sf::String to char buffers ────────────────
            char name_buf[64];
            char age_buf[8];
            char gender_buf[4];
            char contact_buf[16];
            char pass_buf[64];

            sf_string_to_char(name_field.get_text(),    name_buf,    sizeof(name_buf));
            sf_string_to_char(age_field.get_text(),     age_buf,     sizeof(age_buf));
            sf_string_to_char(gender_field.get_text(),  gender_buf,  sizeof(gender_buf));
            sf_string_to_char(contact_field.get_text(), contact_buf, sizeof(contact_buf));
            sf_string_to_char(pass_field.get_text(),    pass_buf,    sizeof(pass_buf));

            // ── Step 3: validate contact via backend Validator ────────────
            try { Validator::validate_contact(contact_buf); }
            catch (...)
            {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Contact must be 11 digits starting with 03.");
                return;
            }

            // ── Step 4: validate gender ───────────────────────────────────
            if ((gender_buf[0] != 'M' && gender_buf[0] != 'm' &&
                 gender_buf[0] != 'F' && gender_buf[0] != 'f') ||
                 gender_buf[1] != '\0')
            {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Gender must be M or F only.");
                return;
            }

            // ── Step 5: parse and validate age ────────────────────────────
            int age = 0;
            bool age_valid = true;

            for (int i = 0; age_buf[i] != '\0'; i++)
            {
                if (age_buf[i] < '0' || age_buf[i] > '9')
                {
                    age_valid = false;
                    break;
                }
                age = age * 10 + (age_buf[i] - '0');
            }

            if (!age_valid || age <= 0 || age > 120)
            {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Age must be a number between 1 and 120.");
                return;
            }

            // ── Step 6: validate positive float via backend Validator ─────
            try { Validator::validate_positive_float((float)age); }
            catch (...)
            {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Invalid age.");
                return;
            }

            // ── Step 7: set gender string ─────────────────────────────────
            const char* ptr_gender = (gender_buf[0] == 'M' || gender_buf[0] == 'm')
                                     ? "Male" : "Female";

            // ── Step 8: create patient and save via backend ───────────────
            try
            {
                int new_id = FileHandler::generate_new_id(
                                 HospitalSystem::instance().get_patients());

                Patient new_patient(new_id, pass_buf, name_buf,
                                    ptr_gender, age, contact_buf, 0.0);

                HospitalSystem::instance().get_patients().add(new_patient);
                FileHandler::append_patient(new_patient, "patients.txt");

                // Build success message with assigned ID
                char success_msg[80];
                const char* prefix = "Account created! Your ID is: ";
                int pos = 0;
                for (int i = 0; prefix[i] != '\0'; i++)
                    success_msg[pos++] = prefix[i];
                char id_buf[16];
                int_to_char(new_id, id_buf);
                for (int i = 0; id_buf[i] != '\0'; i++)
                    success_msg[pos++] = id_buf[i];
                success_msg[pos] = '\0';

                status_label.set_color(sf::Color::Green);
                status_label.set_text(success_msg);

                // Clear all fields after success
                name_field.clear();
                age_field.clear();
                gender_field.clear();
                contact_field.clear();
                pass_field.clear();
            }
            catch (...)
            {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Something went wrong. Please try again.");
            }
        });

        // ── Back button ───────────────────────────────────────────────────
        back_btn.set_on_click([this]() {
            UIManager::instance().set_screen(new LoginDialog(PATIENT));
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        name_field.handle_event   (event, window);
        age_field.handle_event    (event, window);
        gender_field.handle_event (event, window);
        contact_field.handle_event(event, window);
        pass_field.handle_event   (event, window);
        signup_btn.handle_event   (event, window);
        back_btn.handle_event     (event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        name_label.render(window);    name_field.render(window);
        age_label.render(window);     age_field.render(window);
        gender_label.render(window);  gender_field.render(window);
        contact_label.render(window); contact_field.render(window);
        pass_label.render(window);    pass_field.render(window);
        signup_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};