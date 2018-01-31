#include"cFileMgr.hpp"

// -- Konstruktor --
cFileMgr::cFileMgr() {

}

// -- openFile --
// Methode versucht eine Datei zu öffnen
// @param path: Pfad zur/Name der Datei die geöffnet werden soll
bool cFileMgr::openFile(std::string file) {
    return true;
}

// -- closeFile --
// Methode versucht die aktuell geöffnete Datei zu schliessen
bool cFileMgr::closeFile() {
    return true;
}

// -- writeToFile --
// Methode versucht einen String in die aktuell geöffnete Datei zu schreiben
// @param str: String der geschrieben werden soll
bool cFileMgr::writeToFile(std::string str) {
    return true;
}

// -- readFileContent --
// Methode versucht den Inhalt der aktuell geöffneten Datei auszulesen
std::vector<std::string> cFileMgr::readFileContent() {
    return std::vector<std::string>();
}

// -- Destruktor --
cFileMgr::~cFileMgr() {

}
