#include "viewdoctorsscreen.hpp"
#include "adminmenuscreen.hpp"

void ViewDoctorsScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}