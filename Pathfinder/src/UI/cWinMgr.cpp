#include"cWinMgr.hpp"

// -- Konstruktor --
// @param map_path: Pfad zur/Name der Datei welche die Karte beinhaltet
cWinMgr::cWinMgr(std::string map_path) {
    // Werte setzen und Fenster erstellen
    _window.create(sf::VideoMode(1280, 720), "Pathfinder"); // Fenster erstellen
    running = true;

    // ImGui erstellen
    ImGui::CreateContext();
    ImGui::SFML::Init(_window);

    // MapViewer setup
    _mapViewer.loadMap(map_path);
    _mapViewer.updateView(_window);
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
    while(_window.pollEvent(_sfEvent)) {
        // ImGui Events verarbeiten
        ImGui::SFML::ProcessEvent(_sfEvent);
        // Prüfen ob das Fenster geschlossen wird
        if(_sfEvent.type == sf::Event::Closed) {
            running = false;
        }
        // Prüfen ob die Fenstergröße verändert wird
        if(_sfEvent.type == sf::Event::Resized) {
            _mapViewer.updateView(_window); // Größe der Karte usw anpassen
        }
    }
}

// -- update --
// Methode updated Objekte
void cWinMgr::update() {
    // ImGui updaten
    ImGui::SFML::Update(_window, _deltaClock.restart());
}

// -- render --
// Methode zeichnet Objekte
void cWinMgr::render() {
    _window.clear(sf::Color::Red);

    //ImGui::ShowDemoWindow();
    /*ImGui::Begin("Test");
    ImGui::SetWindowPos(ImVec2(0,0), true);
    ImGui::SetWindowSize(ImVec2(300, _window.getSize().y));
    ImGui::End();*/

    // ImGui zeichnen
    ImGui::SFML::Render(_window);

    // Karte, Knoten und deren Verbindungen zeichnen
    _mapViewer.render(_window);

    _window.display();
}

// -- Destruktor --
cWinMgr::~cWinMgr() {

}































//
