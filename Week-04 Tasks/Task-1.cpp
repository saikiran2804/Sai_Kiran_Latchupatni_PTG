#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Define Control struct
struct Control {
    int id;
    string type; // "button" or "slider"
    string state; // "visible", "invisible", "disabled"

    // Overload the == operator for Control
    bool operator==(const Control& other) const {
        return id == other.id && type == other.type && state == other.state;
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

    // 1. Print all controls using for_each
    cout << "All controls:" << endl;
    for_each(controls.begin(), controls.end(), [](const Control& c) {
        cout << "ID: " << c.id << ", Type: " << c.type << ", State: " << c.state << endl;
    });

    // 2. Find a control with specific ID
    int searchId;
    cout << "Enter ID to search for: " ;
    cin >> searchId;
    auto it = find_if(controls.begin(), controls.end(), [searchId](const Control& c) {
        return c.id == searchId;
    });
    if (it != controls.end()) {
        cout << "Control with ID " << searchId << "- Type: " << it->type << ", State: " << it->state << endl;
    } else {
        cout << "No control with ID " << searchId << " found" << endl;
    }

    // 3. Find first invisible control
    auto invisibleControl = find_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "invisible";
    });
    if (invisibleControl != controls.end()) {
        cout << "First invisible control - ID: " << invisibleControl->id << endl;
    }

    // 4. Check for consecutive controls with the same state
    auto consecutive = adjacent_find(controls.begin(), controls.end(), [](const Control& a, const Control& b) {
        return a.state == b.state;
    });
    if (consecutive != controls.end()) {
        cout << "Consecutive controls with same state found at ID: " << consecutive->id << endl;
    } else {
        cout << "No consecutive controls with the same state" << endl;
    }

    // 5. Count visible controls
    int visibleCount = count_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "visible";
    });
    cout << "Number of visible controls: " << visibleCount << endl;

    // 6. Count disabled sliders
    int disabledSliders = count_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.type == "slider" && c.state == "disabled";
    });
    cout << "Number of disabled sliders: " << disabledSliders << endl;

    // 7. Compare two subranges of controls
    bool areEqual = equal(controls.begin(), controls.begin() + 3, controls.begin() + 7, controls.begin() + 10);
    cout << "Are the two subranges equal? " << (areEqual ? "Yes" : "No") << endl;

    return 0;
}