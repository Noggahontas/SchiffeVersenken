
#pragma once

#include "stdafx.h"
#include <string>
#include "Global_Definitions.h"
#include "Player.h"
#include "Global_Definitions_DisplayOutput.h"
using namespace std;

// Anmerkung zu wichtigen Aenderungen
// user.cpp Z.52 und Z.58 zu übernehmende Änderungen als Kommentar in der jeweiligen Zeile
// Z.52:	Graphics.Kaestchengroesse = 20; // NEU: Graphics..DisplayOutput(); Konstruktor aufrufen
// Z.58: 	Graphics.Grafikfenster(Bildschirm, Startpunkt); // Erstellen Grafikfenster: Test für einmaligen Aufruf // NEU: Graphics.Grafikfenster();

class DisplayOutput
{
public:
	// Funktion, um die Spielfelder, die Schiffe und die Treffer der Spieler darzustellen
	// 
	// Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	// int Farbe : Farbe der Schiffe des Spielers
	void Ausgabe(Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2);

	// einmaliger Aufruf zum Positionieren eines Grafikfensters
	void Grafikfenster();

	// Abfrage, ob Spiel schneller laufen soll (schneller  => true, nicht schneller/ unverändert => false)
	// Ausgabe eines Buttons "schneller"
	// 
	bool Beschleunigung();

	//Breite eines Kaestchens des dargestellten Spielfeldes
	int Kaestchengroesse; 

	// Position des Grafikfensters auf dem Bildschirm
	Position Bildschirm;						

	// "Ankerpunkt" auf der Grafikoberfläche
	int Startpunkt;

	// Konstruktor, Zuweisung sinnvoller Werte
	DisplayOutput()
	{
		Kaestchengroesse = 20;
		Bildschirm.x = 500;
		Bildschirm.y = 250;
		Startpunkt = 50;
	}
private:
	// diese Funktionen werden in der Funktion Ausgabe(...) aufgerufen

	//	Funktion zum Erstellen eines Spielfeldes linke obere Ecke zur Orientierung zurück
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	Position SpielfeldErstellen(int index);

	//  Ausgabe einer Legende mit den wichtigen Informationen zum Spieler ( Verteidigungsstartegie, Angriffsstrategie, Schüsse, versenkte Schiffe etc.)
	//	
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	//  Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	void DisplayOutput::Legende(Position EckpunktSpielfeld, int index, Player Spieler1, Player Spieler2);

	//  Funktion zeichnet ein Schiff in das Spielfeld (muss überarbeitet werden / im Bezug auf Klasse ship)
	//	
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	Ship Schiff : darzustellendes Schiff
	//	int Farbe : Farbe der Schiffe des Spielers
	void DarstellungSchiff(Position EckpunktSpielfeld, Ship Schiff, int Farbe);

	//  kennzeichnet ein getroffenes Feld
	//	
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  Position Treffer : Koordinaten des Treffers 
	//  int Farbe : Farbe des Treffers (Rot / Weiss)
	void getroffenesFeld (Position EckpunktSpielfeld, Position Treffer, int Farbe);
};

