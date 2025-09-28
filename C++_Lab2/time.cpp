#include <iostream>
#include <string>
#include <iomanip>
#include "time.hpp"

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

std::string to_string(const Time& time, int format) //24-hour or 12-hour clock format
{
    std::string format_time;
    Time time_tmp{};
    if(format == 24)                                // 24 hour format time
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
        return format_time = time_zero_padding(time_tmp) + " " + is_am(time);
    }
}

std::string time_zero_padding(const Time& time)
{
    std::string hour_str = (time.hour < 10) ? "0" + std::to_string(time.hour) : std::to_string(time.hour);
    std::string minute_str = (time.minute < 10) ? "0" + std::to_string(time.minute) : std::to_string(time.minute);
    std::string second_str = (time.second < 10) ? "0" + std::to_string(time.second) : std::to_string(time.second);
    return hour_str + ":" + minute_str + ":" + second_str;
}

bool is_am(const Time &time) {
    return time.hour < 12;  
}
std::string am_pm(const Time &time) {
    return time.hour < 12 ? "am" : "pm";
}

Time time_normalization(Time &time)    // deal with non-normal time, like hour > 24, minute&second > 60
{
    int total_second = time.hour * 3600 + time.minute * 60 + time.second;
    int n;
    if (total_second < 0)
    {        
        n = -total_second / 86400 + 1;
        total_second += 24 * 3600 * n;      // if the result is negtive, need rollback n day
    }
    if (total_second >= 0 && total_second / 86400 >= 1){
        n = total_second / 86400 + 1;
        total_second -= 24 * 3600 * (n - 1);
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
    return total_second_t1 > total_second_t2 ? true : false ;
}

bool operator <(const Time& time1, const Time& time2)   // use operator > overloading, only need to change parameter position
{
    return time2 > time1;       // it's equal to time1 < time2           
}

bool operator ==(const Time& time1, const Time& time2)
{
    int total_second_t1 = time1.hour*3600 + time1.minute*60 + time1.second;
    int total_second_t2 = time2.hour*3600 + time2.minute*60 + time2.second;
    return total_second_t1 == total_second_t2 ? true : false ;
}

bool operator !=(const Time& time1, const Time& time2)
{
    return time1 == time2 ? false : true;
}

bool operator >=(const Time& time1, const Time& time2)
{
    return (time1 > time2 || time1 == time2) ? true : false;
}

bool operator <=(const Time& time1, const Time& time2)
{
    return (time1 < time2 || time1 == time2) ? true : false;
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
        char colon1, colon2;
    if (is >> time.hour >> colon1 >> time.minute >> colon2 >> time.second && colon1 == ':' && colon2 == ':') {
        Time tmp{time.hour, time.minute, time.second};
        if (is_valid(tmp)) {
            time = tmp; 
        } else {
            is.setstate(std::ios::failbit);
        }
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

