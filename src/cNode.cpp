#include"cNode.hpp"

// -- Konstruktor --
cNode::cNode(std::string id) {
    // Alloc Mem
    _connections = new std::vector<sConnection>();
    _id = new std::string();

    // Werte setzen
    *_id = id;
}

// -- getID --
// Methdode gibt die ID des Knotens zurück
std::string cNode::getID() {
    return *_id;
}

// -- addConnection --
// Methode fügt dem Knoten eine Verbindung hinzu
// @param con: Verbindung die hinzugefügt werden soll
void cNode::addConnection(sConnection con) {
    _connections->push_back(con);
}

// -- getConnections --
// Methode gibt alle Verbindungen des aktuellen Knotens zurück
std::vector<cNode::sConnection> cNode::getConnections() {
    return *_connections;
}

// -- Destruktor --
cNode::~cNode() {
    // Free Mem
    _connections->clear(); // Alle Verbindunge löschen
    SAFE_DELETE(_connections); // _connections freigeben
    SAFE_DELETE(_id); // id freigeben

}
