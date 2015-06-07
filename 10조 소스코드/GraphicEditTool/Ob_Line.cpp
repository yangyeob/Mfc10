#include "StdAfx.h"
#include "Ob_Line.h"
#include <afxtempl.h>

Ob_Line::Ob_Line(void)
{
	ObNum = 1;
	m_PrePoint = (-1, -1);
	m_NextPoint = (-1, -1);
	
	m_Lpatt=PS_SOLID;
	m_Lthin=3;
	m_Lcolor=RGB(0,0,0);
	m_Grouped = false;
	pen.CreatePen(m_Lpatt, m_Lthin,m_Lcolor);
}


Ob_Line::~Ob_Line(void)
{
}
bool Ob_Line::MoveAll(int move_X, int move_Y)
{
	m_PrePoint.x -= move_X;
	m_PrePoint.y -= move_Y;
	m_NextPoint.x -= move_X;
	m_NextPoint.y -= move_Y;
	return false;
}

bool Ob_Line::Move_SubPoint(int Pointnum, int move_X, int move_Y)
{
	if(Pointnum == 1 ){

	m_PrePoint.x -= move_X;
	m_PrePoint.y -= move_Y;
	}
	else if (Pointnum == 2){
	m_NextPoint.x -= move_X;
	m_NextPoint.y -= move_Y;
	
	
	}
	return true;
}

bool Ob_Line::SetPrePoint(CPoint PrePoint)
{
	m_PrePoint = PrePoint;
	return false;
}


bool Ob_Line::SetNextPoint(CPoint NextPoint)
{
	m_NextPoint = NextPoint;
	return false;
}


CPoint Ob_Line::GetPrePoint(void)
{
		return m_PrePoint;
}


CPoint Ob_Line::GetNextPoint(void)
{
	return m_NextPoint;
}


int Ob_Line::Get_ObNum(void)
{
	return ObNum;
}
int Ob_Line::Get_ObCount(void)
{
	return Ob_Count;
}
bool Ob_Line::SetObCount(int count)
{
	Ob_Count = count;
	return true;
}

Ob_Line& Ob_Line::operator=(const Ob_Line& var){

	this->m_NextPoint = var.m_NextPoint;
	this->m_PrePoint = var.m_PrePoint;
	//pen
	this->m_Lpatt = var.m_Lpatt;
	this->m_Lthin = var.m_Lthin;
	this->m_Lcolor = var.m_Lcolor;
	this->pen.DeleteObject();
	this->pen.CreatePen(m_Lpatt,m_Lthin,m_Lcolor);
	return *this;
}
bool Ob_Line::RemoveAll(void)
{
	m_PrePoint.x = -100;
	m_PrePoint.y=-100;
	m_NextPoint.x=-100;
	m_NextPoint.y=-100;
	return false;
}
