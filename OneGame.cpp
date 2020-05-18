#include "stdafx.h"
#include "OneGame.h"
#include "Global_Definitions.h"
#include "Alternate.h"
#include <Windows.h>		// ben�togt f�r Funktion sleep()
#include <iostream>
#include "DisplayOutput.h"


void OneGame()			// Momentan Endlosschleife und noch ohne Vetreidigungsstrategie
{
	Player P[2];			// Spieler werden erstellt -> Standartkonstruktor

	//F�r die graphische Ausgabe
	DisplayOutput Graphics;	
	int Kaestchengroesse = 20;
	int FarbeSchiffe = WEISS;

	// F�r die zeitliche Verz�gerung
	int WaitTime = 4000;

	Position AttackShot ;	// Koordinaten f�r Schuss beim Angreifen werden hier gespeichert
	AttackResult Result[2] = {0,0};	// Angabe ob vom Schuss AttackShot ein Schiff getroffen wurde:  Result.Hit: 1 = ein Schiff wurde getroffen,  0 = kein Schiff getroffen
							// Angabe ob vom Schuss AttackShot ein Schiff versenkt wurde:  Result.Sunk: 1 = ein Schiff wurde versenkt, 0 = kein Schiff versenkt
							// F�r jeden Spieler eine Variable, notwendig f�r Strategien (ben�togen die Infos)
	int i = 0;

	//int count = 0;		// Zum Testen

	Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics
	Sleep(WaitTime);										// Versetzt Programm f�r 2 Sekunden in einen inaktiven Modus


	//Angriff erster Spieler
	cout << "Spieler " << i+1 << " an der Reihe: Angriff \n";
	AttackShot = P[i].FindAttackShot(Result[Alternate(i)]);	// Durch ausgew�hlte Strategie des Spielers P[0] werden Koordinaten ausgew�hlt, auf die geschossen werden soll
	Result[i] = P[Alternate(i)].ShotOn(AttackShot);			// Auf ausgew�hlte Koordinaten wird geschossen: Schuss auf Spielfeld von zweitem Spieler P[1] 
															// Das Ergebnis des Schusses von P[0] wird f�r P[0] in Result[0] abgespeichert

	Sleep(WaitTime);										// Versetzt Programm f�r 2 Sekunden in einen inaktiven Modus
	Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics

	if (Result[i].Hit == 1)								// Ausgabe Resultat des Schusses von P[0]
	{
		cout << "Treffer \n";
		if (Result[i].Sunk == 1)
		{
			cout << "Schiff wurde versenkt \n";		
		}
	}
	else
	{
		cout << "Kein Treffer \n";
	}

	Sleep(WaitTime);						// Versetzt Programm f�r 2 Sekunden in einen inaktiven Modus


	while (!P[0].Lost & !P[1].Lost)	// Solange noch kein Spieler verloren hat, wird weitergespielt
	{

		i = Alternate(i);			// �ndert i: 1->0 , 0->1

		// Verteidigung von Spieler i
		cout << "Spieler " << i + 1 << " an der Reihe: Drehen/Bewegen \n";
		//P[i].DefensiveAction(Result[Alternate(i)].Hit);				// Durch gew�hlte Versteidigungsstrategie des jew. Spielers wird Aktion zum Verteidigen ausgwe�hlt und ausgef�hrt
																	// �bergabe, ob letzter Schuss des Gegners Treffer war

		Sleep(WaitTime);												// Versetzt Programm f�r 2 Sekunden in einen inaktiven Modus

		Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics

		Sleep(WaitTime);												// Versetzt Programm f�r 2 Sekunden in einen inaktiven Modus


		// Angriff von Spieler i
		cout << "Spieler " << i + 1 << " an der Reihe: Angriff \n";
		AttackShot = P[i].FindAttackShot(Result[Alternate(i)]);							// Durch ausgew�hlte Strategie des Spielers werden Koordinaten ausgew�hlt, auf die geschossen werden soll
		Result[i] = P[Alternate(i)].ShotOn(AttackShot);				// Auf ausgew�hlte Koordinaten wird geschossen (auf Spielfeld von zweitem Spieler )

		Sleep(2000);												// Versetzt Programm f�r 2 Sekunden in einen inaktiven Modus
		Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics

		if (Result[i].Hit == 1)
		{
			cout << "Treffer \n";
			if (Result[i].Sunk == 1)
			{
				cout << "Schiff wurde versenkt \n";
			}
		}
		else
		{
			cout << "Kein Treffer \n";
		}

		Sleep(WaitTime);									// Versetzt Programm f�r 2 Sekunden in einen inaktiven Modus

		/*count++;

		if (count == 3)				// Zum Testen
		{
			P[1].Lost = 1;
		}*/
	}
}

