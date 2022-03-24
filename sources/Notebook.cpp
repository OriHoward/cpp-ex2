
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

    Page &Notebook::getPage(int page) {
        if (this->notebookMap.count(page) == 0) {
            this->notebookMap[page] = Page();
        }
        return this->notebookMap[page];
    }

    void Notebook::checkStrInput(const string &strToCheck) {
        if (contains(strToCheck, "\n") || contains(strToCheck, "\r") || contains(strToCheck, "~") ||
            contains(strToCheck, "\0") || contains(strToCheck, "\t")) {
            throw std::invalid_argument("bad input");
        }
    }

    bool Notebook::contains(const string &str, const string &str2) {
        return str.find(str2) != std::string::npos;
    }

    void Notebook::write(int page, int row, int col, Direction direction, const string &toWrite) {
        checkStrInput(toWrite);
        if (direction == Direction::Horizontal) {
            if (int(toWrite.size()) + col > MAX_COL) {
                throw std::invalid_argument("bad input");
            }
        }
        Page &currPage = this->getPage(page);
        std::vector<char> currVec = currPage.getRow(row);
        unsigned int newCol = (unsigned int) col;
        for (string::size_type i = 0; i < toWrite.size(); ++i) {
            currVec.at(newCol + i) = toWrite.at(i);
        }

        std::cout << "he";
    }

    string Notebook::read(int page, int row, int col, Direction direction, int numOfChar) {

        std::cout << "he";
        return "";
    }

    void
    Notebook::erase(int page, int row, int col, Direction direction, int numOfChar) {
        this->notebookMap.find(page);
        std::cout << "he";
    }

    void Notebook::show(int page) {
        this->notebookMap.find(page);
        std::cout << "he";
    }
}

