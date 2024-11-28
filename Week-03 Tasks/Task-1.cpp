#include <iostream>
#include <vector>
#include <string>
using namespace std;
class MenuItem {
public:
    string name;
    vector<MenuItem*> subMenu;

    MenuItem(const string& name) : name(name) {}

    void addSubItem(MenuItem* item) {
        subMenu.push_back(item);
    }
};

class Menu {
private:
    MenuItem* currentMenu;
    MenuItem* rootMenu;
    vector<MenuItem*> menuStack;
    int currentSelection;

public:
    Menu(MenuItem* root) : rootMenu(root), currentMenu(root), currentSelection(0) {}

    void displayMenu() {
        cout <<"\n -- " << currentMenu->name << " --" <<endl;
        for (int i = 0; i < currentMenu->subMenu.size(); ++i) {
            if (i == currentSelection)
                cout << "-> ";
            else
                cout << "  ";
            cout << currentMenu->subMenu[i]->name << endl;
        }
        cout << "0: Exit 1: Down  2: Up  3: Enter  4: Back" <<endl;
    }

    void navigateDown() {
        if (!currentMenu->subMenu.empty()) {
            currentSelection = (currentSelection + 1) % currentMenu->subMenu.size();
        }
    }

    void navigateUp() {
        if (!currentMenu->subMenu.empty()) {
            currentSelection = (currentSelection + currentMenu->subMenu.size() - 1) % currentMenu->subMenu.size();
        }
    }

    void enter() {
        if (!currentMenu->subMenu.empty()) {
            menuStack.push_back(currentMenu);
            currentMenu = currentMenu->subMenu[currentSelection];
            currentSelection = 0;
        }
    }

    void back() {
        if (!menuStack.empty()) {
            currentMenu = menuStack.back();
            menuStack.pop_back();
            currentSelection = 0;
        }
    }

    void handleInput(int input) {
        switch (input) {
        case 1:
            navigateDown();
            break;
        case 2:
            navigateUp();
            break;
        case 3:
            enter();
            break;
        case 4:
            back();
            break;
        default:
            cout << "Invalid input";
        }
    }
};

int main() {

    MenuItem* mainMenu = new MenuItem("MAIN MENU");
    MenuItem* settings = new MenuItem("Settings");
    MenuItem* media = new MenuItem("Media");

    MenuItem* displaySettings = new MenuItem("Display Settings");
    MenuItem* audioSettings = new MenuItem("Audio Settings");

    MenuItem* radio = new MenuItem("Radio");
    MenuItem* bluetoothAudio = new MenuItem("Bluetooth Audio");


    mainMenu->addSubItem(settings);
    mainMenu->addSubItem(media);

    settings->addSubItem(displaySettings);
    settings->addSubItem(audioSettings);

    media->addSubItem(radio);
    media->addSubItem(bluetoothAudio);


    Menu menu(mainMenu);
    int input;

    while (true) {
        menu.displayMenu();
        cout << "Enter your choice: ";
        cin >> input;

        if (input == 0) break;
        menu.handleInput(input);
    }


    return 0;
}