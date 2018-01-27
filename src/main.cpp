#include<iostream>
#include"cGraph.hpp"

int main() {
    cGraph g;

    std::cout << "Test: " << std::endl;

    g.addNode("1");
    g.addNode("2");
    g.addNode("3");

    g.addConnection("1", "2", 10.F);
    g.addConnection("1", "3", 1.F);
    g.addConnection("2", "3", 5.F);

    g.info();

    //delete g;

    return 0;
}
