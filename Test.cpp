#include "doctest.h"
#include "sources/Notebook.hpp"
#include "sources/Direction.hpp"


using namespace ariel;

Notebook notebook;


TEST_CASE ("Bad input") {
    // string _ is not good
//            CHECK_THROWS(notebook.write(100, 30, 15, Direction::Horizontal, "_")); // need to check
    // tilda string
            CHECK_THROWS(notebook.write(50, 10, 37, Direction::Vertical, "~~~"));
            CHECK_THROWS(notebook.write(12, 10, 37, Direction::Horizontal, "~~~"));
    // \n or \t or \0 or \r in a middle of a string
            CHECK_THROWS(notebook.write(15, 14, 50, Direction::Horizontal, "aba\nhello"));
            CHECK_THROWS(notebook.write(8, 8, 88, Direction::Horizontal, "aba\tdadi"));
            CHECK_THROWS(notebook.write(6, 66, 60, Direction::Horizontal, "beast\ret"));
    // \t cannot be a string input
            CHECK_THROWS(notebook.write(32, 44, 40, Direction::Vertical, "\t"));
            CHECK_THROWS(notebook.write(3, 5, 90, Direction::Horizontal, "\t"));
    // \n cannot be a string input
            CHECK_THROWS(notebook.write(32, 44, 33, Direction::Vertical, "\n"));
            CHECK_THROWS(notebook.write(5, 5, 5, Direction::Horizontal, "\n"));
    // \r cannot be a string input
            CHECK_THROWS(notebook.write(32, 44, 0, Direction::Horizontal, "\r"));
            CHECK_THROWS(notebook.write(32, 44, 0, Direction::Vertical, "\r"));
    // pass line limit - over 100
            CHECK_THROWS(notebook.write(60, 50, 95, Direction::Horizontal, "only five chars are allowed"));
    // writing on the same page,row and col twice
    notebook.write(2, 2, 2, Direction::Vertical, "nice!");
            CHECK_THROWS(notebook.write(2, 2, 2, Direction::Vertical, "olaa"));
    // erase an erased spot already
//    notebook.erase(55, 12, 40, Direction::Horizontal, 5);
//            CHECK_THROWS(notebook.erase(55, 12, 40, Direction::Horizontal, 5));
}
//
//TEST_CASE ("bad output") {
//    notebook.write(10, 10, 0, Direction::Vertical, "hello");
//            CHECK_EQ(notebook.read(10, 10, 0, Direction::Vertical, 5), "~~~~~");
//
//}
//
//TEST_CASE ("good output") {
//    notebook.write(4, 40, 5, Direction::Horizontal, "babi");
//            CHECK_EQ(notebook.read(4, 40, 5, Direction::Horizontal, 4), "babi");
//}





