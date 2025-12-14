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
using namespace std;


text_editor::text_editor(const string& filename, vector<string>& args)
    :arguments{args}
{
    ifstream data(filename);
    copy(istream_iterator<string>(data), istream_iterator<string>(), back_inserter(text));
}

void text_editor::split_argument(const string& arg)
{
    size_t pos = arg.find('=');
    if (pos != string::npos)
    {
        flag = arg.substr(0, pos);
        argument = arg.substr(pos + 1);
    } else {
        flag = arg;
    }
}

string text_editor::get_flag()
{
    return flag;
}

string text_editor::get_argument()
{
    return argument;
}

void text_editor::print() const
{
    copy(text.begin(), text.end(), ostream_iterator<string>(cout, " "));
    cout << "\n";
}

void text_editor::frequency_table()
{
    map<string, int> table{};
    for_each(text.begin(), text.end(),
            [&table](const string& word)
            {
                table[word]++;
            });
    vector<pair<string, int>> sort_table{table.begin(), table.end()};

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
    
    transform(sort_table.begin(), sort_table.end(), ostream_iterator<string>(cout, "\n"),
            [&max_word](const auto& word)
            {
                ostringstream oss;
                oss << right << setw(max_word->first.size()) << word.first
                    << " " << word.second;
                return oss.str();
            });
}

void text_editor::substitude(const string& arg)
{
    string old_word;
    string new_word;
    size_t pos = arg.find('+');
    if(pos != string::npos)
    {
        old_word = arg.substr(0, pos);
        new_word = arg.substr(pos + 1);
    }
    replace(text.begin(), text.end(), old_word, new_word);
}

void text_editor::remove_word(const string& arg)
{
    auto it = remove(text.begin(), text.end(), arg);
    text.erase(it, text.end());
}

void text_editor::remove_duplicates()
{
    map<string, int> count_table{};
    auto it = remove_if(text.begin(), text.end(),
                        [&count_table](const string& word)
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


