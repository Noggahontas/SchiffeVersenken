#pragma once
#include "DisplayOutput.h"

void NGames(DisplayOutput &Graphics);		// F�hrt meherere Speiler hintereinander aus
											// Anzahl der Spiele, die gespielt werden sollen werden vom Nutzer eingegeben
											// �bergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig f�r die graphische Ausgabe
											// Speichern der Ergebnisse von jedem Spiel f�r beide Spieler
											// Nachdem alle Spiele gespielt wurden, wird eine Statistik f�r jede Angriffsstrategie erstellt
