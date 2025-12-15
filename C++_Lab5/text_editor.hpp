#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <iostream>
#include <vector>
#include <string>

class text_editor
{
public:
    text_editor(const std::string& filename, std::vector<std::string>& args);
    void split_argument(const std::string& arg);
    std::string get_flag();
    std::string get_parameter();
    void print() const;
    void frequency_table();
    bool word_is_exist(const std::string& word);
    void substitude(const std::string& arg);
    void remove_word(const std::string& arg);
    void remove_duplicates();
    
private:
    std::string flag{};
    std::string parameter{};
    std::vector<std::string> arguments{};
    std::vector<std::string> text{}; 
};

#endif