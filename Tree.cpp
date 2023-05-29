#include <iostream>
#include "Tree.h"
using namespace std;


Tree::Tree()
{
    root = nullptr;
}


void Tree::recursion_destructor(Node* obj)
{
    if (obj->_left)
        recursion_destructor(obj->_left);
    if (obj->_right)
        recursion_destructor(obj->_right);
    delete obj;
    obj = nullptr;
}


Tree:: ~Tree()
{
    if (root)
        recursion_destructor(root);
}


void Tree::recursion_copy(const Node* obj)
{
    insert(obj->_data);
    if (obj->_left)
        recursion_copy(obj->_left);
    if (obj->_right)
        recursion_copy(obj->_right);
}


Tree::Tree(const Tree& obj)
{
    recursion_destructor(root);
    recursion_copy(obj.root);
}


void Tree::recursion_print(const Node* obj, int level)
{
    if (obj)
    {
        recursion_print(obj->_right, level + 1);
        for (int i = 0; i < level; i++)
            cout << "   ";
        cout << obj->_data << endl;
        recursion_print(obj->_left, level + 1);
    }
}


void Tree::print()
{
    recursion_print(root);
}


bool Tree::insert(int key)//вставка элемента
{
    if (!root)
    {
        root = new Node(key);
        return true;
    }

    Node* tmp = root;
    tmp->_predoc = nullptr;
    while (tmp)
    {
        if (tmp->_data == key)
        {
            return true;
        }


        if (tmp->_data < key)
        {
            if (tmp->_right)
                tmp = tmp->_right;
            else
            {
                tmp->_right = new Node(key, tmp);
                return true;
            }
        }
        else
        {
            if (tmp->_left)
                tmp = tmp->_left;
            else
            {
                tmp->_left = new Node(key, tmp);
                return true;
            }

        }
    }
    return false;
}


Node* Tree::search(int key)
{
    if (!root) return nullptr;
    Node* tmp = root;

    while (tmp)
    {
        if (tmp->_data == key)
            return tmp;

        else
        {
            if (tmp->_data < key)
                tmp = tmp->_right;
            else
            {
                if (tmp->_data > key)
                    tmp = tmp->_left;
            }
        }
    }
    return nullptr;
}


bool Tree::contains(int key)//проверка наличия элемента
{
    if (search(key))
        return true;
    return false;
}


Node* Tree::min(Node* obj)
{
    if (obj)
    {
        if (obj->_right)
            return min(obj->_right);
    }
    return obj;
}


bool Tree::erase(int key)//удаление элемента
{
    if (contains(key) == false)
        return false;
    Node* tmp = search(key);
    Node* min_tmp = min(tmp->_right);

    if (tmp->_left && tmp->_right)
    {
        tmp->_data = min_tmp->_data;
        min_tmp->_predoc->_right = nullptr;
        delete min_tmp;
        min_tmp = nullptr;
        return true;
    }
    else
    {
        if (tmp->_left || tmp->_right)
        {
            if (tmp->_left)
            {
                tmp->_data = tmp->_left->_data;
                delete tmp->_left;
                tmp->_left = nullptr;
                return true;
            }
            if (tmp->_right)
            {
                tmp->_data = tmp->_right->_data;
                delete tmp->_right;
                tmp->_right = nullptr;
                return true;
            }
        }
        else
        {
            if (!(tmp->_left || tmp->_right))
            {
                if (!tmp->_predoc)
                {
                    delete tmp;
                    tmp = nullptr;
                    root = nullptr;
                }
                else
                {
                    if (tmp->_predoc->_left && tmp->_predoc->_left->_data == tmp->_data)
                        tmp->_predoc->_left = nullptr;
                    else
                        tmp->_predoc->_right = nullptr;
                    delete tmp;
                    tmp = nullptr;
                }
                return true;
            }
        }
    }
    return false;
}


Tree& Tree:: operator=(const Tree& obj)
{
    recursion_copy(obj.root);
    return (*this);
}