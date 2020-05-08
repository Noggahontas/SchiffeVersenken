#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
using namespace std;


bool Player::ShotOn(Position Shot)
{
	// Schuss von Gegner auf Koordinaten Shot	
	// ändert Last3ShotsOfOpponent
	// Gibt zurück ob ein Schiff getroffen wurde: 1 = getroffen, 0= nicht getroffen

	Last3ShotsOfOpponent.insert(Last3ShotsOfOpponent.begin(), Shot);	//An Position 0 neuen Schuss des Gegners einfügen (Iterator auf Position 0 wird übergeben)
																		//Nun sind es 4 Element!
	Last3ShotsOfOpponent.pop_back();									//Letztes Element löschen -> Es sind wieder die letzten 3 Schüsse gespeichert

	bool Hit;							// Angabe ob ein Schiff getroffen wurde
	int i = 0;
	do									// Ausführen bis ein getroffenes Schiff gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
	{
		Hit = Ships[i].IsHit(Shot);		// Funktion ISHit gibt zurück ob dieses Schiff getroffen wurde
		i++;
	} while ( (i < 10) & (Hit != 1) );	

	return Hit;			// Rückgabe ob ein Schiff getroffen wurde
}



Player::Player() {
	 // Konstruktor 
	 // Stößt Konstruktor für jedes Schiff an
	 // legt Größe von Last3ShotsOfOpponent fest und initialisiert mit NULL
	 // Wählt zufällig AttackStrategy und DefenseStrategy aus

	 //Bei Player P1
	// Einlesen der Initialisierungswerte der Schiffe aus Textdatei
	// Eigentlich mit Lexikalischer Analyse:
	//...
	// Vorläufige Lösung: Direktes, festes Initialisieren; Korrekte Lösung kommt noch

	Ships[0].Length = 5;
	Ships[0].StartPos = { 0,0 };
	Ships[0].Orientation = Direction::Down;
	Ships[0].Status.resize(Ships[0].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[0].Sunk = 0;							// Noch keine Treffer, noch nicht versenkt

	Ships[1].Length = 4;
	Ships[1].StartPos = { 4,2 };
	Ships[1].Orientation = Direction::Right;
	Ships[1].Status.resize(Ships[1].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[1].Sunk = 0;

	Ships[2].Length = 4;
	Ships[2].StartPos = { 8,6 };
	Ships[2].Orientation = Direction::Down;
	Ships[2].Status.resize(Ships[2].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[2].Sunk = 0;

	Ships[3].Length = 3;
	Ships[3].StartPos = { 0,7 };
	Ships[3].Orientation = Direction::Right;
	Ships[3].Status.resize(Ships[3].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[3].Sunk = 0;

	Ships[4].Length = 3;
	Ships[4].StartPos = { 2,3 };
	Ships[4].Orientation = Direction::Down;
	Ships[4].Status.resize(Ships[4].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[4].Sunk = 0;

	Ships[5].Length = 3;
	Ships[5].StartPos = { 5,4 };
	Ships[5].Orientation = Direction::Down;
	Ships[5].Status.resize(Ships[5].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[5].Sunk = 0;

	Ships[6].Length = 2;
	Ships[6].StartPos = { 3,0 };
	Ships[6].Orientation = Direction::Right;
	Ships[6].Status.resize(Ships[6].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[6].Sunk = 0;

	Ships[7].Length = 2;
	Ships[7].StartPos = { 9,0 };
	Ships[7].Orientation = Direction::Down;
	Ships[7].Status.resize(Ships[7].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[7].Sunk = 0;

	Ships[8].Length = 2;
	Ships[8].StartPos = { 9,3 };
	Ships[8].Orientation = Direction::Down;
	Ships[8].Status.resize(Ships[8].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[8].Sunk = 0;

	Ships[9].Length = 2;
	Ships[9].StartPos = { 3,9 };
	Ships[9].Orientation = Direction::Right;
	Ships[9].Status.resize(Ships[9].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[9].Sunk = 0;

	// Dies soll später zufällig passieren
	AttackStrategy = 1;
	DefenseStrategy = 1;

	Last3ShotsOfOpponent.resize(3, { NULL, NULL });	// Noch keine Schüsse abgefeuert -> NULL




// Ohne lexikalische Analyse - so war es nicht gedacht
// Folgende Probleme hier: Letztes Schiff wird falsch initialisiert und ein NULL Problem -> Mystery
// Einlesen aus Textdatei, um Schiffe zu initialisieren

	//FILE* File;
	//char *Element;						//separiertes Element aus einer Zeile
	//char* Filename = "SetShips.txt";
	//const int Bufferlen = 20;
	//char Buffer[Bufferlen];				// Puffer zum Einlesen einer Zeile

	//int ShipNumber = 0;		// Zum Zählen der Zeilen. Zeilen werden Schiffen zugeordnet


	//File = fopen(Filename, "r");

	//if (File == NULL)
	//{
	//	printf("Cannot open file %s", Filename);
	//	return;							// Springt das auch aus dem Konstruktor?
	//}

	//while (!feof(File))
	//{
	//	fgets(Buffer, Bufferlen, File);			// eine Zeile einlesen

	//	Element = strtok(Buffer, "\n \t");		// erstes Element ohne Trennzeichen aus Buffer separieren

	//	while (Element != NULL)					// Bis der Buffer ganz durchlaufen wurde			
	//	{							//Quick and Dirt Lösung	// - 48, weil die Zhalen aus Textdatei werden als ASCII Zeichen zurückgegeben int 0 -> 48 in ASCII
	//		Ships[ShipNumber].Length = *Element - 48 ;		// In Textdatei steht die Länge in erster Spalte
	//		
	//		Element = strtok(NULL, "\n \t");			//nächstes Elemente aus Buffer separieren
	//		Ships[ShipNumber].StartPos.x = *Element - 48;	// In Textdatei steht die x-Koordinate der Startposition in der zweiten Spalte

	//		Element = strtok(NULL, "\n \t");			//nächstes Elemente aus Buffer separieren
	//		Ships[ShipNumber].StartPos.y = *Element - 48;	// In Textdatei steht y-Koordinate der Startposition in der ditten Spalte

	//		Element = strtok(NULL, "\n \t");			//nächstes Elemente aus Buffer separieren
	//		if((*Element - 48) == 0)							// In Textdatei steht in letzter Spalte die Ausrichtung
	//		{
	//			Ships[ShipNumber].Orientation = Direction::Right;	
	//		}
	//		else if ((*Element -48) == 1)
	//		{
	//			Ships[ShipNumber].Orientation = Direction::Down;	
	//		}
	//		
	//		Element = strtok(NULL, "\n \t");

	//	}

	//	ShipNumber++;	// nächste Zeile wird geholt, gilt für nächstes Schiff
	//}




}

// Lösung Problem enum -> Typumwandlung
//
//enum class Test { a, b, c };
//
//Test T;
//
//T = (Test)1;
//
//T = static_cast <Test> (2);





//_______________________________________________________________________________________
// Zum test ShotOn
//Player P1;
//
//cout << P1.ShotOn({ 5,2 });
//
//cout << "Status getr. Schiff: " << P1.Ships[1].Status.at(0) << P1.Ships[1].Status.at(1) << P1.Ships[1].Status.at(2) << P1.Ships[1].Status.at(3);
//
//cout << "\n letzte 3 Schüsse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}
//
//cout << "\n" << P1.ShotOn({ 1,0 });
//cout << "\n letzte 3 Schüsse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}
//
//cout << "\n" << P1.ShotOn({ 2,3 });
//cout << "\n letzte 3 Schüsse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}


//______________________________________________________________________________________________________________

// Zum Testen Konstruktor
//
//Player P1;
//for (int i = 0; i < 10; i++)
//{
//	cout << "Ships[" << i << "]: " << P1.Ships[i].Length << "{" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "}" << P1.Ships[i].Sunk << "\n";
//}
//if (P1.Ships[0].Orientation == Direction::Down)
//{
//	cout << 1 << "\n";
//}
//else if (P1.Ships[0].Orientation == Direction::Right)
//{
//	cout << 0;
//}
//
//P1.Ships[0].IsHit({ 0,3 });
//cout << "Status: " << P1.Ships[0].Status.at(0) << P1.Ships[0].Status.at(1) << P1.Ships[0].Status.at(2) << P1.Ships[0].Status.at(3) << P1.Ships[0].Status.at(4) << "\n";
//cout << P1.Ships[0].Sunk;
