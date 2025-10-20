#include <iostream>
#include <string>
#include <fstream>      //Import file stream head file
using namespace std;
class FileHandler {
public:
    bool readFile(const string& path, string& content) {
       ifstream file(path);     //Use input file stream to read file
       if(!file) return false;
       content.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());  //I don't know how to extract all content from a file,so DS taught me this.
       return true;
    }
    bool writeFile(const string& path, const string& content) {
       ofstream file(path);     //Use output file stream to write file
       if(!file) return false;
       file << content;
       return true;
    }
};