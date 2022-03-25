
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
            contains(strToCheck, "\t")) {
            throw std::invalid_argument("bad input");
        }
    }

    void Notebook::checkValidLen(const string &toWrite, int col) {
        if (int(toWrite.size()) + col > MAX_COL) {
            throw std::invalid_argument("String is exceeding row limit");
        }
    }

    bool Notebook::isCleanH(std::vector<char> &currRow, unsigned int col, unsigned int wordLen) {
        for (string::size_type i = 0; i < wordLen; ++i) {
            if (currRow[col + i] != '_') {
                return false;
            }
        }
        return true;
    }

    bool Notebook::isCleanV(Page &currPage, int row, unsigned int col, unsigned int wordLen) {
        for (int i = 0; i < wordLen; ++i) {
            std::vector<char> currRow = currPage.getRow(row + i);
            if (currRow.at(col) != '_') {
                return false;
            }
        }
        return true;
    }

    bool Notebook::contains(const string &str, const string &str2) {
        return str.find(str2) != std::string::npos;
    }

    void Notebook::write(int page, int row, int col, Direction direction, const string &toWrite) {
        checkStrInput(toWrite);
        if (direction == Direction::Horizontal) {
            checkValidLen(toWrite, col);
            HandleWriteH(page, row, col, toWrite);
        } else {
            HandleWriteV(page, row, col, toWrite);
        }
    }

    void Notebook::HandleWriteH(int page, int row, int col, const std::string &toWrite) {
        Page &currPage = this->getPage(page);
        std::vector<char> &currRow = currPage.getRow(row);
        unsigned int newCol = (unsigned int) col;
        if (!isCleanH(currRow, newCol, toWrite.size())) {
            throw std::invalid_argument("Cannot overwrite other word");
        }
        for (string::size_type i = 0; i < toWrite.size(); ++i) {
            currRow.at(newCol + i) = toWrite.at(i);
        }
    }

    void Notebook::HandleWriteV(int page, int row, int col, const std::string &toWrite) {
        Page &currPage = this->getPage(page);
        unsigned int newCol = (unsigned int) col;
        if (!isCleanV(currPage, row, newCol, toWrite.size())) {
            throw std::invalid_argument("Cannot overwrite other word");
        }

    }

    string Notebook::read(int page, int row, int col, Direction direction, int numOfChar) {

        return "";
    }

    void
    Notebook::erase(int page, int row, int col, Direction direction, int numOfChar) {
        this->notebookMap.find(page);
    }

    void Notebook::show(int page) {
        std::vector<char> toShow = this->notebookMap.at(page).getRow(0);
        std::cout << toShow.at(0) << toShow.at(1) << toShow.at(2) << std::endl;
    }
}

