#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "text_editor.hpp"

int main(int argc, char* argv[])
{
    std::vector<std::string> arguments{argv + 2, argv + argc};
    text_editor text_edit(argv[1]);

    try
    {
        std::for_each(arguments.begin(), arguments.end(), [&](const std::string& arg)
        {
            std::string flag;
            std::string parameter;
            size_t pos = arg.find('=');
            if (pos != std::string::npos)
            {
                flag = arg.substr(0, pos);
                parameter = arg.substr(pos + 1);
            } else {
                flag = arg;
                parameter = "";
            }

            if(flag == "--print")
            {
                text_edit.print();
            }

            else if(flag == "--frequency")       
            {
                text_edit.frequency_table();
            }

            else if(flag == "--substitute")
            {
                std::string old_word;
                std::string new_word;
                size_t pos = parameter.find('+');
                if(pos != std::string::npos)
                {
                    old_word = parameter.substr(0, pos);
                    new_word = parameter.substr(pos + 1);
                }
                text_edit.substitute(old_word, new_word);
            }

            else if(flag == "--remove")
            {
                text_edit.remove_word(parameter);
            }

            else if(flag == "--remove-duplicates")
            {
                text_edit.remove_duplicates();
            } else {
                std::cerr << "Not support yet!";
            }
        });
    } 
    catch(std::out_of_range& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
    catch(std::exception& e)
    {
        std::cerr << "Unkonw Error: " << e.what() << "\n";
    }
    return 0;
}
