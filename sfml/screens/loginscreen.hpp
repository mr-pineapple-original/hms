#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/button.hpp"
#include <iostream>

class LoginScreen : public Screen {
private:
    Label heading;
    Label label;
    Button patient_btn;
    Button doctor_btn;
    Button admin_btn;
    Button exit_btn;

public:
    LoginScreen()
        : heading("Medicore (HMS)"),
        label("Login as: "),
        patient_btn("1. Patient"),
        doctor_btn("2. Doctor"),
        admin_btn("3. Admin"),
        exit_btn("4. Exit")
    {
        heading.set_position(50, 50);
        label.set_position(100, 100);

        patient_btn.set_position(150, 150);
        doctor_btn.set_position(150, 200);
        admin_btn.set_position(150, 250);
        exit_btn.set_position(150, 300);

        patient_btn.set_on_click([]() {
            std::cout << "Login as Patient\n";
        });

        doctor_btn.set_on_click([]() {
            std::cout << "Login as Doctor\n";
        });

        admin_btn.set_on_click([]() {
            std::cout << "Login as Admin\n";
        });

        exit_btn.set_on_click([this]() {
            std::cout << "Exit pressed\n";
            should_close = true;
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        patient_btn.handle_event(event, window);
        doctor_btn.handle_event(event, window);
        admin_btn.handle_event(event, window);
        exit_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        label.render(window);
        heading.render(window);
        patient_btn.render(window);
        doctor_btn.render(window);
        admin_btn.render(window);
        exit_btn.render(window);
    }
};
