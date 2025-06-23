#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date
{
public:
    // Constructor
    Date(void);
    Date(int y, int m, int d);

public:
    // Destructor
    virtual ~Date(void);

    // Setters
    void SetYear(int y);
    void SetMonth(int m);
    void SetDay(int d);

    // Getters
    int GetYear();
    int GetMonth();
    int GetDay();

    // Overloaded operator() for setting properties of Date object
    Date& operator()(int y, int m, int d);

    // Converts date attributes to string in "yy-mm-dd" format.
    string Format();

    // Overloaded comparison operators
    friend bool operator==(Date date1, Date date2);
    friend bool operator!=(Date date1, Date date2);

    // Overloaded standard input operator >> and operator << for I/O operations of Date object
    friend std::istream& operator>>(std::istream& in, Date& date);
    friend std::ostream& operator<<(std::ostream& out, Date& date);

private:
    int year;   // 1900-9999
    int month;  // 1-12
    int day;    // 1-31
};