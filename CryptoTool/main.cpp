#include <iostream>
using namespace std;
class Menu{
public:
    static void menu();
    static void handle();
};
int main() {
    Menu::menu();
    Menu::handle();
    return 0;
}