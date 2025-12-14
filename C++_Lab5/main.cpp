#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "text_editor.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> arguments{argv + 2, argv + argc};
    text_editor text_edit(argv[1], arguments);

    for_each(arguments.begin(), arguments.end(), [&](const string& arg)
    {
        text_edit.split_argument(arg);

        if(text_edit.get_flag() == "--print")
        {
            text_edit.print();
        }

        else if(text_edit.get_flag() == "--frequency")       
        {
            text_edit.frequency_table();
        }

        else if(text_edit.get_flag() == "--substitude")
        {
            text_edit.substitude(text_edit.get_argument());
        }

        else if(text_edit.get_flag() == "--remove")
        {
            text_edit.remove_word(text_edit.get_argument());
        }

        else if(text_edit.get_flag() == "--remove-duplicates")
        {
            text_edit.remove_duplicates();
        }
    });

    return 0;
}
