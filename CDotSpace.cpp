#include "pch.h"
#include "CDotSpace.h"
void CDotSpace::Setting(int X, int Y)
{
	m_Space = CRect(X, Y, X + 36, Y + 36);
	m_Alive = 'A';
}

void CDotSpace::Drawing(CDC* memDC)
{
	memDC->Rectangle(&m_Space);
}

bool CDotSpace::Determine(int x, int y, char Color)
{
	bool A = false;

	if (m_Space.left <= x && m_Space.right >= x &&
		m_Space.top <= y && m_Space.bottom >= y &&
		m_Alive == 'A')
	{
		if (Color == 'B')
		{
			m_Alive = Color;
			A = true;
		}
		else if (Color == 'W')
		{
			m_Alive = Color;
			A = true;
		}
	}
	return A;
}
CRect CDotSpace::GetRect()
{
	return m_Space;
}

char CDotSpace::GetAlive()
{
	return m_Alive;
}

void CDotSpace::DeleteDetermin()
{
	m_Alive = 'A';
}