#include <stdio.h>
#include <iostream>
using namespace std;
struct Node
{
    int _data;
    Node* _predoc;
    Node* _left;
    Node* _right;
    Node(int data = 0, Node* predoc = nullptr, Node* left = nullptr, Node* right = nullptr)
    {
        _data = data;
        _predoc = predoc;
        _left = left;
        _right = right;
    }
};

class Tree
{
private:
    Node* root;
    void recursion_print(const Node* obj, int level = 5);
    void recursion_copy(const Node* obj);
    Node* search(int key);
    Node* min(Node* obj);
public:
    void recursion_destructor(Node* obj);
    Tree();
    ~Tree();
    Tree(const Tree& obj);
    void print();
    bool insert(int key);//вставка элемента
    bool contains(int key);//проверка наличия элемента
    bool erase(int key);//удаление элемента
    Tree& operator=(const Tree& obj);

};