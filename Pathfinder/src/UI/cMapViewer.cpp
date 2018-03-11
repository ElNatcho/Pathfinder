#include"cMapViewer.hpp"

// -- Konstruktor --
// @param g: Graph der auf der Karte gezeichnet werden soll
cMapViewer::cMapViewer(cGraph *g) {
    // Werte setzen
    _graph = g;
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

// -- processEvent --
// Methode bearbeitet Events die den View betreffen könnten
// @param sfEvent: Event das bearbeitet werden soll
void cMapViewer::processEvent(sf::Event sfEvent) {
    switch (sfEvent.type) {
        // Bewegung des Mausrads abfangen
        case sf::Event::MouseWheelMoved:
            // Prüfen ob nach oben ...
            if(sfEvent.mouseWheel.delta < 0) {
                _mapView.zoom(1.F / INZOOM_RATIO);
            } else { // ... oder unten gescrollt wurde
                _mapView.zoom(INZOOM_RATIO);
            }
        break;

        // Betätigung der Pfeiltasten und des +/- Zeichen abfangen
        case sf::Event::KeyPressed: {
            // Prüfen ob eine der Pfeiltasten gedrückt wurde oder das +/- Zeichen
            switch (sfEvent.key.code) {
                // Rechte Pfeiltaste
                case sf::Keyboard::Right:
                    _mapView.setCenter(_mapView.getCenter().x + MOVE_SPEED, _mapView.getCenter().y);
                break;
                // Linke Pfeiltaste
                case sf::Keyboard::Left:
                    _mapView.setCenter(_mapView.getCenter().x - MOVE_SPEED, _mapView.getCenter().y);
                break;
                // Obere Pfeiltaste
                case sf::Keyboard::Up:
                    _mapView.setCenter(_mapView.getCenter().x, _mapView.getCenter().y - MOVE_SPEED);
                break;
                // Untere Pfeiltaste
                case sf::Keyboard::Down:
                    _mapView.setCenter(_mapView.getCenter().x, _mapView.getCenter().y + MOVE_SPEED);
                break;
                // Plus zeichnen
                case sf::Keyboard::Add:
                    _mapView.zoom(INZOOM_RATIO);
                break;
                // Minus zeichen
                case sf::Keyboard::Subtract:
                case sf::Keyboard::Dash:
                    _mapView.zoom(1.F / INZOOM_RATIO);
                break;
            }
        } break;
    }
}

// -- render --
// Methode rendert die Karte und alle dazugehörigen Knoten und deren Verbindungen
// @param rWin: Referenz auf das Hauptfenster des Programms
void cMapViewer::render(sf::RenderWindow &rWin) {
    // In den View-Bereich der Karte zeichnen
    rWin.setView(_mapView);

    // Sprites zeichnen
    rWin.draw(_mapSpr);

    // Graph zeichnen
    _graph->renderGraph(rWin);

}

// -- Destruktor --
cMapViewer::~cMapViewer() {

}
