#ifndef CUI_MGR_HPP
#define CUI_MGR_HPP

// Includes
#include<SFML/Graphics.hpp>
#include<imgui.h>
#include<imgui-SFML.h>
#include<iostream>
#include"../Graph/cGraph.hpp"

// cUI_Mgr
class cUI_Mgr {
public:

    // -- Kon/Destruktor --
    cUI_Mgr(cGraph *graph);
    ~cUI_Mgr();

    // -- Methoden --
    bool renderAddNode_UI(sf::Vector2i mouse_win_pos, sf::Vector2i mouse_pic_pos);


private:

    // -- Private Vars --
    cGraph *_graph; // Graph der erstellt wird

    char *_newNodeID; // ID des Knotens der neu hinzugefügt wird

};

#endif
