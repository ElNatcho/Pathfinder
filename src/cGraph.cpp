#include"cGraph.hpp"

// -- Konstruktor --
cGraph::cGraph() {
    // Alloc Mem
    _nodes = new std::vector<cNode*>();
    _dist = new std::map<std::string, distData>();

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

// -- findPath --
// Methode findet den schnellsten Pfad zwischen zwei Knoten
// @param id_s: Source Knoten (Startknoten)
// @param id_d: Destination Knotne (Zielknoten)
void cGraph::findPath(std::string id_s, std::string id_d) {
    if(!_initDistances(id_s)) { /* TODO: Error Handling */}
    if(_dist->find(id_d) == _dist->end()) { /* TODO: Error Handling */} // Prüfen ob es den Zielknoten gibt

    float tmpMinDist = -1.F; // Temporäre Variable, die die kleinste aktuelle Entfernung speichert
    std::string tmpMinID = ""; // Temporäre Variable, die die ID des Knoten speichert der die aktuell kleinste Entfernung zum Startknoten besitzt

    do { // Solange ausführen bis der Zielknoten gefunden wurde
        for(_dIt = _dist->begin(); _dIt != _dist->end(); _dIt++) { // Durch die gesamte Map iterieren
            if((tmpMinDist < 0) || (_dIt->second.dist < tmpMinDist)) { // Prüfen ob ein Knoten mit einer kleineren Entfernung gefunden wurde
                tmpMinDist = _dIt->second.dist; // Aktuell kleinste Entfernung überschreiben
                tmpMinID   = _dIt->first; // Knoten überschreiben
            }
        }

        if(tmpMinID == id_d) { // Prüfen ob man am Zielknoten angelangt ist
            _evaluatePath(id_s, id_d); // Pfad ausgeben
            break; // Zielknoten ausgeben
        } else {
            _doStep(tmpMinID); //
        }

        tmpMinDist = -1.F;
        tmpMinID = "";
    } while(true);

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

// -- _initDistances --
// Methode initialisiert die Entfernungen zu allen anderen Knoten
// @param snode: Startpunkt des aktuell gesuchten Pfades
bool cGraph::_initDistances(std::string snode) {
    for(auto n : *_nodes) { _dist->insert(std::make_pair(n->getID(), distData{-1, nullptr})); } // Alle Knoten in die dist-Map mit unbekannter Entfernung einfügen
    _dIt = _dist->find(snode); // Startknoten suchen und im Iterator speichern
    if(_dIt != _dist->end()) { // Prüfen ob der Knoten gefunden wurde
        _dIt->second.dist = 0; // Startknoten hat keine Entfernung zu sich selbst
        _startNode = _getNode(_dIt->first); // Startknoten abspeichern
        return true; // Initialisierung erfolgreich
    } else {
        return false; // Initialisierung fehlgeschlagen
    }
}

// -- _doStep --
// Methode führt einen "Schritt" aus: Von einem Knoten aus wird zum nächst besten
// Knoten gesprungen, falls dies der Effizienteste Pfad ist
// @param std::string id: Knoten von dem aus gesprungen wird
bool cGraph::_doStep(std::string id) {
    float tmpDist = 0.F; // Temporäres Gewicht

    cNode *curNode = _getNode(id); // Aktuellen Knoten speichern
    if(curNode == nullptr) { return false; } // Prüfen ob der Knoten gefunden wurde

    std::vector<cNode::sConnection> conns = curNode->getConnections(); // Alle Verbindungen des aktuellen Knoten bekommen

    for(auto con : conns) { // Durch alle Verbindungen iterieren
        tmpDist = _dist->find(id)->second.dist + con.weight; // Entfernung zum aktuellen Zielknoten
        _dIt = _dist->find(con.n->getID()); // Aktuellen Zielknoten bekommen
        if(_dIt != _dist->end()) { // Prüfen ob der Zielknoten gefunden wurde
            if((_dIt->second.dist > tmpDist) || (_dIt->second.dist < 0)) { // Prüfen ob ein (schnellerer) Weg zum Zielknoten gefunden wurde
                _dIt->second.dist = tmpDist;   // Alte Entfernung überschreiben
                _dIt->second.origin = curNode; // Ursprungsknoten überschreiben
            }
            return true;
        } else {
            return false;
        }
    }
}

// -- _evaluatePath --
// Methode wertet die _dist-Map aus und gibt diese zurück bzw. aus
// @param id_s: Source Knoten (Startknoten)
// @param id_d: Destination Knotne (Zielknoten)
void cGraph::_evaluatePath(std::string id_s, std::string id_d) {
    _dIt = _dist->find(id_d); // Zielknoten finden
    do {
        std::cout << _dIt->first << " < " << std::endl;
        if(_dIt->first == id_s) { return; } // Beim Startknoten abbrechen
        _dIt = _dist->find(_dIt->second.origin->getID()); // Ursprungsknoten finden
    } while(true);
}

// -- Destruktor --
cGraph::~cGraph() {
    // Free Mem
    // node-vector freigeben
    for(auto i : *_nodes) { SAFE_DELETE(i); } // Alle Nodes im Vector löschen
    SAFE_DELETE(_nodes); // Vector löschen
    // Dist-Map freigeben
    _dist->clear(); // Alle Einträge löschen
    SAFE_DELETE(_dist); // _dist-Map löschen


}
