// VeRWENDUNF map und string statt Cmap und Cstring
#pragma once

#include "stdafx.h"
//#include "K2mfcmap1.h"
#include <map>
#include <string>
#include <afxtempl.h> // CMap etc.

using namespace std;


/*
#include <iostream>
#include <fstream>
#include "GDE_3.h"
#include "MainFrm.h"
#include "GDE_3Doc.h"
#include "GDE_3View.h"
#include ".\gde_3.h"

#include "user.h"

#include <iostream>
#include <fstream>

*/




class DisplayOutput
{
public:
	struct Position {
		double x;
		double y;
	};
	map <string, int> schiffe; // map oder Cmap??

	//enum Schiffe{Schlachtschiff, Krezuzer, Zerstoerer, Uboot};

	// 
	void Initialisierung();

	// Funktion zum erstellen eines Spielfeldes
	void SpielfeldErstellen(int x, int y);

	// Funktion zeichnet ein Schiff in das Spielfeld
	void Schiff(int x, int y, string Schiffsname);
};

