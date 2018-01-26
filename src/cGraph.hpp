#ifndef CGRAPH_HPP
#define CGRAPH_HPP

// Includes
#include<iostream>
#include<string>
#include<vector>
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

    void findPath(std::string id_1, std::string id_2); // Methode findet den schnellsten Pfad zwischen zwei Knoten

    void info(); // Methode gibt eine Info zu allen Knoten und deren Verbindungen aus

private:

    // -- Private Vars --
    std::vector<cNode*> *_nodes; // Vector speichert alle Knoten

    std::map<std::string, float> *_dist; // Methode speichert die Entfernungen zu den anderen Knoten
    std::map<std::string, float>::iterator _dIt; // Iterator der Entfernungsmap
    cNode *_startNode;



    // -- Private Methods --
    cNode* _getNode(std::string id); // Gibt einen Knoten mit einer bestimmten ID zurück

    bool _initDistances(std::string snode); // Methode initialisiert die Entfernungen
    void _doStep(std::string id); // Methode führt einen "Schritt" im Graphen aus

};

#endif
