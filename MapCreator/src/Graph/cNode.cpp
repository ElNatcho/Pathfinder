#include"cNode.hpp"

// -- Konstruktor --
// @param id      : ID des Knotens
// @param node_pos: Position des Knotens auf der Karte
cNode::cNode(std::string id, sf::Vector2f node_pos) {
    // Werte setzen
    _id = id;
    _isSelected = false;

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

// -- toggleSelectIfClicked --
// Methode prüft ob der Knoten angeklickt wurde und updated ihn ggf. Die Methode gibt zurück
// ob der Knoten nun ausgewählt ist oder nicht
// @param mousePos: Position der Maus im Fenster
cNode::CLICK_TYPE cNode::toggleSelectIfClicked(sf::Vector2f mousePos) {
    if(_nodeSpr.getGlobalBounds().contains(mousePos)) { // Falls der Knoten angeklickt wurde
        if(_isSelected) { // Prüfen ob der Knoten akutell ausgewählt ist
            _nodeSpr.setFillColor(sf::Color::Red);
            _isSelected = false; // Knoten deselektieren
            return CLICK_TYPE::CL_UNSEL;
        } else {
            _nodeSpr.setFillColor(sf::Color::Green);
            _isSelected = true; // Knoten selektieren
            return CLICK_TYPE::CL_SEL;
        }
    }
    return CLICK_TYPE::NCL;
}

// -- Destruktor --
cNode::~cNode() {
    // Free Mem
    _connections.clear(); // Alle Verbindunge löschen

}
