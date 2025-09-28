#include "catch_amalgamated.hpp"
#include "time.hpp"

TEST_CASE("create a time")
{
    Time time{10,10,10};
    CHECK(time.hour == 10);
    CHECK(time.minute == 10);
    CHECK(time.second == 10);
}

TEST_CASE("check time is vaild")
{
    Time time1{10,10,10};   // valid
    Time time2{10,10,60};   // not valid
    Time time3{10,60,10};   // not valid  
    Time time4{25,10,10};   // not valid

    CHECK(is_valid(time1)); 
    CHECK(!is_valid(time2));
    CHECK_FALSE(is_valid(time2));
    CHECK_FALSE(is_valid(time3));
    CHECK_FALSE(is_valid(time4));
}

TEST_CASE("pad zero at the front of time")
{
    Time time{1,0,9};
    CHECK(time_zero_padding(time) == "01:00:09");
}

TEST_CASE("get a time as a string use 24 format or 12 format")
{
    Time time1{0,3,40};   
    Time time2{12,30,24};
    
    CHECK(to_string(time1,24) == "00:03:40");
    CHECK(to_string(time1,12) == "12:03:40 am");
    CHECK(to_string(time2,12) == "12:30:24 pm");
}

TEST_CASE("judge time hour is am or pm")
{
    Time time1{12,23,23};
    Time time2{0,23,23};

    CHECK(am_pm(time1) == "pm");
    CHECK(am_pm(time2) == "am");
    CHECK_FALSE(is_am(time1));
    CHECK(is_am(time2));
}
TEST_CASE("test non-normal time convert to a normal time")
{
    Time time1{23,58,70};
    CHECK(time_normalization(time1).hour == 23);
    CHECK(time_normalization(time1).minute == 59);
    CHECK(time_normalization(time1).second == 10);

    Time time2{0,0,-20};
    CHECK(time_normalization(time2).hour == 23);
    CHECK(time_normalization(time2).minute == 59);
    CHECK(time_normalization(time2).second == 40);
}

TEST_CASE("test time plus second, [operator +]")
{
    Time time1{23,59,59};      
    Time time2{};
    time2 = time1 + 1;          // span a day
    Time time_result1{0,0,0};
    CHECK(time2.second == time_result1.second);
    CHECK(time2.minute == time_result1.minute);
    CHECK(time2.hour == time_result1.hour);

    Time time3{0,0,10};
    Time time4{};
    time4 = time3 + 86400;      // plus a day
    Time time_result2{0,0,10};
    CHECK(time4.second == time_result2.second);
    CHECK(time4.minute == time_result2.minute);
    CHECK(time4.hour == time_result2.hour);

    Time time5{23,59,10};      
    Time time6{};
    time6 = time5 + 3600;          // plus a hour
    Time time_result3{0,59,10};
    CHECK(time6.second == time_result3.second);
    CHECK(time6.minute == time_result3.minute);
    CHECK(time6.hour == time_result3.hour);
}

TEST_CASE("test second plus time, [operator +]")
{
    Time time1{23,59,59};      
    Time time2{};
    time2 = 1 + time1;          // span a day
    Time time_result1{0,0,0};
    CHECK(time2.second == time_result1.second);
    CHECK(time2.minute == time_result1.minute);
    CHECK(time2.hour == time_result1.hour);

    Time time3{0,0,10};
    Time time4{};
    time4 = 86400 + time3;      // plus a day
    Time time_result2{0,0,10};
    CHECK(time4.second == time_result2.second);
    CHECK(time4.minute == time_result2.minute);
    CHECK(time4.hour == time_result2.hour);

    Time time5{23,59,10};      
    Time time6{};
    time6 = 3600 + time5;          // plus a hour
    Time time_result3{0,59,10};
    CHECK(time6.second == time_result3.second);
    CHECK(time6.minute == time_result3.minute);
    CHECK(time6.hour == time_result3.hour);

    Time time7{};
    time7 = 3 * 86400 + time3;
    Time time_result4{0,0,10};     //plus 3 days
    CHECK(time7.second == time_result4.second);
    CHECK(time7.minute == time_result4.minute);
    CHECK(time7.hour == time_result4.hour);
}

TEST_CASE("test time minus second, [operator -]")
{
    Time time1{0,0,2};      
    Time time2{};
    time2 = time1 - 3;          // roolback a day
    Time time_result1{23,59,59};
    CHECK(time2.second == time_result1.second);
    CHECK(time2.minute == time_result1.minute);
    CHECK(time2.hour == time_result1.hour);

    Time time3{0,10,10};
    Time time4{};
    time4 = time3 - 86400;      // minus a day
    Time time_result2{0,10,10};
    CHECK(time4.second == time_result2.second);
    CHECK(time4.minute == time_result2.minute);
    CHECK(time4.hour == time_result2.hour);

    Time time5{0,59,10};      
    Time time6{};
    time6 = time5 - 3600;        // minus a hour
    Time time_result3{23,59,10};
    CHECK(time6.second == time_result3.second);
    CHECK(time6.minute == time_result3.minute);
    CHECK(time6.hour == time_result3.hour);
}

TEST_CASE("test second minus time, [operator -]")
{
    Time time1{0,0,2};      
    Time time2{};
    time2 = 3 - time1;          // roolback a day
    Time time_result1{23,59,59};
    CHECK(time2.second == time_result1.second);
    CHECK(time2.minute == time_result1.minute);
    CHECK(time2.hour == time_result1.hour);

    Time time3{0,10,10};
    Time time4{};
    time4 = 86400 - time3;      // minus a day
    Time time_result2{0,10,10};
    CHECK(time4.second == time_result2.second);
    CHECK(time4.minute == time_result2.minute);
    CHECK(time4.hour == time_result2.hour);

    Time time5{0,59,10};      
    Time time6{};
    time6 = 3600 - time5;        // minus a hour
    Time time_result3{23,59,10};
    CHECK(time6.second == time_result3.second);
    CHECK(time6.minute == time_result3.minute);
    CHECK(time6.hour == time_result3.hour);

    Time time7{};
    time7 = time3 - 3 * 86400;
    Time time_result4{0,10,10};   //minus 3 days
    CHECK(time7.second == time_result4.second);
    CHECK(time7.minute == time_result4.minute);
    CHECK(time7.hour == time_result4.hour);
}

TEST_CASE("test ++time, [operator prefix ++]")
{
    Time time1{10,10,59};
    Time time_result1{++ time1};
    CHECK(time1.hour == 10);
    CHECK(time1.minute == 11);
    CHECK(time1.second == 0);
    CHECK(time_result1.hour == time1.hour);
    CHECK(time_result1.minute == time1.minute);
    CHECK(time_result1.second == time1.second);

    Time time2{23,59,59};
    Time time_result2{++ time2};
    CHECK(time2.hour == 0);
    CHECK(time2.minute == 0);
    CHECK(time2.second == 0);
    CHECK(time_result2.hour == time2.hour);
    CHECK(time_result2.minute == time2.minute);
    CHECK(time_result2.second == time2.second);

}

TEST_CASE("test time++, [operator postfix ++]")
{
    Time time1{10,10,59};
    Time time_result1{time1 ++};
    CHECK(time1.hour == 10);
    CHECK(time1.minute == 11);
    CHECK(time1.second == 0);
    CHECK(time_result1.hour == 10);
    CHECK(time_result1.minute == 10);
    CHECK(time_result1.second == 59);

    Time time2{23,59,59};
    Time time_result2{time2 ++};
    CHECK(time2.hour == 0);
    CHECK(time2.minute == 0);
    CHECK(time2.second == 0);
    CHECK(time_result2.hour == 23);
    CHECK(time_result2.minute == 59);
    CHECK(time_result2.second == 59);
}

TEST_CASE("test --time, [operator prefix --]")
{
    Time time1{10,10,0};
    Time time_result1{-- time1};
    CHECK(time1.hour == 10);
    CHECK(time1.minute == 9);
    CHECK(time1.second == 59);
    CHECK(time_result1.hour == time1.hour);
    CHECK(time_result1.minute == time1.minute);
    CHECK(time_result1.second == time1.second);

    Time time2{0,0,0};
    Time time_result2{-- time2};
    CHECK(time2.hour == 23);
    CHECK(time2.minute == 59);
    CHECK(time2.second == 59);
    CHECK(time_result2.hour == time2.hour);
    CHECK(time_result2.minute == time2.minute);
    CHECK(time_result2.second == time2.second);
}

TEST_CASE("test time--, [operator postfix --]")
{
    Time time1{10,10,0};
    Time time_result1{time1 --};
    CHECK(time1.hour == 10);
    CHECK(time1.minute == 9);
    CHECK(time1.second == 59);
    CHECK(time_result1.hour == 10);
    CHECK(time_result1.minute == 10);
    CHECK(time_result1.second == 0);

    Time time2{0,0,0};
    Time time_result2{time2 --};
    CHECK(time2.hour == 23);
    CHECK(time2.minute == 59);
    CHECK(time2.second == 59);
    CHECK(time_result2.hour == 0);
    CHECK(time_result2.minute == 0);
    CHECK(time_result2.second == 0);
}

TEST_CASE("compare two time, [opeartor > & < ]")
{
    Time time1{20,10,10};
    Time time2{10,10,10};

    CHECK(time1 > time2);
    CHECK_FALSE(time2 > time1);
    CHECK(time2 < time1);
    CHECK_FALSE(time1 < time2);
}

TEST_CASE("compare two time, [opeartor == && !=]")
{
    Time time1{20,10,10};
    Time time2{20,10,10};
    Time time3{10,10,10};

    CHECK(time1 == time2);
    CHECK_FALSE(time1 == time3);
    CHECK(time1 != time3);
    CHECK_FALSE(time1 != time2);
}

TEST_CASE("compare two time, [opeartor >= && <=]")
{
    Time time1{20,10,10};
    Time time2{20,10,10};
    Time time3{10,10,10};

    CHECK(time1 >= time2);
    CHECK(time1 >= time3);
    CHECK_FALSE(time3 >= time2);
    CHECK(time1 <= time2);
    CHECK(time3 <= time2);
    CHECK_FALSE(time2 <= time3);
}

TEST_CASE("format output a time, [operator <<]")
{
    std::ostringstream oss{};
    Time time{1,2,30};
    oss << time;
    CHECK(oss.str() == "01:02:30");
}

TEST_CASE("format input a time, [operator >>]")
{
    std::istringstream iss1{"24:66:30"};
    Time time1{};
    iss1 >> time1;
    CHECK(iss1.fail());

    std::istringstream iss2{"24,66,30"};
    Time time2{};
    iss2 >> time2;
    CHECK(iss2.fail());

    std::istringstream iss3{"11,2"};
    Time time3{};
    iss3 >> time3;
    CHECK(iss3.fail());

    std::istringstream iss4{"99:99:99"};
    Time time4{};
    iss4 >> time4;
    CHECK(iss4.fail());

    std::istringstream iss{"23:20:30"};
    Time time{};
    iss >> time;
    CHECK_FALSE(iss.fail());
    CHECK(to_string(time,24) == "23:20:30");
}
