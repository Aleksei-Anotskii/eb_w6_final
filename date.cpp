#include "date.h"

#include <iomanip>
#include <sstream>
#include <tuple>

using namespace std;

// конструкторы
Date::Date()
	: year(0)
	, month(0)
	, day(0)
{};
Date::Date(const int& year, const int& month, const int& day)
	: year(year)
	, month(month)
	, day(day)
{};

// получение данных даты
int Date::GetYear() const { return year; };
int Date::GetMonth() const { return month; };
int Date::GetDay() const { return day; };

// вывод в поток
ostream& operator<<(ostream& stream, const Date& date) {
	return stream << setfill('0') << setw(4) << date.GetYear() << '-'
		<< setw(2) << date.GetMonth() << '-' << setw(2) << date.GetDay();
}

// функция считывание из потока
Date ParseDate(istream& stream) {
	if (stream.peek() == ' ') {
		stream.ignore(1);
	}
	string date;

	getline(stream, date, ' ');
	stringstream date_stream(date);
	int year, month, day;
	char c;
	date_stream >> year >> c;
	if (c != '-' || !(date_stream >> month)) {
		throw runtime_error("Wrong date format: " + date);
	}
	date_stream >> c;
	if (c != '-' || !(date_stream >> day)) {
		throw runtime_error("Wrong date format: " + date);
	}
	if (date_stream >> c) {
		throw runtime_error("Wrong date format: " + date);
	}
	if (month > 12 || 1 > month) {
		throw runtime_error("Month value is invalid: " + to_string(month));
	}
	if (day > 31 || 1 > day) {
		throw runtime_error("Day value is invalid: " + to_string(day));
	}
	return Date(year, month, day);
};

// операторы сравнения
bool operator<(const Date& left, const Date& right) {
	return make_tuple(left.GetYear(), left.GetMonth(), left.GetDay())
		< make_tuple(right.GetYear(), right.GetMonth(), right.GetDay());
};
bool operator==(const Date& left, const Date& right) {
	return make_tuple(left.GetYear(), left.GetMonth(), left.GetDay())
		== make_tuple(right.GetYear(), right.GetMonth(), right.GetDay());
}