#include "viewpatientsscreen.hpp"
#include "adminmenuscreen.hpp"

void ViewPatientsScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}