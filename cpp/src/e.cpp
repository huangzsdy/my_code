#include <iostream>
using namespace std;

class Date;
class Time
{
public:
    Time(int h, int m, int s) :hour(h),minute(m),second(s){};
    void display(Date &);
private:
    int hour,minute,second;
};
class Date
{ 
public:
    Date(int, int, int);
    friend void Time::display(Date &);
private:
    int month, day, year;
};

Date::Date(int m, int d, int y)
{
    month = m;
    day = d;
    year = y;
}

void Time::display(Date &d)
{
    cout << "年:" << d.year << endl;
    cout << "月:" << d.month << endl;
    cout << "日:" << d.day << endl;
    cout << "时:" << hour << endl;
    cout << "分:" << minute << endl;
    cout << "秒:" << second << endl;

}
int main(int argc, char**argv)
{
    Time t1(10, 12, 54);
    Date d1(12, 23, 2003);
    t1.display(d1);
}
