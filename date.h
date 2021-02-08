#pragma once

#include <iostream>

class Date {
public:
	// ������������
	Date();
	Date(const int& year, const int& month, const int& day);
	// ��������� ������ ����
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	const int year, month, day;
};

// ����� � �����
std::ostream& operator<<(std::ostream& stream, const Date& date);

// ������� ���������� �� ������
Date ParseDate(std::istream& stream);

// ��������� ���������
bool operator<(const Date& left, const Date& right);
bool operator==(const Date& left, const Date& right);