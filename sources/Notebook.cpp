
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

    void Notebook::checkValidLen(int numOfChars, int col) {
        if (numOfChars + col > MAX_COL) {
            throw std::invalid_argument("Exceeding row limit");
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
        checkValidLen(numOfChars, col);

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
//        if (isEmpty(page)) {  // NEED TO CHECK IF I SHOULD DO THAT
//            std::cout << "asd";
//            return;
//        }
//        std::cout << "asad";
        unsigned int newCol = (unsigned int) col;
        if (direction == Direction::Horizontal) {
            HandleEraseH(page, row, newCol, numOfChars);
        } else {
            HandleEraseV(page, row, newCol, numOfChars);
        }

    }

    void Notebook::HandleEraseH(int page, int row, unsigned int col, int numOfChars) {
        Page &currPage = this->getPage(page);
        std::vector<char> &currRow = currPage.getRow(row);
        for (string::size_type i = 0; i < numOfChars; ++i) {
            currRow.at(col + i) = '~';
        }
    }

    void Notebook::HandleEraseV(int page, int row, unsigned int col, int numOfChars) {
        Page &currPage = this->getPage(page);
        for (string::size_type i = 0; i < numOfChars; ++i) {
            std::vector<char> &currRow = currPage.getRow(row + int(i));
            currRow.at(col) = '~';
        }
    }

    void Notebook::show(int page) {
        int numOfRowsToShow = 0;
        std::cout << "Enter the number of rows you would like to see: " << std::endl;
        std::cin >> numOfRowsToShow;
        for (int i = 0; i < numOfRowsToShow; ++i) {
            std::vector<char> &currRow = this->notebookMap.at(page).getRow(i);
            if (!this->isCleanH(currRow, 0, MAX_COL)) {
                std::cout << i << ": ";
                for (unsigned int col = 0; col < MAX_COL; ++col) {
                    std::cout << currRow.at(col);
                }
                std::cout << "\n";
            }
        }

    }
}

