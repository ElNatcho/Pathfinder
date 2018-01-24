#include"cNode.hpp"

// -- Konstruktor --
cNode::cNode() {
    // Alloc Mem
    _connections = new std::vector<sConnection>();

}

// -- addConnection --
// Methode fügt dem Knoten eine Verbindung hinzu
// @param con: Verbindung die hinzugefügt werden soll
void cNode::addConnection(sConnection con) {
    _connections->push_back(con);
}

// -- getConnections --
// Methode gibt alle Verbindungen des aktuellen Knotens zurück
std::vector<sConnection> cNode::getConnections() {
    return *_connections;
}

// -- Destruktor --
cNode::~cNode() {
    // Free Mem
    for(auto i : *_connections)
        SAFE_DELETE(i);
    SAFE_DELETE(_connections);

}