#include "Date.h"
#include "time.h"

Date::Date(void) {
	time_t now = time(NULL);
	struct tm t;
	localtime_s(&t,&now);
	this->year = t.tm_year + 1900;
	this->month = t.tm_mon + 1;
	this->day = t.tm_mday;
}

Date::Date(int y, int m, int d) {
	this->year = y;
	this->month = m;
	this->day = d;
}

Date::~Date(void) {

}

void Date::SetYear(int y) {
	year = y;
}

void Date::SetMonth(int m) {
	month = m;
}

void Date::SetDay(int d) {
	day = d;
}

int Date::GetYear() {
	return this->year;
}

int Date::GetMonth() {
	return this->month;
}

int Date::GetDay() {
	return this->day;
}

Date& Date::operator()(int y, int m, int d) {
	this->year = y;
	this->month = m;
	this->day = d;
	return *this;
}

string Date::Format() {
	string data;
	data = to_string(year % 100) + "--" + to_string(month) + "--" + to_string(day);
	return data;
}

bool operator==(Date date1, Date date2) {
	if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day)
		return true;
	else return false;
}

bool operator!=(Date date1, Date date2) {
	if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day)
		return false;
	else return true;
}

istream& operator>>(istream& in, Date& date) {
	in >> date.year >> date.month >> date.day;
	return in;
}

ostream& operator<<(ostream& out, Date& date) {
	out << date.year << " " << date.month << " " << date.day;
	return out;
}