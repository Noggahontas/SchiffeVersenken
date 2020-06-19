
#pragma once

#include "stdafx.h"
#include <string>
#include "Global_Definitions.h"
#include "Player.h"

using namespace std;

class DisplayOutput
{
public:
	/* 
	Funktion:		Ausgabe der Spielfelder, der Schiffe und der Treffer 
	Input:			Player Spieler1: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des 1. Spielers
					Player Spieler2: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des 2. Spielers
					int FarbeSpieler1: Farbe der Schiffe des 1. Spielers
					int FarbeSpieler2: Farbe der Schiffe des 2. Spielers
	Globals:		-
	Transienten:	Position Ecke_1: Ecke des 1. Spielfeldes
					Position Ecke_2: Ecke des 2. Spielfeldes
					Position Schuss1_1, Schuss2_1, Schuss3_1:	 letzten 3 Schuesse des Gegners des 1. Spielers
					Position Schuss1_2, Schuss2_2, Schuss3_2:	 letzten 3 Schuesse des Gegners des 2. Spielers
					Ship Schiff_1: Schiff des 1. Spielers
					Ship Schiff_2: Schiff des 2. Spielers
					Position Textfeld: Position des Überschrift im Grafikfenster
					int Schiff_1_Kontrolle:	  Status des Schiffes (gesunken / nicht gesunken) des 1. Spielers
					int Schiff_2_Kontrolle:	  Status des Schiffes (gesunken / nicht gesunken) des 2. Spielers
					int textgroesse: Schriftgroesse im Grafikfenster
					int i: Zählvariable der for-Schleife
					char* ausgabe: Überschrift
	Output:			-
	*/
	void Ausgabe(Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2);

	
	/*
	Funktion:		Funktion zum einmaligen Aufruf für Positionierungnd Dimensionierung des Grafikfensters
	Input:			-
	Globals:		-
	Transienten:	int breite: Breite des Grafikfensters
					int hoehe: Hoehe des Grafikfensters
					int Kaestchengroesse: Klassenvariable (dient der Dimensionierung)
					int Startpunkt: Klassenvariable (dient der Dimensionierung)
					Position Bildschrim: Klassenvariable
	Output:			-
	*/
	void Grafikfenster();

	// Breite eines Kaestchens des dargestellten Spielfeldes
	int Kaestchengroesse; 

	// Position des Grafikfensters auf dem Bildschirm
	Position Bildschirm;						

	// "Ankerpunkt" auf der Grafikoberfläche
	int Startpunkt;

	// Konstruktor, Zuweisung sinnvoller Werte für die Klassenvariablen
	DisplayOutput()
	{
		Kaestchengroesse = 20;
		Bildschirm.x = 500;
		Bildschirm.y = 250;
		Startpunkt = 50;
	}
private:
	//diese Funktionen werden in der Funktion Ausgabe(...) aufgerufen

	/*
	Funktion:		Funktion zum Erstellen eines Spielfeldes linke obere Ecke zur Orientierung zurück
	Input:			int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	Globals:        -
	Transienten:	int const N = 4: benötigte ArrayGröße	
					int i: Zählvariable der for-Schleife
					int dx, dy: Hilfsvariablen zur Abstandsberechnung der Buchstaben bzw Zahlen zueinander
					int differenz: Schrittweite zwischen den gezeichneten Spielfeldlinien
					int faktor = (Startpunkt / 10): Abstand der Buchstaben / Zahlenreihen vom Spielfeld
					int abstand = (index - 1) * 300: Abstand beider Spielfelder
					int textgroesse: Schriftgroesse im Grafikfenster
					Position Buchstaben: Position der Buchstabenreihe entlang des Spielfeldes
					char *BuchstabenArray[10]: Buchstaben in Array gespeichert
					Position Zahlen: Position der Zahlenreihe entlang des Spielfeldes
					char* ZahlenArray[10]: Zahlen in Array gespeichert
					Position Spielfeld[N]: Speichern aller 4 Ecken des Spielfeldes
					int Kaestchengroesse: Klassenvariable (dient der Dimensionierung)
					int Startpunkt: Klassenvariable (dient der Dimensionierung)
	Output:			Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes  
	*/

	Position SpielfeldErstellen(int index);

	/*
	Funktion:		Ausgabe einer Legende mit den wichtigen Informationen zum Spieler ( Verteidigungsstartegie, Angriffsstrategie, Schüsse, versenkte Schiffe etc.)
	Input:			Position EckpunktSpielfeld: linke obere Ecke des Spielfeldes des jeweiligen Spielers
					int index : Nummer des Spielers, Spieler 1 = 1 und Spieler 2 = 2
					Player Spieler1 : Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des 1.Spielers
					Player Spieler2 : Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des 2.Spielers
	Globals:		-
	Transienten:	Position Legende[2]: Array aus Positionen, speichert die linke obere Ecke und die rechte untere Ecke der auszugebenden Textbox
					int Angriffsstrategie: Nummer der Angriffsstrategie des Spielers
					int Verteidigungsstrategie: Nummer der Verteidigungsstartegie des Spielers
					verfehlteSchuesse: Anzahl verfehlter Schuesse des Spielers (im gegnerischen Spielfeld)
					getroffeneSchuesse: Anzahl getroffener Schuesse des Spielers (im gegnerischen Spielfeld)
					versenkteSchiffe: Anzahl versenkter Schiffe des Spielers (im gegnerischen Spielfeld)
					char InfoSpieler[500]: asuzugebender Informationstext
					int Kaestchengroesse: Klassenvariable (dient der Dimensionierung)
	Output:			-
	*/
	void DisplayOutput::Legende(Position EckpunktSpielfeld, int index, Player Spieler1, Player Spieler2);

	/*
	Funktion:		Darstellung eines Schiffes im Spielfeld einschließlich bereits getroffener Stellen
	Input:			Position EckpunktSpielfeld: linke obere Ecke des Spielfeldes
					Ship Schiff: Objekt der Klasse Ship, darzustellendes Schiff
					int Farbe: Farbe der Schiffe des Spielers
	Globals:		-
	Transienten:	int Schiffslaenge: Schiffslaenge des darzustellenden Schiff
					Direction AusrichtungSchiff: Ausrichtung des Schiffs auf dem Spielfeld
					int x1, x2, y1, y2: Hilfsvariablen zum speichern der Ecken des Schiffes
					vector<bool> StatusSchiff: Status des Sdarzustellenden Schiffs (gesunken / nicht gesunken)
					int Statusabfrage: zu ueberpruefende Stelle des Schiffes (getroffen / nicht getroffen)
					Position getroffenesFeld[2]: Speichern der linken oberen Ecke und der rechten unteren Ecke einer getroffenen Stelle
					int Kaestchengroesse: Klassenvariable (dient der Dimensionierung)
	Output:         -
	*/
	void DarstellungSchiff(Position EckpunktSpielfeld, Ship Schiff, int Farbe);

	/*
	Funktion:		Kennzeichnung eines getroffenen Feldes auf dem Spielfeld mit einem Kreuz
	Input:			Position EckpunktSpielfeld: linke obere Ecke des Spielfeldes
					int Farbe: Farbe des Treffers (Rot / Weiss)
					Position Treffer: Koordinaten des Schusses
	Globals:		-
	Transienten:	int x1,x2,xx1,xx2,y1,y2,yy1,yy2: Hilfsvariablen zur Berechnung sich gegenueberliegender Punkte
					int Kaestchengroesse: Klassenvariable (dient der Dimensionierung)
	Output:			-
	*/
	void getroffenesFeld (Position EckpunktSpielfeld, Position Schuss, int Farbe);
};

