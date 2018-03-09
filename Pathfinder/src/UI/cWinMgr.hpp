#ifndef CWINMGR_HPP
#define CWINMGR_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>

// cWinMgr
class cWinMgr {
public:
    // -- Kon/Destruktor --
    cWinMgr();
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
    sf::RenderWindow _win;
    sf::Event _sfEvent;
    sf::Clock _deltaClock;


};

#endif
