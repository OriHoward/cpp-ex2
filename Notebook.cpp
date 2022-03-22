
#include "Notebook.hpp"
#include <iostream>
#include <stdexcept>
#include "Direction.hpp"
#include <string>
#include <vector>
#include <unordered_map>


namespace ariel {
    using std::string;
    using std::unordered_map;

    Notebook::Notebook() {
        this->notebookMap = unordered_map<unsigned int, unordered_map<unsigned int, vector<char>>>();

    }

    Notebook::~Notebook() {
    }

    void Notebook::write(unsigned int page, unsigned int row, unsigned int col, Direction direction,
                         const string &toWrite) {

        this->notebookMap[page][row] = std::vector<char>();
        this->notebookMap.find(page);
//        this->notebookMap.find(page)
        std::cout << "he";
    }

    string Notebook::read(unsigned int page, unsigned int row, unsigned int col, Direction direction,
                          unsigned int numOfChar) {
        this->notebookMap.find(page);
        std::cout << "he";
        return "";
    }

    void
    Notebook::erase(unsigned int page, unsigned int row, unsigned int col, Direction direction,
                    unsigned int numOfChar) {
        this->notebookMap.find(page);
        std::cout << "he";
    }

    void Notebook::show(unsigned int page) {
        this->notebookMap.find(page);
        std::cout << "he";
    }


}