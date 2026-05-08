#include "dischargepatientscreen.hpp"
#include "adminmenuscreen.hpp"

void DischargePatientScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}
