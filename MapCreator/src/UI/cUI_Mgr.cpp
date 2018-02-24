#include"cUI_Mgr.hpp"

// -- Konstruktor --
// @param graph: Zeiger zu dem Graphen der erstellt werden soll
cUI_Mgr::cUI_Mgr(cGraph *graph) {
    // Alloc Mem
    _newNodeID = new char[255];

    // Werte setzen
    _graph = graph;
    _newNodeID[0] = '\0';
}

// -- renderAddNode_UI --
// Methode zeichnet die UI die nötig ist um einen Knoten hinzuzufügen
// @param mouse_win_pos: Position der Maus im Fenster
// @param mouse_pic_pos: Position der Maus im Bild
bool cUI_Mgr::renderAddNode_UI(sf::Vector2i mouse_win_pos, sf::Vector2i mouse_pic_pos) {
    // ImGui Fenster beginnen
    ImGui::Begin("Punkt hinzufügen");

    // Position der Maus im Fenster anzeigen
    ImGui::LabelText(" ", std::string("Mouse_Pos: X: " + std::to_string(mouse_win_pos.x) +
        " Y: " + std::to_string(mouse_win_pos.y)).c_str());
    // Positon der Maus im Bild anzeigen
    ImGui::LabelText(" ", std::string("Pic_Pos:   X: " + std::to_string(mouse_pic_pos.x) +
        " Y: " + std::to_string(mouse_pic_pos.y)).c_str());

    // ID des Knotens abfragen
    ImGui::InputText("ID", _newNodeID, 255);

    // Falls der OK Button gedrückt wird ..
    if(ImGui::Button("OK") && _newNodeID[0] != '\0') {
        _graph->addNode(std::string(_newNodeID), mouse_win_pos); // Den neuen Knoten erstellen
        _newNodeID[0] = '\0'; // String zurücksetzen
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

// -- Destruktor --
cUI_Mgr::~cUI_Mgr() {


}



































//
