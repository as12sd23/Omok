#pragma once
class CDotSpace
{
private:
	CRect m_Space;
	char m_Alive; //'A' 없는 상태 'B' 검은돌 'W' 흰돌
public:
	void Setting(int X, int Y);
	void Drawing(CDC* memDC);
	bool Determine(int x, int y, char Color);
	CRect GetRect();
	char GetAlive();
};

