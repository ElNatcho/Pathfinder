#include<iostream>
#include"UI/cWinMgr.hpp"

int main() {
    cWinMgr winMgr;

    // CORE_LOOP solange ausführen, bis die Anwendung beendet wird
    while(winMgr.running) {
        winMgr.run();
    }

    return 0;
}
