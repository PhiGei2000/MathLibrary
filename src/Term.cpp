#include "../include/Term.h"
#include <cmath>

Term::Term()
	:m_operator{ Operator::ADD }, m_left{ nullptr }, m_right{ nullptr } {

}

Term::Term(Operator _operator, Term* left, Term* right)
	: m_operator{ _operator }, m_left{ left }, m_right{ right } {

}

Term::Term(const Term& other)
	: m_operator{ other.m_operator }, m_left{ other.m_left }, m_right{ other.m_right } {

}

bool Term::isConstant() const {
	return (m_left->isConstant() && m_right->isConstant());
}

//void Term::add(const Term& term) {
//	if (m_left == nullptr) {
//		m_left = new Term(term);
//	}
//	else if (m_right == nullptr) {
//		m_right = new Term(m_operator);
//		m_right->m_left = new Term(term);
//	}
//	else {
//		m_right->add(term);
//	}
//}

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
