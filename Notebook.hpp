
#include <iostream>
#include <stdexcept>
#include <string.h>
#include "Direction.hpp"

#ifndef CPP_EX2_NOTEBOOK_HPP
#define CPP_EX2_NOTEBOOK_HPP

namespace ariel {
    class Notebook {
    private:

    public:
        void write(unsigned int page, unsigned int row, unsigned int col, Direction direction, const std::string &toWrite);

        std::string
        read(unsigned int page, unsigned int row, unsigned int col, Direction direction, unsigned int numOfChar);

        void erase(unsigned int page, unsigned int row, unsigned int col, Direction direction, unsigned int numOfChar);

        void show(unsigned int page);
    };
}


#endif //CPP_EX2_NOTEBOOK_HPP
