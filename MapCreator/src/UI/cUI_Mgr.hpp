#ifndef CUI_MGR_HPP
#define CUI_MGR_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>
#include<Core/Graph/cGraph.hpp>

// cUI_Mgr
class cUI_Mgr {
public:

    // -- Kon/Destruktor --
    cUI_Mgr(cGraph *graph);
    ~cUI_Mgr();

    // -- Methoden --
    bool renderAddNode_UI(sf::Vector2f mouse_win_pos, sf::Vector2f mouse_pic_pos);
    bool renderAddConn_UI();

private:

    // -- Private Vars --
    cGraph *_graph; // Graph der erstellt wird
    std::vector<cNode*> _selectedNodes; // Aktuell ausgewählte Knoten

    char *_newNodeID; // ID des Knotens der neu hinzugefügt wird
    char *_nodeTags;  // Tags die dem Knoten hinzugefügt werden sollen
    float _newWeight; // Gewichtung einer neuen Verbindung

};

#endif
