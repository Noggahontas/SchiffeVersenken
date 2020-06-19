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

		/*
			Funktion: Gibt an ob Schiff getroffen wurde
			Input:	- Shot (Struct): Koordinaten des Schusses (vom Gegner)
			Transienten: Status (Vektor)
			Output: Rückgabe 1=Schiff wurde gehittet; 0=nicht geghittet
		*/
		bool IsHit(Position Shot);	


		/*
			Funktion: Prüft anhand des Statusvektors Status ob das Schiff schon an allen Feldern getroffen wurde, also ob es schon versenkt wurde
			Transienten: Sunk
		*/
		void StillAlive();			


		/*
			Funktion: Überprüft ob das Schiff sich an übergebenen Koordinaten befidet 
			Input:	- CriticalCoordinates: Koordinaten, von denen geckeckt werden soll ob Schiff darauf steht
			Output: Angabe ob sich das Schiff an diesen Koordinaten befindet
		*/
		bool AreYouThere(Position CriticalCoordinates);	



		/*
			Funktion: Erste Initialisierung Klassenvariablen
			Transient: Alle Klassenvariablen
		*/
		Ship();

};





