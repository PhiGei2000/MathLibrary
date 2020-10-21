#pragma once

enum class Operator { ADD, MUL, POW };

struct Term {
private:
	Term* m_left;
	Term* m_right;
	Operator m_operator;

public:
	Term();
	Term(Operator _operator, Term* left, Term* right);
	Term(const Term& other);

	virtual bool isConstant() const;	

	virtual double getValue() const;
};
