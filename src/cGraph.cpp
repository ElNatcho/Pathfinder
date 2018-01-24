#include"cGraph.hpp"

// -- Konstruktor --
cGraph::cGraph() {
    // Alloc Mem
    _nodes = new std::map<std::string, cNode*>();

}

// -- addNode --
// Methode fügt einen neuen Knoten hinzu
// @param id: ID des Knotens
void cGraph::addNode(std::string id) {
    _nodes->insert(std::make_pair(id, new cNode())); // Neues ID Node Pair einfügen
}

// -- addConnection --
// Methode fügt eine Verbindung zwischen zwei Knoten hinzu
// @param id_1  : ID des ersten Knotens
// @param id_2  : ID des zweiten Knotens
// @param weight: Gewichtung des Knotens
void cGraph::addConnection(std::string id_1, std::string id_2, float weight) {
    cNode::sConnection con; // Verbindung der beiden Knoten
    cNode *n1 = _getNode(id_1); // Knoten 1 setzen
    cNode *n2 = _getNode(id_2); // Knoten 2 setzen
    if(n1 != nullptr && n2 != nullptr) {  // Prüfen ob beide Knoten gefunden wurden
        con {n2, weight}; // Knoten 2 als Zielknoten und Gewichtung setzen
        n1->addConnection(con); // Verbindung in Knoten 1 einfügen
        con.n = n1; // Zielknoten in Konten 1 ändern
        n2->addConnection(con); // Verbindung in Knoten 2 einfügen
    }

}

// -- _getNode --
// Methode gibt einen Knoten mit einer bestimmten ID zurück
// @param id: ID des gesuchten Knotens
cNode* cGraph::_getNode(std::string id) {
    _nodeIt = _nodes->find(id);
    return (_nodeIt == _nodes->end()) ? nullptr : _nodeIt->second;
}

// -- Destruktor --
cGraph::~cGraph() {


}
