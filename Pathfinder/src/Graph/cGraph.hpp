#ifndef CGRAPH_HPP
#define CGRAPH_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<algorithm>
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
    void addNode(cNode *n); // Methode fügt einen neuen Knoten hinzu
    void addConnection(std::string id_1, std::string id_2, float weight); // Methode fügt eine Verbindung zwischen zwei Knoten hinzu

    bool importGraph(std::string path); // Importiert einen Graphen aus einer Datei
    bool exportGraph(std::string path, sf::RenderWindow &rWin, sf::Texture &tex); // Exportiert einen Graphen aus einer Datei

    void findPath(std::string id_s, std::string id_d); // Methode findet den schnellsten Pfad zwischen zwei Knoten

    bool checkNodeSelect(sf::Vector2f mousePos); // Prüft ob ein Knoten angeklickt wurde
    std::vector<cNode*> getSelectedNodes(); // Gibt die aktuell ausgewählten Knoten zurück
    void deselectAllNodes(); // Methode deselektiert alle Knoten

    void renderGraph(sf::RenderWindow &rWin); // Methode rendert den Graphen

    void info(); // Methode gibt eine Info zu allen Knoten und deren Verbindungen aus

private:

    // -- Private Vars --
    std::vector<cNode*> _nodes; // Vector speichert alle Knoten

    struct distData {  // Entfernungsdaten zum Startknoten
        float dist;    // Entfernung zum Startknoten
        cNode *origin; // Knoten von dem aus man den aktuellen Knoten erreichen kann
        bool visited;  // Gibt an ob der Knoten schon besucht wurde
    };

    std::map<std::string, distData> _dist; // Methode speichert die Entfernungen zu den anderen Knoten
    std::map<std::string, distData>::iterator _dIt; // Iterator der Entfernungsmap
    cNode *_startNode; // Knoten bei dem der Pfad gestartet wird

    cFileMgr _fileMgr; // Für die import/export Methode

    // Regex für importGraph
    std::smatch _match;
    std::regex _createNode_pattern; // Ausdruck drückt Strings aus die einen neuen Knoten erstellen
    std::regex _createConnection_pattern; // Ausdruck drückt Strings aus die eine neue Verbindung erstellen

    std::vector<cNode*> _selectedNodes; // Speichert ausgewählte Knoten

    // -- Private Methods --
    cNode* _getNode(std::string id); // Gibt einen Knoten mit einer bestimmten ID zurück

    bool _initDistances(std::string snode); // Methode initialisiert die Entfernungen
    bool _doStep(std::string id); // Methode führt einen "Schritt" im Graphen aus
    void _evaluatePath(std::string id_s, std::string id_d); // _dist-Map auswerten und ausgeben

};

#endif
