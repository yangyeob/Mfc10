
// GraphicEditToolView.cpp : CGraphicEditToolView Ŭ������ ����


#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GraphicEditTool.h"
#endif

#include "GraphicEditToolDoc.h"
#include "GraphicEditToolView.h"
#include <afxtempl.h>

#define margin 5 // ���������� ���� ����(Line, PolyLine���� ���)
//������ü include-------------------------------



#ifdef _DEBUG
#define new DEBUG_NEW
#endif




//�ӽ� ������ü -------------------------
Ob_Line *m_Line;
Ob_PolyLine *m_PolyLine;
Ob_Rectangle *m_Rectangle;
Ob_Elipse *m_Elipse;
Ob_Text *m_Text;
//ī�ǿ� ��ü
Ob_Line mC_Line;
Ob_PolyLine mC_PolyLine;
Ob_Rectangle mC_Rectangle;
Ob_Elipse mC_Elipse;
Ob_Text mC_Text;



//int m_x1, m_x2,m_y1,m_y2;

//-------------------------------------------------------------
//����Ʈ�� ������ �ִ� Ŭ������ ���ø����� ���� �� ����. �ֳ��ϸ� 
//���ø����� �� ��� �� ũ�Ⱑ �������̱� ������ ���Ǹ� ���� �� ���� �����̴�.
//���� �� Ŭ������ ���ø����� �ϴ� ���� �ƴ� �� Ŭ������ �ּҸ� ���ø����� �Ͽ��� 
//CPtrList�� ����Ͽ� �������� ����Ʈ ������ ������ �Ѵ�. 
// ���� ���ø� ����Ʈ������ ��� �� ���� �ƴ� Object�� �ּҸ� ����Ʈ�� ����Ͽ���.
// �̷��� �� ��� ������ ��翡 ������� ������� ������ ������ �� �ֱ� ������ 
// ������ ��,�� ������ �����ϱ� �� ������ ���� 
// ��Ÿ �������� ������ �Լ��� �̸��� ���� �� ��� �� ���������� ȿ������ �� �� �ִ�.
//-------------------------------------------------------------





// CGraphicEditToolView
IMPLEMENT_DYNCREATE(CGraphicEditToolView, CView)

BEGIN_MESSAGE_MAP(CGraphicEditToolView, CView)
	ON_COMMAND(ID_SELECT, &CGraphicEditToolView::OnSelect)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_POLYLINE, &CGraphicEditToolView::OnPolyline)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_DELETEKEY, &CGraphicEditToolView::OnDeletekey)
	ON_COMMAND(ID_Red_Ob, &CGraphicEditToolView::OnRedOb)
	ON_COMMAND(ID_Blue_Ob, &CGraphicEditToolView::OnBlueOb)
	ON_COMMAND(ID_Green_Ob, &CGraphicEditToolView::OnGreenOb)
	ON_COMMAND(ID_Red_Line, &CGraphicEditToolView::OnRedLine)
	ON_COMMAND(ID_Green_Line, &CGraphicEditToolView::OnGreenLine)
	ON_COMMAND(ID_Blue_Line, &CGraphicEditToolView::OnBlueLine)
	ON_COMMAND(ID_Normal_Patton, &CGraphicEditToolView::OnNormalPatton)
	ON_COMMAND(ID_Dot_Patton, &CGraphicEditToolView::OnDotPatton)
	ON_COMMAND(ID_Double_Patton, &CGraphicEditToolView::OnDoublePatton)
	ON_COMMAND(ID_3pt_Think, &CGraphicEditToolView::On3ptThink)
	ON_COMMAND(ID_6pt_Think, &CGraphicEditToolView::On6ptThink)
	ON_COMMAND(ID_10pt_Think, &CGraphicEditToolView::On10ptThink)
	ON_COMMAND(ID_elipse, &CGraphicEditToolView::OnElipse)
	ON_COMMAND(ID_rectangle, &CGraphicEditToolView::OnRectangle)
	ON_COMMAND(ID_EDIT_COPY, &CGraphicEditToolView::OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CGraphicEditToolView::OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, &CGraphicEditToolView::OnEditPaste)
	ON_COMMAND(ID_Line, &CGraphicEditToolView::OnLine)
	ON_WM_CHAR()
	ON_COMMAND(ID_TextButton, &CGraphicEditToolView::OnTextbutton)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_patt1, &CGraphicEditToolView::Onpatt1)
	ON_COMMAND(ID_patt2, &CGraphicEditToolView::OnPatt2)
	ON_COMMAND(ID_patt3, &CGraphicEditToolView::OnPatt3)
	ON_COMMAND(ID_fsize10, &CGraphicEditToolView::OnFsize10)
	ON_COMMAND(ID_fsize20, &CGraphicEditToolView::OnFsize20)
	ON_COMMAND(ID_fsize30, &CGraphicEditToolView::OnFsize30)
	ON_COMMAND(ID_fred, &CGraphicEditToolView::OnFred)
	ON_COMMAND(ID_fgreen, &CGraphicEditToolView::OnFgreen)
	ON_COMMAND(ID_fblue, &CGraphicEditToolView::OnFblue)
	ON_COMMAND(ID_fontstyle1, &CGraphicEditToolView::OnFontstyle1)
	ON_COMMAND(ID_fontstyle2, &CGraphicEditToolView::OnFontstyle2)
	ON_COMMAND(ID_fontstyle3, &CGraphicEditToolView::OnFontstyle3)
END_MESSAGE_MAP()

// CGraphicEditToolView ����/�Ҹ�

CGraphicEditToolView::CGraphicEditToolView()
{

	//������ ��� �ʱ�ȭ
	m_Mode = 0;
	m_TargetCount =-1;
	m_ObjectCount =0;
	m_MoveMode = false;
	m_Delete_Ready = -1;
	m_bDrawMode = false;
	m_CopyObNUm = -1;
	m_GroupCount = 1;
	m_SpacePushed = false;
}

CGraphicEditToolView::~CGraphicEditToolView()
{
}

BOOL CGraphicEditToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGraphicEditToolView �׸���

void CGraphicEditToolView::OnDraw(CDC* /*pDC*/)
{
	CGraphicEditToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CGraphicEditToolView ����

#ifdef _DEBUG
void CGraphicEditToolView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicEditToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicEditToolDoc* CGraphicEditToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditToolDoc)));
	return (CGraphicEditToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditToolView �޽��� ó����


void CGraphicEditToolView::OnSelect()
{
	m_Mode = 0;
}





void CGraphicEditToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	
	
	switch(m_Mode){
	case 0:
	


	//����Ʈ����Ʈ ó���κ�
	
			//���콺 �̵��� Ÿ���� ����
			if(m_MoveMode == false){
				m_MoveMode = true;
				
				if(GetObTarget(point)){
				pr_Movepoint = point;

					//------------------------
					//Ŀ�� �ٲٴ� �ڵ� ����.



					//--------------------------
				}
			}
	
			
			if(m_TargetCount >0){

				POSITION pos_Ptr,pos_Ob;
	void * m_Ob_Ptr;
	pos_Ptr = Ob_PtrList.GetHeadPosition();
	
	for(int i=0;i< m_TargetCount;i++){
		m_Ob_Ptr = Ob_PtrList.GetNext(pos_Ptr);
	}	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
	Ob_PolyLine *BLine = (Ob_PolyLine*)m_Ob_Ptr;
	if(BLine->m_Grouped == true&&this->m_SpacePushed !=true){
		int Groupnum = -1;
		if(BLine->GroupList.GetHeadPosition() != NULL){
			Groupnum = BLine->GroupList.GetTail();
		}else{
		BLine->m_Grouped = false;
		break;
		}
		POSITION pos_buf = Ob_PtrList.GetHeadPosition();	
		void * m_Ob_Buf;
		m_MultySelect.RemoveAll();
		while(pos_buf != NULL){
			if(pos_buf == NULL){ break;}
			m_Ob_Buf = Ob_PtrList.GetNext(pos_buf);
			Ob_PolyLine *BufLine = (Ob_PolyLine*)m_Ob_Buf;
			
			if(BufLine->GroupList.GetHeadPosition() ==NULL){break;}
			if(BufLine->GroupList.GetTail() == Groupnum){
				int buf = BufLine->Get_ObCount();
				m_MultySelect.AddTail(buf);
			}
		}
		
		Invalidate();
	}

	
		//���� ���ý� m_MultySelect�� ObCount�� �ִ´�.
		if(m_SpacePushed != false){
			if(m_MultySelect.Find(m_TargetCount) == false){
			m_MultySelect.AddTail(m_TargetCount);
			}
			
				}
	//Ÿ���� ���� ���¿��� Ŭ���� �� ���
			if(PLine->Get_ObNum() == 1){
				//������ ��츸 �ǵ����ϴ� �ڵ� �����ؾ���.
					m_SubTargetCount = GetObSubTarget(point);//<- ���� ����ǵ���
					if(m_SubTargetCount > 0){
						CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
		
					}
				}
				
				if(PLine->Get_ObNum() == 2){
				//���������� ��츸 �ǵ����ϴ� �ڵ� �����ؾ���.
					m_SubTargetCount = GetObSubTarget(point);
					TRACE("�ٿ�m_SubTargetCount%d",m_SubTargetCount);
					if(m_SubTargetCount > 0){
						CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
		
					}
				}
				//Rectangle �� ��� �׵θ��� ���� �������� �ؾ���.
				if(PLine->Get_ObNum() == 3){
					m_SubTargetCount = GetObSubTarget(point);
					if(m_SubTargetCount > 0){
						CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
					}
				}
				//ellipse�� ��� �׵θ� ��������, �׵θ� ���� ���⵵�� �ؾ���.
				if(PLine->Get_ObNum() == 4){
					m_SubTargetCount = GetObSubTarget(point);
					if(m_SubTargetCount > 0){
						CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
					}

				}
				if(PLine->Get_ObNum() == 5){
					m_SubTargetCount = GetObSubTarget(point);
					if(m_SubTargetCount > 0){
						CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						// �ؽ�Ʈ�ڽ� ���� ǥ�� �߰�
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
					}

				}
			
			}else{//if Ÿ���� �����������( == -1);
		
				 if(m_SpacePushed == false){
					//����Ʈ�� �ȴ������¿��� Ŭ���� ������� m_MultySelect�� �ڷᰡ ������
				m_MultySelect.RemoveAll();//���� ������ �͵��� �����.				
				
				}
			}
				break;
			
	case 3:
		
		m_bDrawMode = true;

		m_Rectangle->m_x1 =m_Rectangle->m_x2 = point.x;
		m_Rectangle->m_y1 =m_Rectangle->m_y1=  point.y;

		break;
		
	case 4:
		m_bDrawMode = true;

		m_Elipse->m_x1 = m_Elipse->m_x2 =point.x;
		m_Elipse->m_y1 = m_Elipse->m_y2 = point.y;

		break;
	case 5:
		m_bDrawMode = true;

		m_Text->m_x1 = m_Text->m_x2 =point.x;
		m_Text->m_y1 = m_Text->m_y2 = point.y;

		break;
	case 1:
		
			m_Line->SetPrePoint(point);

		break;
	//�������� �۾�
	case 2:
		
		m_PolyLine->List.AddTail(point);
		POSITION pos = m_PolyLine->List.GetHeadPosition();
		CPoint prpoint;
		CPoint nextpoint;
		if(pos!=NULL){
			nextpoint = m_PolyLine->List.GetNext(pos);}
		prpoint = nextpoint;
		while(pos !=NULL){
			nextpoint = m_PolyLine->List.GetNext(pos);
			dc.SelectObject(m_PolyLine->pen);
			dc.MoveTo(prpoint);             
			dc.LineTo(nextpoint); 
			prpoint = nextpoint;
		}



		break;

	
}
	
	}




void CGraphicEditToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);

switch(m_Mode){
	//���콺 �̵��� Ÿ�� �۾�
	case 0:
		if(m_TargetCount != -1&&m_MoveMode){
			//Ÿ���� ������ ��� �̵�ó��,�̵������ ��츸 
	POSITION pos;
	void * m_Ob_Ptr;
	pos = Ob_PtrList.GetHeadPosition();
	for(int i =0; i < m_TargetCount ;i++){
		m_Ob_Ptr = Ob_PtrList.GetNext(pos);
	}
	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
	CPoint MovePoint = pr_Movepoint-point;
	Ob_PolyLine *BLine = (Ob_PolyLine*)m_Ob_Ptr;
	//m_SubTargetCount = GetObSubTarget(point);
	TRACE("\n����m_SubTargetCount %d ",m_SubTargetCount);
	int groupnum;
	if(PLine->m_Grouped == true&&m_SpacePushed != true){//�׷� ���� �����϶�, �׷��߰����� �ƴҰ��
		groupnum = -1;
		if(BLine->GroupList.GetHeadPosition() != NULL){
			groupnum = BLine->GroupList.GetTail();
		}else{
		BLine->m_Grouped = false;
		break;
		}
		pos = Ob_PtrList.GetHeadPosition();
		for(int i =0; i < m_ObjectCount ;i++){
		m_Ob_Ptr = Ob_PtrList.GetNext(pos);
		PLine = (Ob_PolyLine*)m_Ob_Ptr;
		if(PLine->GroupList.GetHeadPosition() == NULL){
		break;
		}
		if(PLine->GroupList.GetHeadPosition()==NULL){break;}
		int buf = PLine->GroupList.GetTail();

		if(groupnum == buf){
	
			if(PLine->Get_ObNum() == 1){
				Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
			if(m_SubTargetCount<0){
				PLine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				PLine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
			}
			if(PLine->Get_ObNum() == 2){
				if(m_SubTargetCount<0){
				PLine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				PLine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
			}
			if(PLine->Get_ObNum() == 3){
				Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
				if(m_SubTargetCount<0){
				RLine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				RLine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
			}
			if(PLine->Get_ObNum() == 4){
				Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
				if(m_SubTargetCount<0){
				ELine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				ELine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
			}
			if(PLine->Get_ObNum() == 5){
				Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
				if(m_SubTargetCount<0){
				TLine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				TLine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
			}
			
		}
		
		
		}//for
			pr_Movepoint = point;
			Invalidate();
	
	}//if
	if(PLine->m_Grouped != true){//�׷� ������ �����϶�
	//Ÿ���� ���� ���¿��� Ŭ���� �� ���
	if(PLine->Get_ObNum() == 1){
		Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
			if(m_SubTargetCount<0){
				Line->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				Line->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
		}
		if(PLine->Get_ObNum() == 2){
			if(m_SubTargetCount<0){
				PLine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				PLine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
		}

		if(PLine->Get_ObNum() == 3){
			Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
			if(m_SubTargetCount<0){
				RLine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				RLine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}

		}
		if(PLine->Get_ObNum() == 4){
			Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
			if(m_SubTargetCount<0){
				ELine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				ELine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
		}
		if(PLine->Get_ObNum() == 5){
			Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
			if(m_SubTargetCount<0){
				TLine->MoveAll(MovePoint.x,MovePoint.y);
			}else{
				TLine->Move_SubPoint(m_SubTargetCount,MovePoint.x,MovePoint.y);
			}
		}

	pr_Movepoint = point;
	Invalidate();
	}//if grouped false
		}


		break;
	case 1:
		if(m_Line ->GetPrePoint().x != -1)
		{
			dc.SetROP2(R2_NOT);
			
			if(m_Line -> GetNextPoint().x != -1)
			{
				dc.SelectObject(m_Line->pen);
				dc.MoveTo(m_Line -> GetPrePoint());
				dc.LineTo(m_Line -> GetNextPoint());
			}
			m_Line -> SetNextPoint(point);
			dc.SetROP2(R2_NOT);
			dc.SelectObject(m_Line->pen);
			dc.MoveTo(m_Line -> GetPrePoint());
			dc.LineTo(m_Line -> GetNextPoint());
		}

		break;
	//Rectangle �۾�
	case 3:
		if(m_Rectangle->m_x1 !=-1){
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
		dc.Rectangle(m_Rectangle->m_x1, m_Rectangle->m_y1,m_Rectangle->m_x2,m_Rectangle->m_y2);
		//dc.SelectObject(m_Rectangle->brush);
		//dc.SelectObject(m_Rectangle->pen);
		m_Rectangle->m_x2 = point.x;
		m_Rectangle->m_y2 = point.y;
		dc.Rectangle(m_Rectangle->m_x1,m_Rectangle->m_y1,m_Rectangle->m_x2,m_Rectangle->m_y2);
		}
		break;
	//Ellipe �۾�
	case 4:
		if(m_Elipse->m_x1 !=-1){
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
		dc.Ellipse(m_Elipse->m_x1, m_Elipse->m_y1,m_Elipse->m_x2,m_Elipse->m_y2);
		//dc.SelectObject(m_Rectangle->brush);
		//dc.SelectObject(m_Rectangle->pen);
		m_Elipse->m_x2 = point.x;
		m_Elipse->m_y2 = point.y;
		dc.Ellipse(m_Elipse->m_x1,m_Elipse->m_y1,m_Elipse->m_x2,m_Elipse->m_y2);
		}
		break;
	//Text �۾�
	case 5:
		if(m_Text->m_x1 !=-1){
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_NOT);
			dc.Rectangle(m_Text->m_x1, m_Text->m_y1,m_Text->m_x2,m_Text->m_y2);
			m_Text->m_x2 = point.x;
			m_Text->m_y2 = point.y;
			dc.Rectangle(m_Text->m_x1,m_Text->m_y1,m_Text->m_x2,m_Text->m_y2);
		}
		break;
	//�������� �۾�
	case 2:
		CPoint prpoint;
		CPoint nextpoint;
		POSITION pos;
		//----------------------------------------------------------
		// ó���� ���������� �׸��� �Ҷ� �������ڸ��� 
		// ���������� ��ǥ�� �ϳ��� ���� ���¿��� GetPrev �� �ϸ� ���� ����� ��ǥ�� �ҷ����� �ϹǷ� ������ �����.
		// ���� ������ ��������� �۾��� ��ǥ�� ��� 2�� ������,
		// ���� ������ �׸��� �۾��� ��ǥ�� ���1�� ������ �����ϵ��� ó�����ش�.
		// �̶� �Էµ� ��ǥ�� ���� m_PolyLine->List.GetCount()�� ���Ͽ� ����.
		//----------------------------------------------------------
		//���� ���� �����
		if(m_PolyLine->List.GetCount() > 1){
		pos = m_PolyLine->List.GetTailPosition();
		nextpoint = m_PolyLine->List.GetPrev(pos);
		prpoint = m_PolyLine->List.GetPrev(pos);
		dc.SetROP2(R2_NOT);
		dc.SelectObject(m_PolyLine->pen);
		dc.MoveTo(prpoint);             
		dc.LineTo(nextpoint); 
		m_PolyLine->List.RemoveTail();
		}
		//���ο� ���� �׸���
		if(m_PolyLine->List.GetCount() > 0){
		m_PolyLine->List.AddTail(point);
		pos = m_PolyLine->List.GetTailPosition();
		nextpoint = m_PolyLine->List.GetPrev(pos);
		prpoint = m_PolyLine->List.GetPrev(pos);
		dc.SetROP2(R2_NOT);
		dc.SelectObject(m_PolyLine->pen);
		dc.MoveTo(prpoint);             
		dc.LineTo(nextpoint); 
		}

		break;
	
	
	
	}
}




void CGraphicEditToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	CClientDC dc(this);
	
	switch(m_Mode){
	case 0:

		//�������� ���� �� Ŭ�� ������
		m_MoveMode = false;
		if(m_SubTargetCount >0){
		m_Delete_Ready = m_SubTargetCount;
		}else{
		m_Delete_Ready = -1;
		}
		
		m_SubTargetCount = -1 ;
		Invalidate();
	break;
	//�������� �۾�
	case 1:
		m_Line->SetNextPoint(point);
		m_Line->SetObCount(++m_ObjectCount);
		Ob_PtrList.AddTail(m_Line);
		m_Mode = 0;
		Invalidate();
		break;
	case 2:
		break;
	case 3:
		//dc.SelectStockObject(NULL_BRUSH);
		//dc.SetROP2(R2_COPYPEN);

		m_Rectangle->m_x2 = point.x;
		m_Rectangle->m_y2 = point.y;
		//dc.Rectangle(m_x1, m_y1, m_x2, m_y2);
		
		m_Rectangle->SetObCount(++m_ObjectCount);
		Ob_PtrList.AddTail(m_Rectangle);
		m_Mode = 0;
		Invalidate();
		break;

	case 4:
		//dc.SelectStockObject(NULL_BRUSH);
		//dc.SetROP2(R2_COPYPEN);

		m_Elipse->m_x2 = point.x;
		m_Elipse->m_y2 = point.y;
		//dc.Ellipse(m_x1, m_y1, m_x2, m_y2);

		m_Elipse->SetObCount(++m_ObjectCount);
		Ob_PtrList.AddTail(m_Elipse);
		m_Mode = 0;
		Invalidate();
		break;
	
	case 5:
		//dc.SelectStockObject(NULL_BRUSH);
		//dc.SetROP2(R2_COPYPEN);
		Invalidate();
		m_Text->m_x2 = point.x;
		m_Text->m_y2 = point.y;
		//dc.Rectangle(m_x1, m_y1, m_x2, m_y2);
		m_Text->SetObCount(++m_ObjectCount);
		Ob_PtrList.AddTail(m_Text);
		m_Mode = 0;
		m_TargetCount = m_ObjectCount;
		Invalidate();
	break;
	
	}
}
void CGraphicEditToolView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	
	switch(m_Mode){
	//�������� �۾�
	case 2:
		//����Ŭ���� Ŭ�� �� �� Ŭ���̱� ������
		//����Ʈ�� �ϳ� �� ����. ����
		//�� ������ ����Ʈ����Ʈ ��������.
		m_PolyLine->List.RemoveTail();
		m_PolyLine->SetObCount(++m_ObjectCount);
		Ob_PtrList.AddTail(m_PolyLine);
		m_Mode = 0;
		Invalidate();
		break;
	
	}

	CView::OnLButtonDblClk(nFlags, point);
}

void CGraphicEditToolView::OnPolyline()
{
	m_Mode = 2;
	//m_PolyLine->List.RemoveAll();
	m_PolyLine = new Ob_PolyLine;

	
}





void CGraphicEditToolView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	POSITION pos_Ptr,pos_Ob;
	CPoint point,prpoint;
	void * m_Ob_Ptr;

	//����Ʈ����Ʈ ó���κ�
	pos_Ptr = Ob_PtrList.GetHeadPosition();
	while(pos_Ptr !=NULL){
		m_Ob_Ptr = Ob_PtrList.GetNext(pos_Ptr);

	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;

	//���� �׸���
		if(PLine->Get_ObNum() == 1){
				Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
				if(Line->GetNextPoint().x != -1){
				dc.SelectObject(Line->pen);
				dc.MoveTo(Line->GetPrePoint());             
				dc.LineTo(Line->GetNextPoint()); 
				}
		}

	// ���� �������� �׸���
		if(PLine->Get_ObNum() == 2){
			pos_Ob = PLine->List.GetHeadPosition();
			if(pos_Ob!=NULL){
				point = PLine->List.GetNext(pos_Ob);}
			prpoint = point;
			dc.SelectObject(PLine->pen);
			while(pos_Ob !=NULL){
				point = PLine->List.GetNext(pos_Ob);
				dc.MoveTo(prpoint);             
				dc.LineTo(point); 
				prpoint = point;
			}
		}
	//Rect �׸��� 
				
			if(PLine->Get_ObNum() == 3){
				Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
				//dc.SelectStockObject(NULL_BRUSH);
				dc.SelectObject(RLine->pen);
				dc.SelectObject(RLine->brush);
				dc.Rectangle(RLine->m_x1,RLine->m_y1,RLine->m_x2,RLine->m_y2);
			}
				
	//Ellipse �׸���
			if(PLine->Get_ObNum() == 4){
				Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
				//dc.SelectStockObject(NULL_BRUSH);
				dc.SelectObject(ELine->pen);
				dc.SelectObject(ELine->brush);
				dc.Ellipse(ELine->m_x1,ELine->m_y1,ELine->m_x2,ELine->m_y2);
			}


	//Text �׸���
			if(PLine->Get_ObNum() == 5){
				CRect rect;
				Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
				CPen pen(2,1,RGB(0,0,0));
				dc.SelectObject(&pen); 
				dc.SelectStockObject(NULL_BRUSH);
				rect.SetRect(TLine->m_x1,TLine->m_y1,TLine->m_x2,TLine->m_y2);
				if(m_TargetCount == TLine->Get_ObCount()){
				dc.Rectangle(TLine->m_x1,TLine->m_y1,TLine->m_x2,TLine->m_y2);
				}
				dc.SelectObject(TLine->font);
				dc.SetTextColor(TLine->m_fontcolor);
				dc.SetBkColor(TLine->m_bkcolor);
				dc.DrawText(TLine->m_str.GetData(),TLine->m_str.GetSize(),&rect,DT_LEFT);
				dc.SetBkColor(RGB(255,255,255));
			}	
				
			

	}//���� Ob List�� while
	
	
	//------------------------------------
	//���ø�忡�� ���ý� 
	switch(m_Mode){
	case 0:
		CPen pen(0,1,RGB(0,0,0));
		dc.SelectObject(&pen);
		//Ÿ���� ������ ������� break
		if(m_TargetCount == -1){
		break;
		}
		POSITION pos;
		pos = Ob_PtrList.GetHeadPosition();
		for(int i=0;i<m_TargetCount;i++){
			m_Ob_Ptr = Ob_PtrList.GetNext(pos);
		}

	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
	//�׵θ� �����
	if(PLine->m_Grouped == false){
	//����
	if(PLine->Get_ObNum() == 1){
		Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
				dc.SelectStockObject(WHITE_BRUSH);
				dc.Ellipse(Line->GetPrePoint().x-6,Line->GetPrePoint().y+6,Line->GetPrePoint().x+6,Line->GetPrePoint().y-6);
				dc.Ellipse(Line->GetNextPoint().x-6,Line->GetNextPoint().y+6,Line->GetNextPoint().x+6,Line->GetNextPoint().y-6);

		if(m_TargetCount >0){
				//Ÿ���� ���� ���¿��� Ŭ���� �� ���
				//TRACE("�ٿ�m_SubTargetCount%d",m_SubTargetCount);
					if(m_SubTargetCount > 0){
						CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						m_SubTargetCount = GetObSubTarget(SubTarget);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
						dc.SelectStockObject(NULL_BRUSH);
					}
				}
	}
	//��������
	if(PLine->Get_ObNum() == 2){
		CPoint point;
			pos = PLine->List.GetHeadPosition();
			while(pos !=NULL){
				point = PLine->List.GetNext(pos);
				dc.SelectStockObject(WHITE_BRUSH);
				dc.Ellipse(point.x-6,point.y+6,point.x+6,point.y-6);
			}
		if(m_TargetCount >0){
				//Ÿ���� ���� ���¿��� Ŭ���� �� ���
				//m_SubTargetCount = GetObSubTarget(point);
				//TRACE("�ٿ�m_SubTargetCount%d",m_SubTargetCount);
					if(m_SubTargetCount > 0){
						CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						m_SubTargetCount = GetObSubTarget(SubTarget);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
						dc.SelectStockObject(NULL_BRUSH);
					}
				}
		}
	//rectangle
	if(PLine->Get_ObNum() == 3){
		Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
		dc.SelectStockObject(WHITE_BRUSH);
		dc.Ellipse(RLine->m_x1-6,RLine->m_y1+6,RLine->m_x1+6,RLine->m_y1-6); // x1,y1
		dc.Ellipse(RLine->m_x2-6,RLine->m_y2+6,RLine->m_x2+6,RLine->m_y2-6); // x2,y2
		dc.Ellipse(RLine->m_x1-6,RLine->m_y2+6,RLine->m_x1+6,RLine->m_y2-6); // x1,y2
		dc.Ellipse(RLine->m_x2-6,RLine->m_y1+6,RLine->m_x2+6,RLine->m_y1-6); // x2,y1
		dc.Ellipse(((RLine->m_x1+RLine->m_x2)/2)-6,RLine->m_y1+6,((RLine->m_x1+RLine->m_x2)/2)+6,RLine->m_y1-6); // (x1+x2)/2,y1
		dc.Ellipse(((RLine->m_x1+RLine->m_x2)/2)-6,RLine->m_y2+6,((RLine->m_x1+RLine->m_x2)/2)+6,RLine->m_y2-6); // (x1+x2)/2,y2
		dc.Ellipse(RLine->m_x1-6,((RLine->m_y1+RLine->m_y2)/2)+6,RLine->m_x1+6,((RLine->m_y1+RLine->m_y2)/2)-6); // x1,(y1+y2)/2
		dc.Ellipse(RLine->m_x2-6,((RLine->m_y1+RLine->m_y2)/2)+6,RLine->m_x2+6,((RLine->m_y1+RLine->m_y2)/2)-6); // x2,(y1+y2)/2
	if(m_TargetCount >0){
				//Ÿ���� ���� ���¿��� Ŭ���� �� ��� : ���°��ü������ �˷��ִ� ī��Ʈ 
		if(m_SubTargetCount > 0){
					CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						m_SubTargetCount = GetObSubTarget(SubTarget);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
						dc.SelectStockObject(NULL_BRUSH);
					}
	}
	
	}
	//ellipse
	if(PLine->Get_ObNum() == 4){
		Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
		dc.SelectStockObject(WHITE_BRUSH);
		dc.Ellipse(ELine->m_x1-6,ELine->m_y1+6,ELine->m_x1+6,ELine->m_y1-6); // x1,y1
		dc.Ellipse(ELine->m_x2-6,ELine->m_y2+6,ELine->m_x2+6,ELine->m_y2-6); // x2,y2
		dc.Ellipse(ELine->m_x1-6,ELine->m_y2+6,ELine->m_x1+6,ELine->m_y2-6); // x1,y2
		dc.Ellipse(ELine->m_x2-6,ELine->m_y1+6,ELine->m_x2+6,ELine->m_y1-6); // x2,y1
		dc.Ellipse(((ELine->m_x1+ELine->m_x2)/2)-6,ELine->m_y1+6,((ELine->m_x1+ELine->m_x2)/2)+6,ELine->m_y1-6); // (x1+x2)/2,y1
		dc.Ellipse(((ELine->m_x1+ELine->m_x2)/2)-6,ELine->m_y2+6,((ELine->m_x1+ELine->m_x2)/2)+6,ELine->m_y2-6); // (x1+x2)/2,y2
		dc.Ellipse(ELine->m_x1-6,((ELine->m_y1+ELine->m_y2)/2)+6,ELine->m_x1+6,((ELine->m_y1+ELine->m_y2)/2)-6); // x1,(y1+y2)/2
		dc.Ellipse(ELine->m_x2-6,((ELine->m_y1+ELine->m_y2)/2)+6,ELine->m_x2+6,((ELine->m_y1+ELine->m_y2)/2)-6); // x2,(y1+y2)/2
		CPen pen;
		pen.CreatePen(2, 1, RGB(0, 0, 0));
		//���� rectangle ����ֱ�
		dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(ELine->m_x1,ELine->m_y1,ELine->m_x2,ELine->m_y2);

		if(m_TargetCount >0){
				//Ÿ���� ���� ���¿��� Ŭ���� �� ��� : ���°��ü������ �˷��ִ� ī��Ʈ 
		if(m_SubTargetCount > 0){
					CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						m_SubTargetCount = GetObSubTarget(SubTarget);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
					}
	}
	}
	//text
	if(PLine->Get_ObNum() == 5){
		Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
		dc.SelectStockObject(WHITE_BRUSH);
		dc.Ellipse(TLine->m_x1-6,TLine->m_y1+6,TLine->m_x1+6,TLine->m_y1-6); // x1,y1
		dc.Ellipse(TLine->m_x2-6,TLine->m_y2+6,TLine->m_x2+6,TLine->m_y2-6); // x2,y2
		dc.Ellipse(TLine->m_x1-6,TLine->m_y2+6,TLine->m_x1+6,TLine->m_y2-6); // x1,y2
		dc.Ellipse(TLine->m_x2-6,TLine->m_y1+6,TLine->m_x2+6,TLine->m_y1-6); // x2,y1
		dc.Ellipse(((TLine->m_x1+TLine->m_x2)/2)-6,TLine->m_y1+6,((TLine->m_x1+TLine->m_x2)/2)+6,TLine->m_y1-6); // (x1+x2)/2,y1
		dc.Ellipse(((TLine->m_x1+TLine->m_x2)/2)-6,TLine->m_y2+6,((TLine->m_x1+TLine->m_x2)/2)+6,TLine->m_y2-6); // (x1+x2)/2,y2
		dc.Ellipse(TLine->m_x1-6,((TLine->m_y1+TLine->m_y2)/2)+6,TLine->m_x1+6,((TLine->m_y1+TLine->m_y2)/2)-6); // x1,(y1+y2)/2
		dc.Ellipse(TLine->m_x2-6,((TLine->m_y1+TLine->m_y2)/2)+6,TLine->m_x2+6,((TLine->m_y1+TLine->m_y2)/2)-6); // x2,(y1+y2)/2
	if(m_TargetCount >0){
				//Ÿ���� ���� ���¿��� Ŭ���� �� ��� : ���°��ü������ �˷��ִ� ī��Ʈ 
		if(m_SubTargetCount > 0){
					CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						m_SubTargetCount = GetObSubTarget(SubTarget);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
					}
	}
	}
	}else{//�׷�ȭ�� ��ü�� ���õ� ���̸�
		dc.SelectStockObject(WHITE_BRUSH);
		//GetMultyRgnRect(&p1,&p2);
		dc.Ellipse(p1.x-6,p1.y+6,p1.x+6,p1.y-6); // x1,y1
		dc.Ellipse(p2.x-6,p2.y+6,p2.x+6,p2.y-6); // x2,y2
		dc.Ellipse(p1.x-6,p2.y+6,p1.x+6,p2.y-6); // x1,y2
		dc.Ellipse(p2.x-6,p1.y+6,p2.x+6,p1.y-6); // x2,y1
		dc.Ellipse(((p1.x+p2.x)/2)-6,p1.y+6,((p1.x+p2.x)/2)+6,p1.y-6); // (x1+x2)/2,y1
		dc.Ellipse(((p1.x+p2.x)/2)-6,p2.y+6,((p1.x+p2.x)/2)+6,p2.y-6); // (x1+x2)/2,y2
		dc.Ellipse(p1.x-6,((p1.y+p2.y)/2)+6,p1.x+6,((p1.y+p2.y)/2)-6); // x1,(y1+y2)/2
		dc.Ellipse(p2.x-6,((p1.y+p2.y)/2)+6,p2.x+6,((p1.y+p2.y)/2)-6); // x2,(y1+y2)/2
		if(m_SubTargetCount > 0){
					CBrush brush(RGB(0,0,0));
						dc.SelectObject(&brush);
						m_SubTargetCount = GetObSubTarget(SubTarget);
						dc.Ellipse(SubTarget.x-2,SubTarget.y-2,SubTarget.x+2,SubTarget.y+2);
					}

}

	if(m_MultySelect.GetHeadPosition() != NULL){//���õ� �������� ��ü�� ������.
		
		dc.SelectStockObject(NULL_BRUSH);
		p1.SetPoint(10000 ,10000);//maxrect.bottom);
		p2.SetPoint(-1,-1);
		GetMultyRgnRect(&p1,&p2);
		CPen pen(2,1,RGB(0,0,0));
		dc.SelectObject(&pen);
		dc.Rectangle(p1.x,p1.y,p2.x,p2.y);
		pen.DeleteObject();
		pen.CreatePen(0,1,RGB(0,0,0));
		dc.SelectObject(&pen);

	}


		break;//case0
	}//switch
}

BOOL CGraphicEditToolView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CView::OnEraseBkgnd(pDC);
	//return false;
}


bool CGraphicEditToolView::GetObTarget(CPoint point)
{
	CClientDC dc(this);
	if(m_Mode == 0){
	
	POSITION pos_Ptr,pos_Ob;
	CPoint nextpoint,prpoint;
	CRgn MainRgn,buf;;
	MainRgn.CreateRectRgn(0,0,0,0);
	void * m_Ob_Ptr;
	pos_Ptr = Ob_PtrList.GetTailPosition();
	while(pos_Ptr !=NULL){
		m_Ob_Ptr = Ob_PtrList.GetPrev(pos_Ptr);


	//ó������ ObNum Ȯ���� ���Ͽ� polyline��ü�� ����־��.
	//������ Get_ObNum()�� �Լ��̸��� ���� �Ͽ����Ƿ� 
	//Ȯ�� �� �ٸ� ��ü�� �ٲ۴�.
	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
	
	//���ο�������
	if(PLine->Get_ObNum() == 1){
				Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;

				//------------------
				//���ο��� �յ� �� ���� ������ ��Ȳ
				//nStyle: ALTERNATE(���� ä��) or WINDING (�׵θ�)
				CRgn rgn;
				CPoint pt[4] = {
					CPoint(Line->GetPrePoint().x+margin,Line->GetPrePoint().y+margin),
					CPoint(Line->GetNextPoint().x+margin,Line->GetNextPoint().y+margin),
					CPoint(Line->GetNextPoint().x-margin,Line->GetNextPoint().y-margin),
					CPoint(Line->GetPrePoint().x-margin,Line->GetPrePoint().y-margin),
				};
				rgn.CreatePolygonRgn( pt, 4, ALTERNATE);
				MainRgn.CombineRgn(&MainRgn, &rgn, RGN_OR);
					pt[0]=	CPoint(Line->GetPrePoint().x-margin,Line->GetPrePoint().y+margin);
					pt[1]=	CPoint(Line->GetNextPoint().x-margin,Line->GetNextPoint().y+margin);
					pt[2]=	CPoint(Line->GetNextPoint().x+margin,Line->GetNextPoint().y-margin);
					pt[3]=	CPoint(Line->GetPrePoint().x+margin,Line->GetPrePoint().y-margin);
				rgn.DeleteObject();
				rgn.CreatePolygonRgn( pt, 4, ALTERNATE);
				//MainRgn.DeleteObject();
				MainRgn.CombineRgn(&MainRgn, &rgn, RGN_OR);
				if(Line->m_Grouped == true){
					buf.DeleteObject();
					buf.CreateRectRgn(p1.x-20,p1.y-20,p2.x+20,p2.y+20);
					MainRgn.CombineRgn(&MainRgn, &buf, RGN_OR);
				}
				//------------------------------------
					if(PtInRegion(MainRgn,point.x,point.y) == true){
				m_TargetCount = Line->Get_ObCount();
				/*���� �׽�Ʈ*/
				//CBrush brush(RGB(0,0,0));
				//dc.FillRgn(&MainRgn,&brush);
				//---------------------------------
				return true;
			}else{
			m_TargetCount = -1;
			}
			}

		//�������� ���� ����
		if(PLine->Get_ObNum() == 2){
			pos_Ob = PLine->List.GetHeadPosition();
			if(pos_Ob!=NULL){
				nextpoint = PLine->List.GetNext(pos_Ob);}
			prpoint = nextpoint;
			while(pos_Ob !=NULL){
				nextpoint = PLine->List.GetNext(pos_Ob);
				//------------------
				//�������ο��� �յ� �� ���� ������ ��Ȳ
				//nStyle: ALTERNATE(���� ä��) or WINDING (�׵θ�)
				CRgn rgn;
				CPoint pt[4] = {
					CPoint(prpoint.x+margin,prpoint.y+margin),
					CPoint(nextpoint.x+margin,nextpoint.y+margin),
					CPoint(nextpoint.x-margin,nextpoint.y-margin),
					CPoint(prpoint.x-margin,prpoint.y-margin),
				};
				rgn.CreatePolygonRgn( pt, 4, ALTERNATE);
				MainRgn.CombineRgn(&MainRgn, &rgn, RGN_OR);

				pt[0]=	CPoint(prpoint.x-margin,prpoint.y+margin);
				pt[1]=	CPoint(nextpoint.x-margin,nextpoint.y+margin);
				pt[2]=	CPoint(nextpoint.x+margin,nextpoint.y-margin);
				pt[3]=	CPoint(prpoint.x+margin,prpoint.y-margin);
				rgn.DeleteObject();
				rgn.CreatePolygonRgn( pt, 4, ALTERNATE);
				//MainRgn.DeleteObject();
				MainRgn.CombineRgn(&MainRgn, &rgn, RGN_OR);
				if(PLine->m_Grouped == true){
					buf.DeleteObject();
					buf.CreateRectRgn(p1.x-20,p1.y-20,p2.x+20,p2.y+20);
					MainRgn.CombineRgn(&MainRgn, &buf, RGN_OR);
				}
				//------------------------------------
				prpoint = nextpoint;
			}

			if(PtInRegion(MainRgn,point.x,point.y) == true){
				m_TargetCount = PLine->Get_ObCount();
				/*���� �׽�Ʈ*/
				//CBrush brush(RGB(0,0,0));
				//dc.FillRgn(&MainRgn,&brush);
				//---------------------------------
				return true;
			}else{
			m_TargetCount = -1;
			}
		}//�������ο������� ��

		//Rectangle ��������
		if(PLine->Get_ObNum() == 3){
				Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
				CRgn rgn_out,rgn_inner,Rectrgn;
				Rectrgn.CreateRectRgn(0,0,0,0);
				rgn_out.CreateRectRgn(RLine->m_x1-10,RLine->m_y1-10,RLine->m_x2+10,RLine->m_y2+10);
				//rgn_inner.CreateRectRgn(RLine->m_x1+10,RLine->m_y1+10,RLine->m_x2-10,RLine->m_y2-10);
				//MainRgn.DeleteObject();
				Rectrgn.CombineRgn(&Rectrgn,&rgn_out,RGN_OR);
				if(RLine->m_Grouped == true){
					buf.DeleteObject();
					buf.CreateRectRgn(p1.x-20,p1.y-20,p2.x+20,p2.y+20);
					Rectrgn.CombineRgn(&Rectrgn, &buf, RGN_OR);
				}
				//Rectrgn.CombineRgn(&Rectrgn,&rgn_inner,RGN_XOR);
				/*���� �׽�Ʈ*/
				//CBrush brush(RGB(0,0,0));
				//dc.FillRgn(&Rectrgn,&brush);
				//---------------------------------
				if(PtInRegion(Rectrgn,point.x,point.y) == true){
				m_TargetCount = RLine->Get_ObCount();
				/*���� �׽�Ʈ*/
				//CBrush brush(RGB(0,0,0));
				//	dc.FillRgn(&RectRgn,&brush);
				//---------------------------------
				return true;
			}else{
			m_TargetCount = -1;
			}
		}//Rectangle ���� ���� ��
		

		//Ellipse ��������
		if(PLine->Get_ObNum() == 4){
			
				Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
				CRgn rgn_out,rgn_inner,Elliprgn;
				Elliprgn.CreateRectRgn(0,0,0,0);
				rgn_out.CreateEllipticRgn(ELine->m_x1 -10,ELine->m_y1-10,ELine->m_x2+10,ELine->m_y2+10);
				//rgn_inner.CreateEllipticRgn(ELine->m_x1 +10,ELine->m_y1+10,ELine->m_x2-10,ELine->m_y2-10);
				Elliprgn.CombineRgn(&Elliprgn,&rgn_out,RGN_OR);
				//Elliprgn.CombineRgn(&Elliprgn,&rgn_inner,RGN_XOR);
				if(m_TargetCount>0){
				CRgn rgn_out,rgn_inner,Rectrgn;
				Rectrgn.CreateRectRgn(0,0,0,0);
				rgn_out.CreateRectRgn(ELine->m_x1-10,ELine->m_y1-10,ELine->m_x2+10,ELine->m_y2+10);
				//rgn_inner.CreateRectRgn(ELine->m_x1+10,ELine->m_y1+10,ELine->m_x2-10,ELine->m_y2-10);
				//MainRgn.DeleteObject();
				Rectrgn.CombineRgn(&Rectrgn,&rgn_out,RGN_OR);
				//Rectrgn.CombineRgn(&Rectrgn,&rgn_inner,RGN_XOR);
				Elliprgn.CombineRgn(&Elliprgn,&Rectrgn,RGN_OR);
				if(ELine->m_Grouped == true){
					buf.DeleteObject();
					buf.CreateRectRgn(p1.x-20,p1.y-20,p2.x+20,p2.y+20);
					Elliprgn.CombineRgn(&Elliprgn, &buf, RGN_OR);
				}
			}
				/*���� �׽�Ʈ*/
				
				//---------------------------------
				if(PtInRegion(Elliprgn,point.x,point.y) == true){
				m_TargetCount = ELine->Get_ObCount();
				//CBrush brush(RGB(0,0,0));
				//dc.FillRgn(&Elliprgn,&brush);
				return true;
			}else{
			m_TargetCount = -1;
			}
		}//Ellipse ���� ���� ��
		if(PLine->Get_ObNum() == 5){
				Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
				CRgn rgn_out,/*rgn_inner,*/Rectrgn;
				Rectrgn.CreateRectRgn(0,0,0,0);
				rgn_out.CreateRectRgn(TLine->m_x1-10,TLine->m_y1-10,TLine->m_x2+10,TLine->m_y2+10);
				//rgn_inner.CreateRectRgn(TLine->m_x1+10,TLine->m_y1+10,TLine->m_x2-10,TLine->m_y2-10);
				//MainRgn.DeleteObject();
				Rectrgn.CombineRgn(&Rectrgn,&rgn_out,RGN_OR);
					if(TLine->m_Grouped == true){
					buf.DeleteObject();
					buf.CreateRectRgn(p1.x-20,p1.y-20,p2.x+20,p2.y+20);
					Rectrgn.CombineRgn(&Rectrgn, &buf, RGN_OR);
				}
				//Rectrgn.CombineRgn(&Rectrgn,&rgn_inner,RGN_XOR);
				/*���� �׽�Ʈ*/
				//CBrush brush(RGB(0,0,0));
				//dc.FillRgn(&Rectrgn,&brush);
				//---------------------------------
				if(PtInRegion(Rectrgn,point.x,point.y) == true){
				m_TargetCount = TLine->Get_ObCount();
				/*���� �׽�Ʈ*/
				//CBrush brush(RGB(0,0,0));
				//	dc.FillRgn(&RectRgn,&brush);
				//---------------------------------
				return true;
			}else{
			m_TargetCount = -1;
			}
		}//Text ���� ���� ��
		

	



		}//Ob_List ���������� ��� �޾ƿ��� �κ� ��
	}// mode =0 �϶� if


	
	return false;
}


void CGraphicEditToolView::OnDeletekey()
{
	if(m_MoveMode ==true){
	return;//�����̴� ���߿��� DelŰ�� �۵����� �ʵ��� �Ѵ�.
	}
	switch(m_Mode){
	case 0 :

	if(m_TargetCount != -1){
	//Ÿ���� ������ ��� 
	POSITION pos;
	void * m_Ob_Ptr;
	pos = Ob_PtrList.GetHeadPosition();
	for(int i =0; i < m_TargetCount ;i++){
		m_Ob_Ptr = Ob_PtrList.GetNext(pos);
	}


	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
	int groupnum;
	if(PLine->m_Grouped == true){//�׷� ���� �����϶�
		if(PLine->GroupList.GetHeadPosition() == NULL){
		PLine->m_Grouped == false;
			break;
		}
		groupnum = PLine->GroupList.GetTail();
		pos = Ob_PtrList.GetHeadPosition();
		for(int i =0; i < m_ObjectCount ;i++){
		m_Ob_Ptr = Ob_PtrList.GetNext(pos);
	PLine = (Ob_PolyLine*)m_Ob_Ptr;
	if(groupnum == PLine->GroupList.GetTail()){
	
	if(PLine->Get_ObNum() == 1){
		Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
		Line->RemoveAll();
		}
		if(PLine->Get_ObNum() == 2){
			PLine->List.RemoveAll();
		}
		if(PLine->Get_ObNum() == 3){
			Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
				RLine->RemoveAll();
		}
		if(PLine->Get_ObNum() == 4){
			Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
				ELine->RemoveAll();
		}
		if(PLine->Get_ObNum() == 5){
			Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
				TLine->RemoveAll();
		}
	
	}
		}//for
	Invalidate();
	break;
	}//if

	if(PLine->Get_ObNum() == 1){
	Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
	Line->RemoveAll();
	}
	if(PLine->Get_ObNum() == 2){
	if(m_Delete_Ready>0){
		//delete ready����� ��츸 
		//���������� �κ� ����Ʈ ����� �۾�
		PLine->Delete_SubPoint(m_Delete_Ready);
		m_TargetCount = -1;
	}else{
	//delete_Ready ��尡 �ƴҰ�� delete Ű�� ������ 
	//��ü ���� �� ����Ʈ Ű�� ���� ���̹Ƿ� ��ü�� ������ �Ѵ�.
		PLine->List.RemoveAll();
	}
	}
	if(PLine->Get_ObNum() == 3){
	Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
	RLine->RemoveAll();
	}
	if(PLine->Get_ObNum() == 4){
		Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
	ELine->RemoveAll();
	}
	if(PLine->Get_ObNum() ==5){
		Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
	TLine->RemoveAll();
	}
	Invalidate();
		}

		break;
	}
}


int CGraphicEditToolView::GetObSubTarget(CPoint point)
{
	CClientDC dc(this);
	if(m_Mode == 0&&m_TargetCount != -1){
		int count=0;
		CPoint TargetPoint;
		POSITION pos;
		CRgn MainRgn;
		void * m_Ob_Ptr;
		pos = Ob_PtrList.GetHeadPosition();
			for(int i =0; i < m_TargetCount ;i++){
				if(pos!= NULL){
					m_Ob_Ptr = Ob_PtrList.GetNext(pos);}
			}
	
			Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;

			if(PLine->m_Grouped == false){
		if(PLine->Get_ObNum() == 1){
			Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
			TargetPoint = Line->GetPrePoint();
			count ++; // count == 1 ;
			MainRgn.DeleteObject();
			MainRgn.CreateEllipticRgn(TargetPoint.x -10,TargetPoint.y -10,TargetPoint.x +10,TargetPoint.y +10);
			if(PtInRegion(MainRgn,point.x,point.y)){
					SubTarget = TargetPoint;
				return count;
			}
			TargetPoint = Line->GetNextPoint();
			count ++; // count == 2 ;
			MainRgn.DeleteObject();
			MainRgn.CreateEllipticRgn(TargetPoint.x -10,TargetPoint.y -10,TargetPoint.x +10,TargetPoint.y +10);
			if(PtInRegion(MainRgn,point.x,point.y)){
					SubTarget = TargetPoint;
				return count;
			}
		}
		if(PLine->Get_ObNum() == 2){
			pos = PLine->List.GetHeadPosition();
			while(pos!=NULL){
				TargetPoint = PLine->List.GetNext(pos);
				count ++;
				MainRgn.DeleteObject();
				MainRgn.CreateEllipticRgn(TargetPoint.x -10,TargetPoint.y -10,TargetPoint.x +10,TargetPoint.y +10);
			
				if(PtInRegion(MainRgn,point.x,point.y)){
					SubTarget = TargetPoint;
				return count;
				}
			}
		}
		if(PLine->Get_ObNum() == 3){
			Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
			CRgn rgn[8];
			
			rgn[0].CreateEllipticRgn(RLine->m_x1-10,RLine->m_y1+10,RLine->m_x1+10,RLine->m_y1-10); // x1,y1 [1]
			rgn[1].CreateEllipticRgn(((RLine->m_x1+RLine->m_x2)/2)-10,RLine->m_y1+10,((RLine->m_x1+RLine->m_x2)/2)+10,RLine->m_y1-10); // (x1+x2)/2,y1 [2]
			rgn[2].CreateEllipticRgn(RLine->m_x2-10,RLine->m_y1+10,RLine->m_x2+10,RLine->m_y1-10); // x2,y1 [3]
			rgn[3].CreateEllipticRgn(RLine->m_x2-10,((RLine->m_y1+RLine->m_y2)/2)+10,RLine->m_x2+10,((RLine->m_y1+RLine->m_y2)/2)-10); // x2,(y1+y2)/2 [4]
			rgn[4].CreateEllipticRgn(RLine->m_x2-10,RLine->m_y2+10,RLine->m_x2+10,RLine->m_y2-10); // x2,y2 [5]
			rgn[5].CreateEllipticRgn(((RLine->m_x1+RLine->m_x2)/2)-10,RLine->m_y2+10,((RLine->m_x1+RLine->m_x2)/2)+10,RLine->m_y2-10); // (x1+x2)/2,y2 [6]
			rgn[6].CreateEllipticRgn(RLine->m_x1-10,RLine->m_y2+10,RLine->m_x1+10,RLine->m_y2-10); // x1,y2 [7]
			rgn[7].CreateEllipticRgn(RLine->m_x1-10,((RLine->m_y1+RLine->m_y2)/2)+10,RLine->m_x1+10,((RLine->m_y1+RLine->m_y2)/2)-10); // x1,(y1+y2)/2 [8]
		
			MainRgn.DeleteObject();
			MainRgn.CreateRectRgn(0,0,0,0);
			for(int i=0;i<8;i++){
			
			MainRgn.CombineRgn(&MainRgn,&rgn[i],RGN_OR);
				TRACE("%d",PtInRegion(MainRgn,point.x,point.y));
				if(PtInRegion(MainRgn,point.x,point.y)){
					switch(i){
						case 0:		SubTarget.x = RLine->m_x1;SubTarget.y = RLine->m_y1;break;
						case 1:		SubTarget.x = (RLine->m_x1+RLine->m_x2)/2;SubTarget.y = RLine->m_y1;break;
						case 2:		SubTarget.x = RLine->m_x2;SubTarget.y = RLine->m_y1;break;				
						case 3:		SubTarget.x = RLine->m_x2;SubTarget.y = (RLine->m_y1+RLine->m_y2)/2;break;
						case 4:		SubTarget.x = RLine->m_x2;SubTarget.y = RLine->m_y2;break;				
						case 5:		SubTarget.x = (RLine->m_x1+RLine->m_x2)/2;SubTarget.y = RLine->m_y2;break;
						case 6:		SubTarget.x = RLine->m_x1;SubTarget.y = RLine->m_y2;break;				
						case 7:		SubTarget.x = RLine->m_x1;SubTarget.y = (RLine->m_y1+RLine->m_y2)/2;break;
					}
					return i+1;
				}
			}
		/* //subtargetcount ����
		// 1 2 3 
		// 8 x 4
		// 7 6 5
		*/
		}
		if(PLine->Get_ObNum() == 4){
		Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
			CRgn rgn[8];
		
			rgn[0].CreateEllipticRgn(ELine->m_x1-10,ELine->m_y1+10,ELine->m_x1+10,ELine->m_y1-10); // x1,y1 [1]
			rgn[1].CreateEllipticRgn(((ELine->m_x1+ELine->m_x2)/2)-10,ELine->m_y1+10,((ELine->m_x1+ELine->m_x2)/2)+10,ELine->m_y1-10); // (x1+x2)/2,y1 [2]
			rgn[2].CreateEllipticRgn(ELine->m_x2-10,ELine->m_y1+10,ELine->m_x2+10,ELine->m_y1-10); // x2,y1 [3]
			rgn[3].CreateEllipticRgn(ELine->m_x2-10,((ELine->m_y1+ELine->m_y2)/2)+10,ELine->m_x2+10,((ELine->m_y1+ELine->m_y2)/2)-10); // x2,(y1+y2)/2 [4]
			rgn[4].CreateEllipticRgn(ELine->m_x2-10,ELine->m_y2+10,ELine->m_x2+10,ELine->m_y2-10); // x2,y2 [5]
			rgn[5].CreateEllipticRgn(((ELine->m_x1+ELine->m_x2)/2)-10,ELine->m_y2+10,((ELine->m_x1+ELine->m_x2)/2)+10,ELine->m_y2-10); // (x1+x2)/2,y2 [6]
			rgn[6].CreateEllipticRgn(ELine->m_x1-10,ELine->m_y2+10,ELine->m_x1+10,ELine->m_y2-10); // x1,y2 [7]
			rgn[7].CreateEllipticRgn(ELine->m_x1-10,((ELine->m_y1+ELine->m_y2)/2)+10,ELine->m_x1+10,((ELine->m_y1+ELine->m_y2)/2)-10); // x1,(y1+y2)/2 [8]
		
			MainRgn.DeleteObject();
			MainRgn.CreateRectRgn(0,0,0,0);
			for(int i=0;i<8;i++){
			MainRgn.CombineRgn(&MainRgn,&rgn[i],RGN_OR);
				if(PtInRegion(MainRgn,point.x,point.y)){
					switch(i){
						case 0:		SubTarget.x = ELine->m_x1;SubTarget.y = ELine->m_y1;break;
						case 1:		SubTarget.x = (ELine->m_x1+ELine->m_x2)/2;SubTarget.y = ELine->m_y1;break;
						case 2:		SubTarget.x = ELine->m_x2;SubTarget.y = ELine->m_y1;break;				
						case 3:		SubTarget.x = ELine->m_x2;SubTarget.y = (ELine->m_y1+ELine->m_y2)/2;break;
						case 4:		SubTarget.x = ELine->m_x2;SubTarget.y = ELine->m_y2;break;				
						case 5:		SubTarget.x = (ELine->m_x1+ELine->m_x2)/2;SubTarget.y = ELine->m_y2;break;				
						case 6:		SubTarget.x = ELine->m_x1;SubTarget.y = ELine->m_y2;break;				
						case 7:		SubTarget.x = ELine->m_x1;SubTarget.y = (ELine->m_y1+ELine->m_y2)/2;break;
					}
					return i+1;
				}
			
			}
		/*
		// 1 2 3 
		// 8 x 4
		// 7 6 5
		*/

		}
	
			if(PLine->Get_ObNum() == 5){
			Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
			CRgn rgn[8];
		
			rgn[0].CreateEllipticRgn(TLine->m_x1-10,TLine->m_y1+10,TLine->m_x1+10,TLine->m_y1-10); // x1,y1 [1]
			rgn[1].CreateEllipticRgn(((TLine->m_x1+TLine->m_x2)/2)-10,TLine->m_y1+10,((TLine->m_x1+TLine->m_x2)/2)+10,TLine->m_y1-10); // (x1+x2)/2,y1 [2]
			rgn[2].CreateEllipticRgn(TLine->m_x2-10,TLine->m_y1+10,TLine->m_x2+10,TLine->m_y1-10); // x2,y1 [3]
			rgn[3].CreateEllipticRgn(TLine->m_x2-10,((TLine->m_y1+TLine->m_y2)/2)+10,TLine->m_x2+10,((TLine->m_y1+TLine->m_y2)/2)-10); // x2,(y1+y2)/2 [4]
			rgn[4].CreateEllipticRgn(TLine->m_x2-10,TLine->m_y2+10,TLine->m_x2+10,TLine->m_y2-10); // x2,y2 [5]
			rgn[5].CreateEllipticRgn(((TLine->m_x1+TLine->m_x2)/2)-10,TLine->m_y2+10,((TLine->m_x1+TLine->m_x2)/2)+10,TLine->m_y2-10); // (x1+x2)/2,y2 [6]
			rgn[6].CreateEllipticRgn(TLine->m_x1-10,TLine->m_y2+10,TLine->m_x1+10,TLine->m_y2-10); // x1,y2 [7]
			rgn[7].CreateEllipticRgn(TLine->m_x1-10,((TLine->m_y1+TLine->m_y2)/2)+10,TLine->m_x1+10,((TLine->m_y1+TLine->m_y2)/2)-10); // x1,(y1+y2)/2 [8]
		
			MainRgn.DeleteObject();
			MainRgn.CreateRectRgn(0,0,0,0);
			for(int i=0;i<8;i++){
			
			MainRgn.CombineRgn(&MainRgn,&rgn[i],RGN_OR);
				TRACE("%d",PtInRegion(MainRgn,point.x,point.y));
				if(PtInRegion(MainRgn,point.x,point.y)){
					switch(i){
						case 0:		SubTarget.x = TLine->m_x1;SubTarget.y = TLine->m_y1;break;
						case 1:		SubTarget.x = (TLine->m_x1+TLine->m_x2)/2;SubTarget.y = TLine->m_y1;break;
						case 2:		SubTarget.x = TLine->m_x2;SubTarget.y = TLine->m_y1;break;				
						case 3:		SubTarget.x = TLine->m_x2;SubTarget.y = (TLine->m_y1+TLine->m_y2)/2;break;
						case 4:		SubTarget.x = TLine->m_x2;SubTarget.y = TLine->m_y2;break;				
						case 5:		SubTarget.x = (TLine->m_x1+TLine->m_x2)/2;SubTarget.y = TLine->m_y2;break;
						case 6:		SubTarget.x = TLine->m_x1;SubTarget.y = TLine->m_y2;break;				
						case 7:		SubTarget.x = TLine->m_x1;SubTarget.y = (TLine->m_y1+TLine->m_y2)/2;break;
					}
					return i+1;
				}
			}
		}
		SubTarget = (-1,-1);
	
		return m_SubTargetCount;
		//}
		}else{//{�׷�ȭ�� ��ü ������ ���
			CRgn rgn[8];
			rgn[0].CreateEllipticRgn(p1.x-15,p1.y+15,p1.x+15,p1.y-15); // x1,y1 [1]
			rgn[1].CreateEllipticRgn(((p1.x+p2.x)/2)-15,p1.y+15,((p1.x+p2.x)/2)+15,p1.y-15); // (x1+x2)/2,y1 [2]
			rgn[2].CreateEllipticRgn(p2.x-15,p1.y+15,p2.x+15,p1.y-15); // x2,y1 [3]
			rgn[3].CreateEllipticRgn(p2.x-15,((p1.y+p2.y)/2)+15,p2.x+15,((p1.y+p2.y)/2)-15); // x2,(y1+y2)/2 [4]
			rgn[4].CreateEllipticRgn(p2.x-15,p2.y+15,p2.x+15,p2.y-15); // x2,y2 [5]
			rgn[5].CreateEllipticRgn(((p1.x+p2.x)/2)-15,p2.y+15,((p1.x+p2.x)/2)+15,p2.y-15); // (x1+x2)/2,y2 [6]
			rgn[6].CreateEllipticRgn(p1.x-15,p2.y+15,p1.x+15,p2.y-15); // x1,y2 [7]
			rgn[7].CreateEllipticRgn(p1.x-15,((p1.y+p2.y)/2)+15,p1.x+15,((p1.y+p2.y)/2)-15); // x1,(y1+y2)/2 [8]
		
			MainRgn.DeleteObject();
			MainRgn.CreateRectRgn(0,0,0,0);
			for(int i=0;i<8;i++){
			
			MainRgn.CombineRgn(&MainRgn,&rgn[i],RGN_OR);
			//test
			

				if(PtInRegion(MainRgn,point.x,point.y)){
					switch(i){
						case 0:		SubTarget.x = p1.x;SubTarget.y = p1.y;break;
						case 1:		SubTarget.x = (p1.x+p2.x)/2;SubTarget.y = p1.y;break;
						case 2:		SubTarget.x = p2.x;SubTarget.y = p1.y;break;				
						case 3:		SubTarget.x = p2.x;SubTarget.y = (p1.y+p2.y)/2;break;
						case 4:		SubTarget.x = p2.x;SubTarget.y = p2.y;break;				
						case 5:		SubTarget.x = (p1.x+p2.x)/2;SubTarget.y = p2.y;break;
						case 6:		SubTarget.x = p1.x;SubTarget.y = p2.y;break;				
						case 7:		SubTarget.x = p1.x;SubTarget.y = (p1.y+p2.y)/2;break;
					}
					return i+1;
				}
			}

SubTarget = (-1,-1);
return m_SubTargetCount;
}
	}//if mode
}


void CGraphicEditToolView::OnLine()
{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Mode = 1;
	//m_PolyLine->List.RemoveAll();
    m_Line = new Ob_Line;
}


void CGraphicEditToolView::OnElipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Mode = 4;
	//m_PolyLine->List.RemoveAll();
    m_Elipse = new Ob_Elipse;
}


void CGraphicEditToolView::OnRectangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Mode = 3;
	//m_PolyLine->List.RemoveAll();
	m_Rectangle = new Ob_Rectangle;
}


void CGraphicEditToolView::OnTextbutton()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_Mode = 5;
	m_Text= new Ob_Text;
}



void CGraphicEditToolView::OnEditCopy()//ctrl + c
{
	if(m_MoveMode ==true){
	return;//�����̴� ���߿��� DelŰ�� �۵����� �ʵ��� �Ѵ�.
	}
	switch(m_Mode){
		case 0:
			
			POSITION pos;
			void * m_Ob_Ptr;
			pos = Ob_PtrList.GetHeadPosition();
			for(int i =0; i < m_TargetCount ;i++){
				m_Ob_Ptr = Ob_PtrList.GetNext(pos);
			}
			Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
				if(PLine->Get_ObNum() == 1){
				Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
				mC_Line = *Line;
				m_CopyObNUm = 11;
				}
				if(PLine->Get_ObNum() == 2){
				mC_PolyLine = *PLine;
				m_CopyObNUm = 12;
				}
				if(PLine->Get_ObNum() == 3){
					Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
					mC_Rectangle = *RLine;
					m_CopyObNUm = 13;
				}
				if(PLine->Get_ObNum() == 4){
					Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
					mC_Elipse = *ELine;
					m_CopyObNUm = 14;
				}
				if(PLine->Get_ObNum() == 5){
					Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
					mC_Text = *TLine;
					m_CopyObNUm = 15;
				}
			
			
			
		break;
	}//case
}
void CGraphicEditToolView::OnEditCut()//ctrl + x
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnEditCopy();
	m_Delete_Ready = -1;//�������� ���� �� �κ�����Ʈ�� ������ �ʵ���.
	m_CopyObNUm -=10;
	OnDeletekey();

}


void CGraphicEditToolView::OnEditPaste()//ctrl + v
{
	
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(m_CopyObNUm%10 ==  1 ){
	Ob_Line *Line = new Ob_Line;
	*Line = mC_Line;
	Line->MoveAll(-(m_CopyObNUm/10)*10,-(m_CopyObNUm/10)*10);//������ �ٿ��ֱ�� ��ġ ����
	Line->SetObCount(++m_ObjectCount);//��ü����Ʈ ��(Tail)�� ��ü ī��Ʈ �߰��Ͽ� �־���
	Ob_PtrList.AddTail(Line);
	}
	if(m_CopyObNUm%10 ==  2 ){
	Ob_PolyLine *PLine = new Ob_PolyLine;
	*PLine = mC_PolyLine;
	PLine->MoveAll(-(m_CopyObNUm/10)*10,-(m_CopyObNUm/10)*10);//������ �ٿ��ֱ�� ��ġ ����
	PLine->SetObCount(++m_ObjectCount);//��ü����Ʈ ��(Tail)�� ��ü ī��Ʈ �߰��Ͽ� �־���
	Ob_PtrList.AddTail(PLine);
	}
	if(m_CopyObNUm%10 ==  3 ){
	Ob_Rectangle *RLine = new Ob_Rectangle;
	*RLine = mC_Rectangle;
	RLine->MoveAll(-(m_CopyObNUm/10)*10,-(m_CopyObNUm/10)*10);
	RLine->SetObCount(++m_ObjectCount);
	Ob_PtrList.AddTail(RLine);
	}
	if(m_CopyObNUm%10 ==  4 ){
	Ob_Elipse *ELine = new Ob_Elipse;
	*ELine = mC_Elipse;
	ELine->MoveAll(-(m_CopyObNUm/10)*10,-(m_CopyObNUm/10)*10);
	ELine->SetObCount(++m_ObjectCount);
	Ob_PtrList.AddTail(ELine);
	}
	if(m_CopyObNUm%10 ==  5 ){
	Ob_Text *TLine = new Ob_Text;
	*TLine = mC_Text;
	TLine->MoveAll(-(m_CopyObNUm/10)*10,-(m_CopyObNUm/10)*10);
	TLine->SetObCount(++m_ObjectCount);
	Ob_PtrList.AddTail(TLine);
	}
	if(m_CopyObNUm <10){
	m_CopyObNUm = -1;//�ٿ��ֱ�� 1���� �ǵ��� ó��
	}else{
	m_CopyObNUm += 10;
	}
	Invalidate();
}



void CGraphicEditToolView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(m_Mode){
		case 0 :
			if(m_TargetCount != -1&&m_SpacePushed!=true){
			//Ÿ���� ������ ��� 
			POSITION pos;
			void * m_Ob_Ptr;
			pos = Ob_PtrList.GetHeadPosition();
			for(int i =0; i < m_TargetCount ;i++){
				m_Ob_Ptr = Ob_PtrList.GetNext(pos);
			}
			Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
			//�ؽ�Ʈ ����� �� 
			if(TLine->Get_ObNum() == 5){
				if(nChar == '\b'){
					if(TLine->m_str.GetSize() > 0){
						TLine->m_str.RemoveAt(TLine->m_str.GetSize()-1);
					}
				}else{
						TLine->m_str.Add(nChar);
					}
				Invalidate();

			}
			
		}//if
		break;


	}//switch
}


void CGraphicEditToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
		POSITION pos,pos_index;
		void * m_Ob_Ptr;
	if(m_Mode ==0){
		switch(nChar){
			case VK_SHIFT:// ��� 0 �϶� �����̽��� ���������� 
				m_SpacePushed = true;
				if(this->m_TargetCount>0){
					this->m_MultySelect.AddTail(m_TargetCount);
				}
				break;
			case 'G'://�׷� ����
				pos = m_MultySelect.GetHeadPosition(); 
				if(pos == NULL){break;}
				m_GroupCount++;
				while(pos != NULL){
					pos_index = Ob_PtrList.GetHeadPosition();
					int count = m_MultySelect.GetNext(pos);
					for(int i=0;i<count-1;i++){
						if(pos_index !=NULL){
						Ob_PtrList.GetNext(pos_index);
						}
					}
					m_Ob_Ptr = Ob_PtrList.GetAt(pos_index);
					Ob_Rectangle *GLine = (Ob_Rectangle*)m_Ob_Ptr;
					GLine->m_Grouped = true;
					
					int buf = -1;
					if(GLine->GroupList.GetHeadPosition() != NULL){
						buf= GLine->GroupList.GetTail();
					}
					if(m_GroupCount != buf){
						GLine->GroupList.AddTail(m_GroupCount);	
					}
				}//while
				this->m_MultySelect.RemoveAll();
				Invalidate();
				break;
			case  'U'://�׷� Ǯ��
				pos = m_MultySelect.GetHeadPosition(); 
				if(pos == NULL){break;}
				while(pos != NULL){
					pos_index = Ob_PtrList.GetHeadPosition();
					int count = m_MultySelect.GetNext(pos);
					for(int i=0;i<count-1;i++){
						if(pos_index !=NULL){
						Ob_PtrList.GetNext(pos_index);
						}
					}
					m_Ob_Ptr = Ob_PtrList.GetAt(pos_index);
					Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;

					if(PLine->Get_ObNum() == 1 ){
						Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
						if(PLine->GroupList.GetHeadPosition()!=NULL){
							Line->GroupList.RemoveTail();
							m_MultySelect.RemoveHead();
						}
						POSITION pos_buf = Line->GroupList.GetHeadPosition();
						Line->GroupList.GetNext(pos_buf);
						if( pos_buf == NULL){//�׷� �� ���� ������ �÷��� ����
							Line->m_Grouped = false;
						}
					}
					else if(PLine->Get_ObNum() == 2 ){
						
					if(PLine->GroupList.GetHeadPosition()!=NULL){
						PLine->GroupList.RemoveTail();
						m_MultySelect.RemoveHead();
					}
					POSITION pos_buf = PLine->GroupList.GetHeadPosition();				
						if( pos_buf == NULL){//�׷� �� ���� ������ �÷��� ����
					PLine->m_Grouped = false;
					}
					}
					else if(PLine->Get_ObNum() == 3 ){
						Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
						if(RLine->GroupList.GetHeadPosition()!=NULL){
							RLine->GroupList.RemoveTail();
							m_MultySelect.RemoveHead();
						}
						POSITION pos_buf = RLine->GroupList.GetHeadPosition();
						if( pos_buf == NULL){//�׷� �� ���� ������ �÷��� ����
							RLine->m_Grouped = false;
						}
					}
					else if(PLine->Get_ObNum() == 4 ){
						Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
						if(ELine->GroupList.GetHeadPosition()!=NULL){
							ELine->GroupList.RemoveTail();
							m_MultySelect.RemoveHead();
						}
						POSITION pos_buf = ELine->GroupList.GetHeadPosition();
						if( pos_buf == NULL){//�׷� �� ���� ������ �÷��� ����
							ELine->m_Grouped = false;
						}
					}
					else if(PLine->Get_ObNum() == 5 ){
						Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
						if(TLine->GroupList.GetHeadPosition()!=NULL){
							TLine->GroupList.RemoveTail();
							m_MultySelect.RemoveHead();
						}
						POSITION pos_buf = TLine->GroupList.GetHeadPosition();
						if( pos_buf == NULL){//�׷� �� ���� ������ �÷��� ����
							TLine->m_Grouped = false;
						}
					}


				}//while

				this->m_MultySelect.RemoveAll();
				Invalidate();
				break;
		}//switch
	}//if
	
}


void CGraphicEditToolView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_Mode ==0 && nChar == VK_SHIFT){// ��� 0 �϶� �����̽��� ������
	m_SpacePushed = false;
	}
	
}



// �������� ��ü�� �����Ͽ����� ��ü ������ ���� rect�� point�� ���ϴ� �Լ�
bool CGraphicEditToolView::GetMultyRgnRect(CPoint *p1, CPoint* p2)
{
	
	POSITION pos,pos_index;
	void * m_Ob_Ptr;
	pos = m_MultySelect.GetHeadPosition(); 
	CPoint pb1,pb2;

	while(pos != NULL){
		if(pos == NULL){break;}
		pos_index = Ob_PtrList.GetHeadPosition();
		int count = m_MultySelect.GetNext(pos);
		for(int i=0;i<count-1;i++){
			if(pos_index !=NULL){
			Ob_PtrList.GetNext(pos_index);
			}
		}
	m_Ob_Ptr = Ob_PtrList.GetAt(pos_index);
	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
	
	
	if(PLine->Get_ObNum() == 1){
		
	Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
	
	int m_x1,m_x2,m_y1,m_y2;
	
	if(Line->GetPrePoint().x > Line->GetNextPoint().x){
	m_x1 = Line->GetNextPoint().x;
	m_x2 = Line->GetPrePoint().x;
	}else{
	m_x1 = Line->GetPrePoint().x;
	m_x2 = Line->GetNextPoint().x;
	}
	if(Line->GetPrePoint().y > Line->GetNextPoint().y){
	m_y1 = Line->GetNextPoint().y;
	m_y2 = Line->GetPrePoint().y;
	}else{
	m_y1 = Line->GetPrePoint().y;
	m_y2 = Line->GetNextPoint().y;
	}

	if(p1->x > m_x1){	p1->x = m_x1-10;	}
	if(p1->y > m_y1){	p1->y = m_y1-10;	}
	if(p2->x < m_x2){	p2->x = m_x2+10;	}
	if(p2->y < m_y2){	p2->y = m_y2+10;	}
	
	}else if(PLine->Get_ObNum() == 2){
		
	int m_x1,m_x2,m_y1,m_y2;
	pos = PLine->List.GetHeadPosition();
	CPoint point;
	pb1.x= 10000;
	pb1.y= 10000;
			while(pos!=NULL){
				point = PLine->List.GetNext(pos);
				if(pb1.x > point.x){	pb1.x = point.x-10;	}
				if(pb1.y > point.y){	pb1.y = point.y-10;	}
			}
	pb2.x = -1;
	pb2.y = -1;
	pos = PLine->List.GetHeadPosition();
			while(pos!=NULL){
				point = PLine->List.GetNext(pos);
				if(pb2.x < point.x){	pb2.x = point.x+10;	}
				if(pb2.y < point.y){	pb2.y = point.y+10;	}
			}
			if(p1->x > pb1.x){p1->x = pb1.x;}
			if(p1->y > pb1.y){p1->y = pb1.y;}
			if(p2->x < pb2.x){p2->x = pb2.x;}
			if(p2->y < pb2.y){p2->y = pb2.y;}

	}else if(PLine->Get_ObNum() > 2 ){//3,4,5 �ϰ�� rect,elipse,text�� �޾ƿ��� ������ ����.
	Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
	
	if(RLine->m_x1<RLine->m_x2){
	if(p1->x > RLine->m_x1){	p1->x = RLine->m_x1-10;	}
	}else{
	if(p1->x > RLine->m_x2){	p1->x = RLine->m_x2-10;	}
	}
	
	if(RLine->m_y1<RLine->m_y2){
	if(p1->y > RLine->m_y1){	p1->y = RLine->m_y1-10;	}
	}else{
	if(p1->y > RLine->m_y2){	p1->y = RLine->m_y2-10;	}
	}
	if(RLine->m_x1>RLine->m_x2){
	if(p2->x < RLine->m_x1){	p2->x = RLine->m_x1+10;	}
	}else{
	if(p2->x < RLine->m_x2){	p2->x = RLine->m_x2+10;	}
	}
	if(RLine->m_y1>RLine->m_y2){
	if(p2->y < RLine->m_y1){	p2->y = RLine->m_y1+10;	}
	}else{
	if(p2->y < RLine->m_y2){	p2->y = RLine->m_y2+10;	}
	}

	}
	
	}


	return false;
}

void CGraphicEditToolView::OptionSetting(int thin, int linepatt,int patt, int font, int fontsize, COLORREF LineColor, COLORREF color, COLORREF fontcolor)
{
	if(m_TargetCount <0){
	return;
	}
	
	POSITION pos,pos_Ptr,pos_Ob;
	CPoint point,prpoint;
	void * m_Ob_Ptr;
	//����Ʈ����Ʈ ó���κ�
	pos_Ptr = Ob_PtrList.GetHeadPosition();
	
	for(int i = 0; i < m_TargetCount; i++)
	{
		m_Ob_Ptr = Ob_PtrList.GetNext(pos_Ptr);
	}
	Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
	Ob_PolyLine *BLine = (Ob_PolyLine*)m_Ob_Ptr;
	int groupnum = -1;
	if(PLine->m_Grouped == true){//�׷� ���� �����϶�
		if(BLine->GroupList.GetHeadPosition()!=NULL){
		groupnum = BLine->GroupList.GetTail();
		}else{
			BLine->m_Grouped = false;
			return;
		}
		pos = Ob_PtrList.GetHeadPosition();
		for(int i =0; i < m_ObjectCount ;i++){
		m_Ob_Ptr = Ob_PtrList.GetNext(pos);
	BLine = (Ob_PolyLine*)m_Ob_Ptr;
	if(BLine->GroupList.GetHeadPosition() == NULL){break;}
	if(groupnum == BLine->GroupList.GetTail()){


	if(PLine -> Get_ObNum() == 1)//linecolor thin linepattern
		{
			Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
			if(LineColor == NULL){		LineColor = Line->m_Lcolor;		}
			if(thin == NULL){			thin = Line->m_Lthin;			}
			if(linepatt == -1){			linepatt = Line->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			Line->m_Lcolor = LineColor;
			Line->m_Lthin = thin;
			Line->m_Lpatt = linepatt;
			Line->pen.DeleteObject();
			Line->pen.CreatePen(linepatt,thin,LineColor);
		}
	// ���� �������� �׸���
		if(PLine -> Get_ObNum() == 2)//linecolor thin linepattern
		{
			
			if(LineColor == NULL){		LineColor = PLine->m_Lcolor;	}
			if(thin == NULL){			thin = PLine->m_Lthin;			}
			if(linepatt == -1){			linepatt = PLine->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			PLine->m_Lcolor = LineColor;
			PLine->m_Lthin = thin;
			PLine->m_Lpatt = linepatt;
			PLine->pen.DeleteObject();
			PLine->pen.CreatePen(linepatt,thin,LineColor);

		}
		if(PLine -> Get_ObNum() == 3)//linecolor thin linepattern color colorpattern
		{
			Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;

			if(LineColor == NULL){		LineColor = RLine->m_Lcolor;	}
			if(thin == NULL){			thin = RLine->m_Lthin;			}
			if(linepatt == -1){			linepatt = RLine->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			RLine->m_Lcolor = LineColor;
			RLine->m_Lthin = thin;
			RLine->m_Lpatt = linepatt;
			RLine->pen.DeleteObject();
			RLine->pen.CreatePen(linepatt,thin,LineColor);
			if(color == NULL){			color = RLine->m_color;			}
			if(patt == -1 ){			patt = 	RLine->m_patt;			}
			RLine->m_color = color;
 			RLine->m_patt = patt;	
			RLine->brush.DeleteObject();
			switch(patt){
				case 0:
					RLine->brush.CreateSolidBrush(color);
					break;
				case 1:	case 2:
					RLine->brush.CreateHatchBrush(patt,color);
					break;
			}
		}
		if(PLine -> Get_ObNum() == 4)//linecolor thin linepattern color colorpattern
		{
			Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;							
			if(LineColor == NULL){		LineColor = ELine->m_Lcolor;	}
			if(thin == NULL){			thin = ELine->m_Lthin;			}
			if(linepatt == -1){			linepatt = ELine->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			ELine->m_Lcolor = LineColor;
			ELine->m_Lthin = thin;
			ELine->m_Lpatt = linepatt;
			ELine->pen.DeleteObject();
			ELine->pen.CreatePen(linepatt,thin,LineColor);
			if(color == NULL){			color = ELine->m_color;			}
			if(patt == -1 ){			patt = 	ELine->m_patt;			}
			ELine->m_color = color;
 			ELine->m_patt = patt;	
			ELine->brush.DeleteObject();
			switch(patt){
				case 0:
					ELine->brush.CreateSolidBrush(color);
					break;
				case 1:
				case 2:
					ELine->brush.CreateHatchBrush(patt,color);
					break;
			}
			
			
		}
		if(PLine -> Get_ObNum() == 5)//fontcolor font fontsize color
		{
			CString fstr;
			Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
			if(color == NULL){	color = TLine->m_bkcolor;		 }
			if(fontcolor == NULL){	fontcolor=TLine->m_fontcolor;}
			if(font == NULL){		font=TLine->m_font;			 }
			if(fontsize == NULL){	fontsize = TLine->m_fsize;	 }
			switch(font){
			case 1: fstr = "�ü�";
			break;
			case 2: fstr = "����";
			break;
			case 3: fstr = "����";
			break;
			}
			TLine->font.DeleteObject();
			TLine->font.CreateFontA(fontsize,0,0,0,0,0,0,0,0,0,0,0,0,fstr);
			TLine->m_fsize = fontsize;
			TLine->m_font = font;
			TLine->m_fontcolor = fontcolor;
			TLine->m_bkcolor = color;
		}
		Invalidate();
	
	}
		}//for
		return;
	}//if

	//���� �׸���
		if(PLine -> Get_ObNum() == 1)//linecolor thin linepattern
		{
			Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
			if(LineColor == NULL){		LineColor = Line->m_Lcolor;		}
			if(thin == NULL){			thin = Line->m_Lthin;			}
			if(linepatt == -1){			linepatt = Line->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			Line->m_Lcolor = LineColor;
			Line->m_Lthin = thin;
			Line->m_Lpatt = linepatt;
			Line->pen.DeleteObject();
			Line->pen.CreatePen(linepatt,thin,LineColor);
		}
	// ���� �������� �׸���
		if(PLine -> Get_ObNum() == 2)//linecolor thin linepattern
		{
			
			if(LineColor == NULL){		LineColor = PLine->m_Lcolor;	}
			if(thin == NULL){			thin = PLine->m_Lthin;			}
			if(linepatt == -1){			linepatt = PLine->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			PLine->m_Lcolor = LineColor;
			PLine->m_Lthin = thin;
			PLine->m_Lpatt = linepatt;
			PLine->pen.DeleteObject();
			PLine->pen.CreatePen(linepatt,thin,LineColor);

		}
		if(PLine -> Get_ObNum() == 3)//linecolor thin linepattern color colorpattern
		{
			Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;

			if(LineColor == NULL){		LineColor = RLine->m_Lcolor;	}
			if(thin == NULL){			thin = RLine->m_Lthin;			}
			if(linepatt == -1){			linepatt = RLine->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			RLine->m_Lcolor = LineColor;
			RLine->m_Lthin = thin;
			RLine->m_Lpatt = linepatt;
			RLine->pen.DeleteObject();
			RLine->pen.CreatePen(linepatt,thin,LineColor);
			if(color == NULL){			color = RLine->m_color;			}
			if(patt == -1 ){			patt = 	RLine->m_patt;			}
			RLine->m_color = color;
 			RLine->m_patt = patt;	
			RLine->brush.DeleteObject();
			switch(patt){
				case 0:
					RLine->brush.CreateSolidBrush(color);
					break;
				case 1:	case 2:
					RLine->brush.CreateHatchBrush(patt,color);
					break;
			}
		}
		if(PLine -> Get_ObNum() == 4)//linecolor thin linepattern color colorpattern
		{
			Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;							
			if(LineColor == NULL){		LineColor = ELine->m_Lcolor;	}
			if(thin == NULL){			thin = ELine->m_Lthin;			}
			if(linepatt == -1){			linepatt = ELine->m_Lpatt;		}
			else if(linepatt >0){ thin = 1;}//���� ������ �ٸ����� �β� 1������ ������ �ȴ�
			ELine->m_Lcolor = LineColor;
			ELine->m_Lthin = thin;
			ELine->m_Lpatt = linepatt;
			ELine->pen.DeleteObject();
			ELine->pen.CreatePen(linepatt,thin,LineColor);
			if(color == NULL){			color = ELine->m_color;			}
			if(patt == -1 ){			patt = 	ELine->m_patt;			}
			ELine->m_color = color;
 			ELine->m_patt = patt;	
			ELine->brush.DeleteObject();
			switch(patt){
				case 0:
					ELine->brush.CreateSolidBrush(color);
					break;
				case 1:
				case 2:
					ELine->brush.CreateHatchBrush(patt,color);
					break;
			}
			
			
		}
		if(PLine -> Get_ObNum() == 5)//fontcolor font fontsize color
		{
			CString fstr;
			Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
			if(color == NULL){	color = TLine->m_bkcolor;		 }
			if(fontcolor == NULL){	fontcolor=TLine->m_fontcolor;}
			if(font == NULL){		font=TLine->m_font;			 }
			if(fontsize == NULL){	fontsize = TLine->m_fsize;	 }
			switch(font){
			case 1: fstr = "�ü�";
			break;
			case 2: fstr = "����";
			break;
			case 3: fstr = "����";
			break;
			}
			TLine->font.DeleteObject();
			TLine->font.CreateFontA(fontsize,0,0,0,0,0,0,0,0,0,0,0,0,fstr);
			TLine->m_fsize = fontsize;
			TLine->m_font = font;
			TLine->m_fontcolor = fontcolor;
			TLine->m_bkcolor = color;
		}
		Invalidate();
}


void CGraphicEditToolView::OnRedOb()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,NULL,RGB(255,0,0),NULL);
}


void CGraphicEditToolView::OnGreenOb()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,NULL,RGB(0,255,0),NULL);
}

void CGraphicEditToolView::OnBlueOb()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,NULL,RGB(0,0,255),NULL);
}



void CGraphicEditToolView::OnRedLine()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,RGB(255,0,0),NULL,NULL);
}


void CGraphicEditToolView::OnGreenLine()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,RGB(0,255,0),NULL,NULL);
}


void CGraphicEditToolView::OnBlueLine()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,RGB(0,0,255),NULL,NULL);
}


void CGraphicEditToolView::OnNormalPatton()
{
	OptionSetting(NULL,0,-1,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnDotPatton()
{
	OptionSetting(NULL,1,-1,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnDoublePatton()
{
	OptionSetting(NULL,2,-1,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::On3ptThink()
{
	OptionSetting(3,-1,-1,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::On6ptThink()
{
	OptionSetting(6,-1,-1,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::On10ptThink()
{
	OptionSetting(10,-1,-1,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::Onpatt1()
{
	OptionSetting(NULL,-1,0,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnPatt2()
{
	OptionSetting(NULL,-1,1,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnPatt3()
{
	OptionSetting(NULL,-1,2,NULL,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnFsize10()
{
	OptionSetting(NULL,-1,-1,NULL,20,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnFsize20()
{
	OptionSetting(NULL,-1,-1,NULL,40,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnFsize30()
{
	OptionSetting(NULL,-1,-1,NULL,60,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnFred()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,NULL,NULL,RGB(255,0,0));
}


void CGraphicEditToolView::OnFgreen()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,NULL,NULL,RGB(0,255,0));
}


void CGraphicEditToolView::OnFblue()
{
	OptionSetting(NULL,-1,-1,NULL,NULL,NULL,NULL,RGB(0,0,255));
}


void CGraphicEditToolView::OnFontstyle1()
{
	OptionSetting(NULL,-1,-1,1,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnFontstyle2()
{
	OptionSetting(NULL,-1,-1,2,NULL,NULL,NULL,NULL);
}


void CGraphicEditToolView::OnFontstyle3()
{
	OptionSetting(NULL,-1,-1,3,NULL,NULL,NULL,NULL);
}
