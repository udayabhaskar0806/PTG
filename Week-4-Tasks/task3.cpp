#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
using namespace std;

struct Control {
    int id;
    string type;
    string state;

    void print() const {
        cout << "ID: " << id << ", Type: " << type << ", State: " << state << endl;
    }
};

int main() {
    vector<Control> controls = {
        {1, "button", "visible"}, {2, "slider", "invisible"},
        {3, "button", "disabled"}, {4, "slider", "visible"},
        {5, "button", "visible"}, {6, "slider", "disabled"},
        {7, "button", "visible"}, {8, "slider", "visible"},
        {9, "button", "invisible"}, {10, "slider", "visible"}
    };

    vector<Control> backup(controls.size());
    copy(controls.begin(), controls.end(), backup.begin());
    cout << "Backup of controls:" << endl;
    for (const auto& c : backup) c.print();

    fill(controls.begin(), controls.end(), Control{0, "any", "disabled"});
    cout << "\nAll controls temporarily disabled:" << endl;
    for (const auto& c : controls) c.print();

    vector<string> states = {"visible", "invisible", "disabled"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 2);

    generate(controls.begin(), controls.end(), [&states, &dist, &gen]() {
        static int id = 1;
        return Control{id++, "button", states[dist(gen)]};
    });
    cout << "\nControls with random states:" << endl;
    for (const auto& c : controls) c.print();

    transform(controls.begin(), controls.end(), controls.begin(), [](Control& c) {
        if (c.type == "slider") c.state = "invisible";
        return c;
    });
    cout << "\nAfter setting all sliders to invisible:" << endl;
    for (const auto& c : controls) c.print();

    for (auto& c : controls) {
        if (c.state == "disabled") {
            c.state = "enabled";
        }
    }
    cout << "\nAfter replacing 'disabled' with 'enabled':" << endl;
    for (const auto& c : controls) c.print();

    controls.erase(remove_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "invisible";
    }), controls.end());
    cout << "\nAfter removing invisible controls:" << endl;
    for (const auto& c : controls) c.print();

    reverse(controls.begin(), controls.end());
    cout << "\nAfter reversing the control order:" << endl;
    for (const auto& c : controls) c.print();

    partition(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "visible";
    });
    cout << "\nAfter grouping visible controls together:" << endl;
    for (const auto& c : controls) c.print();

    return 0;
}
