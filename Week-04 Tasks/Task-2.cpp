#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    // Step 1: Initialize Containers
    vector<string> dynamicWidgets = {"Speedometer", "Tachometer", "FuelGauge"};
    set<string> staticWidgets = {"Logo", "WarningLights"};

    // Step 2: Print all dynamic widgets using an iterator
    cout << "Dynamic Widgets:" << endl;
    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it) {
        cout << *it << endl;
    }

    // Step 3: Check if "WarningLights" is in the set
    string searchWidget = "WarningLights";
    auto found = staticWidgets.find(searchWidget);
    if (found != staticWidgets.end()) {
        cout << searchWidget << " is in the static widgets set." << endl;
    } else {
        cout << searchWidget << " is not in the static widgets set." << endl;
    }

    // Step 4: Combine both containers into a single vector
    vector<string> combinedWidgets;
    copy(dynamicWidgets.begin(), dynamicWidgets.end(), back_inserter(combinedWidgets));
    copy(staticWidgets.begin(), staticWidgets.end(), back_inserter(combinedWidgets));

    // Step 5: Find a specific widget in the combined container
    string searchCombined = "Tachometer";
    auto it = find(combinedWidgets.begin(), combinedWidgets.end(), searchCombined);
    if (it != combinedWidgets.end()) {
        cout << searchCombined << " found in the combined widget list." << endl;
    } else {
        cout << searchCombined << " not found in the combined widget list." << endl;
    }

    // Step 6: Print all combined widgets
    cout << "Combined Widgets:" << endl;
    for (const auto& widget : combinedWidgets) {
        cout << widget << endl;
    }

    return 0;
}