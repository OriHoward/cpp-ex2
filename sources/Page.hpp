#include <iostream>
#include <stdexcept>
#include <string>
#include "Direction.hpp"
#include <unordered_map>
#include <vector>

#define MAX_COL 100

#ifndef CPP_EX2_PAGE_HPP
#define CPP_EX2_PAGE_HPP

class Page {

private:
    std::unordered_map<int, std::vector<char>> pageMap;
public:
    std::vector<char> &getRow(int row);

};

#endif
