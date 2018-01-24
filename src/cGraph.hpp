#ifndef CGRAPH_HPP
#define CGRAPH_HPP

// Includes
#include<iostream>
#include<map>
#include"cNode.hpp"

// cGraph
class cGraph {
public:

    // -- Kon/Destruktor --
    cGraph();
    ~cGraph();

    // -- Public Methods --
    void addNode(std::string id); // Methode fügt einen neuen Knoten hinzu
    void addConnection(std::string id_1, std::string id_2, float weight); // Methode fügt eine Verbindung zwischen zwei Knoten hinzu

private:

    // -- Private Vars --
    std::map<std::string, cNode*> *_nodes; // Map speicher alle Knoten und deren IDs
    std::map<std::string, cNode*>::iterator _nodeIt; // Iterator der Node Map

    // -- Private Methods --
    cNode* _getNode(std::string id); // Gibt einen Knoten mit einer bestimmten ID zurück

};

#endif
