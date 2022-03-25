
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

    bool Notebook::isEmpty(int page) {
        return bool(this->notebookMap.count(page));
    }

    void Notebook::checkStrInput(const string &strToCheck) {
        if (contains(strToCheck, "\n") || contains(strToCheck, "\r") || contains(strToCheck, "~") ||
            contains(strToCheck, "\t")) {
            throw std::invalid_argument("bad input");
        }
    }

    void Notebook::checkNegativeInput(int page, int row, int col) {
        if (page < 0 || col < 0 || row < 0) {
            throw std::invalid_argument("bad input - page row and col must be positive");
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
            std::vector<char> &currRow = currPage.getRow(row + i);
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
        checkNegativeInput(page, row, col);
        checkStrInput(toWrite);
        unsigned int newCol = (unsigned int) col;
        if (direction == Direction::Horizontal) {
            checkValidLen(toWrite, col);
            HandleWriteH(page, row, newCol, toWrite);
        } else {
            HandleWriteV(page, row, newCol, toWrite);
        }
    }

    void Notebook::HandleWriteH(int page, int row, unsigned int col, const std::string &toWrite) {
        Page &currPage = this->getPage(page);
        std::vector<char> &currRow = currPage.getRow(row);
        if (!isCleanH(currRow, col, toWrite.size())) {
            throw std::invalid_argument("Cannot overwrite other word");
        }
        for (string::size_type i = 0; i < toWrite.size(); ++i) {
            currRow.at(col + i) = toWrite.at(i);
        }
    }

    void Notebook::HandleWriteV(int page, int row, unsigned int col, const std::string &toWrite) {
        Page &currPage = this->getPage(page);
        if (!isCleanV(currPage, row, col, toWrite.size())) {
            throw std::invalid_argument("Cannot overwrite other word");
        }
        for (string::size_type i = 0; i < toWrite.size(); ++i) {
            std::vector<char> &currRow = currPage.getRow(row + int(i));
            currRow.at(col) = toWrite.at(i);
        }
    }

    string Notebook::read(int page, int row, int col, Direction direction, int numOfChars) {
        checkNegativeInput(page, row, col);
        if (numOfChars < 0) {
            throw std::invalid_argument("numOfChars must be positive");
        }

        string wordRead;
        if (this->isEmpty(page)) {
            throw std::invalid_argument("Page is empty");
        }
        if (direction == Direction::Horizontal) {
            HandleReadH(page, row, col, numOfChars, wordRead);
        } else {
            HandleReadV(page, row, col, numOfChars, wordRead);
        }
        return wordRead;
    }

    void Notebook::HandleReadH(int page, int row, int col, int numOfChars, string &wordRead) {
//        Page &currPage = this->getPage(page);
//        std::vector<char> currRow = currPage.getRow(row);
//        if (this->notebookMap[page].)
    }

    void Notebook::HandleReadV(int page, int row, int col, int numOfChars, string &wordRead) {

    }

    void
    Notebook::erase(int page, int row, int col, Direction direction, int numOfChars) {
        if (isEmpty(page)) {
            return;
        }
        unsigned int newCol = (unsigned int) col;
        unsigned int newRow = (unsigned int) row;
        if (direction == Direction::Horizontal) {
            HandleEraseH(page, row, newCol, numOfChars);
        } else {
            HandleEraseV(page, newRow, col, numOfChars);
        }

    }

    void Notebook::HandleEraseH(int page, int row, unsigned int col, int numOfChars) {
        Page &currPage = this->getPage(page);
        std::vector<char> &currRow = currPage.getRow(row);
        for (string::size_type i = 0; i < numOfChars; ++i) {
            if (currRow.at(col + i) != '~' && currRow.at(col + i) != '_') {
                currRow.at(col + i) = '~';
            }
        }

    }

    void Notebook::HandleEraseV(int page, unsigned int row, int col, int numOfChars) {

    }

    void Notebook::show(int page) {
        std::vector<char> toShow = this->notebookMap.at(page).getRow(0);
        std::cout << toShow.at(0) << toShow.at(1) << toShow.at(2) << std::endl;
    }
}

