#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"

class AdminMenuScreen;

// ── SecurityLogScreen ─────────────────────────────────────────────────────
// Reads and displays all entries from security_log.txt.
// Each entry is written by LoginDialog when an account gets locked (3 fails).
// Format in file: LOCKED,role=<role>,id=<id>
// ─────────────────────────────────────────────────────────────────────────
class SecurityLogScreen : public Screen
{
private:
    Label heading;
    Label divider;
    Label col_header;
    Label log_list;
    ColorLabel status_label;
    Button back_btn;

    void load()
    {
        // TODO: open security_log.txt with std::ifstream and read line by line
        // Parse each line: LOCKED,role=X,id=Y
        // Build display string with all entries
        // If file empty or not found → show "No security events recorded."
        col_header.set_text("Event    | Role    | ID");
        log_list.set_text("--------------------------------\n"
                          "(security log entries will load from security_log.txt)");
    }

public:
    SecurityLogScreen()
        : heading("Security Log"),
          divider("===================="),
          col_header(""),
          log_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        col_header.set_position(50, 80);
        log_list.set_position(50, 108);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);

        load();

        back_btn.set_on_click([this]()
                              { go_back(); });
    }

    void handle_event(sf::RenderWindow &window, const sf::Event &event) override
    {
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow &window) override
    {
        heading.render(window);
        divider.render(window);
        col_header.render(window);
        log_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }

    void go_back();
};
