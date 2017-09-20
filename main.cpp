#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Node.h"
#include "wrap.h"

using namespace std;

const int MAX_LEN = 10;


int main() {
    int temp;
    int count = 0;
    char data[MAX_LEN];
    char fileName[] = "dataFile.txt";
    FILE *fp = fopen(fileName, "r");

    auto *n = new Node(0);

    while(!feof(fp)) {
        fgets(data, MAX_LEN, fp);
        temp = atoi(data);
        std::cout << temp << std::endl;

    }


//    auto *n = new Node(1);
//    int data[] = {3, 23, 2983, 34, 23,
//                  56, 23, 465, 3, 43,
//                  23, 54, 6, 453, 867,
//                  79, 4563, 2334, 23, 123,
//                  45, 675, 546, 34, 2,
//                  312, 648, 245, 87, 2,
//                  45, 567, 111, 36, 856,
//                  245, 0};
//    int i = sizeof(data) / 4;
//    for (int j = 0; j < i; j++) {
//        n->insert(data[j]);
//    }
//    n->rootNode()->listAll();
//    delete n->rootNode()->child[3];
//    n->rootNode()->listAll();

    return 0;
}


