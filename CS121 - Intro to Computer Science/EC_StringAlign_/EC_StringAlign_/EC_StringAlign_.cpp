#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string str;
    int width;

    // Accept input from console
    cout << "Enter a string: ";
    getline(cin, str);

    // Bool to check if width input is number rather than other characters
    bool is_valid_width = false;
    while (!is_valid_width) {
        cout << "Enter width: ";
        string width_str;
        getline(cin, width_str);
        is_valid_width = true;
        for (char c : width_str) {
            if (!isdigit(c)) {
                is_valid_width = false;
                break;
            }
        }
        if (is_valid_width) {
            width = stoi(width_str);
        }
        else {
            cout << "Width must be a numeric value. Please try again." << endl;
        }
    }

    int str_len = str.length();

    // Calculate number of spaces needed to center the string
    int padding = (width - str_len) / 2;

    // Print the padded string
    for (int i = 0; i < padding; i++) {
        cout << " ";
    }
    cout << str;
    for (int i = 0; i < padding; i++) {
        cout << " ";
    }

    // Add an extra space if the width is odd
    if ((width - str_len) % 2 != 0) {
        cout << " ";
    }

    return 0;
}
