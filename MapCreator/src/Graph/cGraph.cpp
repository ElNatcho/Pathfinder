#include"cGraph.hpp"

// -- Konstruktor --
cGraph::cGraph() {
    // Werte setzen
    _createNode_pattern = "id=[\\w\\d_-]+";
    _createConnection_pattern = ">c_id=[\\w\\d]+.+";
}

// -- addNode --
// Methode fügt einen neuen Knoten hinzu
// @param n: Knoten der hinzugefügt werden soll
void cGraph::addNode(cNode *n) {
    _nodes.push_back(n);
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
        con = {n2, new float(weight), new sf::VertexArray(sf::Lines, 2)}; // Knoten 2 als Zielknoten und Gewichtung setzen
        con.con->operator[](0).position = n1->getShape().getPosition(); // Position eines Endes der Verbindung festlegen
        con.con->operator[](1).position = n2->getShape().getPosition(); // Position des anderen Endes der Verbindung festlegen
        con.con->operator[](0).color = sf::Color::Black; // Farbe eines Endes der Verbindung festlegen
        con.con->operator[](1).color = sf::Color::Black; // Farbe des anderen Endes der Verbindung festlegen
        n1->addConnection(con); // Verbindung in Knoten 1 einfügen
        con.n = n1; // Zielknoten in Konten 1 ändern
        n2->addConnection(con); // Verbindung in Knoten 2 einfügen
    }
}

// -- importGraph --
// Methode importiert einen Graphen aus einer Datei
// @param path: Pfad zur/Name der Datei
bool cGraph::importGraph(std::string path) {
    /*if(!_fileMgr->openFile(path)) { // Datei öffnen und prüfen ob sie korrekt geöffnet wurde
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
    }*/
    return false;
}

// -- exportGraph --
// Methode exportiert einen Graphen in eine Datei
// @param path: Pfad zur/Name der Datei
// @param rWin: Das aktuelle Fenster
// @param tex : Das aktuelle Bild
bool cGraph::exportGraph(std::string path, sf::RenderWindow &rWin, sf::Texture &tex) {
    if(!_fileMgr.openFile(path)) { // Datei öffnen und prüfen ob sie korrekt geöffnet wurde
        return false; // Vorgang abbrechen falls die Datei nicht geöffnet werden konnte
    }

    sf::Vector2f tmpPicPos; // Variable speichert temporär die Position des Knotens auf dem Bild

    // TODO: writeToFile Error Handling
    for(auto n : _nodes) { // Durch jeden Eintrag des Node-Vectors iterieren
        _fileMgr.writeToFile("id=" + n->getID()); // ID des aktuellen Knotens in die Datei exportieren
        _fileMgr.writeToFile(" pos=" + std::to_string(n->getShape().getPosition().x) + ":" + // Position des Knotens im Fenster abspeichern
                                       std::to_string(n->getShape().getPosition().y));
        tmpPicPos = com::getMousePosPic(sf::Vector2i(n->getShape().getPosition().x, // Position des Knotens auf dem Bild ausrechen
                                                     n->getShape().getPosition().y),
                                        rWin, tex);
        _fileMgr.writeToFile(" pic_pos=" + std::to_string(tmpPicPos.x) + ":" + // Position des Knotens im Bild abspeichern
                                           std::to_string(tmpPicPos.y));
        _fileMgr.writeToFile(" tags=" + n->getTags() + "\n"); // Tags des Knotens speichern
        for(auto c : n->getConnections()) { // Durch alle Verbindungen des aktuellen Knotens iterieren
            _fileMgr.writeToFile("\t>c_id=" + c.n->getID() + " w=" + std::to_string(*c.weight) + "\n"); // Speichert die ID und die Gewichtung der aktuellen Verbindung
        }
    }

    _fileMgr.closeFile(); // Datei schliessen
    return true;
}

// -- checkNodeSelect --
// Methode prüft ob ein Knoten angeklickt wurde und updatet ggf. dessen Aussehen
// @param mousePos: Position der Maus im Fenster
bool cGraph::checkNodeSelect(sf::Vector2f mousePos) {
    cNode::CLICK_TYPE ct; //
    for(cNode *n : _nodes) { // Durch alle Knoten iteriern
        ct = n->toggleSelectIfClicked(mousePos); // Prüfen ob der aktuelle Knoten angeklickt wurde
        if(ct == cNode::CLICK_TYPE::CL_SEL) { // Knoten wurde angeklickt und ist nun selektiert
            _selectedNodes.push_back(n);
            return true;
        } else if(ct == cNode::CLICK_TYPE::CL_UNSEL) { // Knoten wurde angeklickt und wurde nun unselektiert
            _selectedNodes.erase(std::remove(                     // Den nicht mehr ausgewählten Knoten
                _selectedNodes.begin(), _selectedNodes.end(), n), // aus der selectedNodes Liste löschen
                _selectedNodes.end());                            //
            return true;
        }
    }
    return false;
}

// --getSelectedNodes --
// Methode gibt die aktuell ausgewählten Knoten zurück
std::vector<cNode*> cGraph::getSelectedNodes() {
    return _selectedNodes;
}

// -- deselectAllNodes --
// Methode deselektiert alle aktuell ausgewählten Knoten
void cGraph::deselectAllNodes() {
    for (cNode *n : _selectedNodes) { // Durch alle ausgewählten Knoten iterieren
        n->toggleSelect(); // Knoten deselektieren
    }
    _selectedNodes.clear(); // Alle Knoten aus der Liste löschen
}

// -- renderGraph --
// Methode rendert den Graphen
// @param rWin: Fenster in dem der Graph gezeichnet werden soll
void cGraph::renderGraph(sf::RenderWindow &rWin) {
    for(cNode *n : _nodes) { // Durch alle Knoten iterieren
        rWin.draw(n->getShape()); // Knoten darstellen
        for(cNode::sConnection con : n->getConnections()) { // Durch alle Verbindungen des aktuellen Knotens iteriern
            rWin.draw(*con.con); // Aktuelle Verbindung zeichnen
        }
    }
}

// -- info --
// Methode gibt eine Info zu allen Knoten und deren Verbindungen aus
void cGraph::info() {
    for(std::size_t i = 0; i < _nodes.size(); i++) { // Durch alle Knoten iterieren
        std::cout << "<" << i << "> ID=" << _nodes.at(i)->getID() << " ADDR=" << _nodes.at(i) << " Verbindungen:" << std::endl;
        for(auto i : _nodes.at(i)->getConnections()) { // Verbindungen des aktuellen Knotens bekommen und durch diese iteriern
            std::cout << "\t >n.ID=" << i.n->getID() << " n.ADDR=" << i.n << " gew=" << i.weight << std::endl;
        }
    }
}

// -- _getNode --
// Methode gibt einen Knoten mit einer bestimmten ID zurück
// @param id: ID des gesuchten Knotens
cNode* cGraph::_getNode(std::string id) {
    for(std::size_t i = 0; i < _nodes.size(); i++) { // Prüfen ob der gesuchte Knoten gefunden wurde
        if(_nodes.at(i)->getID() == id) return _nodes.at(i); // Den gesuchten Knoten zurückgeben
    }
    return nullptr; // nullptr zurückgeben falls nichts gefunden wurde
}

// -- Destruktor --
cGraph::~cGraph() {
    // Free Mem

    // node-vector freigeben
    for(auto i : _nodes) { SAFE_DELETE(i); } // Alle Nodes im Vector löschen
    _nodes.clear();

}
