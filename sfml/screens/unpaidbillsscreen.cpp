#include "unpaidbillsscreen.hpp"
#include "adminmenuscreen.hpp"

void UnpaidBillsScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}