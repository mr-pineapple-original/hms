#include "securitylogscreen.hpp"
#include "adminmenuscreen.hpp"

void SecurityLogScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}