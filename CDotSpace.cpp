#include "pch.h"
#include "CDotSpace.h"
void CDotSpace::Setting()
{
	for (int i = 0, X = 22; i < 19; i++, X+=20)
	{
		for (int j = 0, Y = 22; j < 19; j++, Y+=20)
		{
			m_Space[i] = CRect(X, Y, X + 18, Y + 18);
		}
	}
}