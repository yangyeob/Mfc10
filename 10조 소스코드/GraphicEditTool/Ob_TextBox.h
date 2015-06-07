#pragma once
class Ob_TextBox : public CObject 
{
	//持失切,社瑚切
public:
	Ob_TextBox(void);
	~Ob_TextBox(void);

	
private:
	COLORREF m_color;
	int think;
	int pattennum;
	int ObNum;
	CPoint m_PrePoint;
	CPoint m_NextPoint;

public:
	COLORREF GetColor(void);
	bool SetColor(COLORREF color);
	int GetThinks(void);
	bool SetThinks(void);
	bool MoveAll(int move_X, int move_Y);
	
	bool SetPrePoint(CPoint PrePoint);
	bool SetNextPoint(CPoint NextPoint);
	CPoint GetPrePoint(void);
	CPoint GetNextPoint(void);
	int Get_ObNum(void);
private:
};

