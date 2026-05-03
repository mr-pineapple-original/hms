#pragma once
#include <SFML/Graphics.hpp>
#include "../screens/screen.hpp"
#include <stdexcept>

class UIManager {
private:
    static UIManager* s_instance;
    sf::Font font;
    Screen* m_ptr_current_screen;

    UIManager(); 

public:
    static UIManager& instance();

    sf::Font& get_font();

    void set_screen(Screen* ptr_screen);
    Screen* get_screen();

    void handle_event(sf::RenderWindow& window, const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);

    ~UIManager();
};
