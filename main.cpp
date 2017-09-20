#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Node.h"
#include "wrap.h"

using namespace std;


int main() {

    auto *n = new Node(1);
    int data[] = {3, 23, 2983, 34, 23,
                  56, 23, 465, 3, 43,
                  23, 54, 6, 453, 867,
                  79, 4563, 2334, 23, 123,
                  45, 675, 546, 34, 2,
                  312, 648, 245, 87, 2,
                  45, 567, 111, 36, 856,
                  245, 0};
    int i = sizeof(data) / 4;
    for (int j = 0; j < i; j++) {
        n->insert(data[j]);
    }
    n->rootNode()->listAll();
    delete n->rootNode()->child[3];
    n->rootNode()->listAll();

    return 0;
}


