#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "../components/userrole.hpp"

class LoginScreen; // forward declaration

class LoginDialog : public Screen {
private:
    UserRole role;
    Label heading;
    Label id_label;
    Label password_label;
    TextField id_field;
    TextField password_field;
    Button login_btn;
    Button back_btn;
public:
    int failed_attempts;
    LoginDialog(UserRole user_role);
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};
