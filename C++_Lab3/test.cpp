#include "catch_amalgamated.hpp"
#include "link_list.hpp"

TEST_CASE("Initialize a list in order")
{
    List list{5, 1, 9, 8};      // initialize a list in order, called list constructor
    REQUIRE(list.list_print() == "1 -> 5 -> 8 -> 9");
    List list1{};               // initialize a empty list, called constructor
    REQUIRE(list1.list_print() == "");
}

TEST_CASE("Test destructor")
{
    {
        List list{1, 2, 3, 4, 5};
    }
    REQUIRE(true);
}

TEST_CASE("Test the list is empty or not")
{
    List list{};
    REQUIRE(list.isEmpty());
    list.insert_node(1);
    REQUIRE_FALSE(list.isEmpty());
}

TEST_CASE("Insert a node to list")
{
    List list{};
    list.insert_node(8);                        // insert node to empty list
    REQUIRE(list.list_print() == "8");
    list.insert_node(1);
    REQUIRE(list.list_print() == "1 -> 8");     // insert node in head
    list.insert_node(5);
    REQUIRE(list.list_print() == "1 -> 5 -> 8");    // insert node in middle
    list.insert_node(9);
    REQUIRE(list.list_print() == "1 -> 5 -> 8 -> 9");   // insert node in tail
    list.insert_node(5);
    REQUIRE(list.list_print() == "1 -> 5 -> 5 -> 8 -> 9");  // insert a same value node to list
}

TEST_CASE("Remove a node by value from list")
{
    List list{1, 5, 8, 9};
    REQUIRE_THROWS_AS(list.remove_node(10), std::out_of_range);     // remove a node not exist in list
    list.remove_node(1);
    REQUIRE(list.list_print() == "5 -> 8 -> 9");    // remove a node from head
    list.remove_node(8);
    REQUIRE(list.list_print() == "5 -> 9");     // remove a node from middle
    list.remove_node(9);
    REQUIRE(list.list_print() == "5");      // remove a node from tail
    list.remove_node(5);
    REQUIRE(list.list_print() == "");                
    REQUIRE_THROWS_AS(list.remove_node(1),std::out_of_range);     // remove a node from empty list
}

TEST_CASE("get a node value according to index")
{
    List list1{};
    REQUIRE_THROWS_AS(list1.at_list(0), std::out_of_range);     // get a value from empty list
    REQUIRE_THROWS_AS(list1.at_list(-1), std::out_of_range);     // negative index
    List list{1, 2, 3, 4};
    REQUIRE(list.at_list(0) == 1);
    REQUIRE(list.at_list(1) == 2);
    REQUIRE(list.at_list(2) == 3);
    REQUIRE(list.at_list(3) == 4);
    REQUIRE_THROWS_AS(list.at_list(4), std::out_of_range);      // get a value out of list
}

TEST_CASE("copy constructor and copy assignment operator")
{
    List list{1, 2, 3, 4};
    List list1{list};
    REQUIRE(list1.list_print() == "1 -> 2 -> 3 -> 4");
    List list2{4, 5, 6, 7};
    list2 = list;
    REQUIRE(list2.list_print() == "1 -> 2 -> 3 -> 4");

    List list3{};       // copy a empty list
    List list4{list3};      
    REQUIRE(list4.isEmpty());
    List list5{1, 2, 3};
    list5 = list3;
    REQUIRE(list5.isEmpty());
}

TEST_CASE("move constructor and move assignment operator")
{
    List list{1, 2, 3, 4};
    List list1{std::move(list)};        // use move convert list to a temporary object
    REQUIRE(list1.list_print() == "1 -> 2 -> 3 -> 4");
    REQUIRE(list.list_print() == "");
    List list2{4, 5, 6, 7};
    list2 = std::move(list1);
    REQUIRE(list2.list_print() == "1 -> 2 -> 3 -> 4");
    REQUIRE(list1.list_print() == "");

    List list3{};       // move a empty list
    List list4{std::move(list3)};      
    REQUIRE(list4.isEmpty());
    List list5{1, 2, 3};
    list5 = std::move(list3);
    REQUIRE(list5.isEmpty());
}
