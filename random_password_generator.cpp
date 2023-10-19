#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Function to generate a random password
    string generatePassword(int len) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    const int charCount = characters.length();
    string password;

    for (int i = 0; i < len; ++i) {
        int index = rand() % charCount;
        password += characters[index];
    }

    return password;
}

int main() {
    system("cls");
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    int passwordlen;
    
    cout << "\t\t\t\tRANDOM PASSWORD GENERATOR" << endl << endl;
    while(1){
    cout << "Enter the desired password length: ";
    cin >> passwordlen;

    if (passwordlen <= 0) {
        cout << "Password length must be a positive integer." << endl;
    }
    else{
        break;
    }
    }

    string password = generatePassword(passwordlen);

    cout << "Generated Password for You: " << password << endl;

    return 0;
}
