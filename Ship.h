#pragma once
#include <vector>
#include "Global_Definitions.h"
using namespace std;


class Ship
{

	public:
		int Length;									//Anzahl der Felder, die ein Schiff lang ist
		Position StartPos;							// x,y Position an der Schiff startet
		Direction Direction;						// Richtung, in die Schiff von Startposition aus ausgerichtet ist; Es gibt nur nach rechts und nach unten
		vector<bool> Status;						// Gibt an auf welchen Feldern des Schiffs das Schiff schon getroffen wurde; 0=kein Treffer; 1=Treffer
		bool Sunk;									// =1 wenn Schiff versunken


	public:
		bool IsHit(Position Shot);	// Rückgabe 1=Schiff wurde gehittet; 0=nicht geghittet
								//ändert bei einem Hit Status-Vector
								// Aufruf StillAlive
		void StillAlive();		// ändert Variable Sunk wenn nötig
	


};


/*
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