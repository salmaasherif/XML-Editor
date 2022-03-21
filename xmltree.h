#ifndef XMLTREE_H
#define XMLTREE_H
#include <bits/stdc++.h>

class Node {
public:
    std::string Tag_Name;
    std::string Tag_value;
    std::vector<Node*> children;
    Node* parent;
    int level;
    int index = 0;
    bool isList;


public:
    Node(std::string Tag_Name)
    {
        this->Tag_Name = Tag_Name;
        this->Tag_value = ' ';
        parent = nullptr;
    }

};


class XML_tree {
public:
    Node* root;
    int size_of_children;


public:
    XML_tree() {
        root = nullptr;
    }



    Node* add_node(std::string Tag_Name)
    {
        Node* newnode = new Node(Tag_Name);
        return newnode;
    }



    void add_child(Node* parent, Node* child) {
        parent->children.push_back(child);
        child->parent = parent;
    }



    Node* get_root() {
        return this->root;
    }

    void add_data(Node* n, std::string data) {
        n->Tag_value = data;
    }

    void add_level(Node* n, int level1)
    {
        n->level = level1;
    }

    std::string get_data(Node* n) {
        return n->Tag_value;
    }

    std::string get_TagName(Node* n) {
        return n->Tag_Name;
    }


    std::vector<Node*> get_children(Node* n) {
        return n->children;
    }

    Node* get_child(int index, Node* n)
    {
        return n->children[index];
    }

    void add_root(Node* root)
    {
        this->root = root;
    }
    int get_index(Node* n) {
        return n->index;
    }

};


#endif // XMLTREE_H
