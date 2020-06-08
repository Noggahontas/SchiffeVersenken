
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
	// Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	// int Farbe : Farbe der Schiffe des Spielers
	// Ausgabe liefert zur�ck ob Button "schneller" (seit dem letzten Funktionsaufruf) bet�tigt wurde
	bool Ausgabe(Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2);

	// einmaliger Aufruf zum Positionieren eines Grafikfensters
	// Parameter:
	// Position Bildschirm: Position des Grafikfensters auf dem Bildschrim
	//	int Startpunkt : "Ankerpunkt" auf der Grafikoberfl�che (wird zur Skalierung der Breite ben�tigt)
	void Grafikfenster(Position Bildschirm, int Startpunkt);

	//Breite eines Kaestchens des dargestellten Spielfeldes
	int Kaestchengroesse;  // sinnvolle Angabe: 20

private:
	// diese Funktionen werden in der Funktion Ausgabe(...) aufgerufen

	//	Funktion zum Erstellen eines Spielfeldes linke obere Ecke zur Orientierung zur�ck
	//	Parameter: 
	//	Position Bildschirm : Koordinate der linken oberen Ecke des Grafikfensters
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	//	int Startpunkt : "Ankerpunkt" auf der Grafikoberfl�che
	Position SpielfeldErstellen(Position Bildschirm, int index, int Startpunkt);

	//  Ausgabe einer Legende mit den wichtigen Informationen zum Spieler ( Verteidigungsstartegie, Angriffsstrategie, Sch�sse, versenkte Schiffe etc.)
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	//  Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	Position DisplayOutput::Legende(Position EckpunktSpielfeld, int Startpunkt, int index, Player Spieler);

	//  Funktion zeichnet ein Schiff in das Spielfeld (muss �berarbeitet werden / im Bezug auf Klasse ship)
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	Ship Schiff : darzustellendes Schiff
	//	int Farbe : Farbe der Schiffe des Spielers
	void DarstellungSchiff(Position EckpunktSpielfeld, Ship Schiff, int Farbe);

	//  kennzeichnet ein getroffenes Feld
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  Position Treffer : Koordinaten des Treffers 
	//  int Farbe : Farbe des Treffers (Rot / Weiss)
	void getroffenesFeld (Position EckpunktSpielfeld, Position Treffer, int Farbe);

	// fr�gt ab, ob Spiel schneller laufen muss
	// Parameter:
	// int Startpunkt : "Ankerpunkt" auf der Grafikoberfl�che zur Positionierung des "schneller"-Buttons
	bool Beschleunigung(int Startpunkt);
};

