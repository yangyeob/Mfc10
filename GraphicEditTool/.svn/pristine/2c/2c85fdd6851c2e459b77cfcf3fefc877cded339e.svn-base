#pragma once
#include <afxtempl.h>
class Ob_Line : public CObject
{
	
public:
	int ObNum; //ObNum은 강제 캐스팅을 하므로 위치는 모든 객체가 같아야 한다.(첫번째)
	int Ob_Count;
	bool m_Grouped;
	CList <int> GroupList;
public:
	CPen pen;
	int m_Lpatt;
	int m_Lthin;
	COLORREF m_Lcolor;
	CPoint m_PrePoint;
	CPoint m_NextPoint;

public:
	Ob_Line(void);
	~Ob_Line(void);
	COLORREF GetColor(void);
	bool SetColor(COLORREF color);
	int GetThinks(void);

	bool SetThinks(int);
	bool MoveAll(int move_X, int move_Y);
	bool Move_SubPoint(int Pointnum, int move_X, int move_Y);
	bool SetPrePoint(CPoint PrePoint);
	bool SetNextPoint(CPoint NextPoint);
	int Get_ObCount(void);
	bool SetObCount(int);
	CPoint GetPrePoint(void);
	CPoint GetNextPoint(void);
	int Get_ObNum(void);
	bool RemoveAll(void);
	//CPoint prepoint, nextpoint;
	Ob_Line& operator=(const Ob_Line& var);
private:


};
