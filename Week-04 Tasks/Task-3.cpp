#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
using namespace std;

// Define Control struct
struct Control {
    int id;
    string type;  // "button" or "slider"
    string state; // "visible", "invisible", "disabled"

    void print() const {
        cout << "ID: " << id << ", Type: " << type << ", State: " << state << endl;
    }
};

int main() {
    // Initialize sample controls
    vector<Control> controls = {
        {1, "button", "visible"}, {2, "slider", "invisible"},
        {3, "button", "disabled"}, {4, "slider", "visible"},
        {5, "button", "visible"}, {6, "slider", "disabled"},
        {7, "button", "visible"}, {8, "slider", "visible"},
        {9, "button", "invisible"}, {10, "slider", "visible"}
    };

    // 1. Create a backup using std::copy
    vector<Control> backup(controls.size());
    copy(controls.begin(), controls.end(), backup.begin());
    cout << "Backup of controls:" << endl;
    for (const auto& c : backup) c.print();

    // 2. Temporarily disable all controls using std::fill
    fill(controls.begin(), controls.end(), Control{0, "any", "disabled"});
    cout << "\nAll controls temporarily disabled:" << endl;
    for (const auto& c : controls) c.print();

    // 3. Generate random states using std::generate
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

    // 4. Change all sliders' state to "invisible" using std::transform
    transform(controls.begin(), controls.end(), controls.begin(), [](Control& c) {
        if (c.type == "slider") c.state = "invisible";
        return c;
    });
    cout << "\nAfter setting all sliders to invisible:" << endl;
    for (const auto& c : controls) c.print();

    // 5. Replace "disabled" with "enabled" using std::replace
    replace_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "disabled";
    }, Control{0, "any", "enabled"}.state);
    cout << "\nAfter replacing 'disabled' with 'enabled':" << endl;
    for (const auto& c : controls) c.print();

    // 6. Remove all invisible controls using std::remove_if
    controls.erase(remove_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "invisible";
    }), controls.end());
    cout << "\nAfter removing invisible controls:" << endl;
    for (const auto& c : controls) c.print();

    // 7. Reverse the control order using std::reverse
    reverse(controls.begin(), controls.end());
    cout << "\nAfter reversing the control order:" << endl;
    for (const auto& c : controls) c.print();

    // 8. Group visible controls together using std::partition
    partition(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "visible";
    });
    cout << "\nAfter grouping visible controls together:" << endl;
    for (const auto& c : controls) c.print();

    return 0;
}