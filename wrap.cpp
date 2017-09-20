//
// Created by jinhao on 17-9-14.
//

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <random>
#include <cstring>

#include "wrap.h"

void doubleLine() {
    std::cout << "===========================================" << std::endl;
}

void singleLine() {
    std::cout << "-------------------------------------------" << std::endl;
}

void underLine() {
    std::cout << "___________________________________________" << std::endl;
}

void plusLine() {
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;


}
void newLine() {
    std::cout << std::endl;
}

void indent() {
    std::cout << "\t";
}

void createDataFile(int num, int max) {
    int fd;
    char fileName[] = "dataFile.txt";
    fd = open(fileName, O_RDWR | O_CREAT);
    if (fd == -1) {
        std::cout << "E: CAN NOT CREATE FILE.";
        return;
    }
    int data[num];
    std::random_device rd;
    for (int j = 0; j < num; j++) {
        data[j] = int(rd() % max);
    }
    char temp[10];
    for (int k = 0; k < num; k++) {
        sprintf(temp, "%d", data[k]);
        write(fd, temp, strlen(temp));
        write(fd, "\n", 1);
    }
    close(fd);
}

