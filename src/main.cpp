#include<iostream>
#include"cGraph.hpp"

int main() {
    cGraph *g = new cGraph();

    std::cout << "Hallo, Welt!" << std::endl;

    delete g;

    return 0;
}
