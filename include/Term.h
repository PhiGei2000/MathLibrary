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

struct ValueTerm : public Term {
private:
	double m_value = 0;

public:
	ValueTerm(double value);

	bool isConstant() const override;
	double getValue() const override;
};