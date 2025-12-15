#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <iostream>
#include <vector>
#include <string>

class text_editor
{
public:
    text_editor(const std::string& filename);
    void print() const;
    void frequency_table() const;
    bool word_exists(const std::string& word) const;
    void substitute(const std::string& old_word, const std::string& new_word);
    void remove_word(const std::string& word);
    void remove_duplicates();
    
private:
    std::string filename{};
    std::vector<std::string> text{}; 
};

#endif