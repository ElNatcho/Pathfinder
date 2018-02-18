#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>
#include<string>

int main(int argc, char **argv) {
    // Prüfen ob ein Bild zum laden übergeben wurde
    if(argc != 2) {
        std::cout << "./MapCreator <img_file>" << std::endl;
        return 0;
    }

    // Das Fenster und dessen Event(s) erstellen
    sf::RenderWindow window(sf::VideoMode(600,480), "Map Creator v0.1");
    sf::Event        sfEvent;

    // ImGui Initialisieren
    sf::Clock deltaClock;
    ImGui::CreateContext();
    ImGui::SFML::Init(window);

    // Texture/Sprite welche die Karte darstellen erstellen
    sf::Texture tex;
    if(!tex.loadFromFile(argv[1])) { // Versuchen das Bild zu laden
        std::cout << "[ERROR] Bild konnte nicht geladen werden: " << argv[1] << std::endl;
        return 0;
    }
    // Sprite erstellen
    sf::Sprite spr;
    spr.setTexture(tex); // Textur des Sprites festlegen
    // Bild skalieren, sodass keine schwarzen Balken an den Rändern des Fenster entstehen oder ein Teil des Bildes abgeschnitten wird
    spr.setScale((float)window.getSize().x / (float)tex.getSize().x,
                 (float)window.getSize().y / (float)tex.getSize().y);

    // Speichert ob der Punkt hinzufügen Dialog angezeigt werden soll
    bool addPoint = false;
    sf::Vector2i mouse_pos; // Vector speichert die Position der Maus bei der der linke Knopf das letzte mal gedrückt wurde

    // Window-Loop erstellen und aufrechterhalten solange bis das Fenster geschlossen wird
    while (window.isOpen()) {
        while (window.pollEvent(sfEvent)) {
            // ImGui Event verarbeiten
            ImGui::SFML::ProcessEvent(sfEvent);

            // Fenster schliessen falls der User es schliessen will
            if(sfEvent.type == sf::Event::Closed) {
                window.close();
            }

            // Prüfen ob ein Knopf der Maus gedrückt wurde
            if(sfEvent.type == sf::Event::MouseButtonReleased) {
                if(sfEvent.mouseButton.button == 0) { // Linker Knopf wurde gedrückt
                    mouse_pos = sf::Mouse::getPosition(window);
                    addPoint  = true;
                }
            }
        }

        // ImGui Elemente Update
        ImGui::SFML::Update(window, deltaClock.restart());

        // Karte/Bild zeichnen
        window.clear();

        window.draw(spr);

        // Prüfen ob ein Punkt hinzugefügt werden soll
        if(addPoint) {
            // ImGui Fenster beginnen
            ImGui::Begin("Punkt hinzufügen");

            ImGui::LabelText(" ", std::string("Mouse_Pos: X: " + std::to_string(mouse_pos.x) + " Y: " + std::to_string(mouse_pos.y)).c_str());

            if(ImGui::Button("OK")) {
                addPoint = false;
            }

            ImGui::End();
        }

        // ImGui Elemente Zeichnen
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
