#include "../include/Value.h"

Value::Value(const double& value)
	: m_value{ value }, Term{} {

}

bool Value::isConstant() const {
	return true;
}

double Value::getValue() const {
	return m_value;
}

Value::operator double() const {
	return m_value;
}
