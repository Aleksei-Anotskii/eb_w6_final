#pragma once
#pragma warning(disable : 4996)

#include "date.h"
//#include "node.h"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <functional>

class Database {
public:
	// �������� ����� ������� event � ����� date
	void Add(const Date& date, const std::string& event);

	// ������� ��� ������� ��������������� �������
	int RemoveIf(std::function<bool(Date, std::string)> predicate);

	// ����� ������� ��������������� �������
	std::vector<std::pair<Date, std::string>> FindIf(
		const std::function<bool(const Date&, const std::string&)>& predicate) const;

	// ����������� ��� �������
	void Print(std::ostream& stream) const;

	// ����� ������� �� ����� �������� ����
	std::pair<Date, std::string> Last(const Date& date) const;
private:
	std::map<Date, std::vector<std::string>> Data_vec;
	std::map<Date, std::set<std::string>> Data_set;
};

// ����� � �����
std::ostream& operator<<(std::ostream& stream, const std::pair<Date, std::string>& date_event);