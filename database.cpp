#include "database.h"

#include <iostream>
#include <algorithm>

using namespace std;

// вывод в поток
ostream& operator<<(ostream& stream, const pair<Date, string>& date_event) {
	return stream << date_event.first << ' ' << date_event.second;
}

// добавить новое событие event с датой date
void Database::Add(const Date& date, const string& event) {
	if (Data_set[date].count(event)) {
		return;
	}
	else {
		Data_set[date].insert(event);
		Data_vec[date].push_back(event);
	}
};

// удалить все события удовлетворяющие условию
int  Database::RemoveIf(function<bool(Date, string)> predicate) {
	map<Date, vector<string>> new_Data_vec;
	Data_set.clear();
	int count = 0;
	for (const auto& item : Data_vec) {
		for (const auto& event : item.second) {
			if (predicate(item.first, event)) {
				++count;
			}
			else {
				new_Data_vec[item.first].push_back(event);
				Data_set[item.first].insert(event);
			}
		}
	}
	Data_vec = new_Data_vec;
	return count;
};

// найти события удовлетворяющие условию
vector<pair<Date, string>> Database::FindIf(
	const function<bool(const Date&, const string&)>& predicate) const {
	vector<pair<Date, string>> result;
	for (const auto& item : Data_vec) {
		for (const auto& event : item.second) {
			if (predicate(item.first, event)) {
				result.push_back(make_pair(item.first, event));
			}
		}
	}
	return result;
};

// найти событие не позже заданной даты
std::pair<Date, std::string> Database::Last(const Date& date) const {
	auto it = Data_vec.upper_bound(date);
	if (it == Data_vec.begin()) {
		throw invalid_argument("No entries");
	}
	--it;
	return make_pair(it->first, it->second[it->second.size() - 1]);
}

// распечатать все события
void Database::Print(ostream& stream) const {
	for (const auto& item : Data_vec) {
		for (auto event : item.second) {
			stream << item.first << " " << event << endl;
		}
	}
};