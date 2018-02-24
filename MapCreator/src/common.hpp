#ifndef COMMON_HPP
#define COMMON_HPP

// Bestimmte Warnung ignorieren
#pragma GCC diagnostic ignored "-Wunused-function"

// Includes
#include<SFML/Graphics.hpp>

// SAFE_DELETE Makro
#define SAFE_DELETE(X) {if(X!=nullptr) {delete X; X=nullptr;}}

// Namespace für allgemeine Methoden
namespace com {

    // -- getMousePosWin --
    // Gibt die Position der Maus im Fenster zurück
    // @param mousePos: Position der Maus im skalierten/vergrößerten/verkleinerten Fenseter
    // @param rWin    : Referenz auf jenes Fenster
    static sf::Vector2i getMousePosWin(sf::Vector2i mousePos, sf::RenderWindow &rWin) {
        sf::Vector2f tmp = rWin.mapPixelToCoords(mousePos); // Koordinaten konvertieren
        return sf::Vector2i(tmp.x, tmp.y);
    }

    // -- getMousePosPic --
    // Gibt die Position der Maus im Bild zurück
    // @param mousePos: Position der Maus im skalierten/vergrößerten/verkleinerten Fenseter
    // @param rWin    : Referenz auf jenes Fenster
    // @param tex     : Textur die jenes Bild darstellt
    static sf::Vector2i getMousePosPic(sf::Vector2i mousePos, sf::RenderWindow &rWin, sf::Texture &tex) {
        return sf::Vector2i((float)tex.getSize().x * ((float)mousePos.x / (float)rWin.getSize().x),  // Position der Maus im Bild
                          (float)tex.getSize().y * ((float)mousePos.y / (float)rWin.getSize().y)); // ausrechen und zurückgeben
    }

}

#endif
