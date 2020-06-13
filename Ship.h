#pragma once
#include <vector>
#include "Global_Definitions.h"
using namespace std;


class Ship											// ein Schiff auf dem Spielfeld
{

	public:
		int Length;									// Anzahl der Felder, die ein Schiff lang ist
		Position StartPos;							// Koordinate (1 Feld), an der sich Schiff aktuell befindet. Von dort aus belegt das Schiff (Length-1) Felder in Richtung Orientation
		Direction Orientation;						// Richtung, in die Schiff von Startposition(StartPos) aus ausgerichtet ist; Es gibt nur nach rechts und nach unten
		vector<bool> Status;						// Gibt an auf welchen Feldern des Schiffs das Schiff schon getroffen wurde; 0=kein Treffer; 1=Treffer
		bool Sunk;									// =1 wenn Schiff versunken


	public:
		bool IsHit(Position Shot);	// Im Übergabeparameter Shot (Struct) werden die Koordinaten des Schusses (vom Gegner) übergeben
									// Gibt an ob Schiff getroffen wurde: Rückgabe 1=Schiff wurde gehittet; 0=nicht geghittet
									// ändert bei einem Hit den Status-Vector
									// Aufruf Funktion StillAlive

		void StillAlive();			// ändert Variable Sunk wenn nötig
									// Prüft anhand des Statusvektors Status ob das Schiff schon an allen Feldern getroffen wurde, also ob es schon versenkt wurde
									// Wenn es versenkt wurde, ändert es die Klassenvariable Sunk zu 1

		bool AreYouThere(Position CriticalCoordinates);	// Übergabe: Koordinaten, von denen geckeckt werden soll ob Schiff darauf steht
														// Rückgabe: Befindet sich an diesen Koordinaten ein Schiff:  1=ja, 0=nein

		Ship(int Len, Position &SPos, Direction Orient);		//Nur zum Testen //Parameter-Konstruktor
																//initialsisiert ein Schiff mit übergebenen Werten: Length=Len, StartPos=SPos, Orientation=Orient

		Ship();					// Standardkonstruktor, weil es ohne eine Fehlermeldung gab

};




//Testen des Konstruktors und IsHit
//
//Position Koord{ 3,2 };
//
//Ship Ship(3, Koord, Direction::Down);
//
//
//cout << "Sunk =" << Ship.Sunk << "\n";
//cout << "Length =" << Ship.Length << "\n";
//cout << "Status[0] =" << Ship.Status.at(0) << "\n";
//cout << "Status[1] =" << Ship.Status.at(1) << "\n";
//cout << "Status[2] =" << Ship.Status.at(2) << "\n";
//
//cout << "StartPosX =" << Ship.StartPos.x << "\n";
//cout << "StartPosY =" << Ship.StartPos.y << "\n";
//cout << "Orientation =" << (int)Ship.Orientation << "\n\n";
//
//cout << "Is Hit bei 3,3? -> " << Ship.IsHit({ 3,3 }) << "\n";
//cout << "Status[0] =" << Ship.Status.at(0) << "\n";
//cout << "Status[1] =" << Ship.Status.at(1) << "\n";
//cout << "Status[2] =" << Ship.Status.at(2) << "\n";
//cout << "Sunk =" << Ship.Sunk << "\n";
//



/* Zum Testen: Ganz am Anfang
Ship Ships[5];
Ships[0].Length = 2;
Ships[0].Direction = Down;
Ships[0].StartPos.x = 3;
Ships[0].StartPos.y = 2;
Ships[0].Sunk = 0;
Ships[0].Status.resize(Ships[0].Length);
for (int i = 0; i < Ships[0].Length; i++)
{
	Ships[0].Status.at(i) = 0;
};

Ships[0].IsHit({ 3,2 });
cout << Ships[0].Sunk;

Ships[0].IsHit({ 3,3 });
cout << Ships[0].Sunk;
*/ 


