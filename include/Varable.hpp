#pragma once
#include "Term.hpp"

struct Variable : public Term {
  private:
    char m_name;

  protected:
    bool isVariable() const override;

  public:
    Variable(const char& name);
    Variable(const Variable& other);

    bool isConstant() const override;
    double getValue() const override;

    Term* simplify() override;

    operator char() const;

    std::string toString() const override;
};