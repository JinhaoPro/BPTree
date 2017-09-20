//
// Created by jinhao on 17-9-12.
//

#ifndef BPTREE_NODE_H
#define BPTREE_NODE_H

const int MAX_ITEM = 4;
const int MIN_ITEM = 2;

const int DIR_UP = 0;
const int DIR_DOWN = 1;

const int LEFT_BRO_FIRST = 0;
const int RIGHT_BRO_FIRST = 1;

class Node {
private:

public:
    int index[MAX_ITEM];
    Node *parent;
    Node *child[MAX_ITEM];

    Node *leftNode(int i, int dir);
    Node *rightNode(int i, int dir);

    Node();
    explicit Node(int index);
    ~Node();

    /// tool function
    int used();
    bool isFull();
    bool isEmpty();
    bool isRoot();
    bool isLeaf();
    bool haveLeftBro();
    bool haveRightBro();
    bool haveParent();
    Node *leftNode();
    Node *rightNode();
    Node *broNode(int type);
    Node *parentNode();
    Node *rootNode();


    /// crucial funciton
    void split();
    void insert(int index);
    void insert(int index, Node *node);
    void changeIndex(int index);
    bool exist(int index);
    Node *search(int index);
    void deleteIndex(int index);
    void deleteNode();

    /// for test
    void show();
    void list();
    void listAll();
    void listAll(Node *nextLine);
};


#endif //BPTREE_NODE_H
