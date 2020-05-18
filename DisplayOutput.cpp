// WICHTIG: Ausgabe der Zahlenreihe nur provisorisch und sehr unhuebsch da sprintf nicht funktioniert hat

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

Position DisplayOutput::SpielfeldErstellen(Position Bildschirm, int Kaestchengroesse, int index) // Spielfeld an der Stelle(x,y) auf dem Bildschirm
{
	int const N = 4;
	int const start = 50;
	int const delta = Kaestchengroesse;		//10; // Breite eines "Spielkaestchens" auf dem Spielfeld

	int i;
	int dx, dy;
	int differenz, schrittweite;;
	int faktor = (start / 10 );
	int abstand = (index - 1) * 300;

	// Definition der verschiedenen Textfelder im Spielfeld
	// alle Texte sollen dieselbe Schriftgroesse haben
	int textgroesse = Kaestchengroesse/2 ;

	// Ueberschrift
	Position Textfeld;
	Textfeld.x = start / 2 + (Kaestchengroesse*2) + abstand;
	Textfeld.y = start / 2;

	// Buchstabenreihe
	Position Buchstaben;
	Buchstaben.x = start + faktor + abstand;
	Buchstaben.y = start - (faktor*2);

	char *BuchstabenArray[10];
	BuchstabenArray[0] = "A"; BuchstabenArray[1] = "B"; BuchstabenArray[2] = "C"; BuchstabenArray[3] = "D"; BuchstabenArray[4] = "E";
	BuchstabenArray[5] = "F"; BuchstabenArray[6] = "G"; BuchstabenArray[7] = "H"; BuchstabenArray[8] = "I"; BuchstabenArray[9] = "J";

	// Zahlenreihe
	Position Zahlen;
	Zahlen.x = start - faktor + abstand;
	Zahlen.y = start + (faktor*2);

	// PROVISORISCHE LOESUNG Zahlenreihe
	char* ZahlenArray[10];
	ZahlenArray[0] = "1"; ZahlenArray[1] = "2"; ZahlenArray[2] = "3"; ZahlenArray[3] = "4"; ZahlenArray[4] = "5";
	ZahlenArray[5] = "6"; ZahlenArray[6] = "7"; ZahlenArray[7] = "8"; ZahlenArray[8] = "9"; ZahlenArray[9] = "10";


	// Hoehe und Breite des Graphikfensters
	int breite = (10 * start);
	int hoehe = (10 * delta) + (2 * start);

	// Erstellen des Graphikfensters
	set_windowpos(Bildschirm.x, Bildschirm.y, breite, hoehe); 


	// Speichern der 4 Eckpunkte des Spielfeldes
	Position Spielfeld[N]; 
   	Spielfeld[0].x = start + abstand; Spielfeld[0].y = start;			// linke Ecke oben
	Spielfeld[1].x = start + (10*delta) + abstand; Spielfeld[1].y = start;				// rechte Ecke oben
	Spielfeld[2].x = start + (10*delta) + abstand; Spielfeld[2].y = start + (10*delta);	// rechte Ecke unten
	Spielfeld[3].x = start+ abstand; Spielfeld[3].y = start + (10*delta);				// linke Ecke unten

	
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
	char* ausgabe = "xx";
	//char *ausgabe = "fancy Schiffe versenken von Norrer, Dommev & Vranzi";
	if (index == 1)
	{
		ausgabe = "Spieler 1";
	}
	else
	{
		ausgabe = "Spieler 2";
	}
	text(Textfeld.x, Textfeld.y, textgroesse, WEISS, ausgabe);	
	
	// Rückgabe der linken oberen Ecke 
	Position linkeEckeOben = Spielfeld[0];
	return linkeEckeOben;
};

// falls zur Kontrolle des Spielablaufes ein Übersichtsfenster genutzt werden muss, indem beide Schiffe dargestellt werden sollen
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

void DisplayOutput::DarstellungSchiff(Position EckpunktSpielfeld, Position Schiffsposition, int Kaestchengroesse, int Farbe, int Schiffslaenge, Direction AusrichtungSchiff)
{
	int x1, x2, y1, y2 = 0;
	if (AusrichtungSchiff == Direction::Right) // Schiffsausrichtung auf dem Spielfeld: waagrecht
	{
		// Schiffsposition muss mit Kaestchengroesse skaliert werden
		x1 = EckpunktSpielfeld.x + (Schiffsposition.x * Kaestchengroesse) + 1;
		y1 = EckpunktSpielfeld.y + (Schiffsposition.y * Kaestchengroesse) + 1 ;
		x2 = x1 + (Schiffslaenge * Kaestchengroesse) - 1;
		y2 = y1 + Kaestchengroesse - 1;
	} 
	else if (AusrichtungSchiff == Direction::Down) // Schiffsausrichtung auf dem Spielfeld: senkrecht
	{
		// Schiffsposition muss mit Kaestchengroesse skaliert werden
		x1 = EckpunktSpielfeld.x + (Schiffsposition.x * Kaestchengroesse) + 1;
		y1 = EckpunktSpielfeld.y + (Schiffsposition.y * Kaestchengroesse) + 1;
		x2 = x1 + Kaestchengroesse - 1;
		y2 = y1 + (Schiffslaenge * Kaestchengroesse)-1;
	}
	rectangle(x1,y1, x2, y2, Farbe, Farbe);


}

void DisplayOutput::getroffenesFeld(Position EckpunktSpielfeld, Position Treffer, int Kaestchengroesse, int Farbe)
{
	int x1, x2, xx1, xx2, y1, y2, yy1, yy2 = 0;
	// Skalierung des Ausgangspunktes an das Spielfeld
	x1 = EckpunktSpielfeld.x + Treffer.x*Kaestchengroesse; 
	y1 = EckpunktSpielfeld.y + Treffer.y*Kaestchengroesse;

	x2 = x1 + Kaestchengroesse; 
	y2 = y1 + Kaestchengroesse;

	xx1 = x1 + Kaestchengroesse; yy1 = y1;
	xx2 = x1; yy2 = y1 + Kaestchengroesse;

	// Zeichenen eines roten Kreuzes
	line(x1, y1, x2, y2, Farbe);
	line(xx1, yy1, xx2, yy2, Farbe);
}

void DisplayOutput::Ausgabe(int Kaestchengroesse, Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2)
{
	int i;										// Zählvariable für die for- Schleife
	Position Ecke_1, Ecke_2;					// Position der linken oberen Ecke der Spielfelder, Rückgabewert beim Erstellen des Spielfeldes
												// Ecke_1 : Ecke des Spielfeldes des 1. Spielers
												// Ecke_2 : Ecke des Spielfeldes des 2. Spielers
	Position Schuss1_1, Schuss2_1, Schuss3_1;	// letzten 3 Schuesse des Gegners (Spieler 1)
	Position Schuss1_2, Schuss2_2, Schuss3_2;	// letzten 3 Schuesse des Gegners (Spieler 2)

	Ship Schiff_1, Schiff_2;					// Schiff_1 : Schiff Spieler 1
												// Schiff_2 : Schiff Spieler 2
	Position Schiffsposition_1;					// aktuelle Koordinaten des Schiffes auf dem Spielfeld (Spieler 1)
	Position Schiffsposition_2;					// aktuelle Koordinaten des Schiffes auf dem Spielfeld (Spieler 2)

	Direction Ausrichtung_1;					// Ausrichtung des Schiffes auf dem Spielfeld (Spieler 1)
	Direction Ausrichtung_2;					// Ausrichtung des Schiffes auf dem Spielfeld (Spieler 2)

	int Schiffslaenge_1;						// Schiffslaenge (Spieler 1)
	int Schiffslaenge_2;						// Schiffslaenge (Spieler 2)
	int faktor = 0;

	Position Bildschirm;						// Position des Grafikfensters auf dem Bildschirm
	Bildschirm.x = 500;
	Bildschirm.y = 250;

	// Spielfeld zeichnen
	Ecke_1 = SpielfeldErstellen(Bildschirm, Kaestchengroesse,1); // Spielfeld fuer Spieler 1
	Ecke_2 = SpielfeldErstellen(Bildschirm, Kaestchengroesse, 2); // Spielfeld fuer Spieler 2

	// Schiffe zeichnen
	for (i = 0; i < 10; i++)
	{
		// Ausgabe Spieler 1
		Schiff_1 = Spieler1.Ships[i];				// aktuelles Schiff
		Schiff_2 = Spieler2.Ships[i];

		Schiffsposition_1 = Schiff_1.StartPos;		// Koordinaten des aktuellen Schiffes auf dem Spielfeld
		Schiffsposition_2 = Schiff_2.StartPos;

		Ausrichtung_1 = Schiff_1.Orientation;		// Ausrichtung des aktuellen Schiffes auf dem Spielfeld
		Ausrichtung_2 = Schiff_2.Orientation;

		Schiffslaenge_1 = Schiff_1.Length;
		Schiffslaenge_2 = Schiff_2.Length;

		// Schuesse
		// Spieler 1
		Schuss1_1 = Spieler1.Last3ShotsOfOpponent[0];	// letzter Schuss des Gegners
		Schuss2_1 = Spieler1.Last3ShotsOfOpponent[1];
		Schuss3_1 = Spieler1.Last3ShotsOfOpponent[2];

		// Spieler 2
		Schuss1_2 = Spieler2.Last3ShotsOfOpponent[0];	// letzter Schuss des Gegners
		Schuss2_2 = Spieler2.Last3ShotsOfOpponent[1];
		Schuss3_2 = Spieler2.Last3ShotsOfOpponent[2];

		// Spieler 1
		DarstellungSchiff(Ecke_1, Schiffsposition_1, Kaestchengroesse, FarbeSpieler1, Schiffslaenge_1, Ausrichtung_1);
		getroffenesFeld(Ecke_1, Schuss1_1, Kaestchengroesse, ROT);		  // letzter Schuss des Gegeners wird in Rot angezeigt
		getroffenesFeld(Ecke_1, Schuss2_1, Kaestchengroesse, WEISS);
		getroffenesFeld(Ecke_1, Schuss3_1, Kaestchengroesse, WEISS);

		// Spieler 2
		DarstellungSchiff(Ecke_2, Schiffsposition_2, Kaestchengroesse, FarbeSpieler2, Schiffslaenge_2, Ausrichtung_2);
		getroffenesFeld(Ecke_2, Schuss1_2, Kaestchengroesse, ROT);		  // letzter Schuss des Gegeners wird in Rot angezeigt
		getroffenesFeld(Ecke_2, Schuss2_2, Kaestchengroesse, WEISS);
		getroffenesFeld(Ecke_2, Schuss3_2, Kaestchengroesse, WEISS);

	}	
}