#include<iostream>
#include"cGraph.hpp"

int main() {
    cGraph g;

    g.addNode("1");
    g.addNode("2");
    g.addNode("3");
    g.addNode("4");

    g.addConnection("1", "2", 1.F);
    g.addConnection("1", "3", 3.F);
    g.addConnection("2", "4", 10.F);
    g.addConnection("3", "4", 2.F);
    g.addConnection("2", "3", 1.F);

    g.info();

    g.findPath("1", "4");

    //delete g;

    return 0;
}
