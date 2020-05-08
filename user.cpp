// User.cpp : header file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "user.h"
#include "graphics\graphicfunctions.h"

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


void user_main()
{

	// für die Ausgabe braucht man diese Sachen scheinabr -> nicht vergessen auf Run zu drücken!!

	int ww, hh;
	set_windowpos(0, 0, 600, 400);

	get_windowsize(&ww, &hh);
	set_drawarea(ww, hh);				// Setzen des Zeichenbereiches
	clrscr();

	//_________________________________________________________________________________________

	srand(time(0)); // Startet den Pseudozufallszahlengenerator


	Player P1;

	int i = 6; // Number of Ship to be moved

	MoveDirection Dir = MoveDirection::Forward;

	cout << "Orientation: " << static_cast <int> (P1.Ships[i].Orientation) << "\n";
	cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";

	cout << " Bewegen-Ergebnis: " << P1.Move(i, Dir) << "\n";
	cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";
	cout << "-----------------------------\n";
	cout << " Bewegen-Ergebnis: " << P1.Move(i, Dir) << "\n";
	cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";
	cout << "-----------------------------\n";
	cout << " Bewegen-Ergebnis: " << P1.Move(i, Dir) << "\n";
	cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";



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