#include <iostream>
#include <vector>
#include <string>
using namespace std;
class MenuItem {
public:
    string name;
    vector<MenuItem*> submenus;  // Child submenus
    
    // Constructor to initialize a menu item
    MenuItem(string n) : name(n) {}

    // Add a submenu to the current menu item
    void addSubmenu(MenuItem* submenu) {
        submenus.push_back(submenu);
    }

    // Display the current menu and allow navigation
    void displayMenu(int level) {
        cout << string(level * 2, ' ') << name << endl;
        if (submenus.empty()) {
            return;  // No submenus to display
        }
        for (size_t i = 0; i < submenus.size(); ++i) {
            cout << string((level + 1) * 2, ' ') << i + 1 << ". " << submenus[i]->name << endl;
        }
    }

    // Get the submenu by index
    MenuItem* getSubmenu(int index) {
        if (index < 0 || index >= submenus.size()) return nullptr;
        return submenus[index];
    }
};

class MenuSystem {
private:
    MenuItem* currentMenu;
    MenuItem* rootMenu;

public:
    MenuSystem(MenuItem* root) : rootMenu(root), currentMenu(root) {}

    // Navigate through the menu based on user input
    void navigate() {
        int choice;
        while (true) {
            // Display the current menu
            currentMenu->displayMenu(0);

            // Show navigation instructions
            cout << "\nEnter (1) to navigate down, (2) to go up, (3) to enter, or (0) to exit: ";
            cin >> choice;

            if (choice == 0) {
                cout << "Exiting menu system.\n";
                break;
            }

            if (choice == 1) {
                // Navigate down to a submenu
                int subChoice;
                cout << "Select submenu to enter: ";
                cin >> subChoice;
                MenuItem* submenu = currentMenu->getSubmenu(subChoice - 1); // 1-indexed input
                if (submenu) {
                    currentMenu = submenu;
                } else {
                    cout << "Invalid submenu choice.\n";
                }
            } else if (choice == 2) {
                // Navigate up to the parent menu
                if (currentMenu != rootMenu) {
                    currentMenu = rootMenu;
                } else {
                    cout << "You are already at the root menu.\n";
                }
            } else if (choice == 3) {
                // Enter into the selected submenu
                int subChoice;
                cout << "Select submenu to enter: ";
                cin >> subChoice;
                MenuItem* submenu = currentMenu->getSubmenu(subChoice - 1); // 1-indexed input
                if (submenu) {
                    currentMenu = submenu;
                } else {
                    cout << "Invalid submenu choice.\n";
                }
            }
        }
    }
};

int main() {
    // Create the menu structure
    MenuItem* mainMenu = new MenuItem("Main Menu");
    MenuItem* settingsMenu = new MenuItem("Settings");
    MenuItem* displayMenu = new MenuItem("Display Settings");
    MenuItem* audioMenu = new MenuItem("Audio Settings");
    MenuItem* mediaMenu = new MenuItem("Media");
    MenuItem* radioMenu = new MenuItem("Radio");
    MenuItem* bluetoothMenu = new MenuItem("Bluetooth Audio");

    // Build the hierarchical structure
    mainMenu->addSubmenu(settingsMenu);
    mainMenu->addSubmenu(mediaMenu);
    
    settingsMenu->addSubmenu(displayMenu);
    settingsMenu->addSubmenu(audioMenu);
    
    mediaMenu->addSubmenu(radioMenu);
    mediaMenu->addSubmenu(bluetoothMenu);

    // Create a MenuSystem object to control navigation
    MenuSystem menuSystem(mainMenu);

    // Start the navigation system
    menuSystem.navigate();

    // Cleanup
    delete mainMenu;
    delete settingsMenu;
    delete displayMenu;
    delete audioMenu;
    delete mediaMenu;
    delete radioMenu;
    delete bluetoothMenu;

    return 0;
}
