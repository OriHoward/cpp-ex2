
#include <iostream>
#include <stdexcept>
#include <string>
#include "Direction.hpp"
#include <unordered_map>
#include <array>
#include "Page.hpp"

#ifndef CPP_EX2_NOTEBOOK_HPP
#define CPP_EX2_NOTEBOOK_HPP

#define MAX_COL 100
using std::unordered_map;

namespace ariel {
    class Notebook {
    private:
        unordered_map<int, Page> notebookMap;
    public:
        static void checkStrInput(const std::string &strToCheck);

        static void checkValidLen(const std::string &toWrite, int col);

        static void checkNegativeInput(int page, int row, int col);

        static bool contains(const std::string &str, const std::string &str2);

        static bool isCleanH(std::vector<char> &, unsigned int, unsigned int);

        static bool isCleanV(Page &, int, unsigned int, unsigned int);

        Page &getPage(int page);

        bool isEmpty(int page);

        void HandleWriteH(int page, int row, unsigned int col, const std::string &toWrite);

        void HandleWriteV(int page, int row, unsigned int col, const std::string &toWrite);

        void HandleReadH(int page, int row, int col, int numOfChars, std::string &wordRead);

        void HandleReadV(int page, int row, int col, int numOfChars, std::string &wordRead);

        void HandleEraseH(int page, int row, unsigned int col, int numOfChars);

        void HandleEraseV(int page, unsigned int row, int col, int numOfChars);

        void
        write(int page, int row, int col, Direction direction, const std::string &toWrite);

        std::string
        read(int page, int row, int col, Direction direction, int numOfChars);

        void
        erase(int page, int row, int col, Direction direction, int numOfChars);

        void show(int page);
    };
}


#endif
