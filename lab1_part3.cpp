#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    ifstream data{"data.txt"};
    int word_num;
    int total_length;
    double average_length;
    string shortest_word;
    string longest_word;
    string line;

    while(getline(data, line))
    {
        string current_word{};
        for(char letter : line)              // iterate every character of line
        {
            // first situation: letter is a character or number, only in this condition, record character and count length
            if(letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z' || letter >= '0' && letter <= '9')
            {
                current_word += letter;
                total_length ++;
            }
            // other situation: means end of character, begin counting word
            else
            {
                if(!current_word.empty())    // check current word, avoid consecutive spaces or symbols
                {
                    word_num ++;
                    // update longest word
                    if(current_word.size() >= longest_word.size())
                    {
                        longest_word = current_word;
                    }
                    // update shortest word
                    if(shortest_word.empty() || current_word.size() <= shortest_word.size())       // shortest word is empty at first, need assignment 
                    {
                        shortest_word = current_word;
                    }
                    current_word = "";      // update current word to empty
                }
            }
        } 
    }
    average_length = total_length * 1.0 / word_num;

    cout << total_length << "\n";
    cout << "There are " << word_num << " words in the file." << "\n";
    cout << "The shortest word was \"" << shortest_word << "\" with " << shortest_word.size() << " character(s)." << "\n";
    cout << "The longest word was \"" << longest_word << "\" with " << longest_word.size() << " character(s)." << "\n";
    cout << "The average length was " << fixed << setprecision(2) << average_length << " character(s)." << "\n";
    return 0;

}

