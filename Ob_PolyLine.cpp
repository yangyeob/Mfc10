#include "StdAfx.h"
#include "Ob_PolyLine.h"

Ob_PolyLine::Ob_PolyLine(void)
{
	Ob_Num = 2;
	new = 1;
	abc = 1;
	
	m_Lpatt=PS_SOLID;
	m_Lthin=3;
	m_Lcolor=RGB(0,0,0);
	m_Grouped = false;
	pen.CreatePen(m_Lpatt, m_Lthin,m_Lcolor);
}

Ob_PolyLine::~Ob_PolyLine(void)
{
	new = 1;
	abc = 2;
}

Ob_PolyLine::~Ob_PolyLine(void)
{

}
bool Ob_PolyLine::Delete_SubPoint(int pointnum)
{
	POSITION pos;
	pos = List.GetHeadPosition();
	for(int i =0;i < pointnum -1;i++){
		List.GetNext(pos);
	}
	List.RemoveAt(pos);
	return false;
}


bool Ob_PolyLine::MoveAll(int move_X, int move_Y)
{
	POSITION pos;
	pos = List.GetHeadPosition();
	while(pos != NULL){
		List.GetAt(pos).x -= move_X;
		List.GetAt(pos).y -= move_Y;
		List.GetNext(pos);
	}



	return true;
}


bool Ob_PolyLine::Move_SubPoint(int Pointnum, int move_X, int move_Y)
{
	POSITION pos;
	pos = List.GetHeadPosition();
	for(int i =0;i < Pointnum -1;i++){
		List.GetNext(pos);
	}

		List.GetAt(pos).x -= move_X;
		List.GetAt(pos).y -= move_Y;
	
	return true;
}


int Ob_PolyLine::Get_ObNum(void)
{
	return Ob_Num;
}
int Ob_PolyLine::Get_ObCount(void)
{
	return Ob_Count;
}
bool Ob_PolyLine::SetObCount(int count)
{
	Ob_Count = count;
	return true;
}

Ob_PolyLine& Ob_PolyLine::operator=(const Ob_PolyLine& var){

	
	POSITION pos;
	CPoint point;
	//pen
	this->m_Lpatt = var.m_Lpatt;
	this->m_Lthin = var.m_Lthin;
	this->m_Lcolor = var.m_Lcolor;
	this->pen.DeleteObject();
	this->pen.CreatePen(m_Lpatt,m_Lthin,m_Lcolor);

	pos = var.List.GetHeadPosition();
	this->List.RemoveAll();
	while(pos != NULL){
		point = var.List.GetNext(pos);
		this->List.AddTail(point);
	}

	return *this;


}