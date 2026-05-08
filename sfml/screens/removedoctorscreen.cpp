#include "removedoctorscreen.hpp"
#include "adminmenuscreen.hpp"

void RemoveDoctorScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}