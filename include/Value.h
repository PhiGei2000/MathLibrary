#pragma once
#include "Term.h"

struct Value : public Term {
private:
	double m_value = 0;

public:
	Value(const double& value);

	bool isConstant() const override;
	double getValue() const override;

	operator double() const;
};