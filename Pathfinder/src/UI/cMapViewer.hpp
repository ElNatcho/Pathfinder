#ifndef CMAPVIEWER_HPP
#define CMAPVIEWER_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Core/Graph/cGraph.hpp"

#define X_SIZE_RATIO 0.7F

// cMapViewer
class cMapViewer {
public:
    // -- Kon/Destruktor --
    cMapViewer();
    ~cMapViewer();

    // -- Methoden --
    void loadMap(std::string map_path); // Lädt die Bilddatei Welche die Karte darstellt
    void updateView(sf::RenderWindow &rWin); // Updated den Anzeigebereich des Views

    void render(sf::RenderWindow &rWin); // Zeichnet die Karte, Knoten und deren Verbindungen

private:
    // -- Private Vars --
    sf::View _mapView;
    sf::Texture _mapTex;
    sf::Sprite  _mapSpr;
};

#endif
