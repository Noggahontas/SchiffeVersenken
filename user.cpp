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
#include "OneGame.h"
#include "PlayerHistory.h"
#include "NGames.h"

// Includes für Strategien
#include <time.h>
#include "Global_Definitions_Strategies.h"
#include "AttackStrategy1.h"
#include "AttackStrategy2.h"
#include "AttackStrategy3.h"
#include "AttackStrategy4.h"
#include "DefenseStrategy1.h"


// Include fuer Ausgabe des Graphikfensters
#include "DisplayOutput.h"






void user_main()
{
	srand(static_cast<unsigned int>(time(nullptr)));	// PZG starten; Seed = time  -- nur ein einziges mal zu Programmstart

	//Für die graphische Ausgabe
	DisplayOutput Graphics;			// Übergabe --> Ngames()
	Graphics.Kaestchengroesse = 20;
	int FarbeSchiffe = BLAU;
	Position Bildschirm;										// Position des Grafikfensters auf dem Bildschirm
	Bildschirm.x = 500;
	Bildschirm.y = 250;
	int Startpunkt = 50;
	Graphics.Grafikfenster(Bildschirm, Startpunkt);	// Erstellen Grafikfenster: Test für einmaligen Aufruf 

	while (1)
	{
		NGames(Graphics);		// Übergabe der DisplayOutput Klassen-Variable Graphics
		
		clrscr();				// clear screen
	}


	cout << "\n \n \n__________________________________________________________________\n\n\n";
}