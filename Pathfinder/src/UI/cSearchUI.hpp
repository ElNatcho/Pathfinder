#ifndef CSEARCHUI_HPP
#define CSEARCHUI_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>
#include"Core/Graph/cGraph.hpp"

#define X_WIN_RATIO 0.3

class cSearchUI {
public:
    // -- Kon/Destruktor --
    cSearchUI();
    ~cSearchUI();

    // -- Methoden --
    void updateWinSize(sf::RenderWindow &rWin); // Updated die Größe des Search-Fensters

    void render(sf::RenderWindow &rWin); // Zeichnet das Search-Fenster

private:
    // -- Private Vars --
    ImVec4 _winBounds; // Speichert Position und Größe des Search-Fensters

    ImGuiWindowFlags _winFlags;

};

#endif
