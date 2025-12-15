#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <iomanip>
#include <sstream>
#include "text_editor.hpp"

text_editor::text_editor(const std::string& filename)
    :filename{filename}
{
    std::ifstream data(filename);
    copy(std::istream_iterator<std::string>(data), 
         std::istream_iterator<std::string>(), 
         back_inserter(text));
}

void text_editor::print() const
{
    copy(text.begin(), text.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "\n";
}

void text_editor::frequency_table() const
{
    std::map<std::string, int> table{};
    for_each(text.begin(), text.end(),
            [&table](const std::string& word)
            {
                table[word]++;
            });
    std::vector<std::pair<std::string, int>> sort_table{table.begin(), table.end()};

    sort(sort_table.begin(), sort_table.end(),
        [](const auto& w1, const auto& w2)
        {
            return w1.second > w2.second;
        });
    
    auto max_word = max_element(sort_table.begin(), sort_table.end(),
                                [](const auto& w1, const auto& w2)
                                {
                                    return w1.first.size() < w2.first.size();
                                });
    
    transform(sort_table.begin(), sort_table.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
            [&max_word](const auto& word)
            {
                std::ostringstream oss;
                oss << std::right << std::setw(max_word->first.size()) << word.first
                    << " " << word.second;
                return oss.str();
            });
}

bool text_editor::word_exists(const std::string& word) const
{
    return find(text.begin(), text.end(), word) != text.end();
}

void text_editor::substitute(const std::string& old_word, const std::string& new_word)
{
    if(!word_exists(old_word))
    {
        throw std::invalid_argument("This word isn't exist in file!");
    }
    replace(text.begin(), text.end(), old_word, new_word);
}

void text_editor::remove_word(const std::string& word)
{
    if(!word_exists(word))
    {
        throw std::invalid_argument("This word isn't exist in file!");
    } else {
        auto it = remove(text.begin(), text.end(), word);
        text.erase(it, text.end());
    }
}

void text_editor::remove_duplicates()
{
    std::map<std::string, int> count_table{};
    auto it = remove_if(text.begin(), text.end(),
                        [&count_table](const std::string& word)
                        {
                            if(count_table[word] != 0)
                            {
                                return true;
                            }
                            count_table[word]++;
                            return false;
                        });
    text.erase(it, text.end());
}


