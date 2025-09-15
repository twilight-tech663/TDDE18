#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// TODO: Complementary work: The code is unnecessarily complex.
//Hint: you can iterate by every string in the file instead.

// understood, but i think ", . * $ " these symbols should not be counted as a word or length, so i use char to filter it
// but if i don't need to consider it, i can change iterate by string

int main()
{
    int word_num{0};
    int total_length{0};
    double average_length{0};
    string shortest_word{};
    string longest_word{};
    //string line{};

    ifstream data{"data.txt"};
    
    if(data.peek() == ifstream::traits_type::eof())     // peek is a function in fstream, use to check next character in file
    {                                                   // eof is a special signal, represents the end of file
        cout << "The file is empty!" << "\n";
    } else {
        string word{};
        while(data >> word)
        {
            word_num ++;
            total_length += word.size();

            if(word.size() >= longest_word.size())
            {
                longest_word = word;
            }
            
            if(shortest_word.empty() || word.size() <= shortest_word.size())
            {
                shortest_word = word;
            }
        }
    }

    /* this way consider that filter special symbols
    else
    {
        while(getline(data, line))
        {
            string current_word{};
            for(char letter : line)              // iterate every character of line
            {
                // first situation: letter is a character or number, only in this condition, record character and count length
                if(letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z' || letter >= '0' && letter <= '9')
                {
                    current_word += letter;
                    ++ total_length;
                }
                // other situation: means end of character, begin counting word
                else
                {
                    if (!current_word.empty()) // check current word, avoid consecutive spaces or symbols
                    {
                        word_num++;
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
        */
       if(word_num > 0)
       {
            average_length = static_cast<double>(total_length) / word_num;

            cout << total_length << "\n";
            cout << "There are " << word_num << " words in the file." << "\n";
            cout << "The shortest word was \"" << shortest_word << "\" with " << shortest_word.size() << " character(s)." << "\n";
            cout << "The longest word was \"" << longest_word << "\" with " << longest_word.size() << " character(s)." << "\n";
            cout << "The average length was " << fixed << setprecision(2) << average_length << " character(s)." << "\n";
       }
        
    data.close();
    return 0;

}

