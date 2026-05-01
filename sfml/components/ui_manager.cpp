#include "ui_manager.hpp"

UIManager* UIManager::s_instance = nullptr;

UIManager::UIManager() {
    m_ptr_current_screen = nullptr;
    if (!font.openFromFile("assets/fonts/jetbrains.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

UIManager& UIManager::instance() {
    if (s_instance == nullptr) {
        s_instance = new UIManager();
    }
    return *s_instance;
}

sf::Font& UIManager::get_font() {
    return font;
}

void UIManager::set_screen(Screen* ptr_screen) {
    if (m_ptr_current_screen != nullptr) {
        delete m_ptr_current_screen;
    }
    m_ptr_current_screen = ptr_screen;
}

Screen* UIManager::get_screen() {
    return m_ptr_current_screen;
}

void UIManager::handle_event(sf::RenderWindow& window, const sf::Event& event) {
    if (m_ptr_current_screen != nullptr) {
        m_ptr_current_screen->handle_event(window, event);
    }
}

void UIManager::update() {
    if (m_ptr_current_screen != nullptr) {
        m_ptr_current_screen->update();
    }
}

void UIManager::render(sf::RenderWindow& window) {
    if (m_ptr_current_screen != nullptr) {
        m_ptr_current_screen->render(window);
    }
}

UIManager::~UIManager() {
    delete m_ptr_current_screen;
    m_ptr_current_screen = nullptr;
}
