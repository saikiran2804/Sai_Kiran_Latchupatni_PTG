#include <iostream>
#include <map>
#include <string>

using namespace std;

class Theme {
public:
    string backgroundColor;
    string fontColor;
    int fontSize;
    string iconStyle;

    // Default constructor
    Theme() : backgroundColor("DefaultBG"), fontColor("DefaultFont"), fontSize(12), iconStyle("DefaultIcon") {}

    // Parameterized constructor
    Theme(const string& bg, const string& font, int size, const string& icon)
        : backgroundColor(bg), fontColor(font), fontSize(size), iconStyle(icon) {}

    void apply() const {
        cout << "Applying Theme: " << backgroundColor << ", " << fontColor << ", "
             << fontSize << "px Font Size, " << iconStyle << " Icons." << endl;
    }

    void display() const {
        cout << "Theme Preview: " << backgroundColor << " Background, " << fontColor
             << " Font, " << fontSize << "px Font Size, " << iconStyle << " Icons." << endl;
    }
};

int main() {
    // Map to store themes
    map<string, Theme> themes;

    // Adding themes to the map
    themes["Classic"] = Theme("White", "Black", 14, "Square");
    themes["Sport"] = Theme("Red", "White", 16, "Bold");
    themes["Eco"] = Theme("Green", "Brown", 12, "Leaf");

    string choice;

    // User interface to switch themes
    while (true) {
        cout << "\nAvailable Themes: Classic, Sport, Eco" << endl;
        cout << "Enter theme name to apply (or 'exit' to quit): ";
        cin >> choice;

        if (choice == "exit") {
            break;
        }

        auto it = themes.find(choice);
        if (it != themes.end()) {
            cout << "\n" << choice << " Theme selected:\n";
            it->second.display(); // Display theme preview
            it->second.apply();   // Apply theme
        } else {
            cout << "Theme not found. Please try again." << endl;
        }
    }

    return 0;
}