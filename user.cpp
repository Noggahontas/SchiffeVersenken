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
#include "AttackStrategy2.h"
#include "AttackStrategy3.h"


void user_main()
{

	// für die Ausgabe braucht man diese Sachen scheinabr -> nicht vergessen auf Run zu drücken!!

	int ww, hh;
	set_windowpos(0, 0, 600, 400);

	get_windowsize(&ww, &hh);
	set_drawarea(ww, hh);				// Setzen des Zeichenbereiches
	clrscr();

	//_________________________________________________________________________________________

	srand(static_cast<unsigned int>(time(NULL)));	// Macht PNG an 

	// Test Strat1:
	struct Position Pos1;							// da stehen die Angriffskoordinaten
	AttackStrategy1(&Pos1);							// Angriffskoordinaten holen
	cout << endl << "Strat 1: Coordinates to be attacked (x,y): " << 
		"(" << (Pos1.x) << "," << (Pos1.y) << ")" << "  " << "Pew Pew" << endl;
	
	// Test Strat2:
	struct Position Pos2 = { 0,3 };					// Erster Angriff bei (0,3)
	int sum = 3;									// Nur zum checken
	for (int ii = 0; ii < 23; ii++)
	{	
		AttackStrategy2(&Pos2);	
		sum = sum + Pos2.x + Pos2.y;
	}
	cout << "(x,y): " << "(" << Pos2.x << "," << Pos2.y << ")" << 
		"\t" <<"CheckSum Strat2: " << sum << "/216"<< endl;

	// Test Strat3:
	enum AttackDirection AttDir = S;			// Richtungsverlauf der Angriffe (vielleicht geht das irgendwie sinnvoller..)
	struct Position Pos3 = { 0 , 0 };			// Erster Angriff bei (0,0)
	sum = 0;
	for (int ii = 0 ; ii < 99 ; ii++)
	{
		AttackStrategy3(&Pos3, &AttDir);
		sum = sum + Pos3.x + Pos3.y;
	}
	cout << "(x,y): " << "(" << Pos3.x << "," << Pos3.y << ")" << "\t" << "CheckSum Strat3: " << sum << "/900" << endl;


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