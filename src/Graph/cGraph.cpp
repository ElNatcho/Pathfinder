#include"cGraph.hpp"

// -- Konstruktor --
cGraph::cGraph() {
    // Alloc Mem
    _createConnection_pattern = new std::regex();
    _createNode_pattern = new std::regex();
    _fileMgr = new cFileMgr();
    _match = new std::smatch();
    _nodes = new std::vector<cNode*>();
    _dist = new std::map<std::string, distData>();

    // Werte setzen
    *_createNode_pattern = "id=[\\w\\d_-]+";
    *_createConnection_pattern = ">c_id=[\\w\\d]+.+"; // \t>c_id=[:word:]+[:space:]{1}w=[:digit:]+
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
    std::string tmpMinID = id_s; // Temporäre Variable, die die ID des Knoten speichert der die aktuell kleinste Entfernung zum Startknoten besitzt

    do { // Solange ausführen bis der Zielknoten gefunden wurde
        _doStep(tmpMinID); // Nächst besten Knoten besuchen
        _dIt = _dist->find(tmpMinID); // Aktuellen Knoten als besucht markieren
        _dIt->second.visited = true;  // *

        if(tmpMinID == id_d) { // Prüfen ob man am Zielknoten angelangt ist
            _evaluatePath(id_s, id_d); // Pfad ausgeben
            break; // Zielknoten ausgeben
        }

        tmpMinDist = -1.F;
        tmpMinID = "";

        for(_dIt = _dist->begin(); _dIt != _dist->end(); _dIt++) { // Durch die gesamte Map iterieren
            if(!_dIt->second.visited && ((tmpMinDist <= 0) || ((_dIt->second.dist >= 0) && (_dIt->second.dist < tmpMinDist)))) { // Prüfen ob ein Knoten mit einer kleineren Entfernung gefunden wurde
                tmpMinDist = _dIt->second.dist; // Aktuell kleinste Entfernung überschreiben
                tmpMinID   = _dIt->first; // Knoten überschreiben
            }
        }
    } while(true);
}

// -- importGraph --
// Methode importiert einen Graphen aus einer Datei
// @param path: Pfad zur/Name der Datei
bool cGraph::importGraph(std::string path) {
    if(!_fileMgr->openFile(path)) { // Datei öffnen und prüfen ob sie korrekt geöffnet wurde
        return false; // Vorgang abbrechen falls die Datei nicht geöffnet werden konnte
    }
    std::vector<std::string> fc = _fileMgr->readFileContent(); // Daten auslesen
    _fileMgr->closeFile(); // Datei schliessen

    cNode *_tmpNode = nullptr; // Temporären Knoten erstellen
    std::string _tmpStr = ""; // Temporären String erstellen
    float _tmpWeight = 0.F; // Temporäre Gewichtung erstellen
    std::vector<std::pair<std::string, std::pair<std::string, float>>> _conVec; // Speichert temporär die Verbindungen zwischen Knoten

    if(fc.size() > 0) { // Prüfen ob Daten importiert wurden
        for(std::string str : fc) { // Druch alle Zeilen der ausgelesenen Datei iterieren
            if (std::regex_search(str, *_match, *_createConnection_pattern)) { // Prüfen ob in der aktuellen Zeile eine neue Verbindung erstellt wird
                _tmpStr = _match->str().substr(_match->str().find(">c_id=") + 6); // Alles bis eingeschlossen "c_id=" abtrennen
                _tmpWeight = std::stof(_tmpStr.substr(_tmpStr.find(" w=") + 3, _tmpStr.size())); // Die Gewichtung aus dem String extrahieren, zu float konvertiern und abspeichern
                _tmpStr = _tmpStr.substr(0, _tmpStr.find(" w=")); // Speichert die ID in _tmpStr
                if(_tmpNode == nullptr) { return false; } // Parsing-Fehler auslösen falls kein Knoten erzeugt wurde
                _conVec.push_back(std::make_pair(_tmpNode->getID(), std::make_pair(_tmpStr, _tmpWeight))); // Verbindung temporär in der Verbindungs-Map speichern
            } else if(std::regex_search(str, *_match, *_createNode_pattern)) { // Prüfen ob in der aktuellen Zeile ein neuer Knoten erstellt wird
                if(_tmpNode != nullptr) { _nodes->push_back(_tmpNode); } // Falls der temporäre Knoten auf ein Objekt zeigt dieses abspeichern
                _tmpNode = new cNode(_match->str().substr(3, _match->str().size())); // Neuen Knoten mit der ID des aktuell ausgelesenen Knoten erstellen
            }
        }
        _nodes->push_back(_tmpNode); // Zuletzt erstellten Knoten in den Knoten Vektor eintragen
        for(auto c : _conVec) { // Durch alle temporär gespeicherte Verbindungen iterieren
            if(_tmpNode->getID() != c.first){ // Prüfen ob die Verbindung einen anderen Knoten hinzugefügt werden soll
                _tmpNode = _getNode(c.first); // Knoten suchen und abspeichern
            }
            _tmpNode->addConnection({_getNode(c.second.first), c.second.second}); // Verbindung hinzufügen
        }

        return true;
    } else { // Falls keine Daten importiert wurden
        return false; // Fehlschlag zurückgeben
    }
}

// -- exportGraph --
// Methode exportiert einen Graphen in eine Datei
// @param path: Pfad zur/Name der Datei
bool cGraph::exportGraph(std::string path) {
    if(!_fileMgr->openFile(path)) { // Datei öffnen und prüfen ob sie korrekt geöffnet wurde
        return false; // Vorgang abbrechen falls die Datei nicht geöffnet werden konnte
    }

    // TODO: writeToFile Error Handling
    for(auto n : *_nodes) { // Durch jeden Eintrag des Node-Vectors iterieren
        _fileMgr->writeToFile("id=" + n->getID() + "\n"); // ID des aktuellen Knotens in die Datei exportieren
        for(auto c : n->getConnections()) { // Durch alle Verbindungen des aktuellen Knotens iterieren
            _fileMgr->writeToFile("\t>c_id=" + c.n->getID() + " w=" + std::to_string(c.weight) + "\n"); // Speichert die ID und die Gewichtung der aktuellen Verbindung
        }
    }

    _fileMgr->closeFile(); // Datei schliessen
    return true;
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
    for(auto n : *_nodes) { _dist->insert(std::make_pair(n->getID(), distData{-1, nullptr, false})); } // Alle Knoten in die dist-Map mit unbekannter Entfernung einfügen
    _dIt = _dist->find(snode); // Startknoten suchen und im Iterator speichern
    if(_dIt != _dist->end()) { // Prüfen ob der Knoten gefunden wurde
        _dIt->second.dist = 0; // Startknoten hat keine Entfernung zu sich selbst
        _dIt->second.visited = true; // Knoten kann sich nicht selbst nicht besuchen
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
        } else {
            return false;
        }
    }
    return true;
}

// -- _evaluatePath --
// Methode wertet die _dist-Map aus und gibt diese zurück bzw. aus
// @param id_s: Source Knoten (Startknoten)
// @param id_d: Destination Knotne (Zielknoten)
void cGraph::_evaluatePath(std::string id_s, std::string id_d) {
    _dIt = _dist->find(id_d); // Zielknoten finden
    do {
        std::cout << _dIt->first << " < ";
        if(_dIt->first == id_s) { break; } // Beim Startknoten abbrechen
        _dIt = _dist->find(_dIt->second.origin->getID()); // Ursprungsknoten finden
    } while(true);
    std::cout << std::endl;
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

    // FileMgr freigeben
    SAFE_DELETE(_fileMgr);

    // Regex Variablen freigeben
    SAFE_DELETE(_match);
    SAFE_DELETE(_createNode_pattern);
    SAFE_DELETE(_createConnection_pattern);

}
