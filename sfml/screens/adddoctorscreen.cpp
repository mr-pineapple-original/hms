#include "adddoctorscreen.hpp"
#include "adminmenuscreen.hpp"

void AddDoctorScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}