#pragma once
#include <afxtempl.h>
class Ob_Rectangle : public CObject 
{
public:
	int Ob_Num;	
	int Ob_Count;
	bool m_Grouped;
	CList <int> GroupList;
	int m_x1, m_x2, m_y1,m_y2;
	CPen pen;
	int m_Lpatt;
	int m_Lthin;
	COLORREF m_Lcolor;
	CBrush brush;
	int m_patt;
	COLORREF m_color;
public:
	Ob_Rectangle(void);
	~Ob_Rectangle(void);
	COLORREF GetColor(void);

	int GetThinks(void);
	int Get_ObNum(void);
	int Get_ObCount(void);
		bool SetColor(COLORREF color);
	bool SetObCount(int);
	bool SetThinks(int);
	bool MoveAll(int move_X, int move_Y);
	bool Move_SubPoint(int Pointnum, int move_X, int move_Y);
	bool RemoveAll(void);
	Ob_Rectangle& operator=(const Ob_Rectangle& var);

};