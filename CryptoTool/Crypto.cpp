#include <iostream>
#include <string>
using namespace std;
class Crypto {
public:
    string encrypt(string data, int key) {
        for(int i = 0; i < data.length(); i++) {
            char c = data[i];
            if(isupper(c)) {
                c = (c + key - 'A') % 26 + 'A';
            }
            else if(islower(c)) {
                c = (c + key - 'a') % 26 + 'a';
            }
            data[i] = c;
        }
        return data;
    }

    string decrypt(string data, int key) {
        for(int i = 0; i < data.length(); i++) {
            char c = data[i];
            if(isupper(c)) {
                c = (c - key + 26 - 'A') % 26 + 'A';
            }
            else if(islower(c)) {
                c = (c - key + 26 - 'a') % 26 + 'a';
            }
            data[i] = c;
        }
        return data;
    }
};