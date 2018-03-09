#include"cWinMgr.hpp"

// -- Konstruktor --
cWinMgr::cWinMgr() {
    // Werte setzen
    _win.create(sf::VideoMode(1280, 720), "Pathfinder"); // Fenster erstellen
}

// -- run --
// Führt den CORE_LOOP der Anwendung aus
void cWinMgr::run() {
    // Events abfangen und verarbeiten
    this->processEvents();

    // Objekte ggf. updaten
    this->update();

    // Objekte ggf. zeichnen
    this->render();
}

// -- processEvents --
// Methode fängt Events ab und verarbeitet diese
void cWinMgr::processEvents() {
    // Solange ausführen bis kein Event mehr vorhanden ist
    while(_win.pollEvent(_sfEvent)) {
        // Prüfen ob das Fenster geschlossen wird
        if(_sfEvent.type == sf::Event::Closed) {
            running = false;
        }
    }
}

// -- update --
// Methode updated Objekte
void cWinMgr::update() {

}

// -- render --
// Methode zeichnet Objekte
void cWinMgr::render() {
    _win.clear();

    _win.display();
}

// -- Destruktor --
cWinMgr::~cWinMgr() {

}
