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
//#include "Ship.h"
//#include "Global_Definitions.h" // hier k�nnen alle Structs etc rein, die wir quer durch unsre Dateien brauchen; da einbinden, wo sie gebraucht werden!
//#include "Player.h"
//#include "OneGame.h"
//#include "PlayerHistory.h"
#include "NGames.h"

// Includes f�r Strategien
#include <time.h>
//#include "Global_Definitions_Strategies.h"
//#include "AttackStrategy1.h"
//#include "AttackStrategy2.h"
//#include "AttackStrategy3.h"
//#include "AttackStrategy4.h"
//#include "DefenseStrategy1.h"


// Include fuer Ausgabe des Graphikfensters
#include "DisplayOutput.h"






void user_main()
{
	// Rahmen f�r den gesamten Programmablauf
	// Initialisierungen f�r die grafische Ausgabe, Aufruf von NGames(), die f�r Durchlauf von N (=Nutzereingabe) Spielen sorgt

	srand(static_cast<unsigned int>(time(nullptr)));	// PZG starten; Seed = time  -- nur ein einziges mal zu Programmstart

	//F�r die graphische Ausgabe
	DisplayOutput Graphics;			// �bergabe --> Ngames()
	int FarbeSchiffe = BLAU;
	Graphics.Grafikfenster(); // Erstellt das Grafikfenster mit Zeichenbereich, einmaligen Aufruf

	while (1)
	{
		NGames(Graphics);		// Durchf�hren von N Spielen  // �bergabe der DisplayOutput Klassen-Variable Graphics
		
		clrscr();				// clear screen
	}


	cout << "\n \n \n__________________________________________________________________\n\n\n";
}