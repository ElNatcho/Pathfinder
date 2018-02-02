#include"cFileMgr.hpp"

// -- Konstruktor --
cFileMgr::cFileMgr() {
    //Alloc Mem
    _ofstream = new std::ofstream();
    _ifstream = new std::ifstream();
    _tmpString = new std::string();
    _fileContent = new std::vector<std::string>();

}

// -- openFile --
// Methode versucht eine Datei zu öffnen
// @param path: Pfad zur/Name der Datei die geöffnet werden soll
bool cFileMgr::openFile(std::string file) {
    if(_ofstream->is_open()) { // Prüfen ob der ofstream aktuell geöffnet ist
        _ofstream->close(); // Falls ja ofstream schliessen
    }

    if(_ifstream->is_open()) { // Prüfen ob der ifstream aktuell geöffnet ist
        _ifstream->close(); // Falls ja ifstream schliessen
    }

    _ofstream->open(file, std::ios::out | std::ios::trunc); // Datei mit dem ofstream öffnen
    _ifstream->open(file, std::ios::in); // Datei mit dem ifstream öffnen

    return (_ofstream->is_open() && _ifstream->is_open()); // Status zurückgeben
}

// -- closeFile --
// Methode versucht die aktuell geöffnete Datei zu schliessen
bool cFileMgr::closeFile() {
    if(_ofstream->is_open()) { // Prüfen ob der ofstream aktuell geöffnet ist
        _ofstream->close(); // Falls ja ofstream schliessen
    }

    if(_ifstream->is_open()) { // Prüfen ob der ifstream akutell geöffnet ist
        _ifstream->close(); // Falls ja infstream schliessen
    }

    return ((!_ifstream->is_open()) && (!_ofstream->is_open())); // Status zurückgeben
}

// -- writeToFile --
// Methode versucht einen String in die aktuell geöffnete Datei zu schreiben
// @param str: String der geschrieben werden soll
bool cFileMgr::writeToFile(std::string str) {
    if(_ofstream->is_open()) {
        *_ofstream << str;
        return true;
    } else {
        return false;
    }
}

// -- readFileContent --
// Methode versucht den Inhalt der aktuell geöffneten Datei auszulesen
std::vector<std::string> cFileMgr::readFileContent() {
    _fileContent->clear(); // Aktuellen Inhalt löschen

    if(_ifstream->is_open()) { // Prüfen ob eine Datei geöffnet ist
        while(!_ifstream->eof() && _ifstream->good()) { // Solange Daten auslesen bis man das Ende der Datei erreicht hat und der stream noch ok ist
            std::getline(*_ifstream, *_tmpString); // Aktuelle Zeile auslesen
            _fileContent->push_back(*_tmpString); // Zeile abspeichern
        }
    }

    return *_fileContent;
}

// -- Destruktor --
cFileMgr::~cFileMgr() {
    // Free Mem
    SAFE_DELETE(_ofstream);
    SAFE_DELETE(_ifstream);
    SAFE_DELETE(_tmpString);
    SAFE_DELETE(_fileContent);


}
