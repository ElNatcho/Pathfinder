#include<iostream>
#include"UI/cWinMgr.hpp"

int main(int argc, char **argv) {
    if(argc != 2) { // Prüfen ob alle Parameter übergeben wurden
        std::cout << "Pathfinder <MAP>" << std::endl;
        return -1;
    }

    cWinMgr winMgr(argv[1]);

    // CORE_LOOP solange ausführen, bis die Anwendung beendet wird
    while(winMgr.running) {
        winMgr.run();
    }

    return 0;
}
