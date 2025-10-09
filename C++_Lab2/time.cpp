#include <iostream>
#include <string>
#include <iomanip>
#include "time.hpp"

// TODO: Complementary work: If your functions only return true or 
// false with one condition then you should change it to return condition or 
// !(condition). For ex: if (t1 < t2) {return false} --> return !(t1 < t2)      // done

// TODO: Complementary work: operator>> should not destroy a valid time if it
// gets invalid input.                                                          // done


bool is_valid(const Time &time) // check time is valid
{
    if(0 <= time.hour && time.hour <= 23)
    {
        if(0 <= time.minute && time.minute <= 59)
        {
            if(0 <= time.second && time.second <= 59)
            {
                return true;
            }
        }
    }
    return false;
}

std::string to_string(const Time& time, bool is_24hour) //24-hour or 12-hour clock format
{
    std::string format_time;
    Time time_tmp{};
    if(is_24hour)                                // 24 hour format time
    {
        return format_time = time_zero_padding(time);
    } else {                                        // 12 hour format time
        time_tmp.hour = time.hour % 12;
        if(time_tmp.hour == 0)                      // special time 12:00:00 am = 00:00:00
        {                                           // special time 12:00:00 pm = 12:00:00
            time_tmp.hour = 12;
        }
        time_tmp.minute = time.minute;
        time_tmp.second = time.second;
        if(is_am(time))
        {
            return format_time = time_zero_padding(time_tmp) + " am";
        } else {
            return format_time = time_zero_padding(time_tmp) + " pm";
        }
    }
}

std::string time_zero_padding(const Time& time)
{
    std::string hour_str = (time.hour < 10) ? "0" + std::to_string(time.hour) : std::to_string(time.hour);
    std::string minute_str = (time.minute < 10) ? "0" + std::to_string(time.minute) : std::to_string(time.minute);
    std::string second_str = (time.second < 10) ? "0" + std::to_string(time.second) : std::to_string(time.second);
    return hour_str + ":" + minute_str + ":" + second_str;
}

bool is_am(const Time& time)   //check if the time is before or after noon (am or pm)
{  
    return time.hour < 12;
}

Time time_normalization(Time &time)    // deal with non-normal time, like hour > 24, minute&second > 60
{
    int total_second = time.hour * 3600 + time.minute * 60 + time.second;
    if (total_second < 0)                           //if the result is negtive, need rollback day
    {   
        int roll_back_day = 1;
        roll_back_day += total_second / (-86400);   // caculate roll back days
        total_second += 86400 * roll_back_day;
    }
    time.hour = (total_second / 3600) % 24;
    time.minute = (total_second % 3600) / 60;
    time.second = total_second % 60;
    return time;
}

Time operator +(const Time& time, int second)   // T + second
{
    Time time_result{};
    time_result.hour = time.hour;
    time_result.minute = time.minute;
    time_result.second = time.second + second;
    return time_normalization(time_result);

    /*this way is hard to deal with plus bid second, low efficient
    time_result.second = time.second + second;
    time_result.minute = time.minute;
    time_result.hour = time.hour;

    if(time_result.second >= 60)           // if second over 60, need update second and minute
    {
        time_result.minute += time_result.second / 60;
        time_result.second %= 60;
        
        if(time_result.minute >= 60)       // if minute over 60, need update hour and minute
        {
            time_result.hour += time_result.minute / 60;
            time_result.minute %= 60;
        }
    }
    time_result.hour %= 24;            // if hour over 24, need update hour*/
}

Time operator +(int second, const Time& time)   // second + T
{
    return time + second;             // use T+second, reduce duplicate code
}

Time operator -(const Time& time, int second)
{
    Time time_result{};
    time_result.hour = time.hour;
    time_result.minute = time.minute;
    time_result.second = time.second - second;
    return time_result = time_normalization(time_result);
}

Time operator -(int second, const Time& time)
{
    return time - second;
}

Time& operator ++(Time &time)    // ++time, return new time
{
    ++ time.second;
    return time = time_normalization(time);    //update time
}

Time operator ++(Time &time, int)   //time++, return old time
{
    Time time_old{time};
    ++ time.second;
    time = time_normalization(time);
    return time_old;
}

Time& operator --(Time& time)   // --time, return new time
{
    -- time.second;
    return time = time_normalization(time);
}

Time operator --(Time &time, int)   // time --, return old time
{
    Time old_time{time};
    -- time.second;
    time = time_normalization(time);
    return old_time;
}

bool operator >(const Time& time1, const Time& time2)
{
    int total_second_t1 = time1.hour*3600 + time1.minute*60 + time1.second;
    int total_second_t2 = time2.hour*3600 + time2.minute*60 + time2.second;
    return total_second_t1 > total_second_t2;
}

bool operator <(const Time& time1, const Time& time2)   // use operator > overloading, only need to change parameter position
{
    return !(time1 > time2);       // it's equal to time1 < time2           
}

bool operator ==(const Time& time1, const Time& time2)
{
    int total_second_t1 = time1.hour*3600 + time1.minute*60 + time1.second;
    int total_second_t2 = time2.hour*3600 + time2.minute*60 + time2.second;
    return total_second_t1 == total_second_t2;
}

bool operator !=(const Time& time1, const Time& time2)
{
    return !(time1 == time2);
}

bool operator >=(const Time& time1, const Time& time2)
{
    return time1 > time2 || time1 == time2;
}

bool operator <=(const Time& time1, const Time& time2)
{
    return !(time1 > time2);
}

std::ostream& operator <<(std::ostream& os, const Time& time)
{
    os <<  std::setfill('0') << std::setw(2) << time.hour 
       << ":" << std::setw(2) << time.minute 
       << ":" << std::setw(2) << time.second;
    return os;
}

std::istream& operator >>(std::istream& is, Time& time)
{
    char colon1{};
    char colon2{};
    Time tmp_time;

    is >> tmp_time.hour >> colon1 >> tmp_time.minute >> colon2 >> tmp_time.second;
    if(!is_valid(tmp_time) || colon1 != ':' || colon2 != ':')
    {
        is.setstate(std::ios::failbit);
    } else {
        time = tmp_time;
    }
    return is;
}