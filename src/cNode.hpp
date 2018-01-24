#ifndef CNODE_HPP
#define CNODE_HPP

// Includes
#include<vector>

// cNode
class cNode {

    // Verbindungsstruktur
    struct sConnection {
        cNode *n1; // Knoten 1
        cNode *n2; // Knoten 2
        float weight; // Gewichtung der Verbindung
    };

public:

    // -- Kon/Destruktor --
    cNode();
    ~cNode();

    // -- Public Methods --
    void addConnection(sConnection con); // Methode fügt eine Verbindung hinzu
    std::vector<sConnection> getConnections(); // Methode gibt alle Verbindungen des Kotens zurück

private:

    // Private Vars
    std::vector<sConnection> *_connections; // Vector speichert alle Verbindungen des Knotens

};

#endif
