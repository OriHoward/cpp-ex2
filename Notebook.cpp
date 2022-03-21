
#include "Notebook.hpp"
#include <iostream>
#include <stdexcept>
#include "Direction.hpp"


namespace ariel {
    using std::string;

    void Notebook::write(unsigned int page, unsigned int row, unsigned int col, Direction direction,
                         const string &toWrite) {
        std::cout << "he";
    }

    string Notebook::read(unsigned int page, unsigned int row, unsigned int col, Direction direction,
                          unsigned int numOfChar) {
        std::cout << "he";
        return "";
    }

    void
    Notebook::erase(unsigned int page, unsigned int row, unsigned int col, Direction direction,
                    unsigned int numOfChar) {
        std::cout << "he";
    }

    void Notebook::show(unsigned int page) {
        std::cout << "he";
    }
}