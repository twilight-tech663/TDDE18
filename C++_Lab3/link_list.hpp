#ifndef LINK_LIST_HPP
#define LINK_LIST_HPP

// TODO: Complementary work: Do not have a space after the '#' sign. That
// includes the "ifndef", "define", "endif", and "include"                  - done
//
// TODO: Complementary work: print() should not return a string. It should as
// the names suggest, print the list.                                       - done
//
// TODO: Complementary work: You should not have to define a constructor for
// the Node, use aggregate initialization, i.e. Node{5, nullptr}.           - done
//
// TODO: Complementary work: Function implementations should not be
// done in the header file. This includes constructors/destructors.         - done

#include <string>
#include <sstream>
class List
{
public:
    List();
    List(std::initializer_list<int> list);      // initialize the list in order
    ~List();
    bool isEmpty() const;          // use const, make sure member value not be modified
    void list_print() const;
    void insert_node(int value);
    void remove_node(int value);
    int at_list(int index) const;
    List(List const& other);
    List& operator=(List const& other);
    List(List&& other);
    List& operator=(List&& other);
private:
    struct Node
    {
        int value;
        Node* next;
    };
    Node* head;
    void list_copy_from(const List& other);
    void clear();
    Node* insert_node_recursive(int value, Node* current);
    Node* remove_node_recursive(int value, Node* current);
};


#endif