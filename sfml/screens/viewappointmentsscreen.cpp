#include "viewappointmentsscreen.hpp"
#include "adminmenuscreen.hpp"

void ViewAppointmentsScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}