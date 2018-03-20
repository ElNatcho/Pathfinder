#ifndef COMMON_HPP
#define COMMON_HPP

// Bestimmte Warnung ignorieren
#pragma GCC diagnostic ignored "-Wunused-function"

// Includes
#include<SFML/Graphics.hpp>
#include"Graph/cGraph.hpp"

// SAFE_DELETE Makro
#define SAFE_DELETE(X) {if(X!=nullptr) {delete X; X=nullptr;}}

// Namespace für allgemeine Methoden
namespace com {

    // -- getMousePosWin --
    // Gibt die Position der Maus im Fenster zurück
    // @param mousePos: Position der Maus im skalierten/vergrößerten/verkleinerten Fenseter
    // @param rWin    : Referenz auf jenes Fenster
    static sf::Vector2f getMousePosWin(sf::Vector2i mousePos, sf::RenderWindow &rWin) {
        return rWin.mapPixelToCoords(mousePos); // Koordinaten konvertieren
    }

    // -- getMousePosPic --
    // Gibt die Position der Maus im Bild zurück
    // @param mousePos: Position der Maus im skalierten/vergrößerten/verkleinerten Fenseter
    // @param rWin    : Referenz auf jenes Fenster
    // @param tex     : Textur die jenes Bild darstellt
    static sf::Vector2f getMousePosPic(sf::Vector2i mousePos, sf::RenderWindow &rWin, sf::Texture &tex) {
        return sf::Vector2f((float)tex.getSize().x * ((float)mousePos.x / (float)rWin.getSize().x),  // Position der Maus im Bild
                          (float)tex.getSize().y * ((float)mousePos.y / (float)rWin.getSize().y)); // ausrechen und zurückgeben
    }

    // -- getIDFromTag --
    // Methode extrahiert die Knoten ID aus einem der Tags die angezeigt werden
    // @param g     : Graph in dem sich die betroffenen Knoten mit den jeweiligen Tags befinden
    // @param tagNum: Position des Tags im Tag-Vector
    static std::string getIDFromTag(cGraph *g, int tagNum) {
        std::string tmpStr = g->getTags().at(tagNum);
        int beginPos = tmpStr.find("(") + 1;
        return tmpStr.substr(beginPos, tmpStr.find(")") - beginPos);
    }

}

#endif
