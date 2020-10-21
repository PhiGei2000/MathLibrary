#pragma once
#include "Term.h"

struct Variable : public Term {
private:
	char m_name;

public:
	Variable(const char& name);

	operator char() const;
};