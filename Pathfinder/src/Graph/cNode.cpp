#include"cNode.hpp"

// -- Konstruktor --
// @param id      : ID des Knotens
// @param node_pos: Position des Knotens auf der Karte
// @param tag     : Tag(s) die der Knoten besitzt
cNode::cNode(std::string id, sf::Vector2f node_pos, std::string tag = "") {
    // Werte setzen
    _id = id;
    _isSelected = false;
    _tags = tag;

    // Eigenschaften des repräsentativen Kreises festlegen
    _nodeSpr.setOrigin(5.F, 5.F);
    _nodeSpr.setPosition(node_pos.x, node_pos.y);
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

// -- getTags --
// Methode gibt die Tags des Knoten zurück
std::string cNode::getTags() {
    return _tags;
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

// -- toggleSelect --
// Methode ändert den aktuellen Select-Status des Knoten und gibt den Klick-Status zurück
cNode::CLICK_TYPE cNode::toggleSelect() {
    CLICK_TYPE ct;
    if(_isSelected) { // Wenn der Knoten bereits ausgewählt ist in deselektieren
        _nodeSpr.setFillColor(sf::Color::Red);
        ct = CLICK_TYPE::CL_UNSEL; // Wichtig für die User auswahl des Knotens
    } else { // Falls er nicht ausgewählt ist in selektieren
        _nodeSpr.setFillColor(sf::Color::Green);
        ct = CLICK_TYPE::CL_SEL; // Wichtig für die User auswahl des Knotens
    }
    _isSelected = !_isSelected; // Status umkehren
    return ct;
}

// -- toggleSelectIfClicked --
// Methode prüft ob der Knoten angeklickt wurde und updated ihn ggf. Die Methode gibt zurück
// ob der Knoten nun ausgewählt ist oder nicht
// @param mousePos: Position der Maus im Fenster
cNode::CLICK_TYPE cNode::toggleSelectIfClicked(sf::Vector2f mousePos) {
    if(_nodeSpr.getGlobalBounds().contains(mousePos)) { // Falls der Knoten angeklickt wurde
        return toggleSelect();
    }
    return CLICK_TYPE::NCL;
}

// -- Destruktor --
cNode::~cNode() {
    // Free Mem
    _connections.clear(); // Alle Verbindunge löschen

}
