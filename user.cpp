// User.cpp : header file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "user.h"

#include <iostream>
#include <fstream>


#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif

#include "math.h"

// Includes für Klassen Ship, Player, PlayerHistory
//#include <vector>
#include "Ship.h"
#include "Global_Definitions.h" // hier können alle Structs etc rein, die wir quer durch unsre Dateien brauchen; da einbinden, wo sie gebraucht werden!
#include "Player.h"

// Includes für Strategien
#include <time.h>
#include "AttackStrategy1.h"

// Include fuer Ausgabe des Graphikfensters
#include "DisplayOutput.h"



void user_main()
{

	// für die Ausgabe braucht man diese Sachen scheinabr -> nicht vergessen auf Run zu drücken!!
	DisplayOutput Ausgabe;
	Schiffsposition schiff_spieler1_Schlachtschiff, schiff_spieler2_UBoot_1;
	Position linkeEckeOben, Treffer;

	// Beispielpositionschiff
	schiff_spieler1_Schlachtschiff.linkeEckeOben.x = 1;
	schiff_spieler1_Schlachtschiff.linkeEckeOben.y = 2;
	schiff_spieler1_Schlachtschiff.ausrichtung = 'w'; // Schiff liegt waagrecht
	
	schiff_spieler2_UBoot_1.linkeEckeOben.x = 0;
	schiff_spieler2_UBoot_1.linkeEckeOben.y = 8;
	schiff_spieler2_UBoot_1.ausrichtung = 's';

	// Einlesen der Kaestchengroesse
	int Kaestchengroesse = 20; // guter Wert ist 20

	Treffer = schiff_spieler1_Schlachtschiff.linkeEckeOben;

	int Laenge_Schlachtschiff = 5;
	int Laaenge_Kreuzer = 4;
	int Laenge_Zerstoerer = 3;
	int Laenge_UBoot = 2;

	// statt der Strings könnte auch eine Kennung {1 = Spieler 1; 2= Spieler 2} übergeben werden
	string spieler1 = "Spieler 1";
	string spieler2 = "Spieler 2";

	// Legende
	Position Legende;

	int bedingung = 1; // Bedingung das Spiel noch läuft;

	//Kaestchengroesse = Ausgabe.Initialisierung();
	linkeEckeOben = Ausgabe.SpielfeldErstellen(500,200, Kaestchengroesse);
	Ausgabe.Legende(linkeEckeOben, Kaestchengroesse, BLAU, GRUEN);

	while (bedingung != 0)
	{
		Ausgabe.Schiff(linkeEckeOben, schiff_spieler1_Schlachtschiff, Kaestchengroesse, Laenge_Schlachtschiff, spieler1);
		Ausgabe.Schiff(linkeEckeOben, schiff_spieler2_UBoot_1, Kaestchengroesse, Laenge_UBoot, spieler2);
		Ausgabe.getroffenesFeld(linkeEckeOben,Treffer, Kaestchengroesse);
		break;
	}


	//clrscr();

	//_________________________________________________________________________________________
	/*
	int ww, hh;
	set_windowpos(0, 0, 600, 400);

	get_windowsize(&ww, &hh);
	set_drawarea(ww, hh);				// Setzen des Zeichenbereiches
	*/
	srand(time(0)); // Startet den Pseudozufallszahlengenerator








	//_________________________________________________________________________________________
	/* Schäfer Teil, meiste rausgeschmissen

	int ww,hh;
	set_windowpos(0,0,600,400);
	while (1) {								// Endlosschleife
		get_windowsize(&ww, &hh);
		set_drawarea(ww, hh);				// Setzen des Zeichenbereiches
		clrscr();
		
		//......


		Restart();						// Den "Restart"-Button malen und auf eine Aktivierung warten.
		if(StopProcess())break;
		
	}

	*/
}