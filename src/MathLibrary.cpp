#include "../include/TermParser.h"

#include <iostream>
#include <sstream>

int main()
{
    std::string line;
    while (true) {
        std::getline(std::cin, line);

        Term* term = TermParser::parse(line);

        if (term->isConstant()) {
            std::cout << term->getValue() << std::endl;
        }
    }
}

