#include<iostream>
#include"cGraph.hpp"

int main() {
    cGraph g;

    g.addNode("1");
    g.addNode("2");
    g.addNode("3");

    g.addConnection("1", "2", 10.F);
    g.addConnection("1", "3", 1.F);
    g.addConnection("2", "3", 5.F);

    g.info();

    g.findPath("1", "3");

    //delete g;

    return 0;
}
