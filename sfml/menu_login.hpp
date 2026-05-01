// menu_login.hpp
#pragma once
#include "screen_base.hpp"
#include "../src/admin.hpp"
#include "../src/patient.hpp"
#include "../src/doctor.hpp"
#include "gui_manager.hpp"

class LoginMenu : public ScreenBase {
private:
    sf::Font font;
    sf::Text title, rolePrompt, idPrompt, passPrompt, errorMsg;
    sf::RectangleShape inputBox;
    char userInput[50];
    int inputMode; // 0=role, 1=id, 2=password
    int selectedRole;
    bool idEntered, passwordEntered;

public:
    LoginMenu();
    void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};

if(role == 3) {
    for(int i=0; i<admins.size(); ++i)
       if(admins.get_data()[i].authenticate(id, pwd)) 
          // Switch to Admin screen
}
