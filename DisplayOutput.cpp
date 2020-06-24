#include "stdafx.h"
#include "DisplayOutput.h"

#include "stdafx.h"
#include "console\console.h"
#include "graphics\graphicfunctions.h"

#include <iostream>
#include <stdio.h>




void DisplayOutput::Grafikfenster()
{
	// Hoehe und Breite des Graphikfensters
	int breite = (20 * Kaestchengroesse) + (4 * Startpunkt);
	int hoehe = (16 * Kaestchengroesse) + (2 * Startpunkt);

	// Erstellen des Graphikfensters
	set_drawarea(breite, hoehe); 
	set_windowpos(Bildschirm.x, Bildschirm.y, breite, hoehe);
	
}

void DisplayOutput::Screen(char indikator)
{
	clrscr();
	int breite, hoehe, x, y, klick = 0;
	get_drawarea(&breite, &hoehe);
	Position Text;
	Text.x = (breite - 2 * 50) / 2;
	Text.y = (hoehe - 50) / 2;

	if (indikator == 'S')
	{
		text(Text.x, Text.y, 50, SCHWARZ, WEISS, "S T A R T", CENTER_ALIGN);
		text(Text.x + 10, Text.y + 50, 20, SCHWARZ, WEISS, "press start to play", CENTER_ALIGN);
	}
	else if (indikator == 'E')
	{
		text(Text.x, Text.y, 50, SCHWARZ, WEISS, "E N D E", CENTER_ALIGN);
	}
}

Position DisplayOutput::SpielfeldErstellen(int index) // Spielfeld an der Stelle(x,y) auf dem Bildschirm
{
	int const N = 4;				 // Definition einer festen Array-Groesse
	int i;							 // Zaehlvariable der for- Schleife
	int dx, dy;						 // Hilfsvariablen zur Abstandberechnung der Buchstaben bzw Zahlen zueinander
	int differenz;					 // Abstand der gezeichneten Spielfeldlinien
	int faktor = (Startpunkt / 10);  // Abstand der Buchstaben / Zahlenreihen vom Spielfeld
	int abstand = (index - 1) * 300; // Berechnen des Abstandes beider Spielfelder

	// Definition der verschiedenen Textfelder im Spielfeld
	// alle Texte sollen dieselbe Schriftgroesse haben
	int textgroesse = Kaestchengroesse/2 ;

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

	char* ZahlenArray[10];
	ZahlenArray[0] = "1"; ZahlenArray[1] = "2"; ZahlenArray[2] = "3"; ZahlenArray[3] = "4"; ZahlenArray[4] = "5";
	ZahlenArray[5] = "6"; ZahlenArray[6] = "7"; ZahlenArray[7] = "8"; ZahlenArray[8] = "9"; ZahlenArray[9] = "10";

	// Speichern der 4 Eckpunkte des Spielfeldes
	Position Spielfeld[N]; 
   	Spielfeld[0].x = Startpunkt + abstand; Spielfeld[0].y = Startpunkt;								// linke Ecke oben
	Spielfeld[1].x = Startpunkt + (10*Kaestchengroesse) + abstand; Spielfeld[1].y = Startpunkt;				// rechte Ecke oben
	Spielfeld[2].x = Startpunkt + (10* Kaestchengroesse) + abstand; Spielfeld[2].y = Startpunkt + (10*Kaestchengroesse);	// rechte Ecke unten
	Spielfeld[3].x = Startpunkt+ abstand; Spielfeld[3].y = Startpunkt + (10*Kaestchengroesse);					// linke Ecke unten

	// Zeichnen des Spielfeldes
	for (i = 0; i < 11; i++)
	{
		differenz = i* Kaestchengroesse;

		// senkrechte Linien
		line((Spielfeld[0].x + differenz), Spielfeld[0].y, (Spielfeld[3].x + differenz), Spielfeld[3].y, SCHWARZ);
		// waagrechte Linien
		line(Spielfeld[0].x, (Spielfeld[0].y + differenz), Spielfeld[1].x, (Spielfeld[1].y + differenz), SCHWARZ);

		// Ausgabe der Beschriftung bestehend aus Zahlen(senkrecht) und Buchstaben (waagrecht)
		if (i != 10)
		{
			dx = Buchstaben.x + differenz;
			dy = Buchstaben.y + differenz + Kaestchengroesse;
			text(dx, Buchstaben.y, textgroesse, SCHWARZ, BuchstabenArray[i]);
			text(Buchstaben.x - Kaestchengroesse, dy, textgroesse, SCHWARZ, ZahlenArray[i]);
		}
	}

	// Rückgabe der linken oberen Ecke 
	return Spielfeld[0];
};

void DisplayOutput::Legende(Position EckpunktSpielfeld, int index, Player Spieler1, Player Spieler2)
{
	// Positionierung des Textes unter dem zugehörigen Spielfeld
	Position Legende[2] = {};
	Legende[0].x = EckpunktSpielfeld.x;			// linkes oberes Eck der Textbox
	Legende[0].y = 14 * Kaestchengroesse;

	Legende[1].x = Legende[0].x + Kaestchengroesse * 10;
	Legende[1].y = Legende[0].y + Kaestchengroesse * 6;

	// Initialisierung
	int Angriffsstrategie = 0, Verteidigungsstrategie = 0, verfehlteSchuesse = 0,getroffeneSchuesse = 0,versenkteSchiffe = 0;

	if (index == 1)
	{
		// Informationen zur Angriffs- und Verteidigungsstrategie des Spielers
		Angriffsstrategie = Spieler1.AttackStrategy;
		Verteidigungsstrategie = Spieler1.DefenseStrategy;

		// die Information über Treffe /Schüsse/ gesunkene Schiffe steht beim Gegner
		verfehlteSchuesse = Spieler2.MissedShotsOfOpponent;
		getroffeneSchuesse = Spieler2.HitShotsOfOpponent;
		versenkteSchiffe = Spieler2.SunkShipsByOpponent;
	}
	else if( index == 2)
	{
		// Informationen zur Angriffs- und Verteidigungsstrategie des Spielers
		Angriffsstrategie = Spieler2.AttackStrategy;
		Verteidigungsstrategie = Spieler2.DefenseStrategy;

		// die Information über Treffe /Schüsse/ gesunkene Schiffe steht beim Gegner
		verfehlteSchuesse = Spieler1.MissedShotsOfOpponent;
		getroffeneSchuesse = Spieler1.HitShotsOfOpponent;
		versenkteSchiffe = Spieler1.SunkShipsByOpponent;
	}


	// Informationstext
	char InfoSpieler[500];
		snprintf(InfoSpieler, sizeof(InfoSpieler), 
			"Spieler Nr. % d \n Angriffsstrategie Nr. %d \n  Verteidigungsstrategie Nr. %d \n\n verfehlte Schüsse : %d \n getroffene Schüsse : %d \n versenkte Schiffe : %d"
			,index, Angriffsstrategie, Verteidigungsstrategie, verfehlteSchuesse, getroffeneSchuesse, versenkteSchiffe);

		textbox(Legende[0].x, Legende[0].y, Legende[1].x, Legende[1].y, 15, SCHWARZ, SCHWARZ, WEISS, CENTER_ALIGN, InfoSpieler); 
		//updatescr();
}

void DisplayOutput::DarstellungSchiff(Position EckpunktSpielfeld,Ship Schiff, int Farbe)
{
	int Schiffslaenge = Schiff.Length;						// Schiffslaenge des darzustellenden Schiff
	Direction AusrichtungSchiff = Schiff.Orientation;		// Ausrichtung des Schiffs auf dem Spielfeld
	Position Schiffsposition = Schiff.StartPos;				// Position des darzustellenden Schiffs auf dem Spielfeld

	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	// Ueberpruefung, ob Schiff bereits getroffen wurde
	vector<bool> StatusSchiff = Schiff.Status;
	int Statusabfrage = 0;										// zu überprüfende Stelle des Schiffes
	Position getroffenesFeld[2] = {};
	
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
	// zuerst wird das gesamte Schiff in der gewünschten Farbe gezeichnet
	rectangle(x1, y1, x2, y2, Farbe, Farbe);
	
	// danach wird geprüft, ob Schiff bereits getroffen wurde
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
				getroffenesFeld[1].x = getroffenesFeld[0].x + Kaestchengroesse - 1;
				getroffenesFeld[1].y = getroffenesFeld[0].y + Kaestchengroesse - 1;
			}
			else if (AusrichtungSchiff == Direction::Down) // Schiffsausrichtung auf dem Spielfeld: senkrecht
			{
				getroffenesFeld[0].x = x1;
				getroffenesFeld[0].y = y1 + (j * Kaestchengroesse);
				getroffenesFeld[1].x = getroffenesFeld[0].x + Kaestchengroesse - 1;
				getroffenesFeld[1].y = getroffenesFeld[0].y + Kaestchengroesse - 1;
			}
			rectangle(getroffenesFeld[0].x, getroffenesFeld[0].y, getroffenesFeld[1].x, getroffenesFeld[1].y, ROT, ROT); // Zeichnen eines roten Feldes als Treffer
		} 

	}
}

void DisplayOutput::getroffenesFeld(Position EckpunktSpielfeld, Position Schuss,int Farbe)
{
	int x1 = 0, x2 = 0, xx1 = 0, xx2 = 0, y1 = 0, y2 = 0, yy1 = 0, yy2 = 0;
	// Skalierung des Ausgangspunktes an das Spielfeld
	x1 = EckpunktSpielfeld.x + Schuss.x*Kaestchengroesse;
	y1 = EckpunktSpielfeld.y + Schuss.y*Kaestchengroesse;

	x2 = x1 + Kaestchengroesse; 
	y2 = y1 + Kaestchengroesse;

	xx1 = x1 + Kaestchengroesse; yy1 = y1;
	xx2 = x1; yy2 = y1 + Kaestchengroesse;

	// Zeichnen eines Kreuzes
	line(x1, y1, x2, y2, Farbe);
	line(xx1, yy1, xx2, yy2, Farbe);
}

void DisplayOutput::Ausgabe(Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2)
{
	int i = 0;									// Zählvariable für die for- Schleife
	
	// Position der linken oberen Ecke der Spielfelder, Rückgabewert beim Erstellen des Spielfeldes
	Position Ecke_1;							// Ecke_1 : Ecke des Spielfeldes des 1. Spielers
	Position Ecke_2;							// Ecke_2 : Ecke des Spielfeldes des 2. Spielers

	Position Schuss1_1, Schuss2_1, Schuss3_1;	// letzten 3 Schuesse des Gegners (Spieler 1)
	Position Schuss1_2, Schuss2_2, Schuss3_2;	// letzten 3 Schuesse des Gegners (Spieler 2)

	Ship Schiff_1, Schiff_2;					// Schiff_1 : Schiff Spieler 1, Schiff_2 : Schiff Spieler 2

	int Schiff_1_Kontrolle;						// Status des Schiffes(gesunken / nicht gesunken) des 1. Spielers
	int Schiff_2_Kontrolle;						// Status des Schiffes(gesunken / nicht gesunken) des 2. Spielers

	// Aufräumen
	clrscr(); 

	// Ueberschrift
	Position Textfeld;
	Textfeld.x = Startpunkt + (Kaestchengroesse * 7);
	Textfeld.y = Startpunkt / 5;

	int textgroesse = Kaestchengroesse / 2;
	char* ausgabe = "SCHIFFE VERSENKEN";
	text(Textfeld.x, Textfeld.y, textgroesse*3, SCHWARZ, ausgabe);

	// Spielfeld zeichnen
	Ecke_1 = SpielfeldErstellen(1);// Spielfeld fuer Spieler 1 
	Ecke_2 = SpielfeldErstellen(2); // Spielfeld fuer Spieler 2

	// Ausgabe Legende
	Legende(Ecke_1, 1, Spieler1, Spieler2);
	Legende(Ecke_2, 2, Spieler1, Spieler2);

	// Schuesse
	// Spieler 1
	Schuss1_1 = Spieler1.Last3ShotsOfOpponent[0];	// letzter Schuss des Gegners
	Schuss2_1 = Spieler1.Last3ShotsOfOpponent[1];
	Schuss3_1 = Spieler1.Last3ShotsOfOpponent[2];

	// Spieler 2
	Schuss1_2 = Spieler2.Last3ShotsOfOpponent[0];	// letzter Schuss des Gegners
	Schuss2_2 = Spieler2.Last3ShotsOfOpponent[1];
	Schuss3_2 = Spieler2.Last3ShotsOfOpponent[2];

	// Schiffe zeichnen
	for (i = 0; i < 10; i++)
	{
		// Ausgabe Spieler 1
		Schiff_1 = Spieler1.Ships[i];				// aktuelles Schiff
		Schiff_2 = Spieler2.Ships[i];

		// Lebendkontrolle
		Schiff_1_Kontrolle = Schiff_1.Sunk;
		Schiff_2_Kontrolle = Schiff_2.Sunk;

		// zuerst die Schiffe und dann die getroffenen Felder zeichnen, sonst werde die Kreuze übermalt
		// Schiff von Spieler 1
		if (Schiff_1_Kontrolle != 1) // gesunkene Schiffe sollen nicht gezeichnet werden
		{
			DarstellungSchiff(Ecke_1, Schiff_1, FarbeSpieler1);
		}

		// Schiff von Spieler 2
		if (Schiff_2_Kontrolle != 1) // gesunkene Schiffe sollen nicht gezeichnet werden
		{
			DarstellungSchiff(Ecke_2, Schiff_2, FarbeSpieler2); 	
		}
	}
	
	// Schuesse des 1. Spielers
	if (Schuss1_1.x >= 0 && Schuss1_1.y >= 0) // Iniialisierung soll nicht ausgegeben werden
	{
		getroffenesFeld(Ecke_1, Schuss1_1, ROT);			// letzter Schuss des Gegeners wird in Rot angezeigt
	}
	if (Schuss2_1.x >= 0 && Schuss2_1.y >= 0)
	{
		getroffenesFeld(Ecke_1, Schuss2_1, SCHWARZ);
	}
	if (Schuss3_1.x >= 0 && Schuss3_1.y >= 0)
	{
		getroffenesFeld(Ecke_1, Schuss3_1, SCHWARZ);
	}

	// Schuesse des 2.Spielers
	if (Schuss1_2.x >= 0 && Schuss1_2.y >= 0) // Iniialisierung soll nicht ausgegeben werden
	{
		getroffenesFeld(Ecke_2, Schuss1_2, ROT); 			// letzter Schuss des Gegeners wird in Rot angezeigt
	}
	if (Schuss2_2.x >= 0 && Schuss2_2.y >= 0)
	{
		getroffenesFeld(Ecke_2, Schuss2_2, SCHWARZ);
	}
	if (Schuss3_2.x >= 0 && Schuss3_2.y >= 0)
	{
		getroffenesFeld(Ecke_2, Schuss3_2, SCHWARZ);
	}

	updatescr();
}