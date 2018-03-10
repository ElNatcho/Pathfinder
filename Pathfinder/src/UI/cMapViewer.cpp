#include"cMapViewer.hpp"

// -- Konstruktor --
cMapViewer::cMapViewer() {
    // View initialisieren
}

// -- loadMap --
// Methode lädt die Bilddatei welche die Karte darstellt
// @param map_path: Pfad zur/Name der Datei welche geladen werden soll
void cMapViewer::loadMap(std::string map_path) {
    // Sprite laden
    if(!_mapTex.loadFromFile(map_path)) { // Datei laden und prüfen ob alles OK ist
        std::cout << "[ERROR] cMapViewer: Bilddatei " << map_path << " konnte nicht geladen werden." << std::endl;
    }
    _mapSpr.setTexture(_mapTex); // Sprite laden
}

// -- initView --
// Methode updated den Anzeigebereich des Views
// @param rWin: Referenz auf das Fenster in dem das View gezeichnet wird
void cMapViewer::updateView(sf::RenderWindow &rWin) {
    _mapView.reset(sf::FloatRect(0.F, 0.F,
                                 rWin.getSize().x * X_SIZE_RATIO,
                                 rWin.getSize().y));
    _mapView.setViewport(sf::FloatRect(1.F - X_SIZE_RATIO, 0.F, X_SIZE_RATIO, 1.F));
}

// -- render --
// Methode rendert die Karte und alle dazugehörigen Knoten und deren Verbindungen
// @param rWin: Referenz auf das Hauptfenster des Programms
void cMapViewer::render(sf::RenderWindow &rWin) {
    // In den View-Bereich der Karte zeichnen
    rWin.setView(_mapView);

    // Sprites zeichnen
    rWin.draw(_mapSpr);

}

// -- Destruktor --
cMapViewer::~cMapViewer() {

}
