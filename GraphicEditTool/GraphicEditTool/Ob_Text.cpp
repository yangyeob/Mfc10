#include "StdAfx.h"
#include "Ob_Text.h"
#include <afxtempl.h>

Ob_Text::Ob_Text(void)
{
	Ob_Num = 5;
	m_x1=-1;
	m_x2=-1;
	m_y1=-1;
	m_y1=-1;
	m_font = 1;
	m_fsize = 20;
	m_Grouped = false;
	font.CreateFontA(m_fsize,0,0,0,0,0,0,0,0,0,0,0,0,"�ü�");
	m_fontcolor = RGB(0,0,0);
	m_bkcolor = RGB(255,255,255);
}

Ob_Text::~Ob_Text(void)
{
}

bool Ob_Text::Delete_SubPoint(int pointnum)
{
	return false;
}


bool Ob_Text::MoveAll(int move_X, int move_Y)
{
	 m_x1 -= move_X;
	 m_x2 -= move_X;
	 m_y1 -= move_Y;
	 m_y2 -= move_Y;


	return true;
}


bool Ob_Text::Move_SubPoint(int Pointnum, int move_X, int move_Y)
{
		/* //subtargetcount ����
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


int Ob_Text::Get_ObNum(void)
{
	return Ob_Num;
}
int Ob_Text::Get_ObCount(void)
{
	return Ob_Count;
}
bool Ob_Text::SetObCount(int count)
{
	Ob_Count = count;
	return true;
}

bool Ob_Text::RemoveAll(void)
{
	m_x1=-100;
	m_x2=-100;
	m_y1=-100;
	m_y1=-100;
	return false;
}

Ob_Text& Ob_Text::operator=(const Ob_Text& var){
	this->m_x1 = var.m_x1;
	this->m_y1 = var.m_y1;
	this->m_x2 = var.m_x2;
	this->m_y2 = var.m_y2;
	//�ؽ�Ʈ �κ� �߰�
	this->m_str.RemoveAll();
	for(int i =0;i<var.m_str.GetCount();i++){
	this->m_str.Add(var.m_str.GetAt(i));
	}
	//font & etc
	this->m_fsize = var.m_fsize;
	this->m_font = var.m_font;
	this->m_fontcolor = var.m_fontcolor;
	this->m_bkcolor = var.m_bkcolor;
	CString fstr;
	switch(this->m_font){
			case 1: fstr = "�ü�";
			break;
			case 2: fstr = "����";
			break;
			case 3: fstr = "����";
			break;
			}
	this->font.DeleteObject();
	this->font.CreateFontA(this->m_fsize,0,0,0,0,0,0,0,0,0,0,0,0,fstr);
			
	return *this;
}