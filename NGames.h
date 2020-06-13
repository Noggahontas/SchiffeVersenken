#pragma once
#include "DisplayOutput.h"

void NGames(DisplayOutput &Graphics);		// Führt meherere Speiler hintereinander aus
											// Anzahl der Spiele, die gespielt werden sollen werden vom Nutzer eingegeben
											// Übergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig für die graphische Ausgabe
											// Speichern der Ergebnisse von jedem Spiel für beide Spieler
											// Nachdem alle Spiele gespielt wurden, wird eine Statistik für jede Angriffsstrategie erstellt
