#include <iostream>
#include <iomanip>
using namespace std;

// use a function to change table output, more clear and easy to test
void PrintRow(float price, float tax, float total_price, int price_width, int tax_width, int total_width)
{
    cout << fixed << setprecision(2);
    cout << setw(price_width) << right << price;
    cout << setw(tax_width) << right << tax;
    cout << setw(total_width) << right << total_price << "\n";
}

int main()
{
    float first_price, last_price, stride, tax_percent;
    cout << left << "INPUT PART" << "\n" << "==========" << endl;

    cout << "Enter first price: ";
    cin >> first_price;
    while(first_price < 0)                  // use while avoid user keep input wrong 
    {
        cerr << "ERROR: First price must be at least 0 (zero) SEK" << "\n";
        cout << "Enter first price: ";
        cin >> first_price;
    }

    cout << left << "Enter last price:  ";
    cin >> last_price;
    while (last_price <= first_price)
    {
        cerr << "ERROR: Last price must greater than first price" << "\n";
        cout << left << "Enter last price:  ";
        cin >> last_price;
    }
    
    cout << left << "Enter stride:      ";
    cin >> stride;
    while(stride <= 0 || stride >= last_price - first_price)
    {
        cerr << "ERROR: Stride must be at least 0.01, between last and first price differences" << "\n";
        cout << left << "Enter stride:      ";
        cin >> stride;
    }

    cout << left << "Enter tax percent: ";
    cin >> tax_percent;
    while(tax_percent < 0)
    {
        cerr << "ERROR: Tax percent must be at least 0(zero)" << "\n";
        cout << left << "Enter tax percent: ";
        cin >> tax_percent;
    }
    cout << "\n";

    //output table
    cout << left << "TAX TABLE" << "\n" << "==========" << "\n";
    cout << right << setw(9) << "Price" << setw(17) << "Tax" << setw(23) << "Price with tax" << "\n";
    cout << "-------------------------------------------------" << "\n";
    float price, tax, total_price;

    price = first_price;
    while (price <= last_price)
    {
        tax = price * tax_percent / 100;
        total_price = price + tax;
        PrintRow(price, tax, total_price, 9, 17, 23);
        price = price + stride; 
    }

    return 0;
}