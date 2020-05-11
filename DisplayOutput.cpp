// WICHTIG: Ausgabe der Zahlenreihe nur provisorisch und sehr unhuebsch da sprintf nicht funktioniert hat
 // char* [xy] ist das ein pointer wennn ja: freigabe wie und wann?
// Zeichenketten in cpp immer pointer?

#include "stdafx.h"
#include "DisplayOutput.h"

#include "stdafx.h"
#include "console\console.h"
#include "graphics\graphicfunctions.h"

#include <iostream>
#include <stdio.h>
#include <afxtempl.h> // CMap etc.
#include <string>

//#include "Global_Definitions.h";


Position DisplayOutput::SpielfeldErstellen(int x, int y, int Kaestchengroesse) // Spielfeld an der Stelle(x,y) auf dem Bildschirm
{
	// Graphikfenster am Punkt (x,y)

	int const N = 4;
	int const start = 50;
	int const delta = Kaestchengroesse;		//10; // Breite eines "Spielkaestchens" auf dem Spielfeld
	
	int i,j,k,m;
	double dx, dy;
	double differenz, schrittweite;;
	double faktor = (start / 10 );

	// Definition der verschiedenen Textfelder im Spielfeld
	// alle Texte sollen dieselbe Schriftgroesse haben
	int textgroesse = Kaestchengroesse/2 ;

	// Ueberschrift
	Position Textfeld;
	Textfeld.x = start / 2 + (Kaestchengroesse*2); 
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
	int breite = (10 * start);
	int hoehe = (10 * delta) + (2 * start);

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
	
	// Rückgabe der linken oberen Ecke 
	Position linkeEckeOben = Spielfeld[0];
	return linkeEckeOben;
};

void DisplayOutput::Legende(Position EckpunktSpielfeld, int Kaestchengroesse, int FarbeSpieler1, int FarbeSpieler2)
{
	Position Legende;
	Legende.x = 2 * EckpunktSpielfeld.x + (10 * Kaestchengroesse);
	Legende.y = EckpunktSpielfeld.y;

	Position Farbkasten1, Farbkasten2;
	Farbkasten1.x = Legende.x + 5 * Kaestchengroesse;
	Farbkasten1.y = Legende.y;

	Farbkasten2.x = Farbkasten1.x;
	Farbkasten2.y = Legende.y + Kaestchengroesse;

	int x1, x2, y1, y2;

	// Kasten 1
	x1 = Farbkasten1.x;
	y1 = Farbkasten1.y;
	x2 = x1 + 3 * Kaestchengroesse;
	y2 = y1 + Kaestchengroesse - 2;

	text(Legende.x, Legende.y, 15, WEISS, SCHWARZ, "Farbe Spieler 2:");
	rectangle(x1, y1, x2, y2, WEISS, FarbeSpieler1);

	// Kasten 2

	x1 = Farbkasten2.x;
	y1 = Farbkasten2.y;
	x2 = x1 + 3 * Kaestchengroesse;
	y2 = y1 + Kaestchengroesse - 2;

	text(Legende.x, Legende.y + Kaestchengroesse, 15, WEISS, SCHWARZ, "Farbe Spieler 1:");
	rectangle(x1, y1, x2, y2, WEISS, FarbeSpieler2);
}

void DisplayOutput::Schiff(Position EckpunktSpielfeld, Schiffsposition LokalisierungSchiff, int Kaestchengroesse, int Schiffslaenge, string Spieler)
{
	int x1, x2, y1, y2, farbe;
	char AusrichtungSchiff = LokalisierungSchiff.ausrichtung;


	if (AusrichtungSchiff == 'w') // Schiff ist waagrecht zu zeichnen
	{
		// Schiffsposition muss mit Kaestchengroesse skaliert werden
		x1 = EckpunktSpielfeld.x + (LokalisierungSchiff.linkeEckeOben.x * Kaestchengroesse);
		y1 = EckpunktSpielfeld.y + (LokalisierungSchiff.linkeEckeOben.y * Kaestchengroesse);
		x2 = x1 + (Schiffslaenge * Kaestchengroesse);
		y2 = y1 + Kaestchengroesse;
	} 
	else if (AusrichtungSchiff == 's') // Schiff ist senkrecht zu zeichen
	{
		// Schiffsposition muss mit Kaestchengroesse skaliert werden
		x1 = EckpunktSpielfeld.x + (LokalisierungSchiff.linkeEckeOben.x * Kaestchengroesse);
		y1 = EckpunktSpielfeld.y + (LokalisierungSchiff.linkeEckeOben.y * Kaestchengroesse);
		x2 = x1 + Kaestchengroesse;
		y2 = y1 + (Schiffslaenge * Kaestchengroesse);
	}
	// Farben 
	if (Spieler.compare("Spieler 1") == 0)
	{
		// Spieler 1 : Blau
		farbe = BLAU;
	} 
	else if(Spieler.compare("Spieler 2") == 0)
	{
		// Spieler 2 : Gruen
		farbe = GRUEN;
	}
	else 
	{
		farbe = WEISS;
	}
	rectangle(x1,y1, x2, y2, farbe, farbe);


}
