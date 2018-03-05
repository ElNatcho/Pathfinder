#include"cUI_Mgr.hpp"

// -- Konstruktor --
// @param graph: Zeiger zu dem Graphen der erstellt werden soll
cUI_Mgr::cUI_Mgr(cGraph *graph) {
    // Alloc Mem
    _newNodeID = new char[50];
    _nodeTags  = new char[100];

    // Werte setzen
    _graph = graph;
    _newNodeID[0] = '\0';
    _newWeight = 0;
}

// -- renderAddNode_UI --
// Methode zeichnet die UI die nötig ist um einen Knoten hinzuzufügen
// @param mouse_win_pos: Position der Maus im Fenster
// @param mouse_pic_pos: Position der Maus im Bild
bool cUI_Mgr::renderAddNode_UI(sf::Vector2f mouse_win_pos, sf::Vector2f mouse_pic_pos) {
    // ImGui Fenster beginnen
    ImGui::Begin("Punkt hinzufügen");

    // Position der Maus im Fenster anzeigen
    ImGui::LabelText(" ", std::string("Mouse_Pos: X: " + std::to_string(mouse_win_pos.x) +
        " Y: " + std::to_string(mouse_win_pos.y)).c_str());
    // Positon der Maus im Bild anzeigen
    ImGui::LabelText(" ", std::string("Pic_Pos:   X: " + std::to_string(mouse_pic_pos.x) +
        " Y: " + std::to_string(mouse_pic_pos.y)).c_str());

    // ID des Knotens abfragen
    ImGui::InputText("ID (max_len = 50)", _newNodeID, 50);

    // Tags des Knotens abfragen
    ImGui::InputText("Tags (max_len = 100)", _nodeTags, 100);

    // Falls der OK Button gedrückt wird ..
    if(ImGui::Button("OK") && _newNodeID[0] != '\0') {
        _graph->addNode(new cNode(std::string(_newNodeID), mouse_win_pos, std::string(_nodeTags))); // Den neuen Knoten erstellen
        _newNodeID[0] = '\0'; // String zurücksetzen
        _nodeTags[0]  = '\0'; // String zurücksetzen
        ImGui::End();
        return false; // Zeichnen des UI-Elements beenden
    } else if(ImGui::Button("Abbrechen")) {
        _newNodeID[0] = '\0'; // String zurücksetzen
        ImGui::End();
        return false; // Zeichnen des UI-Elements beendens
    }

    ImGui::End();

    return true; // Zeichnen des UI Elements beenden
}

// -- renderAddConn_UI --
// Methode zeichnet die UI die nötig ist um Verbindungen zwischen Knoten herzustellen
bool cUI_Mgr::renderAddConn_UI() {
    _selectedNodes = _graph->getSelectedNodes(); // Ausgewählte Knoten abfragen
    if(_selectedNodes.size() >= 2) { // Prüfen ob zwei oder mehr Knoten ausgewählt sind
        // ImGui Fenster beginnen
        ImGui::Begin("Verbindung hinzufügen");

        ImGui::Text("Soll eine Verbindung hinzugefügt werden?");

        // Gewichtung der neuen Verbindung abfragen
        ImGui::InputFloat("Gewichtung", &_newWeight);

        // Falls der OK Button gedrück wird ..
        if(ImGui::Button("OK")) {
            // Verbindung zwischen den ersten zwei ausgewählten Knoten herstellen
            _graph->addConnection(_selectedNodes.at(0)->getID(),
                                  _selectedNodes.at(1)->getID(),
                                  _newWeight);
            _graph->deselectAllNodes();
        }else if(ImGui::Button("Abbrechen")) {
            _graph->deselectAllNodes();
        }

        ImGui::End();

        return true;
    }

    return false;
}

// -- Destruktor --
cUI_Mgr::~cUI_Mgr() {


}



































//
