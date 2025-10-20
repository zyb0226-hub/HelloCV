#include <iostream>
#include <string>
using namespace std;
class Crypto{
public:
    static string encrypt(string data, int key);    //There's need to add static to make it accessible without instantiation.
    static string decrypt(string data, int key);
};
class FileHandler{
public:
    static bool readFile(const string& path, string& content);
    static bool writeFile(const string& path, const string& content);
};
class Menu {
public:
    static void menu(){
        cout << "Welcome to CryptoTool!" << endl;   //I'm so strange why I can't use Chinese in VScode.It's so weird.
        cout << "1. Encrypt Data" << endl;          //But it's extremely good to enjoy it's automatic code producer.
        cout << "2. Decrypt Data" << endl;
        cout << "3. Encrypt File" << endl;
        cout << "4. Decrypt File" << endl;
        cout << "5. Exit" << endl;
        cout << "Please select an option: ";
    }
    static void handle(){
        int choice,key;
        string text;
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter data to encrypt: ";
                getline(cin, text);
                cout << "Enter key: ";
                cin >> key;
                cout << "Encrypted data: " << Crypto::encrypt(text,key) << endl;
                break;
            case 2:
                cout << "Enter data to decrypt: ";
                getline(cin, text);
                cout << "Enter key: ";
                cin >> key;
                cout << "Decrypted data: " << Crypto::decrypt(text,key) << endl;
                break;
            case 3:
                FileHandler::readFile("input.txt",text);
                cout << "Enter key: ";
                cin >> key;
                text = Crypto::encrypt(text,key);
                FileHandler::writeFile("output.txt",text);
                cout << "File encrypted and saved to output.txt" << endl;
                break;
            case 4:
                FileHandler::writeFile("input.txt",text);
                cout << "Enter key: ";
                cin >> key;
                text = Crypto::decrypt(text,key);
                FileHandler::writeFile("output.txt",text);
                cout << "File decrypted and saved to output.txt" << endl;
                break;
            case 5:
                cout << "Exiting..." << endl;
                return;
            default:
               cout << "Invalid option. Please try again." << endl;
        }
    }
};
