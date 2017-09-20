//
// Created by jinhao on 17-9-12.
//

#include <iostream>
#include "Node.h"
#include "wrap.h"


Node::Node() {
    for (int i = 0; i < MAX_ITEM; i++) {
        this->index[i] = -1;
        this->child[i] = nullptr;
    }
    this->parent = nullptr;
}

Node::Node(int index) {
    for (int i = 0; i < MAX_ITEM; i++) {
        this->index[i] = -1;
        this->child[i] = nullptr;
    }
    this->parent = nullptr;
    this->index[0] = index;
}

Node::~Node() {
    if (this->isRoot()) {
        // todo: how to delete root node ?
        return;
    }
    // remove the node from it's parent.
    for (int i = 0; i < MAX_ITEM; i++) {
        if (this->parent->index[i] == this->index[0]) {
            while (true) {
                if (i == MAX_ITEM - 1) {
                    this->parent->index[i] = -1;
                    this->parent->child[i] = nullptr;
                    break;
                }
                if (this->parent->index[i + 1] == -1) {
                    this->parent->index[i] = -1;
                    this->parent->child[i] = nullptr;
                    break;
                }
                this->parent->index[i] = this->parent->index[i + 1];
                this->parent->child[i] = this->parent->child[i + 1];
                i++;
            }
            break;
        }
    }
    // insert all child into it's brother node.
    for (int i = 0; i < MAX_ITEM; i++) {
        if (this->child[i] == nullptr) {
            break;
        }
        doubleLine();
        this->parent->child[0]->insert(this->index[i], this->child[i]);
    }
}

int Node::used() {
    int i = 0;
    for (int j = 0; j < MAX_ITEM; j++) {
        if (this->index[j] == -1) {
            break;
        }
        i++;
    }
    return i;
}

bool Node::isEmpty() {
    return this->used() == -1;
}

bool Node::isFull() {
    return this->index[MAX_ITEM - 1] > -1;
}

bool Node::isRoot() {
    return this->parent == nullptr;
}

bool Node::isLeaf() {
    return this->child[0] == nullptr;
}

bool Node::haveLeftBro() {
    // root node has no bro node
    if (this->isRoot()) {
        return false;
    }
    // if a node and it's parent node both have no left node, then it has no left node.
    if (this->parent->index[0] < this->index[0]) {
        return true;
    } else {
        return this->parent->haveLeftBro();
    }
}

bool Node::haveRightBro() {
    // root node has no bro node
    if (this->isRoot()) {
        return false;
    }
    if (this->parent->index[this->parent->used() - 1] > this->index[0]) {
        return true;
    } else {
        return this->parent->haveRightBro();
    }
}

bool Node::haveParent() {
    return this->parent != nullptr;
}

Node *Node::leftNode() {
    leftNode(0, DIR_UP);
}

Node *Node::leftNode(int i, int dir) {
    // ↑↑↑
    if (dir == DIR_UP) {
        // find bro node, stop to search up.
        if (this->parent->index[0] < this->index[0]) {
            for (int j = 0;; j++) {
                if (this->parent->index[j] == this->index[0]) {
                    return this->parent->child[j - 1]->leftNode(i, DIR_DOWN);
                }
            }
        }
        // no bro node found, continue search up
        if (this->parent->index[0] == this->index[0]) {
            i++;
            return this->parent->leftNode(i, DIR_UP);
        }
    }
    // ↓↓↓
    if (dir == DIR_DOWN) {
        if (i == 0) {
            return this;
        } else {
            i--;
            return this->child[this->used() - 1]->leftNode(i, DIR_DOWN);
        }
    }
}

Node *Node::rightNode() {
    rightNode(0, DIR_UP);
}

Node *Node::rightNode(int i, int dir) {
    if (dir == DIR_UP) {
        // bro node found.
        if (this->parent->index[this->parent->used() - 1] > this->index[0]) {
            for (int j = 0;; j++) {
                if (this->parent->index[j] > this->index[0]) {
                    return this->parent->child[j]->rightNode(i, DIR_DOWN);
                }
            }
        }
        // bro node not found
        if (this->parent->index[this->parent->used() - 1] == this->index[0]) {
            i++;
            return this->parent->rightNode(i++, DIR_UP);
        }
    }
    if (dir == DIR_DOWN) {
        if (i == 0) {
            return this;
        } else {
            i--;
            return this->child[0]->rightNode(i, DIR_DOWN);
        }

    }
}

Node *Node::broNode(int type) {
    if (type == LEFT_BRO_FIRST) {
        if (this->haveLeftBro()) {
            return this->leftNode();
        }
        if (this->haveRightBro()) {
            return this->rightNode();
        }
        return nullptr;
    }
    if (type == RIGHT_BRO_FIRST) {
        if (this->haveRightBro()) {
            return this->rightNode();
        }
        if (this->haveLeftBro()) {
            return this->rightNode();
        }
        return nullptr;
    }
}

Node *Node::parentNode() {
    return this->parent;
}

Node *Node::rootNode() {
    if (!this->isRoot()) {
        return this->parent->rootNode();
    } else {
        return this;
    }
}

void Node::split() {
    //create a new node as arg node's bro node.
    auto *broNode = new Node();
    for (int i = MIN_ITEM; i < MAX_ITEM; i++) {
        broNode->index[i - MIN_ITEM] = this->index[i];
        this->index[i] = -1;
        broNode->child[i - MIN_ITEM] = this->child[i];
        if (this->child[i] != nullptr) {
            this->child[i]->parent = broNode;
        }
        this->child[i] = nullptr;
    }
    //add the broNode to the parent node.
    if (this->parent == nullptr) {
        auto *prtNode = new Node();
        prtNode->insert(this->index[0], this);
    }
    this->parentNode()->insert(broNode->index[0], broNode);
}

void Node::insert(int index) {
    /// the node is empty, insert into 0 place
    if (this->isEmpty()) {
        this->index[0] = index;
        this->child[0] = nullptr;
        return;
    }
    /// insert into left node
    if (index < this->index[0] && this->haveLeftBro()) {
        this->leftNode()->insert(index);
        return;
    }
    /// inserted into right brother node
    if (this->haveRightBro() && index >= this->rightNode()->index[0]) {
        this->rightNode()->insert(index);
        return;
    }
    /// the index should insert into right this node and is full.
    if (this->isFull()) {
        this->split();
        this->insert(index);
        return;
    }
    for (int i = 0;; i++) {
        /// the index is navigate, it means that the node is empty or the arg index is the biggest one
        if (this->index[i] == -1) {
            this->index[i] = index;
            this->child[i] = nullptr;
            break;
        }
        /// the arg index already exists
        if (index == this->index[i]) {
            break;
        }
        /// the arg index insert into right this node !
        if (index < this->index[i]) {
            for (int j = this->used(); j > i; j--) {
                this->index[j] = this->index[j - 1];
                this->child[j] = this->child[j - 1];
            }
            this->index[i] = index;
            this->child[i] = nullptr;
            if (i == 0) {
                this->parent->changeIndex(index);
            }
            break;
        }
    }
}

void Node::insert(int index, Node *node) {
    /// the node is empty, it can only be the very first node.
    if (this->isEmpty()) {
        this->index[0] = index;
        this->child[0] = node;
        node->parent = this;
        return;
    }
    /// inserted into left brother node.
    if (index < this->index[0] && this->haveLeftBro()) {
        this->leftNode()->insert(index, node);
        return;
    }
    /// inserted into right brother node
    if (this->haveRightBro() && index >= this->rightNode()->index[0]) {
        this->rightNode()->insert(index, node);
        return;
    }
    /// the node is full, split and insert.
    if (this->isFull()) {
        this->split();
        this->insert(index, node);
        return;
    }
    for (int i = 0;; i++) {
        /// the index is navigate, it means that the node is empty or the arg index is the biggest one
        if (this->index[i] == -1) {
            this->index[i] = index;
            this->child[i] = node;
            node->parent = this;
            break;
        }
        /// the arg index already exists
        if (index == this->index[i]) {
            return;
        }
        /// the arg index insert and node into right this node !
        if (index < this->index[i]) {
            for (int j = this->used(); j > i; j--) {
                this->index[j] = this->index[j - 1];
                this->child[j] = this->child[j - 1];
            }
            this->index[i] = index;
            this->child[i] = node;
            node->parent = this;
            break;
        }
    }

}

// this function only be called after insert a index which is the smallest one.
void Node::changeIndex(int index) {
    this->index[0] = index;
    if (this->haveParent()) {
        this->parent->changeIndex(index);
    }
}

bool Node::exist(int index) {
    bool flag = false;
    // not leaf node
    if (!this->isLeaf()) {
        // the index is smaller than child[0], so it doesn't exists.
        if (this->index[0] > index) {
            std::cout << "does'nt exist." << std::endl;
            return false;
        }
        int i = this->used() - 1;
        for (int j = 0; j < i; j++) {
            if (this->index[j] == index) {
                std::cout << "exist." << std::endl;
                return true;
            }
            if (this->index[j] < index && index < this->index[j + 1]) {
                return this->child[j]->exist(index);
            }
        }
        if (this->index[this->used() - 1] == index) {
            std::cout << "exist." << std::endl;
            return true;
        }
        if (this->index[this->used() - 1] < index) {
            return this->child[this->used() - 1]->exist(index);
        }
        // leaf node.
    } else {
        for (int i = 0; i < MAX_ITEM; i++) {
            if (this->index[i] == index) {
                std::cout << "exist." << std::endl;
                flag = true;
            }
            if (this->index[i] > index) {
                std::cout << "does'nt exist." << std::endl;
                break;
            }
        }
        return flag;
    }
}

Node *Node::search(int index) {
    // this is not leaf node
    if (!this->isLeaf()) {
        if (this->index[0] > index) {
            return nullptr;
        }
        int i = this->used() - 1;
        for (int j = 0; j < i; j++) {
            if (this->index[j] <= index && this->index[j + 1] > index) {
                return this->child[j]->search(index);
            }
        }
        return this->child[i]->search(index);
        // leaf node
    } else {
        // if find the index, return this node, else return nullptr
        for (int i = 0; i < MAX_ITEM; i++) {
            if (this->index[i] == index) {
                return this;
            }
        }
        return nullptr;
    }
}

void Node::deleteIndex(int index) {
    // if the index doesn't exist, return.
    if (!this->rootNode()->exist(index)) {
        return;
    }
    if (this->isLeaf()) {
        for (int i = 0; i < MAX_ITEM; i++) {
            if (this->index[i] == index) {
                while (true) {
                    if (i == MAX_ITEM - 1) {
                        this->index[i] = -1;
                        break;
                    }
                    if (this->index[i + 1] == -1) {
                        this->index[i] = -1;
                        break;
                    }
                    this->index[i] = this->index[i + 1];
                    i++;
                }
            }
        }
        if (this->used() < MIN_ITEM) {
            delete this;
        }
    }
}

void Node::show() {
    doubleLine();
    std::cout << "NODE INFO" << std::endl;
    std::cout << MAX_ITEM << " at most." << std::endl;
    int i = 0;
    for (; i < MAX_ITEM; i++) {
        if (this->index[i] == -1) {
            break;
        }
        std::cout << "Index[" << i << "]: " << this->index[i] << std::endl;
    }
    std::cout << i << " in all." << std::endl;

    if (i == MAX_ITEM) {
        std::cout << "Full Node" << std::endl;
    }
    if (i == 0) {
        std::cout << "Empty Node" << std::endl;
    }
    if (this->isRoot()) {
        std::cout << "Root Node" << std::endl;
    }
    if (this->isLeaf()) {
        std::cout << "Leaf Node" << std::endl;
    }
    doubleLine();
}

void Node::list() {
    std::cout << "(";
    if (this->index[0] != -1) {
        std::cout << this->index[0];
    }
    for (int i = 1; i < MAX_ITEM; i++) {
        if (this->index[i] == -1) {
            break;
        } else {
            std::cout << "_" << this->index[i];
        }
    }
    std::cout << ")";
    if (this->isLeaf()) {
        std::cout << "L";
    }
    if (this->isRoot()) {
        std::cout << "R";
    }
}

void Node::listAll() {
    newLine();
    if (!this->isLeaf()) {
        this->listAll(this->child[0]);
    } else {
        this->listAll(nullptr);
    }
}

void Node::listAll(Node *nextLine) {
    this->list();
    indent();
    if (this->haveRightBro()) {
        this->rightNode()->listAll(nextLine);
    } else {
        if (nextLine != nullptr) {
            nextLine->listAll();
        } else {
            return;
        }
    }
}