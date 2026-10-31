#include <iostream>
#include <limits>
using namespace std;

char name(int n, string username);

void pattern(int rows, int columns, char frameChar, string username);

void checkValidInteger(int& input, int minInt, string outputMSG);

int main() {
    string username;
    char frameCharacter;
    int numRows, numColumns;
    
    cout << "Please enter your name: ";
    cin >> username;
    
    cout << "Please enter the number of rows: ";
    checkValidInteger(numRows, 3, "Invalid input. Must be integer greater than or equal to 3: ");
    
    cout <<  "Please enter the number of columns: ";
    checkValidInteger(numColumns, 3, "Invalid input. Must be integer greater than or equal to 3: ");
    
    cout << "Please enter the frame character: ";
    cin >> frameCharacter;
    
    pattern(numRows, numColumns, frameCharacter, username);
    return 0;
}

char name(int n, string username) {
    int nameLength = username.length();
    return username[n % nameLength];
}

void checkValidInteger(int& input, int minInt, string outputMSG){
    while (!(cin >> input) or (input < minInt)) {
        cout << outputMSG;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return;
}

void pattern(int rows, int columns, char frameChar, string username) {
    int charPos = 0;
    for (int i = 0; i < rows; i++) {
        for (int n = 0; n < columns; n ++) {
            //Paint the border
            if (i == 0 or i == rows-1 or n == 0 or n == columns-1) {
                cout << frameChar;
            }
            //Increment number to print, saves between rows
            else {
                cout << name(charPos, username);
                charPos += 1;
            }
        }
        cout << endl;
    }
}