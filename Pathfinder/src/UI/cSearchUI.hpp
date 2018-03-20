#ifndef CSEARCHUI_HPP
#define CSEARCHUI_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>
#include"Core/Graph/cGraph.hpp"
#include"Core/common.hpp"

#define X_WIN_RATIO 0.27 // Relative Breite des UI Fenster

#define MAX_RNUM_LEN     50 // Maximale Eingabelänge in den Raumnummer-Inputtext
#define MAX_TAG_LEN      50 // Maximale eingabelänge in den Tag-Inputtext
#define RNUM_IT_X_RATIO 0.4 // Relative Breite des Raumnummer-Inputtextfelds
#define RNUM_LP_X_RATIO 0.4 // Relative Breite des left_pane_rnum Childs
#define RNUM_LP_Y_RATIO 0.15 // Relative Höhe des left_pane_rnum Childs

#define RESULT_P_X_RATIO 0.9 // Relative Breite des result_pane Childs
#define RESULT_P_Y_RATIO 0.15 // Relative Höhe des result_pane Childs

class cSearchUI {
public:
    // -- Kon/Destruktor --
    cSearchUI(cGraph *g);
    ~cSearchUI();

    // -- Methoden --
    void initUI(); // Methode initialisiert das UI
    void updateWinSize(sf::RenderWindow &rWin); // Updated die Größe des Search-Fensters

    void render(sf::RenderWindow &rWin); // Zeichnet das Search-Fenster

private:
    // -- Private Vars --
    ImVec4 _winBounds; // Speichert Position und Größe des Search-Fensters
    ImGuiWindowFlags _winFlags; // Bitflags für das Fenster

    char *_raumnummer_it; // Wert des Raumnummer-Inputfeldes
    char *_tag_it; // Wert des Tag-Inputfeldes

    cGraph *_graph; // Zeiger auf den aktuellen Graphen

    ImGuiTextFilter _rnum_infilter; // Inputfilter für die eingegebenen Raumnummern
    ImGuiTextFilter _tags_infilter; // Inputfilter für die eingegebenen Tags

    int _loopCount; // Counter für die beiden foreach-Loops
    int _selectedRnum; // Speichert den aktuell ausgewählten Raum
    int _selectedTag; // Speichert den aktuell ausgewählten Raum

    // -- Private Methods --
    void _executeSearchPath(); // Methode startet die Suche für den kürzesten Weg zu einem bestimmten Knoten

};

#endif
