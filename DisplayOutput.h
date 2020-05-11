// VERWENDUNG map und string statt Cmap und Cstring
#pragma once

#include "stdafx.h"
//#include "K2mfcmap1.h"
#include <map>
#include <string>
#include <afxtempl.h> // CMap etc.
#include "Global_Definitions.h";

using namespace std;



class DisplayOutput
{
public:

	map <string, int> schiffe; // map oder Cmap??

	//Initialisierung
	// int Initialisierung();

	// Funktion zum erstellen eines Spielfeldes
	// gibt linke obere Ecke zur Orientierung zurück
	Position SpielfeldErstellen(int x, int y, int Kaestchengroesse);

	// Legende Zeichen
	void Legende(Position EckpunktSpielfeld, int Kaestchengroesse, int FarbeSpieler1, int FarbeSpieler2);

	// Funktion zeichnet ein Schiff in das Spielfeld
	void Schiff(Position EckpunktSpielfeld, Schiffsposition LokalisierungSchiff, int Kaestchengroesse, int Schiffslaenge, string Spieler);

	// kennzeichnet ein getroffenes Feld
	void getroffenesFeld (Position EckpunktSpielfeld,Position Treffer, int Kaestchengroesse);
};

