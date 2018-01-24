#ifndef CNODE_HPP
#define CNODE_HPP

// Includes
#include<vector>
#include"common.hpp"

// cNode
class cNode {

    // Verbindungsstruktur
    struct sConnection {
        cNode *n; // Knoten auf den verwiesen wird
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
