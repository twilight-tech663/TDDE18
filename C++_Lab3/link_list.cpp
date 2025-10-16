#include "link_list.hpp"
#include <iostream>
#include <string>

// TODO: Complementary work: Do not repeat similar code
// copy assignment/constructor                                  - done

List::List(): 
    head(nullptr)
    {}

List::List(std::initializer_list<int> list):head{nullptr}   // list constructor: initialize the list in order
{
    for(int i : list)
    {
        insert_node(i);
    }
}

List::~List()       // destructor: move all nodes from list
{
    clear();
}

bool List::isEmpty() const
{
    return head == nullptr;
}

void List::insert_node(int value)
{
    head = insert_node_recursive(value, head);
}

List::Node* List::insert_node_recursive(int value, List::Node* current)
{
    if(current == nullptr || value <= current->value)       // out condition
    {
        Node* tmp = new Node{value, current};
        return tmp;
    }
    // recursive case: keep finding position
    current->next = insert_node_recursive(value, current->next);
    return current;
}

void List::list_print() const
{
    if(isEmpty())
    {
        std::cout << "";
    }
    std::string result{""};
    for(Node* current = head; current != nullptr; current = current->next)
    {
        result += std::to_string(current->value) + " -> ";
    }
    if(result.length() >= 4)
    {
        result.resize(result.length() - 4);
    }
    std::cout << result;
}

void List::remove_node(int value)
{
    if(isEmpty())
    {
        throw std::out_of_range("List is empty");
    }
    head = remove_node_recursive(value, head);
}

List::Node* List::remove_node_recursive(int value, List::Node* current)
{
    if(current == nullptr)      // if arrive end of list
    {
        throw::std::out_of_range("Node not exist in list");
    }
    if(current->value == value)    // base case
    {   
        Node* tmp = current;
        current = current->next;
        delete tmp;
        return current;
    }
    current->next = remove_node_recursive(value, current->next);
    return current;
}

int List::at_list(int index) const
{   
    if(isEmpty())
    {
        throw std::out_of_range("List is empty");
    }
    if(index < 0)
    {
        throw std::out_of_range("Negative index");
    }

    Node* current = head;
    int i = 0;
    while(current != nullptr && i < index)
    {
        current = current->next;
        i++;
    }

    if(current == nullptr)
    {
        throw std::out_of_range("Index out of list"); 
    }

    return current->value;
}

void List::list_copy_from(const List& other)
{
    if(other.isEmpty())
    {   
        head = nullptr;
        return;
    }
    Node* read = other.head;
    Node* write = new Node{read->value, nullptr};
    head = write;                   // copy first node
    while(read->next != nullptr)    // copy other nodes
    {
        read = read->next;
        Node* tmp = new Node{read->value, nullptr};
        write->next = tmp;
        write = write->next;
    }
}

void List::clear()
{
    while(head != nullptr)             // delete all nodes
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

List::List(List const& other)       // copy constructor
{
    list_copy_from(other);
}

List& List::operator=(List const& other)        // copy assignments
{
    if(this == &other)                // check is same list or not
    {
        return *this;
    }
    clear();
    list_copy_from(other);
    return *this;
}

List::List(List&& other)
{
    head = other.head;
    other.head = nullptr;
}

List& List::operator=(List&& other)
{
    if(this == &other)
    {
        return *this;
    }
    clear();
    if(!other.isEmpty())
    {
        head = other.head;
        other.head = nullptr;
    }
    return *this;
}
