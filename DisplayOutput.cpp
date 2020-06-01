// WICHTIG: Ausgabe der Zahlenreihe nur provisorisch und sehr unhuebsch da sprintf nicht funktioniert hat

#include "stdafx.h"
#include "DisplayOutput.h"

#include "stdafx.h"
#include "console\console.h"
#include "graphics\graphicfunctions.h"

#include <iostream>
#include <stdio.h>

void DisplayOutput::Grafikfenster(Position Bildschirm,int Startpunkt, int Kaestchengroesse)
{
	// Hoehe und Breite des Graphikfensters
	int breite = (10 * Startpunkt) + 500;
	int hoehe = (15 * Kaestchengroesse) + (2 * Startpunkt);

	// Erstellen des Graphikfensters

	set_windowpos(Bildschirm.x, Bildschirm.y, breite, hoehe);
	set_drawarea(breite, hoehe); updatescr();
}

Position DisplayOutput::SpielfeldErstellen(Position Bildschirm, int Kaestchengroesse, int index, int Startpunkt) // Spielfeld an der Stelle(x,y) auf dem Bildschirm
{
	int const N = 4;
	int const delta = Kaestchengroesse;		//10; // Breite eines "Spielkaestchens" auf dem Spielfeld

	int i;
	int dx, dy;
	int differenz;
	int faktor = (Startpunkt / 10);
	int abstand = (index - 1) * 300;

	// Definition der verschiedenen Textfelder im Spielfeld
	// alle Texte sollen dieselbe Schriftgroesse haben
	int textgroesse = Kaestchengroesse/2 ;

	// Ueberschrift
	Position Textfeld;
	Textfeld.x = Startpunkt / 2 + (Kaestchengroesse*2) + abstand;
	Textfeld.y = Startpunkt / 3;

	// Buchstabenreihe
	Position Buchstaben;
	Buchstaben.x = Startpunkt + faktor + abstand;
	Buchstaben.y = Startpunkt - (faktor*2);

	char *BuchstabenArray[10];
	BuchstabenArray[0] = "A"; BuchstabenArray[1] = "B"; BuchstabenArray[2] = "C"; BuchstabenArray[3] = "D"; BuchstabenArray[4] = "E";
	BuchstabenArray[5] = "F"; BuchstabenArray[6] = "G"; BuchstabenArray[7] = "H"; BuchstabenArray[8] = "I"; BuchstabenArray[9] = "J";

	// Zahlenreihe
	Position Zahlen;
	Zahlen.x = Startpunkt - faktor + abstand;
	Zahlen.y = Startpunkt + (faktor*2);

	// PROVISORISCHE LOESUNG Zahlenreihe
	char* ZahlenArray[10];
	ZahlenArray[0] = "1"; ZahlenArray[1] = "2"; ZahlenArray[2] = "3"; ZahlenArray[3] = "4"; ZahlenArray[4] = "5";
	ZahlenArray[5] = "6"; ZahlenArray[6] = "7"; ZahlenArray[7] = "8"; ZahlenArray[8] = "9"; ZahlenArray[9] = "10";


	// Speichern der 4 Eckpunkte des Spielfeldes
	Position Spielfeld[N]; 
   	Spielfeld[0].x = Startpunkt + abstand; Spielfeld[0].y = Startpunkt;								// linke Ecke oben
	Spielfeld[1].x = Startpunkt + (10*delta) + abstand; Spielfeld[1].y = Startpunkt;				// rechte Ecke oben
	Spielfeld[2].x = Startpunkt + (10*delta) + abstand; Spielfeld[2].y = Startpunkt + (10*delta);	// rechte Ecke unten
	Spielfeld[3].x = Startpunkt+ abstand; Spielfeld[3].y = Startpunkt + (10*delta);					// linke Ecke unten

	Position Ursprung;
	Ursprung.x = 0;
	Ursprung.y = 0;
	getroffenesFeld(Ursprung, Ursprung, Kaestchengroesse, SCHWARZ); updatescr();// haelt Grafikfenster offen

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
	/*
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
	text(Textfeld.x, Textfeld.y, textgroesse+10, WEISS, ausgabe);	
	*/

	// Rückgabe der linken oberen Ecke 
	return Spielfeld[0];
};

Position DisplayOutput::Legende(Position EckpunktSpielfeld, int Kaestchengroesse, int Startpunkt, int index, Player Spieler)

{
	// Positionierung des Textes unter dem zugehörigen Spielfeld
	Position Legende[2] = {};
	Legende[0].x = EckpunktSpielfeld.x;			// linkes oberes Eck der Textbox
	Legende[0].y = 14 * Kaestchengroesse;

	Legende[1].x = Legende[0].x + Kaestchengroesse * 10;
	Legende[1].y = Legende[0].y + Kaestchengroesse * 5;


	// Informationen zur Angriffs- und Verteidigungsstrategie des Spielers
	int Angriffsstrategie = Spieler.AttackStrategy;
	int Verteidigungsstrategie = Spieler.DefenseStrategy;

	// Platzhalter
	int verfehlteSchuesse = Spieler.MissedShotsOfOpponent;
	int getroffeneSchuesse = Spieler.HitShotsOfOpponent;
	int versenkteSchiffe = Spieler.SunkShipsByOpponent;

	// Informationstext
	char InfoSpieler[500];
		snprintf(InfoSpieler, sizeof(InfoSpieler), 
			"Spieler Nr. % d \n Verteidigungsstrategie Nr. %d \n Angriffsstartegie Nr. %d \n verfehlte Schüsse : %d \n getroffene Schüsse : %d \n versenkte Schiffe : %d"
			,index, Angriffsstrategie, Verteidigungsstrategie, verfehlteSchuesse, getroffeneSchuesse, versenkteSchiffe);

	textbox(Legende[0].x, Legende[0].y, Legende[1].x, Legende[1].y, 15, WEISS, SCHWARZ, SCHWARZ, CENTER_ALIGN,InfoSpieler);

	return Legende[0];
}

void DisplayOutput::DarstellungSchiff(Position EckpunktSpielfeld,Ship Schiff, int Kaestchengroesse, int Farbe)
{
	int Schiffslaenge = Schiff.Length;						// Schiffslaenge des darzustellenden Schiff
	Direction AusrichtungSchiff = Schiff.Orientation;		// Ausrichtung des Schiffs auf dem Spielfeld
	Position Schiffsposition = Schiff.StartPos;				// Position des darzustellenden Schifs auf dem Spielfeld

	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	// Ueberpruefung, ob Schiff bereits getroffen wurde
	vector<bool> StatusSchiff = Schiff.Status;
	int Statusabfrage;										// zu überprüfende Stelle des Schiffes
	Position getroffenesFeld[2] = {};
	
	// Eckpunkt des Schiffes auf dem Spielfeld (Skalierung)
	
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
	rectangle(x1, y1, x2, y2, Farbe, Farbe); updatescr();
	
	for (int j = 0; j < Schiffslaenge; j++)
	{
		// Überprüfung ob Schiff an dieser Stelle bereits getroffen wurde [0 1 ... Schifflänge -1]
		Statusabfrage = StatusSchiff.at(j);

		if (Statusabfrage == 1)				// Stelle wurde bereits erfolgreich getroffen			
		{
			// Lokalisierung des Treffers abhaengig von der Ausrichtung des Schiffes
			if (AusrichtungSchiff == Direction::Right) // Schiffsausrichtung auf dem Spielfeld: waagrecht
			{
				getroffenesFeld[0].x = x1 + (j * Kaestchengroesse);	// in x - Richtung, falls Schiff waagrecht
				getroffenesFeld[0].y = y1;
				getroffenesFeld[1].x = x1 + Kaestchengroesse - 1;
				getroffenesFeld[1].y = y1 + Kaestchengroesse - 1;
			}
			else if (AusrichtungSchiff == Direction::Down) // Schiffsausrichtung auf dem Spielfeld: senkrecht
			{
				getroffenesFeld[0].x = x1;
				getroffenesFeld[0].y = y1 + (j* Kaestchengroesse);

				getroffenesFeld[1].x = x1 + Kaestchengroesse - 1;
				getroffenesFeld[1].y = y1 + 2*Kaestchengroesse - 1;
			}
			rectangle(getroffenesFeld[0].x, getroffenesFeld[0].y, getroffenesFeld[1].x, getroffenesFeld[1].y, ROT, ROT); updatescr();// Zeichnen eines roten Feldes als Treffer
			
			getroffenesFeld[0] = {}; getroffenesFeld[1] = {};
		}

	}
}

void DisplayOutput::getroffenesFeld(Position EckpunktSpielfeld, Position Treffer, int Kaestchengroesse, int Farbe)
{
	int x1 = 0, x2 = 0, xx1 = 0, xx2 = 0, y1 = 0, y2 = 0, yy1 = 0, yy2 = 0;
	// Skalierung des Ausgangspunktes an das Spielfeld
	x1 = EckpunktSpielfeld.x + Treffer.x*Kaestchengroesse; 
	y1 = EckpunktSpielfeld.y + Treffer.y*Kaestchengroesse;

	x2 = x1 + Kaestchengroesse; 
	y2 = y1 + Kaestchengroesse;

	xx1 = x1 + Kaestchengroesse; yy1 = y1;
	xx2 = x1; yy2 = y1 + Kaestchengroesse;

	// Zeichenen eines Kreuzes
	line(x1, y1, x2, y2, Farbe);
	line(xx1, yy1, xx2, yy2, Farbe);
}

bool DisplayOutput::Beschleunigung(int Startpunkt, int Kaestchengroesse)
{

	Position Box[2] = {};
	Box[0].x = 2*Startpunkt + 25 *Kaestchengroesse; // in Relation zu der Spielfeldanordnung
	Box[0].y = Startpunkt;

	Box[1].x = Box[0].x + 4*Kaestchengroesse;
	Box[1].y = Box[0].y + Kaestchengroesse;

	int textgroesse = Kaestchengroesse;

	textbox(Box[0].x, Box[0].y, Box[1].x, Box[1].y, textgroesse, WEISS, WEISS, SCHWARZ, CENTER_ALIGN, "schneller");

	bool beschleunigen = false; // Annahme: Mouse nicht gedrückt

	int klick = checkmouse();
	if (klick == 0)
	{
		beschleunigen = false;
	}
	else if (klick == 1)
	{
		beschleunigen = true;
	}

	return beschleunigen;
}

void DisplayOutput::Ausgabe(int Kaestchengroesse, Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2)
{
	int i = 0;										// Zählvariable für die for- Schleife
	// Position der linken oberen Ecke der Spielfelder, Rückgabewert beim Erstellen des Spielfeldes
	Position Ecke_1;						// Ecke_1 : Ecke des Spielfeldes des 1. Spielers
	Position Ecke_2;						// Ecke_2 : Ecke des Spielfeldes des 2. Spielers

	Position Schuss1_1, Schuss2_1, Schuss3_1;	// letzten 3 Schuesse des Gegners (Spieler 1)
	Position Schuss1_2, Schuss2_2, Schuss3_2;	// letzten 3 Schuesse des Gegners (Spieler 2)

	Ship Schiff_1, Schiff_2;							// Schiff_1 : Schiff Spieler 1, Schiff_2 : Schiff Spieler 2

	Position Bildschirm;						// Position des Grafikfensters auf dem Bildschirm
	Bildschirm.x = 500;
	Bildschirm.y = 250;
	int Startpunkt = 50;

	// Hoehe und Breite des Graphikfensters
	int breite = (10 * Startpunkt) + 500;
	int hoehe = (15 * Kaestchengroesse) + (2 * Startpunkt);

	/*
	// Erstellen des Graphikfensters

	set_windowpos(Bildschirm.x, Bildschirm.y, breite, hoehe);
	set_drawarea(breite, hoehe); updatescr();
	*/
	// Ueberlegung, den Zeichenbereich aufzuhalten
	Position Ursprung;
	Ursprung.x = 0;
	Ursprung.y = 0;
	Position Platzhalter;
	Platzhalter.x = Ursprung.x + Kaestchengroesse;
	Platzhalter.y = Ursprung.y + Kaestchengroesse;
	
	// Schwärzen der Fläche, damit alte Treffer nicht merh angezeigt werden
	rectangle(Startpunkt, Startpunkt, Startpunkt + breite, Startpunkt + hoehe, SCHWARZ, SCHWARZ); updatescr();

	// Spielfeld zeichnen
	Ecke_1 = SpielfeldErstellen(Bildschirm, Kaestchengroesse, 1, Startpunkt); updatescr(); // Spielfeld fuer Spieler 1 
	Ecke_2 = SpielfeldErstellen(Bildschirm, Kaestchengroesse, 2, Startpunkt); updatescr(); // Spielfeld fuer Spieler 2

	// Ausgabe Legende
	Position Legende2 = {}, Legende1 = {};
	Legende1 = Legende(Ecke_1, Kaestchengroesse, Startpunkt, 1, Spieler1);
	Legende2 = Legende(Ecke_2, Kaestchengroesse, Startpunkt, 2, Spieler2);

	Beschleunigung(Startpunkt, Kaestchengroesse); updatescr();

	// Schuesse
	// Spieler 1
	Schuss1_1 = Spieler1.Last3ShotsOfOpponent[0];	// letzter Schuss des Gegners
	Schuss2_1 = Spieler1.Last3ShotsOfOpponent[1];
	Schuss3_1 = Spieler1.Last3ShotsOfOpponent[2];

	// Spieler 2
	Schuss1_2 = Spieler2.Last3ShotsOfOpponent[0];	// letzter Schuss des Gegners
	Schuss2_2 = Spieler2.Last3ShotsOfOpponent[1];
	Schuss3_2 = Spieler2.Last3ShotsOfOpponent[2];

	// Schiffe und Treffer zeichnen
	for (i = 0; i < 10; i++)
	{
		// Ausgabe Spieler 1
		Schiff_1 = Spieler1.Ships[i];				// aktuelles Schiff
		Schiff_2 = Spieler2.Ships[i];

		// Lebendkontrolle
		int Schiff_1_Kontrolle = Schiff_1.Sunk;
		int Schiff_2_Kontrolle = Schiff_2.Sunk;

		// zuerst die Schiffe und dann die getroffenen Felder zeichnen sonst werde die Kreuze übermalt

		// Spieler 1
		if (Schiff_1_Kontrolle != 1) // gesunkene Schiffe sollen nicht gezeichnet werden
		{
			DarstellungSchiff(Ecke_1, Schiff_1, Kaestchengroesse, FarbeSpieler1);
		}

		if (Schuss1_1.x >= 0 && Schuss1_1.y >= 0) // Iniialisierung soll nicht ausgegeben werden
		{
			getroffenesFeld(Ecke_1, Schuss1_1, Kaestchengroesse, ROT);		updatescr();	// letzter Schuss des Gegeners wird in Rot angezeigt
		}
		if (Schuss2_1.x >= 0 && Schuss2_1.y >= 0)
		{
			getroffenesFeld(Ecke_1, Schuss2_1, Kaestchengroesse, WEISS);	updatescr();
		}
		if (Schuss3_1.x >= 0 && Schuss3_1.y >= 0)
		{
			getroffenesFeld(Ecke_1, Schuss3_1, Kaestchengroesse, WEISS);	updatescr();
		}

		// Spieler 2
		if (Schiff_2_Kontrolle != 1) // gesunkene Schiffe sollen nicht gezeichnet werden
		{
			DarstellungSchiff(Ecke_2, Schiff_2, Kaestchengroesse, FarbeSpieler2); 	updatescr();
		}

		if (Schuss1_2.x >= 0 && Schuss1_2.y >= 0) // Iniialisierung soll nicht ausgegeben werden
		{
			getroffenesFeld(Ecke_2, Schuss1_2, Kaestchengroesse, ROT); 		updatescr();	// letzter Schuss des Gegeners wird in Rot angezeigt
		}
		if (Schuss2_2.x >= 0 && Schuss2_2.y)
		{
			getroffenesFeld(Ecke_2, Schuss2_2, Kaestchengroesse, WEISS);	updatescr();
		}
		if (Schuss3_2.x >= 0 && Schuss3_2.y >= 0)
		{
			getroffenesFeld(Ecke_2, Schuss3_2, Kaestchengroesse, WEISS);	updatescr();
		}
	}


}