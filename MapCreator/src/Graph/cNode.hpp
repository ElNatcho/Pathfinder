#ifndef CNODE_HPP
#define CNODE_HPP

// Includes
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include"../common.hpp"

// cNode
class cNode {
public:

    // Enum das angibt ob ein Knopf geklickt wurde und wie sich
    // sein Status dadurch verändert
    enum CLICK_TYPE {
        CL_SEL,   // Angeklickt und nun ausgewählt
        CL_UNSEL, // Angeklickt und nun nicht mehr ausgewählt
        NCL       // Nicht angeklickt
    };

    // Verbindungsstruktur
    struct sConnection {
        cNode *n; // Knoten auf den verwiesen wird
        float weight; // Gewichtung der Verbindung
        //sf::Lines con; // Linie die die zwei Knoten verbindet
    };

    // -- Kon/Destruktor --
    cNode(std::string id, sf::Vector2f node_pos);
    ~cNode();

    // -- Public Methods --
    void addConnection(sConnection con); // Methode fügt eine Verbindung hinzu

    std::string getID(); // Gibt die ID des Knotens zurück
    sf::CircleShape getShape(); // Gibt _nodeSpr zurück
    std::vector<sConnection> getConnections(); // Methode gibt alle Verbindungen des Kotens zurück

    CLICK_TYPE toggleSelectIfClicked(sf::Vector2f mousePos); // Updated den Knoten falls er angeklickt wurde

private:

    // Private Vars
    std::vector<sConnection> _connections; // Vector speichert alle Verbindungen des Knotens
    std::string _id; // ID des Knotens

    sf::CircleShape _nodeSpr; // Kreis der den Knoten darstellt

    bool _isSelected; // Speichert ob der Knoten ausgewählt ist

};

#endif
