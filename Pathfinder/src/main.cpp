#include<iostream>
#include"UI/cWinMgr.hpp"

int main(int argc, char **argv) {
    if(argc != 4) { // Prüfen ob alle Parameter übergeben wurden
        std::cout << "Pathfinder <Map> <Graph> <Root_Node>" << std::endl;
        return -1;
    }

    cGraph graph;
    graph.importGraph(argv[2]);
    graph.setRootNode(std::string(argv[3]));

    graph.info();

    cWinMgr winMgr(argv[1], &graph);

    // CORE_LOOP solange ausführen, bis die Anwendung beendet wird
    while(winMgr.running) {
        winMgr.run();
    }

    return 0;
}
