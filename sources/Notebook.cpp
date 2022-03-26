
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

    bool Notebook::isNotEmpty(int page) {
        return bool(this->notebookMap.count(page));
    }

    void Notebook::checkStrInput(const string &strToCheck) {
        for (string::size_type i = 0; i < strToCheck.size(); ++i) {
            if (isprint(strToCheck.at(i)) == 0 || strToCheck.at(i) == '~') {
                throw std::invalid_argument("bad input");
            }
        }
    }

    void Notebook::checkNegativeLen(int len) {
        if (len < 0) {
            throw std::invalid_argument("len must be positive");
        }
    }

    void Notebook::checkInput(int page, int row, int col) {
        if (page < 0 || col < 0 || row < 0 || col > MAX_COL) {
            throw std::invalid_argument("bad input - page and row must be positive and col between 0 to 100");
        }
    }

    void Notebook::checkValidLen(const string &toWrite, int col) {
        if (int(toWrite.size()) + col > MAX_COL) {
            throw std::invalid_argument("String is exceeding row limit");
        }
    }

    void Notebook::checkValidLen(int col, int numOfChars) {
        if (numOfChars + col > MAX_COL) {
            throw std::invalid_argument("exceeding row limit");
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


    void Notebook::write(int page, int row, int col, Direction direction, const string &toWrite) {
        checkInput(page, row, col);
        checkStrInput(toWrite);
        if (direction == Direction::Horizontal) {
            checkValidLen(toWrite, col);
            HandleWriteH(page, row, (unsigned int) col, toWrite);
        } else {
            HandleWriteV(page, row, (unsigned int) col, toWrite);
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
        checkInput(page, row, col);
        checkNegativeLen(numOfChars);
//        if (!this->isNotEmpty(page)) {
//            return "";
//        }

        string wordRead;
        if (direction == Direction::Horizontal) {
            checkValidLen(col, numOfChars);
            HandleReadH(page, row, (unsigned int) col, numOfChars, wordRead);
        } else {
            HandleReadV(page, row, (unsigned int) col, numOfChars, wordRead);
        }
        return wordRead;
    }

    void Notebook::HandleReadH(int page, int row, unsigned int col, int numOfChars, string &wordRead) {
        Page &currPage = this->getPage(page);
        std::vector<char> &currRow = currPage.getRow(row);
        for (string::size_type i = 0; i < numOfChars; ++i) {
            char charRead = currRow.at(col + i);
            wordRead += charRead;
        }
    }

    void Notebook::HandleReadV(int page, int row, unsigned int col, int numOfChars, string &wordRead) {
        Page &currPage = this->getPage(page);
        for (string::size_type i = 0; i < numOfChars; ++i) {
            std::vector<char> &currRow = currPage.getRow(i);
            char charRead = currRow.at(col);
            wordRead += charRead;
        }
    }

    void
    Notebook::erase(int page, int row, int col, Direction direction, int numOfChars) {
        checkInput(page, row, col);
        checkNegativeLen(numOfChars);
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
//            if (currRow.at(col) != '~') {
//                throw std::invalid_argument("Cannot delete what has been deleted");
//            }
            currRow.at(col) = '~';
        }
    }

    void Notebook::show(int page) {
        if (page < 0) {
            throw std::invalid_argument("Page must be positive!");
        }
        if (!this->isNotEmpty(page)) {
            return;
        }
        int numOfRowsToShow = 0;
        std::cout << "Enter the number of rows you would like to see: " << std::endl;
        std::cin >> numOfRowsToShow;
        for (int i = 0; i <= numOfRowsToShow; ++i) {
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

