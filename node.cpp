#include "node.h"

using namespace std;

// реализация для класса EmptyNode
bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
};

// реализация для класса DateComparisonNode
DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
	: _cmp(cmp)
	, _date(date)
{};
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less) {
		return date < _date;
	}
	else if (_cmp == Comparison::LessOrEqual) {
		return !(_date < date);  // Not greater
	}
	else if (_cmp == Comparison::Greater) {
		return _date < date;
	}
	else if (_cmp == Comparison::GreaterOrEqual) {
		return !(date < _date); // Not less
	}
	else if (_cmp == Comparison::Equal) {
		return _date == date;
	}
	else if (_cmp == Comparison::NotEqual) {
		return !(_date == date);
	}
	else {
		throw logic_error("Unknown comparison token");
	}
};

// реализация для класса EventComparisonNode
EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event)
	: _cmp(cmp)
	, _event(event)
{};
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less) {
		return event < _event;
	}
	else if (_cmp == Comparison::LessOrEqual) {
		return event <= _event;
	}
	else if (_cmp == Comparison::Greater) {
		return event > _event;
	}
	else if (_cmp == Comparison::GreaterOrEqual) {
		return event >= _event;
	}
	else if (_cmp == Comparison::Equal) {
		return event == _event;
	}
	else if (_cmp == Comparison::NotEqual) {
		return event != _event;
	}
	else {
		throw logic_error("Unknown comparison token");
	}
};

// реализация для класса LogicalOperationNode
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op,
	const std::shared_ptr<const Node>& left,
	const std::shared_ptr<const Node>& right)
	: _log_op(op)
	, _left(left)
	, _right(right)
{};
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	if (_log_op == LogicalOperation::And) {
		return _left->Evaluate(date, event) && _right->Evaluate(date, event);
	}
	else if (_log_op == LogicalOperation::Or) {
		return _left->Evaluate(date, event) || _right->Evaluate(date, event);
	}
	else {
		throw logic_error("Unknown logical operation");
	}
};