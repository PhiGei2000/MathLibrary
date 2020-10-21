#pragma once
#include "Term.hpp"

struct Value : public Term {
  private:
    double m_value = 0;

	protected:
      bool isValue() const override;

    public:
      Value(const double& value);
      Value(const Value& other);

      bool isConstant() const override;
      double getValue() const override;

      Term* simplify() override;

      operator double() const;

      std::string toString() const override;
};