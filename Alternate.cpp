#include "stdafx.h"
#include "Alternate.h"

int Alternate(int i)
{
	// Wenn i = 1: gibt 0 zur�ck, wenn i = 0: gibt 1 zur�ck
	// F�r OneGame() im Spielablauf ben�tigt
	// �ndert i nicht

	if (i == 0)
	{
		return 1;
	}
	else if (i == 1)
	{
		return 0;
	}

	return -1;
}