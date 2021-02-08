#pragma once

#include <iostream>

class Date {
public:
	// конструкторы
	Date();
	Date(const int& year, const int& month, const int& day);
	// получение данных даты
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	const int year, month, day;
};

// вывод в поток
std::ostream& operator<<(std::ostream& stream, const Date& date);

// функция считывание из потока
Date ParseDate(std::istream& stream);

// операторы сравнения
bool operator<(const Date& left, const Date& right);
bool operator==(const Date& left, const Date& right);