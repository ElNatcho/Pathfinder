#ifndef CWINMGR_HPP
#define CWINMGR_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>
#include"Core/Graph/cGraph.hpp"
#include"cMapViewer.hpp"
#include"cSearchUI.hpp"

// cWinMgr
class cWinMgr {
public:
    // -- Kon/Destruktor --
    cWinMgr(std::string map_path, cGraph *g);
    ~cWinMgr();

    // -- Methoden --
    void run(); // Führt den CORE_LOOP der Anwendung aus

    void processEvents(); // Fängt Events ab und verarbeitet diese
    void update(); // Updated Objekte
    void render(); // Rendert Objekte

    sf::RenderWindow getWin(); // Gibt das aktuelle Objekt zurück

    // -- Public Vars --
    bool running; // Speichert ob der CORE_LOOP läuft oder nicht

private:

    // -- Private Vars --
    sf::RenderWindow _window;
    sf::Event _sfEvent;
    sf::Clock _deltaClock;

    cMapViewer _mapViewer; // Verwaltung der Karte, Zeichnen der Knoten/Verbindungen
    cSearchUI  _searchUI; // Verwalten und darstellen des UI

    cGraph *_graph; // Graph der die Routen durch die Karte darstellt

};

#endif
