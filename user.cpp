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

// Includes f�r Klassen Ship, Player, PlayerHistory
//#include <vector>
#include "Ship.h"
#include "Global_Definitions.h" // hier k�nnen alle Structs etc rein, die wir quer durch unsre Dateien brauchen; da einbinden, wo sie gebraucht werden!
#include "Player.h"

// Includes f�r Strategien
#include <time.h>
#include "Global_Definitions_Strategies.h"
#include "AttackStrategy1.h"
#include "AttackStrategy2.h"
#include "AttackStrategy3.h"
#include "AttackStrategy4.h"

// Include fuer Ausgabe des Graphikfensters
#include "DisplayOutput.h"



void user_main()
{
	int ww, hh;
	set_windowpos(0, 0, 600, 400);

	get_windowsize(&ww, &hh);
	set_drawarea(ww, hh);				// Setzen des Zeichenbereiches
	clrscr();

	//_________________________________________________________________________________________

	srand(static_cast<unsigned int>(time(NULL)));	// PZG starten; Seed = time

	// Test Strat4:
	Position Schuss = {};
	bool das_war_ein_treffer = false;
	for (int ii = 0; ii < 8; ii++)
	{
		Schuss = AttackStrategy4(&Schuss, &das_war_ein_treffer);
		cout << "(" << (Schuss.x) << "," << (Schuss.y) << ")" << "  " << "Pew Pew" << endl;

		if (ii == 0)
		{
			das_war_ein_treffer = true; cout << ii <<": Schuss hat getroffen." << endl;
		}
		else if (ii == 1)
		{
			das_war_ein_treffer = true; cout << ii << ": Schuss hat getroffen." << endl;
		}
		else if (ii == 3)
		{
			das_war_ein_treffer = true; cout << ii << ": Schuss hat getroffen." << endl;
		}
		else if (ii == 2)
		{
			das_war_ein_treffer = false; cout << ii << ": Schuss ging daneben." << endl;
		}
		else
		{
			das_war_ein_treffer = false; cout << ii << ": Schuss ging daneben." << endl;
		}
		;
	}
	




	//_________________________________________________________________________________________
	/* Sch�fer Teil, meiste rausgeschmissen

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