#ifndef CNODE_HPP
#define CNODE_HPP

// Includes
#include<vector>
#include<string>
#include"../common.hpp"

// cNode
class cNode {
public:

    // Verbindungsstruktur
    struct sConnection {
        cNode *n; // Knoten auf den verwiesen wird
        float weight; // Gewichtung der Verbindung
    };

    // -- Kon/Destruktor --
    cNode(std::string id);
    ~cNode();

    // -- Public Methods --
    std::string getID(); // Gibt die ID des Knotens zurück
    void addConnection(sConnection con); // Methode fügt eine Verbindung hinzu
    std::vector<sConnection> getConnections(); // Methode gibt alle Verbindungen des Kotens zurück

private:

    // Private Vars
    std::vector<sConnection> *_connections; // Vector speichert alle Verbindungen des Knotens
    std::string *_id; // ID des Knotens

};

#endif
