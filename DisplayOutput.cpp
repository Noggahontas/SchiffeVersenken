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

Position DisplayOutput::SpielfeldErstellen(Position Bildschirm, int Kaestchengroesse, int index, int startpunkt) // Spielfeld an der Stelle(x,y) auf dem Bildschirm
{
	int const N = 4;
	int const delta = Kaestchengroesse;		//10; // Breite eines "Spielkaestchens" auf dem Spielfeld

	int i;
	int dx, dy;
	int differenz;
	int faktor = (startpunkt / 10);
	int abstand = (index - 1) * 300;

	// Definition der verschiedenen Textfelder im Spielfeld
	// alle Texte sollen dieselbe Schriftgroesse haben
	int textgroesse = Kaestchengroesse/2 ;

	// Ueberschrift
	Position Textfeld;
	Textfeld.x = startpunkt / 2 + (Kaestchengroesse*2) + abstand;
	Textfeld.y = startpunkt / 3;

	// Buchstabenreihe
	Position Buchstaben;
	Buchstaben.x = startpunkt + faktor + abstand;
	Buchstaben.y = startpunkt - (faktor*2);

	char *BuchstabenArray[10];
	BuchstabenArray[0] = "A"; BuchstabenArray[1] = "B"; BuchstabenArray[2] = "C"; BuchstabenArray[3] = "D"; BuchstabenArray[4] = "E";
	BuchstabenArray[5] = "F"; BuchstabenArray[6] = "G"; BuchstabenArray[7] = "H"; BuchstabenArray[8] = "I"; BuchstabenArray[9] = "J";

	// Zahlenreihe
	Position Zahlen;
	Zahlen.x = startpunkt - faktor + abstand;
	Zahlen.y = startpunkt + (faktor*2);

	// PROVISORISCHE LOESUNG Zahlenreihe
	char* ZahlenArray[10];
	ZahlenArray[0] = "1"; ZahlenArray[1] = "2"; ZahlenArray[2] = "3"; ZahlenArray[3] = "4"; ZahlenArray[4] = "5";
	ZahlenArray[5] = "6"; ZahlenArray[6] = "7"; ZahlenArray[7] = "8"; ZahlenArray[8] = "9"; ZahlenArray[9] = "10";


	// Speichern der 4 Eckpunkte des Spielfeldes
	Position Spielfeld[N]; 
   	Spielfeld[0].x = startpunkt + abstand; Spielfeld[0].y = startpunkt;							// linke Ecke oben
	Spielfeld[1].x = startpunkt + (10*delta) + abstand; Spielfeld[1].y = startpunkt;				// rechte Ecke oben
	Spielfeld[2].x = startpunkt + (10*delta) + abstand; Spielfeld[2].y = startpunkt + (10*delta);	// rechte Ecke unten
	Spielfeld[3].x = startpunkt+ abstand; Spielfeld[3].y = startpunkt + (10*delta);				// linke Ecke unten

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

// falls zur Kontrolle des Spielablaufes ein Übersichtsfenster genutzt werden muss, indem beide Schiffe dargestellt werden sollen
Position DisplayOutput::Legende(Position EckpunktSpielfeld, int Kaestchengroesse, int index, Player Spieler)

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
	int verfehlteSchuesse = 0;
	int getroffeneSchuesse = 0;
	int versenkteSchiffe = 0;

	// Informationstext
	char InfoSpieler[500];
		snprintf(InfoSpieler, sizeof(InfoSpieler), 
			"Spieler Nr. % d \n Verteidigungsstrategie Nr. %d \n Angriffsstartegie Nr. %d \n verfehlte Schüsse : \d \n getroffene Schüsse : %d \n versenkte Schiffe : %d"
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
	rectangle(x1, y1, x2, y2, Farbe, Farbe);
	
	for (int j = 0; j < Schiffslaenge; j++)
	{
		// Überprüfung ob Schiff an dieser Stelle bereits getroffen wurde [0 1 ... Schifflänge -1]
		Statusabfrage = StatusSchiff.at(j);

		if (Statusabfrage == 1)				// Stelle wurde bereits erfolgreich getroffen			
		{
			// Lokalisierung des Treffers abhaengig von der Ausrichtung des Schiffes
			if (AusrichtungSchiff == Direction::Right) // Schiffsausrichtung auf dem Spielfeld: waagrecht
			{
				x1 = x1 + (j * Kaestchengroesse);	// in x - Richtung, falls Schiff waagrecht
				y1 = y1;
				x2 = x1 + Kaestchengroesse - 1;
				y2 = y1 + Kaestchengroesse - 1;
			}
			else if (AusrichtungSchiff == Direction::Down) // Schiffsausrichtung auf dem Spielfeld: senkrecht
			{
				x1 = x1;
				y1 = y1 + (j * Kaestchengroesse);
				x2 = x1 + Kaestchengroesse - 1;
				y2 = y1 + Kaestchengroesse - 1;
			}
			rectangle(x1, y1, x2, y2, ROT, ROT); // Zeichnen eines roten Feldes als Treffer
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

void DisplayOutput::Ausgabe(int Kaestchengroesse, Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2)
{
	int i;										// Zählvariable für die for- Schleife
	Position Ecke_1 = {};						// Position der linken oberen Ecke der Spielfelder, Rückgabewert beim Erstellen des Spielfeldes
												// Ecke_1 : Ecke des Spielfeldes des 1. Spielers
	Position Ecke_2 = {};					
												// Ecke_2 : Ecke des Spielfeldes des 2. Spielers
	Position Schuss1_1, Schuss2_1, Schuss3_1;	// letzten 3 Schuesse des Gegners (Spieler 1)
	Position Schuss1_2, Schuss2_2, Schuss3_2;	// letzten 3 Schuesse des Gegners (Spieler 2)

	Ship Schiff_1, Schiff_2;					// Schiff_1 : Schiff Spieler 1
												// Schiff_2 : Schiff Spieler 2

	Position Bildschirm;						// Position des Grafikfensters auf dem Bildschirm
	Bildschirm.x = 500;
	Bildschirm.y = 250;
	
	int start = 50;

	// Hoehe und Breite des Graphikfensters
	int breite = (10 * start) + 200;
	int hoehe = (10 * Kaestchengroesse) + (2 * start) + 200;

	// Erstellen des Graphikfensters
	set_windowpos(Bildschirm.x, Bildschirm.y, breite, hoehe);

	// Schärzen der Fläche, damit alte Treffer nicht merh angezeigt werden
	rectangle(start, start, start + breite, start + hoehe, SCHWARZ, SCHWARZ); updatescr();

	// Spielfeld zeichnen
	Ecke_1 = SpielfeldErstellen(Bildschirm, Kaestchengroesse, 1, start);				 // Spielfeld fuer Spieler 1 
	Ecke_2 = SpielfeldErstellen(Bildschirm, Kaestchengroesse, 2, start); updatescr(); // Spielfeld fuer Spieler 2

	// Ausgabe Legende
	Position Legende2 = {}, Legende1 = {};
	Legende1 = Legende(Ecke_1, Kaestchengroesse, 1, Spieler1);
	Legende2 = Legende(Ecke_2, Kaestchengroesse, 2, Spieler2);

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
			DarstellungSchiff(Ecke_1, Schiff_1, Kaestchengroesse, FarbeSpieler1); 	updatescr();
		}
		if (Schuss1_1.x != NULL && Schuss1_1.y != NULL) // Iniialisierung (0,0) soll nicht ausgegeben werden
		{
			getroffenesFeld(Ecke_1, Schuss1_1, Kaestchengroesse, ROT);	updatescr();	  // letzter Schuss des Gegeners wird in Rot angezeigt
		}
		if (Schuss2_1.x != NULL && Schuss2_1.y != NULL)
		{
			getroffenesFeld(Ecke_1, Schuss2_1, Kaestchengroesse, GRAU);	updatescr();
		}
		if (Schuss3_1.x != NULL && Schuss3_1.y != NULL)
		{
			getroffenesFeld(Ecke_1, Schuss3_1, Kaestchengroesse, GRAU); updatescr();
		}

		// Spieler 2
		if (Schiff_2_Kontrolle != 1) // gesunkene Schiffe sollen nicht gezeichnet werden
		{
			DarstellungSchiff(Ecke_2, Schiff_2, Kaestchengroesse, FarbeSpieler2); 	updatescr();
		}
		if (Schuss1_2.x != NULL && Schuss1_2.y != NULL)
		{
			getroffenesFeld(Ecke_2, Schuss1_2, Kaestchengroesse, ROT); 	updatescr(); // letzter Schuss des Gegeners wird in Rot angezeigt
		} 
		if (Schuss2_2.x != NULL && Schuss2_2.y != NULL)
		{
			getroffenesFeld(Ecke_2, Schuss2_2, Kaestchengroesse, GRAU); updatescr();
		}
		if (Schuss3_2.x != NULL && Schuss3_2.y != NULL) // Iniialisierung (0,0) soll nicht ausgegeben werden
		{
			getroffenesFeld(Ecke_2, Schuss3_2, Kaestchengroesse, GRAU);	updatescr();
		}
	}	
}