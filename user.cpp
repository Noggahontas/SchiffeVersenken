// User.cpp : header file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "user.h"

// #include "graphics\graphicfunctions.h"

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
#include "AttackStrategy1.h"

// Include fuer Ausgabe des Graphikfensters
#include "DisplayOutput.h"


void user_main()
{

	// f�r die Ausgabe braucht man diese Sachen scheinabr -> nicht vergessen auf Run zu dr�cken!!
	/*
	int ww, hh;
	set_windowpos(0, 0, 600, 400);

	get_windowsize(&ww, &hh);
	set_drawarea(ww, hh);				// Setzen des Zeichenbereiches
	*/

	DisplayOutput Ausgabe;
	Ausgabe.SpielfeldErstellen(500,200);

	//clrscr();

	//_________________________________________________________________________________________

	srand(time(0)); // Startet den Pseudozufallszahlengenerator








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