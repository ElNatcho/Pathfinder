#include"cFileMgr.hpp"

// -- Konstruktor --
cFileMgr::cFileMgr() {
    //Alloc Mem
    _fstream = new std::fstream();
    _tmpString = new std::string();
    _fileContent = new std::vector<std::string>();

}

// -- openFile --
// Methode versucht eine Datei zu öffnen
// @param path: Pfad zur/Name der Datei die geöffnet werden soll
bool cFileMgr::openFile(std::string file) {
    if(_fstream->is_open()) { // Prüfen ob eine Datei geöffnet ist
        _fstream->close(); // Geöffnete Datei schliessen
    }
    _fstream->open(file, std::ios::in | std::ios::out | std::ios::app); // Datei im rw Modus öffnen
    return _fstream->is_open(); // Status zurückgeben
}

// -- closeFile --
// Methode versucht die aktuell geöffnete Datei zu schliessen
bool cFileMgr::closeFile() {
    if(_fstream->is_open()) { // Prüfen ob eine Datei geöffnet ist
        _fstream->close(); // Geöffnete Datei schliessen
    }
    return _fstream->is_open(); // Status zurückgeben
}

// -- writeToFile --
// Methode versucht einen String in die aktuell geöffnete Datei zu schreiben
// @param str: String der geschrieben werden soll
bool cFileMgr::writeToFile(std::string str) {
    _fstream->clear(); // Reset rw-Position
    if(_fstream->is_open()) { // Prüfen ob eine Datei geöffnet ist
        *_fstream << str; // String in die Datei schreiben
        return true;
    } else {
        return false;
    }
}

// -- readFileContent --
// Methode versucht den Inhalt der aktuell geöffneten Datei auszulesen
std::vector<std::string> cFileMgr::readFileContent() {
    _fstream->clear(); // Reset rw_Posi
    _fileContent->clear(); // Aktuellen Inhalt löschen

    if(_fstream->is_open()) { // Prüfen ob eine Datei geöffnet ist
        while(!_fstream->eof() && _fstream->good()) { // Solange Daten auslesen bis man das Ende der Datei erreicht hat und der stream noch ok ist
            std::getline(*_fstream, *_tmpString); // Aktuelle Zeile auslesen
            _fileContent->push_back(*_tmpString); // Zeile abspeichern
        }
    }

    return *_fileContent;
}

// -- Destruktor --
cFileMgr::~cFileMgr() {
    // Free Mem
    SAFE_DELETE(_fstream);
    SAFE_DELETE(_tmpString);
    SAFE_DELETE(_fileContent);


}
