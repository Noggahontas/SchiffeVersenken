#pragma once
#include <iostream>
#include "Global_Definitions.h"						
using namespace std;

void AttackStrategy2(struct Position* Pos)
{
	if ((Pos->x == 9) || (Pos->y == 0))
	{
		if (Pos->x == 3)
		{
			Pos->x = 0;
			Pos->y = 7;
			return;
		}
		else if (Pos->x == 7)
		{
			Pos->x = 2;
			Pos->y = 9;
			return;
		}
		else if (Pos->y == 2)
		{
			Pos->x = 6;
			Pos->y = 9;
			return;
		}
		else if (Pos->y == 6)
		{
			Pos->x = 0;
			Pos->y = 3;
			return;
		}
	}
	else
	{
		Pos->x = Pos->x + 1;
		Pos->y = Pos->y - 1;
		return;
	}

}
