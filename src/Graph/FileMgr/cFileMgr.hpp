#ifndef CFILEMGR_HPP
#define CFILEMGR_HPP

// Includes
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"../../common.hpp"

// cFileMgr
class cFileMgr {
public:

    // -- Kon/Destruktor --
    cFileMgr();
    ~cFileMgr();

    // -- Methoden --
    bool openFile (std::string path); // Versucht eine Datei zu öffnen
    bool closeFile(); // Versucht die aktuell geöffnete Datei zu schliessen

    bool writeToFile(std::string str); // Versucht einen String in die aktuell geöffnete Datei zu schreiben
    std::vector<std::string> readFileContent(); // Versucht den Inhalt der aktuell geöffneten Datei auszulesen

private:

    // -- Member Vars --
    std::ofstream *_ofstream; // Ofstream zum schreiben der Datei
    std::ifstream *_ifstream; // Ifstream zum lesen der Datei

    std::vector<std::string> *_fileContent; // Vector der den Inhalt einer Datei speichert
    std::string *_tmpString; // Speichert temporär eine aus der aktuell geöffneten Datei ausgelesene Zeile

};

#endif
