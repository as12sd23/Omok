#pragma once
class CDotSpace
{
private:
	CRect m_Space;
	char m_Alive = 'A'; //'A' ���� ���� 'B' ������ 'W' ��
public:
	void Setting(int X, int Y);
	void Drawing(CDC* memDC);
	bool Determine(int x, int y, char Color);
	CRect GetRect();
	char GetAlive();
	void DeleteDetermin();
};

