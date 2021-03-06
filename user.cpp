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

// Includes f�r Spielablauf
#include "NGames.h"

// Includes f�r Strategien
#include <time.h>



// Include fuer Ausgabe des Graphikfensters
#include "DisplayOutput.h"





/*
Funktion: Rahmen f�r den gesamten Programmablauf
*/
void user_main()
{
	// Rahmen f�r den gesamten Programmablauf
	// Initialisierungen f�r die grafische Ausgabe, Aufruf von NGames(), die f�r Durchlauf von N (=Nutzereingabe) Spielen sorgt

	srand(static_cast<unsigned int>(time(nullptr)));	// PZG starten; Seed = time  -- nur ein einziges mal zu Programmstart

	//F�r die graphische Ausgabe
	DisplayOutput Graphics;								// �bergabe --> Ngames()
	Graphics.Grafikfenster();							// Erstellen Grafikfenster


	while (1)
	{
		NGames(Graphics);		// Durchf�hren von N Spielen  // �bergabe der DisplayOutput Klassen-Variable Graphics
		
		clrscr();				// clear screen
	}


	cout << "\n \n \n__________________________________________________________________\n\n\n";
}