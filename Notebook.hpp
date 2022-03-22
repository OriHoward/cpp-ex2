
#include <iostream>
#include <stdexcept>
#include <string.h>
#include "Direction.hpp"
#include <vector>
#include <unordered_map>

#ifndef CPP_EX2_NOTEBOOK_HPP
#define CPP_EX2_NOTEBOOK_HPP

using std::vector;
using std::unordered_map;

namespace ariel {
    class Notebook {
    private:
        unordered_map<unsigned int, unordered_map<unsigned int, vector<char>>> notebookMap;

    public:

        Notebook();

        ~Notebook();

        void
        write(unsigned int page, unsigned int row, unsigned int col, Direction direction, const std::string &toWrite);

        std::string
        read(unsigned int page, unsigned int row, unsigned int col, Direction direction, unsigned int numOfChar);

        void
        erase(unsigned int page, unsigned int row, unsigned int col, Direction direction, unsigned int numOfChar);

        void show(unsigned int page);
    };
}


#endif
