#include"cNode.hpp"

// -- Konstruktor --
// @param id      : ID des Knotens
// @param node_pos: Position des Knotens auf der Karte
cNode::cNode(std::string id, sf::Vector2f node_pos) {
    // Werte setzen
    _id = id;

    // Eigenschaften des repräsentativen Kreises festlegen
    _nodeSpr.setPosition(node_pos.x - 5.F, node_pos.y - 5.F);
    _nodeSpr.setRadius(5.F);
    _nodeSpr.setOutlineThickness(1.F);
    _nodeSpr.setOutlineColor(sf::Color::Black);
    _nodeSpr.setFillColor(sf::Color::Red);
}

// -- getID --
// Methdode gibt die ID des Knotens zurück
std::string cNode::getID() {
    return _id;
}

// -- getShape --
// Methode gibt die Form zurück die den Knoten repräsentiert
sf::CircleShape cNode::getShape() {
    return _nodeSpr;
}

// -- addConnection --
// Methode fügt dem Knoten eine Verbindung hinzu
// @param con: Verbindung die hinzugefügt werden soll
void cNode::addConnection(sConnection con) {
    _connections.push_back(con);
}

// -- getConnections --
// Methode gibt alle Verbindungen des aktuellen Knotens zurück
std::vector<cNode::sConnection> cNode::getConnections() {
    return _connections;
}

// -- Destruktor --
cNode::~cNode() {
    // Free Mem
    _connections.clear(); // Alle Verbindunge löschen

}
