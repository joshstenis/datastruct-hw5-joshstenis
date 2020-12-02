#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/**
 * Converts a string number into an integer -- (ex. "-140" == -140)
 * @param str The string number
 */
int strToInt(string str) {
    int val = 0;
    for(int i=0 ;i < str.length(); i++) {
        if(str[i] != '-')
            val += pow(10, str.length()-i) * (str[i] - 48);
    } if(str[0] == '-') val *= -1;
    
    return val/10;
}

int main() {
    string val;
    int op, key;
    vector<int> init;

    while(!cin.fail()) {                        // Takes in keys for initial tree
        cin >> val;
        if(val == "s") break;
        init.push_back(strToInt(val));
    }

    cin.ignore(1, '\n');
    cin >> op;

    cin.ignore(1, '\n');
    cin >> key;

    cin.ignore(1, '\n');

    switch(op) {
        case 1:
        {
            // Search
        } break;

        case 2:
        {
            // Insert
        } break;

        case 3:
        {
            // Delete
        } break;

        default: break;
    }
}