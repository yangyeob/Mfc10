#include "StdAfx.h"
#include "Ob_Elipse.h"


Ob_Elipse::Ob_Elipse(void)
{
	//좌표가 처음에는 안보이도록 -1,-1초기화
	m_x1=-1;
	m_x2=-1;
	m_y1=-1;
	m_y1=-1;
	Ob_Num = 4;
	m_Lpatt=0;
	m_Lthin=3;
	m_Lcolor=RGB(0,0,0);
	m_Grouped = false;
	pen.CreatePen(m_Lpatt, m_Lthin,m_Lcolor);
	m_patt =0;
	m_color = RGB(255,255,255);
	brush.CreateSolidBrush(m_color);
}

Ob_Elipse::~Ob_Elipse(void)
{
}



bool Ob_Elipse::MoveAll(int move_X, int move_Y)
{
	 m_x1 -= move_X;
	 m_x2 -= move_X;
	 m_y1 -= move_Y;
	 m_y2 -= move_Y;
	return true;
}

bool Ob_Elipse::Move_SubPoint(int Pointnum, int move_X, int move_Y)
{
		/* //subtargetcount 배정
		// 1 2 3 
		// 8 x 4
		// 7 6 5
		*/
	switch(Pointnum){
	case 1:
		 m_x1 -= move_X;
		 m_y1 -= move_Y;
		break;
	case 2:
		 m_y1 -= move_Y;
		break;
	case 3:
		 m_y1 -= move_Y;
		 m_x2 -= move_X;
		break;
	case 4:
		 m_x2 -= move_X;
		break;
	case 5:
		m_x2 -= move_X;
		m_y2 -= move_Y;
		break;
	case 6:
		m_y2 -= move_Y;
		break;
	case 7:
		m_x1 -= move_X;
		m_y2 -= move_Y;
		break;
	case 8:
		m_x1 -= move_X;
		break;
	}
	return true;
}
int Ob_Elipse::Get_ObNum(void)
{
	return Ob_Num;
}
int Ob_Elipse::Get_ObCount(void)
{
	return Ob_Count;
}
bool Ob_Elipse::SetObCount(int count)
{
	Ob_Count = count;
	return true;
}

bool Ob_Elipse::RemoveAll(void)
{
	m_x1=-100;
	m_x2=-100;
	m_y1=-100;
	m_y1=-100;
	return false;
}
Ob_Elipse& Ob_Elipse::operator=(const Ob_Elipse &var){
	this->m_x1 = var.m_x1;
	this->m_y1 = var.m_y1;
	this->m_x2 = var.m_x2;
	this->m_y2 = var.m_y2;
	//pen
	this->m_Lpatt = var.m_Lpatt;
	this->m_Lthin = var.m_Lthin;
	this->m_Lcolor = var.m_Lcolor;
	this->pen.DeleteObject();
	this->pen.CreatePen(m_Lpatt,m_Lthin,m_Lcolor);
	//brush
	this->m_patt = var.m_patt;
	this->m_color;
	this->brush.DeleteObject();
	switch(this->m_patt){
		case 0:
			this->brush.CreateSolidBrush(this->m_color);
			break;
		case 1:
		case 2:
			this->brush.CreateHatchBrush(this->m_patt,this->m_color);
			break;
	}
return *this;
}