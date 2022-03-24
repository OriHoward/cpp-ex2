#include <iostream>
#include <stdexcept>
#include <string>
#include "Direction.hpp"
#include <unordered_map>
#include <vector>
#include "Page.hpp"


std::vector<char> &Page::getRow(int row) {
    if (this->pageMap.count(row) == 0) {
        this->pageMap[row] = std::vector<char>(MAX_COL, '_');
        return this->pageMap[row];
    }
    return this->pageMap[row];
}






