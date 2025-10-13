# ifndef LINK_LIST_HPP
# define LINK_LIST_HPP

# include <string>
class List
{
public:
    List(): head(nullptr) {}
    List(std::initializer_list<int> list);      // initialize the list in order
    ~List();
    bool isEmpty() const;          // use const, make sure member value not be modified
    std::string list_print() const;
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

        Node(int val, Node* n = nullptr): value{val}, next(n) {}
    };
    Node* head;
    Node* insert_node_recursive(int value, Node* current);
    Node* remove_node_recursive(int value, Node* current);
};


# endif