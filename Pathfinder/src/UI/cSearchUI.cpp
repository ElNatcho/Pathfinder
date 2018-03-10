#include"cSearchUI.hpp"

// -- Konstruktor --
cSearchUI::cSearchUI() {
    // Werte setzen
    _winBounds.x = 0.F;
    _winBounds.y = 0.F;

    _winFlags = 0;
    _winFlags |= ImGuiWindowFlags_NoMove;
    _winFlags |= ImGuiWindowFlags_NoResize;
    _winFlags |= ImGuiWindowFlags_NoTitleBar;

}

// -- updateWinSize --
// Methode updated die Größe des Search-Fensters
// @param rWin: Referenz auf das Fenster in dem das Search-Fenster gezeichnet wird
void cSearchUI::updateWinSize(sf::RenderWindow &rWin) {
    _winBounds.z = rWin.getSize().x * X_WIN_RATIO;
    _winBounds.w = rWin.getSize().y;
}

// -- render --
// Methode rendert das Search-Fenster
// @param rWin: Referenz auf das Fenster in dem das Search-Fenster gezeichnet werden soll
void cSearchUI::render(sf::RenderWindow &rWin) {
    ImGui::Begin("Test", NULL, _winFlags);
    ImGui::SetWindowPos(ImVec2(_winBounds.x, _winBounds.y), true);
    ImGui::SetWindowSize(ImVec2(_winBounds.z, _winBounds.w));
    ImGui::End();
}

// -- Destruktor --
cSearchUI::~cSearchUI() {

}
