#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class text_editor
{
public:
    text_editor(const string& filename, vector<string>& args);
    void split_argument(const string& arg);
    string get_flag();
    string get_argument();
    void print() const;
    void frequency_table();
    void substitude(const string& arg);
    void remove_word(const string& arg);
    void remove_duplicates();
    
private:
    string flag{};
    string argument{};
    vector<string> arguments{};
    vector<string> text{}; 
};

#endif