#include "doctest.h"
#include "sources/Notebook.hpp"
#include "sources/Direction.hpp"


using namespace ariel;

Notebook notebook;


TEST_CASE ("Bad input") {
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
    // negative and high input
            CHECK_THROWS(notebook.write(-2, 42, 42, Direction::Vertical, "write"));
            CHECK_THROWS(notebook.write(42, -3, 42, Direction::Horizontal, "abiDemon"));
            CHECK_THROWS(notebook.write(42, 42, -5, Direction::Vertical, "abiDemon"));
            CHECK_THROWS(notebook.write(42, 42, 102, Direction::Horizontal, "write demon"));
            CHECK_THROWS(notebook.read(42, 42, 99, Direction::Horizontal, 2)); // need to check
            CHECK_THROWS(notebook.read(42, -3, 42, Direction::Vertical, 15));
            CHECK_THROWS(notebook.read(-2, 42, 42, Direction::Vertical, 0));
            CHECK_THROWS(notebook.read(42, 42, -19, Direction::Horizontal, 4));

}

TEST_CASE ("bad output") {
    notebook.write(10, 10, 0, Direction::Vertical, "hello");
            CHECK(notebook.read(10, 10, 0, Direction::Vertical, 5) != "~~~~~");
    notebook.write(10, 20, 30, ariel::Direction::Horizontal, "hello world!");
    notebook.write(30, 40, 50, ariel::Direction::Vertical, "tutu-tita = kaki");
    notebook.write(60, 70, 80, Direction::Vertical, "babi");
            CHECK(notebook.read(10, 20, 30, ariel::Direction::Horizontal, 4) != "hello world!");
            CHECK(notebook.read(30, 40, 50, ariel::Direction::Horizontal, 1) != "");
            CHECK(notebook.read(50, 60, 70, ariel::Direction::Horizontal, 5) != "babi ");

}

TEST_CASE ("good output") {
    notebook.write(5, 60, 50, ariel::Direction::Horizontal, "hello world!");
    notebook.write(5, 20, 12, ariel::Direction::Vertical, "tutu-tita = kaki");
    notebook.write(4, 40, 5, Direction::Horizontal, "babi");
            CHECK_EQ(notebook.read(5, 60, 0, ariel::Direction::Horizontal, 80), "hello world!");
            CHECK_EQ(notebook.read(5, 10, 12, ariel::Direction::Vertical, 80), "tutu-tita = kaki");
            CHECK_EQ(notebook.read(4, 40, 5, Direction::Horizontal, 4), "babi");
    notebook.erase(5, 60, 50, ariel::Direction::Horizontal, 6);
            CHECK_EQ(notebook.read(5, 60, 50, ariel::Direction::Horizontal, 30), "world!");

}





