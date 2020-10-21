#pragma once
#include <string>

enum class Operator { ADD,
                      MUL,
                      POW };

struct Term {
  protected:
    Term* m_parent;

    Term* m_left;
    Term* m_right;
    Operator m_operator;

  public:
    Term();
    Term(Operator _operator, Term* left, Term* right);
    Term(const Term& other);
    ~Term();

    virtual bool isValue() const;
    virtual bool isVariable() const;
    virtual bool isConstant() const;

    virtual double getValue() const;

    virtual Term* simplify();

    static double getValue(const Operator& _operator, const double& left, const double& right);

    virtual std::string toString() const;

    Term* getLeft() const;
    Term* getRight() const;
    Operator getOperator() const;

    void setLeft(Term* value);
    void setRight(Term* value);
    void setOperator(const Operator& _operator);

};

