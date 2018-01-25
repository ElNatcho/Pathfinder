#include"cGraph.hpp"

// -- Konstruktor --
cGraph::cGraph() {
    // Alloc Mem
    _nodes = new std::vector<cNode*>();

}

// -- addNode --
// Methode fügt einen neuen Knoten hinzu
// @param id: ID des Knotens
void cGraph::addNode(std::string id) {
    _nodes->push_back(new cNode(id)); // Neuer Knoten wird in den Vector eingefügt
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
        con = {n2, weight}; // Knoten 2 als Zielknoten und Gewichtung setzen
        n1->addConnection(con); // Verbindung in Knoten 1 einfügen
        con.n = n1; // Zielknoten in Konten 1 ändern
        n2->addConnection(con); // Verbindung in Knoten 2 einfügen
    }

}

// -- info --
// Methode gibt eine Info zu allen Knoten und deren Verbindungen aus
void cGraph::info() {
    for(std::size_t i = 0; i < _nodes->size(); i++) { // Durch alle Knoten iterieren
        std::cout << "<" << i << "> ID=" << _nodes->at(i)->getID() << " ADDR=" << _nodes->at(i) << " Verbindungen:" << std::endl;
        for(auto i : _nodes->at(i)->getConnections()) { // Verbindungen des aktuellen Knotens bekommen und durch diese iteriern
            std::cout << "\t >n.ID=" << i.n->getID() << " n.ADDR=" << i.n << " gew=" << i.weight << std::endl;
        }
    }
}

// -- _getNode --
// Methode gibt einen Knoten mit einer bestimmten ID zurück
// @param id: ID des gesuchten Knotens
cNode* cGraph::_getNode(std::string id) {
    for(std::size_t i = 0; i < _nodes->size(); i++) { // Prüfen ob der gesuchte Knoten gefunden wurde
        if(_nodes->at(i)->getID() == id) return _nodes->at(i); // Den gesuchten Knoten zurückgeben
    }
    return nullptr; // nullptr zurückgeben falls nichts gefunden wurde
}

// -- Destruktor --
cGraph::~cGraph() {
    // Free Mem
    // node-vector freigeben
    for(auto i : *_nodes) { SAFE_DELETE(i); } // Alle Nodes im Vector löschen
    SAFE_DELETE(_nodes); // Vector löschen

}
