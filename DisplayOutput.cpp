// WICHTIG: Ausgabe der Zahlenreihe nur provisorisch und sehr unhuebsch da sprintf nicht funktioniert hat
 // char* [xy] ist das ein pointer wennn ja: freigabe wie und wann?
// Zeichenketten in cpp immer pointer?

#include "stdafx.h"
#include "DisplayOutput.h"

#include "stdafx.h"
#include "console\console.h"
#include "graphics\graphicfunctions.h"

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <afxtempl.h> // CMap etc.
#include <string>

// Farbe Schwarz in der RGB - Darstellung
#define SCHWARZ 0
#define WEISS RGB(255,255,255)
void DisplayOutput::Initialisierung()
{
	// Name des Schiffes (key) und Laenge des Schiffes (value)
	schiffe["Schlachtschiff"] = 5;
	schiffe["Kreuzer"] = 4;
	schiffe["Zerstoerer"] = 3;
	schiffe["UBoot"] = 2;
}
void DisplayOutput::SpielfeldErstellen(int x, int y) // Spielfeld an der Stelle(x,y) auf dem Bildschirm
{
	// Graphikfenster am Punkt (x,y)

	int const N = 4;
	int const start = 50;
	int const delta = 20;//10; // Breite eines "Spielkaestchens" auf dem Spielfeld
	int i,j,k,m;
	double dx, dy;
	double differenz, schrittweite;;
	double faktor = (start / 10 );

	// Definition der verschiedenen Textfelder im Spielfeld
	// alle Texte sollen dieselbe Schriftgroesse haben
	int textgroesse = 12;

	// Ueberschrift
	Position Textfeld;
	Textfeld.x = start / 2; 
	Textfeld.y = start / 2;

	// Buchstabenreihe
	Position Buchstaben;
	Buchstaben.x = start + faktor;
	Buchstaben.y = start - (faktor*2);

	char *BuchstabenArray[10];
	BuchstabenArray[0] = "A"; BuchstabenArray[1] = "B"; BuchstabenArray[2] = "C"; BuchstabenArray[3] = "D"; BuchstabenArray[4] = "E";
	BuchstabenArray[5] = "F"; BuchstabenArray[6] = "G"; BuchstabenArray[7] = "H"; BuchstabenArray[8] = "I"; BuchstabenArray[9] = "J";

	// Zahlenreihe
	Position Zahlen;
	Zahlen.x = start - faktor;
	Zahlen.y = start + (faktor*2);

	// PROVISORISCHE LOESUNG Zahlenreihe
	char* ZahlenArray[10];
	ZahlenArray[0] = "1"; ZahlenArray[1] = "2"; ZahlenArray[2] = "3"; ZahlenArray[3] = "4"; ZahlenArray[4] = "5";
	ZahlenArray[5] = "6"; ZahlenArray[6] = "7"; ZahlenArray[7] = "8"; ZahlenArray[8] = "9"; ZahlenArray[9] = "10";

	// Hoehe und Breite des Graphikfensters
	int breite = (10*delta) + (2*start); 
	int hoehe = (10*delta) + (2*start);
	
	// Erstellen des Graphikfensters
	set_windowpos(x, y, breite, hoehe); 

	// Speichern der 4 Eckpunkte des Spielfeldes
	Position Spielfeld[N]; 
   	Spielfeld[0].x = start; Spielfeld[0].y = start;								// linke Ecke oben
	Spielfeld[1].x = start + (10*delta); Spielfeld[1].y = start;				// rechte Ecke oben
	Spielfeld[2].x = start + (10*delta); Spielfeld[2].y = start + (10*delta);	// rechte Ecke unten
	Spielfeld[3].x = start; Spielfeld[3].y = start + (10*delta);				// linke Ecke unten

	
	// Zeichnen des Spielfeldes
	for (i = 0; i < 11; i++)
	{
		differenz = i*delta;

		// senkrechte Linien
		line((Spielfeld[0].x + differenz), Spielfeld[0].y, (Spielfeld[3].x + differenz), Spielfeld[3].y, WEISS);
		// waagrechte Linien
		line(Spielfeld[0].x, (Spielfeld[0].y + differenz), Spielfeld[1].x, (Spielfeld[1].y + differenz), WEISS);

		// Ausgabe der Beschriftung bestehend aus Zahlen(senkrecht) und Buchstaben (waagrecht)
		if (i != 10)
		{
			dx = Buchstaben.x + differenz;
			dy = Buchstaben.y + differenz + delta;
			text(dx, Buchstaben.y, textgroesse, WEISS, BuchstabenArray[i]);
			text(Buchstaben.x - delta, dy, textgroesse, WEISS, ZahlenArray[i]);
		}
	}

	char *ausgabe = "fancy Schiffe versenken von Norrer, Dommev & Vranzi";
	text(Textfeld.x, Textfeld.y, textgroesse, WEISS, ausgabe);	
	
};

void DisplayOutput::Schiff(int x, int y, string Schiffsname)
{
	int schiffslaenge;
	if (Schiffsname.compare("Schlachtschiff") == 0)
	{
		schiffslaenge = schiffe["Schlachtschiff"];
	}
}

