#include "../include/Term.hpp"
#include "../include/Value.hpp"
#include <cmath>
#include <sstream>

Term::Term()
    : m_operator{Operator::ADD}, m_left{nullptr}, m_right{nullptr} {
}

Term::Term(Operator _operator, Term* left, Term* right)
    : m_operator{_operator}, m_left{left}, m_right{right} {
    if (m_left)
        m_left->m_parent = this;

    if (m_right)
        m_right->m_parent = this;
}

Term::Term(const Term& other)
    : m_operator{other.m_operator}, m_left{other.m_left}, m_right{other.m_right} {
    if (m_left)
        m_left->m_parent = this;

    if (m_right)
        m_right->m_parent = this;
}

Term::~Term() {
    if (m_left != nullptr) {
        m_left->~Term();
    }
    delete m_left;

    if (m_right != nullptr) {
        m_right->~Term();
    }
    delete m_right;
}

bool Term::isValue() const {
    return false;
}

bool Term::isVariable() const {
    return false;
}

bool Term::isConstant() const {
    return (m_left->isConstant() && m_right->isConstant());
}

double Term::getValue() const {
    switch (m_operator) {
    case Operator::ADD:
        return m_left->getValue() + m_right->getValue();
    case Operator::MUL:
        return m_left->getValue() * m_right->getValue();
    case Operator::POW:
        return std::pow(m_left->getValue(), m_right->getValue());
    default:
        return 0;
    }
}

Term* Term::simplify() {
    if (this->isConstant()) {
        return new Value(this->getValue());
    }
    else {
        if (m_left->isConstant() && m_right->m_operator == m_operator) {
            double leftValue = m_left->getValue();
            if (m_right->m_left->isConstant()) {
                double rightValue = m_right->m_left->getValue();
                return new Term(m_operator,
                                new Value(Term::getValue(m_operator, leftValue, rightValue)),
                                m_right->m_right);
            }
            else if (m_right->m_right->isConstant()) {
                double rightValue = m_right->m_right->getValue();
                return new Term(m_operator,
                                new Value(Term::getValue(m_operator, leftValue, rightValue)),
                                m_right->m_left);
            }
        }
    }
    return this;
}

double Term::getValue(const Operator& _operator, const double& left, const double& right) {
    switch (_operator) {
    case Operator::ADD:
        return left + right;
    case Operator::MUL:
        return left * right;
    case Operator::POW:
        return pow(left, right);
    default:
        return 0;
    }
}

std::string Term::toString() const {
    bool leftBrackets = m_left->m_operator < m_operator;
    bool rightBrackets = m_right->m_operator < m_operator;

    std::stringstream ss;
    if (leftBrackets) {
        ss << '(';
    }

    ss << m_left->toString();

    if (leftBrackets) {
        ss << ')';
    }

    switch (m_operator) {
    case Operator::ADD:
        ss << '+';
        break;
    case Operator::MUL:
        ss << '*';
        break;
    case Operator::POW:
        ss << '^';
        break;
    }

    if (rightBrackets) {
        ss << '(';
    }

    ss << m_right->toString();

    if (rightBrackets) {
        ss << ')';
    }

    return ss.str();
}

Term* Term::getLeft() const {
    return m_left;
}

Term* Term::getRight() const {
    return m_right;
}

Operator Term::getOperator() const {
    return m_operator;
}

void Term::setLeft(Term* value) {
    m_left = value;
}

void Term::setRight(Term* value) {
    m_right = value;
}

void Term::setOperator(const Operator& _operator) {
    m_operator = _operator;
}
