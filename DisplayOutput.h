
#pragma once

#include "stdafx.h"
#include <string>
#include "Global_Definitions.h"
#include "Player.h"
#include "Global_Definitions_DisplayOutput.h"
using namespace std;


class DisplayOutput
{
public:
	// Funktion, um die Schiffe des Spielers und Treffer auf dem Spielfeld darzustellen
	// Parameter:
	// int Kaestchengroesse: Breite eines Kaestchens des dargestellten Spielfeldes // sinnvolle Angabe: 20
	// Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	// int Farbe : Farbe der Schiffe des Spielers
	void Ausgabe(int Kaestchengroesse, Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2);

	// einmaliger Aufruf zum Setzen eines Grafikfensters
	// Parameter:
	// Position Bildschirm: Position des Grafikfensters auf dem Bildschrim
	// int Startpunkt: Abstand der linken oberen Ecke des 1.Spielfeldes zum Ursprung
	// int Kaestchengroesse: Breite eines Kaestchens des dargestellten Spielfeldes // sinnvolle Angabe: 20
	void Grafikfenster(Position Bildschirm, int Startpunkt, int Kaestchengroesse);

	/*
		// set_windowpos(Bildschirm.x, Bildschirm.y, breite, hoehe); Z.279 in DisplaOutput.cpp muss auskommentiert werden
		Position Bildschirm;						// Position des Grafikfensters auf dem Bildschirm
		Bildschirm.x = 500;
		Bildschirm.y = 250;
		int Startpunkt = 50;
		int Kaestchengroesse = 20;		// falls nicht schon anderweitig definiert

		// einmalige Ausgabe pro Spiel
		// moegliche Verbesserung der Ausgabe
		Grafikfenster(Bildschirm,Startpunkt,Kaestchengroesse);
	*/
private:
	// diese Funktionen werden in der Funktion Ausgabe(...) aufgerufen

	//	Funktion zum Erstellen eines Spielfeldes linke obere Ecke zur Orientierung zurück
	//	Parameter: 
	//	Position Bildschirm : Koordinate der linken oberen Ecke des Grafikfensters
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	//	int startpunkt : Ankerpunkt auf der Grafikoberfläche
	Position SpielfeldErstellen(Position Bildschirm, int Kaestchengroesse, int index, int Startpunkt);

	//  Ausgabe einer Legende mit den wichtigen Informationen zum Spieler ( Verteidigungsstartegie, Angriffsstrategie, Schüsse, versenkte Schiffe etc.)
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	//  Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	Position DisplayOutput::Legende(Position EckpunktSpielfeld, int Kaestchengroesse, int Startpunkt, int index, Player Spieler);

	//  Funktion zeichnet ein Schiff in das Spielfeld (muss überarbeitet werden / im Bezug auf Klasse ship)
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	Ship Schiff : darzustellendes Schiff
	//	int Farbe : Farbe der Schiffe des Spielers
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	void DarstellungSchiff(Position EckpunktSpielfeld, Ship Schiff, int Kaestchengroesse, int Farbe);

	//  kennzeichnet ein getroffenes Feld
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  Position Treffer : Koordinaten des Treffers 
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	//  int Farbe : Farbe des Treffers (Rot / Weiss)
	void getroffenesFeld (Position EckpunktSpielfeld, Position Treffer, int Kaestchengroesse, int Farbe);

	bool Beschleunigung(int Startpunkt, int Kaestchengroesse);
};

