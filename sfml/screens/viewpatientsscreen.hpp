// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"

// // ── ViewPatientsScreen ────────────────────────────────────────────────────
// // Loads and displays all patients from patients.txt.
// // ─────────────────────────────────────────────────────────────────────────
// class ViewPatientsScreen : public Screen
// {
// private:
//     Label heading;
//     Label divider;
//     Label col_header;
//     Label patient_list;
//     ColorLabel status_label;
//     Button back_btn;

//     void load()
//     {
//         // TODO: FileHandler::get_all_patients("patients.txt", arr, count)
//         // Build display: ID | Name | Age | Gender | Contact | Balance
//         col_header.set_text("ID  | Name            | Age | Gender | Contact     | Balance (PKR)");
//         patient_list.set_text("--------------------------------------------------------------------\n"
//                               "(patient records will load from backend)");
//     }

// public:
//     ViewPatientsScreen()
//         : heading("All Patients"),
//           divider("===================="),
//           col_header(""),
//           patient_list(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         col_header.set_position(50, 80);
//         patient_list.set_position(50, 108);
//         status_label.set_position(50, 500);
//         back_btn.set_position(50, 540);

//         load();

//         back_btn.set_on_click([this]()
//                               { go_back(); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         divider.render(window);
//         col_header.render(window);
//         patient_list.render(window);
//         status_label.render(window);
//         back_btn.render(window);
//     }

//     void go_back();
// };


#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
#include "../../src/hospital_system.hpp"
#include "../components/sf_string_utils.hpp"

class ViewPatientsScreen : public Screen {
private:
    Label heading, divider, col_header, patient_list;
    ColorLabel status_label;
    Button back_btn;

    static bool str_eq(const char* a, const char* b) {
        int i = 0;
        while (a[i] && b[i]) { if (a[i] != b[i]) return false; i++; }
        return a[i] == '\0' && b[i] == '\0';
    }

    static int write_str(char* buf, int pos, const char* s) {
        for (int i = 0; s[i]; i++) buf[pos++] = s[i];
        return pos;
    }

    static int write_int(char* buf, int pos, int val) {
        char tmp[32]; int_to_char(val, tmp);
        return write_str(buf, pos, tmp);
    }

    void load() {
        Patient* ptr_p  = HospitalSystem::instance().get_patients().get_data();
        Bill*    ptr_b  = HospitalSystem::instance().get_bills().get_data();
        int pat_count   = HospitalSystem::instance().get_patients().size();
        int bill_count  = HospitalSystem::instance().get_bills().size();

        if (pat_count == 0) { patient_list.set_text("No patients registered."); return; }

        static char buf[4096]; int pos = 0;
        for (int i = 0; i < pat_count; i++) {
            int unpaid = 0;
            for (int j = 0; j < bill_count; j++) {
                if ((ptr_b + j)->get_patient_id() == (ptr_p + i)->get_id() &&
                    str_eq((const char*)(ptr_b + j)->get_status(), "unpaid"))
                    unpaid++;
            }
            pos = write_int(buf, pos, (ptr_p + i)->get_id());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_p + i)->get_name());
            pos = write_str(buf, pos, " | ");
            pos = write_int(buf, pos, (ptr_p + i)->get_age());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_p + i)->get_gender());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_p + i)->get_contact());
            pos = write_str(buf, pos, " | PKR ");
            // Use double_to_char for balance
            char bal_buf[32]; double_to_char((ptr_p + i)->get_balance(), bal_buf);
            pos = write_str(buf, pos, bal_buf);
            pos = write_str(buf, pos, " | Unpaid: ");
            pos = write_int(buf, pos, unpaid);
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';
        patient_list.set_text(buf);
    }

public:
    ViewPatientsScreen()
        : heading("All Patients"), divider("===================="),
          col_header("ID  | Name            | Age | Gender | Contact     | Balance (PKR) | Unpaid Bills"),
          patient_list(""), status_label(""), back_btn("Back", 100, 40)
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        col_header.set_position(50, 80);
        patient_list.set_position(50, 108);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);
        load();
        back_btn.set_on_click([this]() { go_back(); });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window); divider.render(window);
        col_header.render(window); patient_list.render(window);
        status_label.render(window); back_btn.render(window);
    }
    void go_back();
};