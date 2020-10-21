#include "../include/Value.hpp"
#include <sstream>

Value::Value(const double& value)
    : m_value{value}, Term{} {
}

Value::Value(const Value& other)
    : m_value{other.m_value} {
}

bool Value::isValue() const {
    return true;
}

bool Value::isConstant() const {
    return true;
}

double Value::getValue() const {
    return m_value;
}

Term* Value::simplify() {
    return this;
}

Value::operator double() const {
    return m_value;
}

std::string Value::toString() const {
    std::stringstream ss;
    ss << m_value;

    return ss.str();
}
