/*Requirements
At least one of these functions must be recursive and at least one of them must be iterative.
*/

# include "link_list.hpp"
# include <iostream>
# include <string>

List::List(std::initializer_list<int> list):head{nullptr}   // list constructor: initialize the list in order
{
    for(int i : list)
    {
        insert_node(i);
    }
}

List::~List()       // destructor: move all nodes from list
{
    while(head != nullptr)
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

bool List::isEmpty() const
{
    return head == nullptr;
}

void List::insert_node(int value)
{
    head = insert_node_recursive(value, head);
    /* iterate way
    Node* tmp = new Node(value);
    if(head == nullptr || value < head->value)      // insert node in head
    {
        tmp->next = head;
        head = tmp;
        return;
    }
    Node* current = head;
    while(current->next != nullptr && value > current->next->value)     // insert node in tail and middle
    {
        current = current->next;
    }
    tmp->next = current->next;
    current->next = tmp; */
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

std::string List::list_print() const
{
    if(isEmpty())
    {
        return "";
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
    return result;
}

void List::remove_node(int value)
{
    if(isEmpty())
    {
        throw std::out_of_range("List is empty");
    }
    head = remove_node_recursive(value, head);

    /* iterate way
    if(isEmpty())       // empty list no node can remove
    {
        throw std::out_of_range("List is empty");
    }

    Node* current = head;
    if(current->value == value)     // remove node from head
    {
        Node* tmp = current;
        head = current->next;
        delete tmp;
        return;
    }
    while(current->next != nullptr && current->next->value != value)    // remove node from middle and tail
    {
        current = current->next;
    }
    if(current->next == nullptr)
    {
        throw std::out_of_range("Value not found");        // node not exist in list
    }
    Node* tmp = current->next;
    current->next = current->next->next;
    delete tmp;*/
}

List::Node* List::remove_node_recursive(int value, List::Node* current)
{
    if(current == nullptr)      // if arrive end of list
    {
        throw::std::out_of_range("Node not exist in list");
    }
    if(current->value == value)    // 
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

List::List(List const& other)       // copy constructor
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

List& List::operator=(List const& other)        // copy assignments
{
    if(this == &other)                // check is same list or not
    {
        return *this;
    }

    while(head != nullptr)             // delete own nodes
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    if(!other.isEmpty())
    {
        Node* read = other.head;        // copy other's nodes into list
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
    while(head != nullptr)             // delete own nodes
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    if(!other.isEmpty())
    {
        head = other.head;
        other.head = nullptr;
    }
    return *this;
}
