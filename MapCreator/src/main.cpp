#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>
#include<string>
#include"Graph/cGraph.hpp"
#include"UI/cUI_Mgr.hpp"
#include"common.hpp"

int main(int argc, char **argv) {
    // Prüfen ob ein Bild zum laden übergeben wurde
    if(argc != 2) {
        std::cout << "./MapCreator <img_file>" << std::endl;
        return 0;
    }

    // Das Fenster und dessen Event(s) erstellen
    sf::RenderWindow window(sf::VideoMode(1280,720), "Map Creator v0.1");
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


    bool addNode = false; // Speichert ob der Punkt-Hinzufügen-Dialog angezeigt werden soll
    bool addConn = false; // Speichert ob der Verbindung-Hinzufügen-Dialog angezeigt wird
    sf::Vector2f mouse_win_pos; // Vector speichert die Position der Maus im Fenseter
    sf::Vector2f mouse_pic_pos;   // Vector speichert die Position der Maus im Bild

    cGraph graph; // Grap der erstellt/bearbeitet wird

    cUI_Mgr ui_mgr(&graph); // UI-Mgr mit Zeiger auf den Graphen erstellen

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
            if(sfEvent.type == sf::Event::MouseButtonReleased && !addNode) {
                if(sfEvent.mouseButton.button == 0) { // Linker Knopf wurde gedrückt
                    mouse_win_pos = com::getMousePosWin(sf::Mouse::getPosition(window), window);      // Position der Maus im Fenster berechen
                    mouse_pic_pos = com::getMousePosPic(sf::Mouse::getPosition(window), window, tex); // Position der Maus im Bild berechen
                    if(!graph.checkNodeSelect(mouse_win_pos)) { // Prüfen ob ein Knoten ausgewählt wurde
                        addNode = true;
                    }
                }
            }
        }

        // ImGui Elemente Update
        ImGui::SFML::Update(window, deltaClock.restart());

        // Karte/Bild zeichnen
        window.clear();

        window.draw(spr);

        // Den Verbindung-Hinzufügen-Dialog anzeign
        addConn = ui_mgr.renderAddConn_UI(); // Klassen entscheident selbst, wann sie diesen anzeigt

        // Prüfen ob ein Knoten hinzugefügt werden soll
        if(addNode && !addConn) {
            addNode = ui_mgr.renderAddNode_UI(mouse_win_pos, mouse_pic_pos); // AddNode UI anzeigen
        }

        //ImGui::ShowDemoWindow();

        // Graph zeichnen
        graph.renderGraph(window);

        // ImGui Elemente Zeichnen
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
