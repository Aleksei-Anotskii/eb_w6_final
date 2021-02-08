#pragma once

#include "date.h"

#include <string>
#include <memory>
#include <cstdint>

enum class LogicalOperation {
	Or,
	And
};

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

class Node
{
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node
{
public:
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);
	bool Evaluate(const Date& date, const std::string& event) const override;

private:
	const Comparison _cmp;
	const Date _date;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& cmp, const std::string& event);
	bool Evaluate(const Date& date, const std::string& event) const override;

private:
	const Comparison _cmp;
	const std::string _event;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& op,
		const std::shared_ptr<const Node>& left,
		const std::shared_ptr<const Node>& right);
	bool Evaluate(const Date& date, const std::string& event) const override;

private:
	const LogicalOperation _log_op;
	const std::shared_ptr<const Node> _left, _right;
};