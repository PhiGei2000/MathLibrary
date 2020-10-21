#include "../include/Varable.hpp"
#include <sstream>

Variable::Variable(const char& name)
    : m_name{name}, Term{} {
}

Variable::Variable(const Variable& other)
    : m_name{other.m_name} {
}

bool Variable::isVariable() const {
    return true;
}

bool Variable::isConstant() const {
    return false;
}

double Variable::getValue() const {
    return 0;
}

Term* Variable::simplify() {
    return this;
}

Variable::operator char() const {
    return m_name;
}

std::string Variable::toString() const {
    std::stringstream ss;
    ss << m_name;
    return ss.str();
}
