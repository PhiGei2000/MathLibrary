#include "../include/TermParser.hpp"
#include "../include/Value.hpp"
#include "../include/Varable.hpp"

Term* TermParser::parseSum(const std::string& str) {
    size_t end = std::min(str.find('+'), str.find('-'));
    if (end < str.find(')') && end > str.find_first_of('(')) {
        return parseProduct(str);
    }

    if (end < str.size()) {
        std::string sumStr = str.substr(0, end);
        std::string restStr = str.substr(end + 1);

        Term* prod = parseProduct(sumStr);
        Term* rest = parseSum(restStr);

        if (str[end] == '-') {
            if (rest->isValue()) {
                rest = new Value(-rest->getValue());
            }
            else if (rest->isVariable()) {
                rest = new Term(Operator::MUL, new Value(-1), rest);
            }
            else {
                if (restStr[0] == '(') {
                    rest = new Term(Operator::MUL, new Value(-1), rest);
                }
                else {
                    Term* left = rest->getLeft();
                    Term* negativeLeft = new Term(Operator::MUL, new Value(-1), left);
                    rest->setLeft(negativeLeft);
                }
            }
        }

        return new Term(Operator::ADD, prod, rest);
    }
    else if (str.size() > 0) {
        return parseProduct(str);
    }
    else {
        return new Value(0);
    }
}

Term* TermParser::parseProduct(const std::string& str) {
    size_t end = std::min(str.find('*'), str.find('/'));

    if (end < str.size()) {
        std::string prodStr = str.substr(0, end);
        std::string restStr = str.substr(end + 1);

        Term* exp = parseExponentiation(prodStr);
        Term* rest = parseProduct(restStr);

        if (str[end] == '/') {
            return new Term(Operator::MUL, exp, new Term(Operator::POW, rest, new Value(-1)));
        }
        else {
            return new Term(Operator::MUL, exp, rest);
        }
    }
    else if (str.size() > 0) {
        return parseExponentiation(str);
    }
    else {
        return new Value(1);
    }
}

Term* TermParser::parseExponentiation(const std::string& str) {
    size_t end = str.find('^');

    if (end < str.size()) {
        std::string expStr = str.substr(0, end);
        std::string restStr = str.substr(end + 1);

        Term* inner;
        if (expStr[0] == '(') {
            inner = parseBrackets(expStr);
        }
        else {
            inner = parseValue(expStr);
        }

        Term* rest = parseExponentiation(restStr);

        return new Term(Operator::POW, inner, rest);
    }
    else if (str.size() > 0) {
        if (str[0] == '(') {
            return parseBrackets(str);
        }
        else {
            return parseValue(str);
        }
    }
    else {
        return new Value(1);
    }
}

Term* TermParser::parseBrackets(const std::string& str) {
    if (str[0] == '(') {
        int index = 0;
        int count = 0;

        do {
            if (str[index] == '(') {
                count++;
            }
            else if (str[index] == ')') {
                count--;
            }

            index++;
        } while (count != 0);

        int begin = 0;
        int end = index;

        std::string innerStr = str.substr(begin + 1, end - 2);
        Term* inner = parseBrackets(innerStr);

        if (end < str.size()) {
            std::string restStr = str.substr(end + 1);
            char _operator = str[end];
            Term* rest = parseBrackets(restStr);
            if (_operator == '+') {
                return new Term(Operator::ADD, inner, rest);
            }
            else if (_operator == '*') {
                return new Term(Operator::MUL, inner, rest);
            }
            else if (_operator == '^') {
                return new Term(Operator::POW, inner, rest);
            }
        }
        else {
            return inner;
        }
    }
    else {
        return parseSum(str);
    }
}

Term* TermParser::parseValue(const std::string& str) {
    if (str[0] >= 0x61 && str[0] <= 0x7A) {
        return new Variable(str[0]);
    }

    return new Value(std::stod(str));
}

Term* TermParser::parse(const std::string& str) {
    int index = 0;
    std::string newStr;
    while (index < str.size()) {
        if (str[index] != '\x20') {
            newStr += str[index];
        }

        index++;
    }

    Term* result = parseBrackets(newStr)->simplify();
    return result;
}
