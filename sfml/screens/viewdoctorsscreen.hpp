// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"

// class AdminMenuScreen;

// // ── ViewDoctorsScreen ─────────────────────────────────────────────────────
// // Loads and displays all doctors from doctors.txt.
// // ─────────────────────────────────────────────────────────────────────────
// class ViewDoctorsScreen : public Screen
// {
// private:
//     Label heading;
//     Label divider;
//     Label col_header;
//     Label doctor_list;
//     ColorLabel status_label;
//     Button back_btn;

//     void load()
//     {
//         // TODO: FileHandler::get_all_doctors("doctors.txt", arr, count)
//         // Build display: ID | Name | Specialization | Fee | Contact
//         col_header.set_text("ID  | Name            | Specialization  | Fee (PKR) | Contact");
//         doctor_list.set_text("-------------------------------------------------------------------\n"
//                              "(doctor records will load from backend)");
//     }

// public:
//     ViewDoctorsScreen()
//         : heading("All Doctors"),
//           divider("===================="),
//           col_header(""),
//           doctor_list(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         col_header.set_position(50, 80);
//         doctor_list.set_position(50, 108);
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
//         doctor_list.render(window);
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

class ViewDoctorsScreen : public Screen {
private:
    Label heading, divider, col_header, doctor_list;
    ColorLabel status_label;
    Button back_btn;

    static int write_str(char* buf, int pos, const char* s) {
        for (int i = 0; s[i]; i++) buf[pos++] = s[i];
        return pos;
    }
    static int write_int(char* buf, int pos, int val) {
        char tmp[32]; int_to_char(val, tmp);
        return write_str(buf, pos, tmp);
    }

    void load() {
        Doctor* ptr_d = HospitalSystem::instance().get_doctors().get_data();
        int doc_count = HospitalSystem::instance().get_doctors().size();

        if (doc_count == 0) { doctor_list.set_text("No doctors registered."); return; }

        static char buf[4096]; int pos = 0;
        for (int i = 0; i < doc_count; i++) {
            char fee_buf[32]; double_to_char((ptr_d + i)->get_fee(), fee_buf);
            pos = write_int(buf, pos, (ptr_d + i)->get_id());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_d + i)->get_name());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_d + i)->get_specialization());
            pos = write_str(buf, pos, " | PKR ");
            pos = write_str(buf, pos, fee_buf);
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_d + i)->get_contact());
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';
        doctor_list.set_text(buf);
    }

public:
    ViewDoctorsScreen()
        : heading("All Doctors"), divider("===================="),
          col_header("ID  | Name            | Specialization  | Fee (PKR) | Contact"),
          doctor_list(""), status_label(""), back_btn("Back", 100, 40)
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        col_header.set_position(50, 80);
        doctor_list.set_position(50, 108);
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
        col_header.render(window); doctor_list.render(window);
        status_label.render(window); back_btn.render(window);
    }
    void go_back();
};