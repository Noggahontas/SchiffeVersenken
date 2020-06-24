
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
	Transienten:	-
	Output:			-
	*/
	void Ausgabe(Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2);

	
	/*
	Funktion:		Funktion zum einmaligen Aufruf für Positionierung und Dimensionierung des Grafikfensters
	Input:			-
	Globals:		-
	Transienten:	-
	Output:			-
	*/
	void Grafikfenster();


	/*
	Funktion:		Funktion zum einmaligen Aufruf für Screen am Anfang / Ende eines Spieles
	Input:			char indikator: S = Start, E = Ende
	Globals:		-
	Transienten:	-
	Output:			-
	*/
	void Screen(char indikator);

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
	Transienten:	-
	Output:			Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes  
	*/
	Position SpielfeldErstellen(int index);

	/*
	Funktion:		Ausgabe einer Legende mit den wichtigen Informationen zum Spieler ( Verteidigungsstartegie, Angriffsstrategie, Schüsse, versenkte Schiffe etc.)
	Input:			Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes des jeweiligen Spielers
					int index : Nummer des Spielers, Spieler 1 = 1 und Spieler 2 = 2
					Player Spieler1 : Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des 1.Spielers
					Player Spieler2 : Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des 2.Spielers
	Globals:		-
	Transienten:	-
	Output:			-
	*/
	void DisplayOutput::Legende(Position EckpunktSpielfeld, int index, Player Spieler1, Player Spieler2);

	/*
	Funktion:		Darstellung eines Schiffes im Spielfeld einschließlich bereits getroffener Stellen
	Input:			Position EckpunktSpielfeld: linke obere Ecke des Spielfeldes
					Ship Schiff: Objekt der Klasse Ship, darzustellendes Schiff
					int Farbe: Farbe der Schiffe des Spielers
	Globals:		-
	Transienten:	-
	Output:         -
	*/
	void DarstellungSchiff(Position EckpunktSpielfeld, Ship Schiff, int Farbe);

	/*
	Funktion:		Kennzeichnung eines getroffenen Feldes auf dem Spielfeld mit einem Kreuz
	Input:			Position EckpunktSpielfeld: linke obere Ecke des Spielfeldes
					int Farbe: Farbe des Treffers (Rot / Weiss)
					Position Treffer: Koordinaten des Schusses
	Globals:		-
	Transienten:	-
	Output:			-
	*/
	void getroffenesFeld (Position EckpunktSpielfeld, Position Schuss, int Farbe);
};

