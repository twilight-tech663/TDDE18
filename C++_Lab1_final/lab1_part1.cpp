#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
// TODO: Complementary work: Always initialize variables to a known value.
// Hint: Remember to use curly braces for initialization.

// TODO: Complementary work: Don't repeat sticky IO manipulators. Every
// manipulator (except setw) will "stick" until a different manipulator
// overrides it, so it is unnecessary to repeat them.

// TODO: Complementary work: Your code should not generate warnings when
// compiling with the -Wall -Wextra -Wpedantic flags.


int main()
{
    int i{0};
    double d(0);
    char c{0};
    string str{};

    cout << "Enter one integer: ";
    cin >> i;
    //cin.clear();                                  // clear error flag, only use in failbit flag, but cin can read float, only need to ignore the buffer
    cin.ignore(1000, '\n');                         // clear input buffer
    cout << "You entered the number: " << i << "\n";

    cout << "Enter four integers: ";
    cin >> i; 
    cout << "You entered the numbers: " << i << " ";
    cin >> i;
    cout << i << " ";
    cin >> i;
    cout << i << " ";
    cin >> i;
    cin.ignore(1000, '\n');
    cout << i << "\n";

    cout << "Enter one integer and one real number: ";  //pro
    cin >> i >> d;
    cin.ignore(1000, '\n');

    cout << fixed << setprecision(3);
    cout << "The real is: ";
    cout << setw(10) << right << d << "\n";        // fixed + setprecision use to fixed digits point format
    cout << "The integer is: ";
    cout << setw(7) << right << i << "\n";

    cout << "Enter one real and one integer number: ";
    cin >> d >> i;
    cin.ignore(1000, '\n');

    cout << setfill('.');
    cout << "The real is: ";
    cout << setw(10) << right << d << "\n";
    cout << "The integer is: ";
    cout << setw(7) << right << i << "\n";

    cout << "Enter a character: ";
    cin >> c;
    cin.ignore(1000, '\n');
    cout << "You entered: " << c << "\n";

    cout << "Enter a word: ";
    cin >> str;
    cout << "The word \'" << str << "\' has " << str.size() << " character(s)." << "\n";

    cout << "Enter an integer and a word: ";    //pro
    cin >> i >> str;                            //in case input error, convert double type to integer type
    cin.ignore(1000, '\n');
    cout << "You entered \'" << i << "\' and \'" << str << "\'." << "\n";        //\' and \" for single or double quotes, only ' can also work

    cout << "Enter an character and a word: ";
    cin >> c >> str;
    cin.ignore(1000, '\n');
    cout << "You entered the string \"" << str << "\" and the character \'" << c << "\'." << "\n";

    cout << "Enter a word and real number: ";
    cin >> str >> d;
    cin.ignore(1000, '\n');
    cout << "You entered \"" << str << "\" and \"" << d << "\"." << "\n";

    cout << "Enter a text-line: ";
    getline(cin, str);
    cout << "You entered: \"" << str << "\"" << "\n";

    cout << "Enter a second line of text: ";
    getline(cin, str);
    cout << "You entered \"" << str << "\"" << "\n";

    cout << "Enter three words: ";
    cin >> str;
    cout << "You entered: \'" << str << " ";
    cin >> str;
    cout << str << " ";
    cin >> str;
    cout << str << "\'" << endl;
    
    return 0;
}