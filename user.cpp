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

// Includes für Spielablauf
#include "NGames.h"

// Includes für Strategien
#include <time.h>



// Include fuer Ausgabe des Graphikfensters
#include "DisplayOutput.h"





/*
Funktion: Rahmen für den gesamten Programmablauf
*/
void user_main()
{
	// Rahmen für den gesamten Programmablauf
	// Initialisierungen für die grafische Ausgabe, Aufruf von NGames(), die für Durchlauf von N (=Nutzereingabe) Spielen sorgt

	srand(static_cast<unsigned int>(time(nullptr)));	// PZG starten; Seed = time  -- nur ein einziges mal zu Programmstart

	//Für die graphische Ausgabe
	DisplayOutput Graphics;								// Übergabe --> Ngames()
	Graphics.Grafikfenster();							// Erstellen Grafikfenster


	while (1)
	{
		NGames(Graphics);		// Durchführen von N Spielen  // Übergabe der DisplayOutput Klassen-Variable Graphics
		
		clrscr();				// clear screen
	}


	cout << "\n \n \n__________________________________________________________________\n\n\n";
}