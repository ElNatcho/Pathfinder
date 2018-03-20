#include"cSearchUI.hpp"

// -- Konstruktor --
// @param g: Graph der gerade dargestellt wird
cSearchUI::cSearchUI(cGraph *g) {
    // Alloc Mem
    _raumnummer_it = new char[MAX_RNUM_LEN];
    _tag_it = new char[MAX_TAG_LEN];

    // Werte setzen
    _raumnummer_it[0] = '\0';
    _tag_it[0] = '\0';
    _graph = g;

    _selectedRnum = -1;
    _selectedTag  = -1;

}

// -- initUI --
// Methode initialisiert das UI
void cSearchUI::initUI() {
    // Position des Fensters angeben
    _winBounds.x = 0.F;
    _winBounds.y = 0.F;

    // Flags setzen
    _winFlags = 0;
    _winFlags |= ImGuiWindowFlags_NoMove;     // Fenster nicht mehr bewegen
    _winFlags |= ImGuiWindowFlags_NoResize;   // Nicht mehr vergrößern/verkleinern
    _winFlags |= ImGuiWindowFlags_NoTitleBar; // Kein Titel

    // Style des UIs anpassen
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 0.F;
}

// -- updateWinSize --
// Methode updated die Größe des Search-Fensters
// @param rWin: Referenz auf das Fenster in dem das Search-Fenster gezeichnet wird
void cSearchUI::updateWinSize(sf::RenderWindow &rWin) {
    _winBounds.z = rWin.getSize().x * X_WIN_RATIO;
    _winBounds.w = rWin.getSize().y;
}

// -- render --
// Methode rendert das Search-Fenster
// @param rWin: Referenz auf das Fenster in dem das Search-Fenster gezeichnet werden soll
void cSearchUI::render(sf::RenderWindow &rWin) {
    // Fenster beginnen
    ImGui::Begin("Test", NULL, _winFlags);
    // Einstellungen zu Position und Größe übernehmen
    ImGui::SetWindowPos(ImVec2(_winBounds.x, _winBounds.y), true);
    ImGui::SetWindowSize(ImVec2(_winBounds.z, _winBounds.w));

    // Anleitung für den USER Anzeigen
    ImGui::Text("-=+ HowTo: +=-");
    ImGui::Separator();
    // Header für die "Orte suchen" Hilfe
    if(ImGui::CollapsingHeader("Orte suchen")) {
        ImGui::Indent();
        ImGui::BulletText("Ein Ort kann über seine Tags(z.B. Essen, Toileten, etc)\noder ggf. seine Raumnummer gesucht werden");
        ImGui::BulletText("Um einen Raum über seinen Tag zu suchen muss man den \ngesuchten Tag in das Tag-Suchfeld eingeben");
        ImGui::BulletText("Um einen Raum über seine Raumnummer zu suchen muss man \ndie gesuchte Raumnummer in das Raumnummer-Suchfeld eingeben");
        ImGui::BulletText("Zusätzlich werden in den Boxen neben den jeweiligen \nSuchfeldern alle möglichen Eingaben angezeigt");
        ImGui::Unindent();
    }
    // Header für die "Manipulation der Karte" Hilfe
    if(ImGui::CollapsingHeader("Manipulation der Karte")) {
        ImGui::Indent();
        ImGui::BulletText("Zoomen kann man mithilfe der + und - Taste beim \nNummernblock");
        ImGui::BulletText("Die Karte kann mit den Pfeiltasten bewegt werden\n\n");
        ImGui::Unindent();
    }

    ImGui::Text("");

    // Suchfelder
    ImGui::Text("-=+ Ort suchen +=-");
    ImGui::Separator();
    ImGui::Text("");

    ImGui::BeginGroup(); // RNUM_Group Anfang
    // Raumnummer-Auflistungsbox
    ImGui::BulletText("Suchen via Raumnummer:");
    ImGui::Indent();
    ImGui::BeginChild("left_pane_rnum", ImVec2(RNUM_LP_X_RATIO * _winBounds.z, RNUM_LP_Y_RATIO * _winBounds.w), true);
    _loopCount = 0; // Loop-Count zurücksetzen
    for(std::string s : _graph->getNames()) { // Durch alle Raumnummern iterieren
        if(_rnum_infilter.PassFilter(s.c_str())) { // Prüfen ob der String valide ist
            if(ImGui::Selectable(s.c_str(), _selectedRnum == _loopCount)) { // Punkt anzeigen und ggf. als ausgewählt anzeigen
                _selectedRnum = _loopCount;
                _selectedTag  = -1;
            }
        }
        _loopCount++;
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // Raumnummer-Inputtext
    ImGui::BeginGroup();
    ImGui::Text("Raumnummer:");
    ImGui::PushItemWidth(RNUM_IT_X_RATIO * _winBounds.z);
    //ImGui::InputText("##rnum_it", _raumnummer_it, MAX_RNUM_LEN);
    _rnum_infilter.Draw("##rnum_it", RNUM_IT_X_RATIO * _winBounds.z);
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    ImGui::Unindent();
    ImGui::EndGroup(); // RNUM_Group Ende

    ImGui::Text("");

    ImGui::BeginGroup(); // TAG_Group Anfang
    // Tags-Auflistungsbox
    ImGui::BulletText("Suchen via Tag:");
    ImGui::Indent();
    ImGui::BeginChild("left_pane_tags", ImVec2(RNUM_LP_X_RATIO * _winBounds.z, RNUM_LP_Y_RATIO * _winBounds.w), true);
    _loopCount = 0; // Loop-Counter zurücksetzen
    for(std::string s : _graph->getTags()) { // Durch alle Tags iterieren
        if(_tags_infilter.PassFilter(s.c_str())) { // Prüfen ob der Strin valide ist
            if(ImGui::Selectable(s.c_str(), _selectedTag == _loopCount )) { // Punkt anzeigen und ggf. als ausgewählt anzeigen
                _selectedRnum = -1;
                _selectedTag  = _loopCount;
            }
        }
        _loopCount++;
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // Tags-Inputtext
    ImGui::BeginGroup();
    ImGui::Text("Tag:");
    ImGui::PushItemWidth(RNUM_IT_X_RATIO * _winBounds.z);
    //ImGui::InputText("##tag_it", _tag_it, MAX_TAG_LEN);
    _tags_infilter.Draw("##tag_it", RNUM_IT_X_RATIO * _winBounds.z);
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    ImGui::Unindent();
    ImGui::EndGroup(); // Tag_Group Ende

    ImGui::Text("");

    // Schnellster Weg
    ImGui::Text("-=+ Schnellster Weg zum ausgewählten Ort +=-");
    ImGui::Separator();
    ImGui::Text("");
    ImGui::Indent();
    if(ImGui::Button("Weg anzeigen")) {
        // Modal Popup öffnen
        ImGui::OpenPopup("Fehler");
    } if(ImGui::BeginPopupModal("Fehler", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        if(_selectedRnum != -1 || _selectedTag != -1) { // Prüfen ob ein Tag oder eine Raumnummer ausgewählt ist
            this->_executeSearchPath(); // Pfad suchen
            ImGui::CloseCurrentPopup();
        }
        ImGui::Text("Sie müssen eine Raumnummer oder einen Tag auswählen.");
        ImGui::Separator();
        if(ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }


    ImGui::Unindent();

    ImGui::End();
}

// -- _executeSearchPath --
// Methode startet die Suche für den kürzesten Weg zu dem aktuell ausgewählten Knoten
void cSearchUI::_executeSearchPath() {
    _graph->resetPath(); // Pfad zurücksetzen
    // Prüfen ob mit einer Raumnummer gesucht wird
    if       (_selectedRnum != -1 && _selectedTag == -1) {
        _graph->findPath(_graph->getRootNode().getID(), _graph->getNames().at(_selectedRnum)); // Schnellsten Weg suchen
    } else if(_selectedRnum == -1 && _selectedTag != -1) { // Prüfen ob mit einem Tag gesucht wird
        _graph->findPath(_graph->getRootNode().getID(), com::getIDFromTag(_graph, _selectedTag)); // Schnellsten Weg suchen
    } else {
        // TODO: Error-Handling
    }
}

// -- Destruktor --
cSearchUI::~cSearchUI() {

}























//
