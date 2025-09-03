#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int i;
    double d;
    float f;
    char c;
    string str;

    cout << "Enter one integer: ";
    cin >> i;
    cin.clear();                                    // clear error flag
    cin.ignore(1000, '\n');                         // clear input buffer
    cout << "You entered the number: " << i << "\n";

    cout << "Enter four integers: ";
    cin >> i;
    cin.clear();
    cin.ignore(1000, ' ');
    cout << "You entered the numbers: " << i << " ";
    cin >> i;
    cin.clear();
    cin.ignore(1000, ' ');
    cout << i << " ";
    cin >> i;
    cin.clear();
    cin.ignore(1000, ' ');
    cout << i << " ";
    cin >> i;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << i << "\n";

    cout << "Enter one integer and one real number: ";
    cin >> f >> d;                                                             // in case integer input error, convert float to int type
    i = f;
    // cin.clear();
    // cin.ignore(1000, '\n');                                                 // cause already deal with type input error, these two line are no need
    cout << "The real is: ";
    cout << setw(10) << right << fixed << setprecision(3) << d << "\n";        // fixed + setprecision use to fixed digits point format
    cout << "The integer is: ";
    cout << setw(7) << right << i << "\n";

    cout << "Enter one real and one integer number: ";
    cin >> d >> i;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "The real is: ";
    cout << setw(10) << right << fixed << setprecision(3) << setfill('.') << d << "\n";
    cout << "The integer is: ";
    cout << setw(7) << setfill('.') << right << i << "\n";

    cout << "Enter a character: ";
    cin >> c;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "You entered: " << c << "\n";

    cout << "Enter a word: ";
    cin >> str;
    cout << "The word \'" << str << "\' has " << str.size() << " character(s)." << "\n";

    cout << "Enter an integer and a word: ";
    cin >> d >> str;                            //in case input error, convert double type to integer type
    i = d;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "You entered \'" << i << "\' and \'" << str << "\'." << "\n";        //\' and \" for single or double quotes, only ' can also work

    cout << "Enter an character and a word: ";
    cin >> c >> str;
    cout << "You entered the string \"" << str << "\" and the character \'" << c << "\'." << "\n";

    cout << "Enter a word and real number: ";
    cin >> str >> d;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "You entered \"" << str << "\" and \"" << fixed << setprecision(3) << d << "\"." << "\n";

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