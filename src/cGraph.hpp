#ifndef CGRAPH_HPP
#define CGRAPH_HPP

// Includes
#include<iostream>
#include<string>
#include<vector>
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
    void info(); // Methode gibt eine Info zu allen Knoten und deren Verbindungen aus

private:

    // -- Private Vars --
    std::vector<cNode*> *_nodes;

    // -- Private Methods --
    cNode* _getNode(std::string id); // Gibt einen Knoten mit einer bestimmten ID zurück

};

#endif
