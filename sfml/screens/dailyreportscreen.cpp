#include "dailyreportscreen.hpp"
#include "adminmenuscreen.hpp"

void DailyReportScreen::go_back()
{
    UIManager::instance().set_screen(new AdminMenuScreen());
}