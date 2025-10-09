// TODO: Complementary work: All includes should be inside the guards.      //done

// TODO: Complementary work: is_am() should return a bool.      //done

// TODO: Complementary work: to_string's extra parameter should not be            
// an int. What would it mean to send something like 5000?          //done

// TODO: Comment: Usually if to_string() take additional arguments they have
// default values, so that you can call them like 'to_string(something)'.       //done

#ifndef TIME_HPP
#define TIME_HPP

#include <string>
struct Time
{
    int hour;
    int minute;
    int second;
};

bool is_valid(const Time &time);                // check time is valid
std::string to_string(const Time& time, bool is_24hour = true);    // 24-hour or 12-hour clock format
std::string time_zero_padding(const Time& time);   
bool is_am(const Time& time);            // check if the time is before or after noon (am or pm)
Time time_normalization(Time &time);    // deal with non-normal time, like hour > 24, minute&second > 60
Time operator +(const Time& time, int second);  // T + second
Time operator +(int second, const Time& time);  // second + T
Time operator -(const Time& time, int second);  // T - second
Time operator -(int second, const Time& time);  // second - T
Time& operator ++(Time &time);                  // ++ time
Time operator ++(Time &time, int);              // time ++
Time& operator --(Time& time);                  // --time, return new time
Time operator --(Time &time, int);              // time --, return old time
bool operator >(const Time& time1, const Time& time2);
bool operator <(const Time& time1, const Time& time2);
bool operator ==(const Time& time1, const Time& time2);
bool operator !=(const Time& time1, const Time& time2);
bool operator >=(const Time& time1, const Time& time2);
bool operator <=(const Time& time1, const Time& time2);
std::ostream& operator <<(std::ostream& os, const Time& time);
std::istream& operator >>(std::istream& os, Time& time);


#endif
