#ifndef CGRAPH_HPP
#define CGRAPH_HPP

// Includes
//#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include"cNode.hpp"
#include"FileMgr/cFileMgr.hpp"

// cGraph
class cGraph {
public:

    // -- Kon/Destruktor --
    cGraph();
    ~cGraph();

    // -- Public Methods --
    void addNode(std::string id, sf::Vector2i &node_pos); // Methode fügt einen neuen Knoten hinzu
    void addConnection(std::string id_1, std::string id_2, float weight); // Methode fügt eine Verbindung zwischen zwei Knoten hinzu


    bool importGraph(std::string path); // Importiert einen Graphen aus einer Datei
    bool exportGraph(std::string path); // Exportiert einen Graphen aus einer Datei

    void renderGraph(sf::RenderWindow &rWin); // Methode rendert den Graphen
    void info(); // Methode gibt eine Info zu allen Knoten und deren Verbindungen aus

private:

    // -- Private Vars --
    std::vector<cNode*> *_nodes; // Vector speichert alle Knoten

    struct distData {  // Entfernungsdaten zum Startknoten
        float dist;    // Entfernung zum Startknoten
        cNode *origin; // Knoten von dem aus man den aktuellen Knoten erreichen kann
        bool visited;  // Gibt an ob der Knoten schon besucht wurde
    };

    cFileMgr *_fileMgr; // Für die import/export Methode

    // Regex für importGraph
    std::smatch *_match;
    std::regex *_createNode_pattern; // Ausdruck drückt Strings aus die einen neuen Knoten erstellen
    std::regex *_createConnection_pattern; // Ausdruck drückt Strings aus die eine neue Verbindung erstellen

    // -- Private Methods --
    cNode* _getNode(std::string id); // Gibt einen Knoten mit einer bestimmten ID zurück

};

#endif