
// GraphicEditToolDoc.cpp : CGraphicEditToolDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS

#endif
#include "MainFrm.h"
#include "GraphicEditToolDoc.h"
#include "GraphicEditToolView.h"//View를 include 할때는 반드시 Doc 헤더파일이 위에잇어야한다
#include "GraphicEditTool.h"



#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphicEditToolDoc

IMPLEMENT_DYNCREATE(CGraphicEditToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicEditToolDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicEditToolDoc 생성/소멸

CGraphicEditToolDoc::CGraphicEditToolDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGraphicEditToolDoc::~CGraphicEditToolDoc()
{
}

BOOL CGraphicEditToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//Doc에서 MainFrame을 거쳐서 View로 접근하면 오류가 나서 
	//MainFrame을 거치지 않고 바로 View로 접근을 하였다.
	CGraphicEditToolView * view = (CGraphicEditToolView *)m_viewList.GetHead();
	//지금까지 만든 객체 다 지우고서 기본 플래그들 초기화
	view->Ob_PtrList.RemoveAll();
	view->m_Mode = 0;
	view->m_TargetCount =-1;
	view->m_ObjectCount =0;
	view->m_MoveMode = false;
	view->m_Delete_Ready = -1;
	view->m_bDrawMode = false;
	view->m_CopyObNUm = -1;
	view->m_GroupCount = 1;
	view->m_SpacePushed = false;
	
	return TRUE;
}




// CGraphicEditToolDoc serialization

void CGraphicEditToolDoc::Serialize(CArchive& ar)
{CArray<char,char> str;
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		CGraphicEditToolView * view = (CGraphicEditToolView *)m_viewList.GetHead();
		//view->Ob_PtrList.Serialize(ar);
		int count;
		count = view->Ob_PtrList.GetCount();
		ar.Write(&count,sizeof(int));
		int obnum;
		POSITION pos;
		void * m_Ob_Ptr;
		pos =  view->Ob_PtrList.GetHeadPosition();
		for(int i=0;i< count;i++){
			m_Ob_Ptr =  view->Ob_PtrList.GetNext(pos);
			Ob_PolyLine *PLine = (Ob_PolyLine*)m_Ob_Ptr;
			if(PLine->Get_ObNum() == 1){
				Ob_Line *Line = (Ob_Line*)m_Ob_Ptr;
				obnum=1;
				ar.Write(&obnum,sizeof(int));
				int obCount = Line->Get_ObCount();
				ar.Write(&obCount,sizeof(int));
				
				//style
				int patt = Line->m_Lpatt;
				ar.Write(&patt,sizeof(int));
				int thin = Line->m_Lthin;
				ar.Write(&thin,sizeof(int));
				COLORREF lcolor = Line->m_Lcolor;
				ar.Write(&lcolor,sizeof(COLORREF));
				
				// pen에 포인터를 안쓰면 오퍼레이터(=) 에러남
				CPen *pen = &(Line->pen);
				ar.Write(pen,sizeof(CPen));
				
				//bool Grouped;
				ar.Write(&(Line->m_Grouped),sizeof(bool));
				Line->GroupList.Serialize(ar);
				ar.Write(&(Line->GetPrePoint()),sizeof(CPoint));
				ar.Write(&(Line->GetNextPoint()),sizeof(CPoint));
				
			}else if(PLine->Get_ObNum() == 2){
				obnum=2;
				ar.Write(&obnum,sizeof(int));
				int obCount = PLine->Get_ObCount();
				ar.Write(&obCount,sizeof(int));
				//style
				int patt = PLine->m_Lpatt;
				ar.Write(&patt,sizeof(int));
				int thin = PLine->m_Lthin;
				ar.Write(&thin,sizeof(int));
				COLORREF lcolor = PLine->m_Lcolor;
				ar.Write(&lcolor,sizeof(COLORREF));
				
				CPen *pen = &(PLine->pen);
				ar.Write(pen,sizeof(CPen));
				
				//bool Grouped;
				ar.Write(&(PLine->m_Grouped),sizeof(bool));
				PLine->GroupList.Serialize(ar);
				PLine->List.Serialize(ar);


			}else if(PLine->Get_ObNum() == 3){
				Ob_Rectangle *RLine = (Ob_Rectangle*)m_Ob_Ptr;
				//size = sizeof(RLine); // 객체 사이즈 write 후 
				obnum=3;
				ar.Write(&obnum,sizeof(int));
				int obCount = RLine->Get_ObCount();
				ar.Write(&obCount,sizeof(int));
				//style-pen
				int patt = RLine->m_Lpatt;
				ar.Write(&patt,sizeof(int));
				int thin = RLine->m_Lthin;
				ar.Write(&thin,sizeof(int));
				COLORREF lcolor = RLine->m_Lcolor;
				ar.Write(&lcolor,sizeof(COLORREF));
				
				//CPen *pen = &(RLine->pen);
				//ar.Write(pen,sizeof(CPen));
				
				//style-brush
				int mpatt = RLine->m_patt;
				ar.Write(&mpatt,sizeof(int));
				COLORREF mcolor = RLine->m_color;
				ar.Write(&mcolor,sizeof(COLORREF));
				
				//CBrush *brush = &(RLine->brush);
				//ar.Write(brush,sizeof(CBrush));
				
				//int m_x1, m_x2, m_y1,m_y2;
				ar.Write(&(RLine->m_x1),sizeof(int));
				ar.Write(&(RLine->m_x2),sizeof(int));
				ar.Write(&(RLine->m_y1),sizeof(int));
				ar.Write(&(RLine->m_y2),sizeof(int));
				//bool Grouped;
				ar.Write(&(RLine->m_Grouped),sizeof(bool));
				RLine->GroupList.Serialize(ar);
			}else if(PLine->Get_ObNum() == 4){
				Ob_Elipse *ELine = (Ob_Elipse*)m_Ob_Ptr;
				//size = sizeof(ELine); // 객체 사이즈 write 후 
				obnum=4;
				ar.Write(&obnum,sizeof(int));
				int obCount = ELine->Get_ObCount();
				ar.Write(&obCount,sizeof(int));
				//int m_x1, m_x2, m_y1,m_y2;
				ar.Write(&(ELine->m_x1),sizeof(int));
				ar.Write(&(ELine->m_x2),sizeof(int));
				ar.Write(&(ELine->m_y1),sizeof(int));
				ar.Write(&(ELine->m_y2),sizeof(int));
				//style-pen
				int patt = ELine->m_Lpatt;
				ar.Write(&patt,sizeof(int));
				int thin = ELine->m_Lthin;
				ar.Write(&thin,sizeof(int));
				COLORREF lcolor = ELine->m_Lcolor;
				ar.Write(&lcolor,sizeof(COLORREF));
				
				CPen *pen = &(ELine->pen);
				ar.Write(pen,sizeof(CPen));
				
				//style-brush
				int mpatt = ELine->m_patt;
				ar.Write(&mpatt,sizeof(int));
				COLORREF mcolor = ELine->m_color;
				ar.Write(&mcolor,sizeof(COLORREF));
				
				CBrush *brush = &(ELine->brush);
				ar.Write(brush,sizeof(CBrush));
				
				//bool Grouped;
				ar.Write(&(ELine->m_Grouped),sizeof(bool));
				ELine->GroupList.Serialize(ar);
			}else if(PLine->Get_ObNum() == 5){
				Ob_Text *TLine = (Ob_Text*)m_Ob_Ptr;
				//size = sizeof(TLine); // 객체 사이즈 write 후 
				obnum=5;
				ar.Write(&obnum,sizeof(int));
				
				int obCount = TLine->Get_ObCount();
				ar.Write(&obCount,sizeof(int));
				//style-font
				int sfont = TLine->m_font;
				ar.Write(&sfont,sizeof(int));
				int fontsize = TLine->m_fsize;
				ar.Write(&fontsize,sizeof(int));
				
				CFont *font = &(TLine->font);
				ar.Write(font,sizeof(CFont));
				
				//tyle-etc
				COLORREF mcolor = TLine->m_fontcolor;
				ar.Write(&mcolor,sizeof(COLORREF));
				COLORREF bkcolor = TLine->m_bkcolor;
				ar.Write(&bkcolor,sizeof(COLORREF));
				
				//int m_x1, m_x2, m_y1,m_y2;
				ar.Write(&(TLine->m_x1),sizeof(int));
				ar.Write(&(TLine->m_x2),sizeof(int));
				ar.Write(&(TLine->m_y1),sizeof(int));
				ar.Write(&(TLine->m_y2),sizeof(int));
				//bool Grouped;
				ar.Write(&(TLine->m_Grouped),sizeof(bool));
				TLine->GroupList.Serialize(ar);
				TLine->m_str.Serialize(ar);
				//str.Copy(TLine->m_str);//.Copy(str);
				//str.Serialize(ar);
			}
	
		}

		ar.Write(&(view->m_Mode),sizeof(int));
		ar.Write(&(view->m_TargetCount),sizeof(int));
		ar.Write(&(view->m_ObjectCount),sizeof(int));
		ar.Write(&(view->m_MoveMode),sizeof(bool));
		ar.Write(&(view->m_Delete_Ready),sizeof(int));
		ar.Write(&(view->m_bDrawMode),sizeof(bool));
		ar.Write(&(view->m_CopyObNUm),sizeof(int));
		ar.Write(&(view->m_GroupCount),sizeof(int));
		ar.Write(&(view->m_SpacePushed),sizeof(bool));
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		OnNewDocument();
		CGraphicEditToolView * view = (CGraphicEditToolView *)m_viewList.GetHead();
		//view->Ob_PtrList.Serialize(ar);
		
		int count;
		ar.Read(&count,sizeof(int));
		int obnum;
		POSITION pos;
		view->Ob_PtrList.RemoveAll();
		pos =  view->Ob_PtrList.GetHeadPosition();
		for(int i=0;i< count;i++){
			//m_Ob_Ptr =  view->Ob_PtrList.GetNext(pos);
		//= (Ob_PolyLine*)m_Ob_Ptr;
			ar.Read(&obnum,sizeof(int));
			if(obnum == 1){
				Ob_Line *Line = new Ob_Line ;

				int obCount ;
				ar.Read(&obCount,sizeof(int));
				Line->SetObCount(obCount);
				//style
				int patt;
				ar.Read(&patt,sizeof(int));
				Line->m_Lpatt = patt;
				int thin ;
				ar.Read(&thin,sizeof(int));
				Line->m_Lthin = thin;
				COLORREF lcolor;
				ar.Read(&lcolor,sizeof(COLORREF));
				Line->m_Lcolor = lcolor;
				
				
				ar.Read(&(Line->pen),sizeof(CPen));
				
				Line->pen.DeleteObject();
				Line->pen.CreatePen(Line->m_Lpatt,Line->m_Lthin,Line->m_Lcolor);
				
				//bool Grouped;
				ar.Read(&(Line->m_Grouped),sizeof(bool));
				Line->GroupList.Serialize(ar);
				CPoint point,npoint;
				ar.Read(&point,sizeof(CPoint));
				Line->SetPrePoint(point);
				ar.Read(&npoint,sizeof(CPoint));
				Line->SetNextPoint(npoint);
				view->Ob_PtrList.AddTail(Line);
			}else if(obnum == 2){
				Ob_PolyLine *PLine = new Ob_PolyLine;
				int obCount ;
				ar.Read(&obCount,sizeof(int));
				PLine->SetObCount(obCount);
				//style
				int patt;
				ar.Read(&patt,sizeof(int));
				PLine->m_Lpatt = patt;
				int thin ;
				ar.Read(&thin,sizeof(int));
				PLine->m_Lthin = thin;
				COLORREF lcolor;
				ar.Read(&lcolor,sizeof(COLORREF));
				PLine->m_Lcolor = lcolor;
				ar.Read(&(PLine->pen),sizeof(CPen));
				PLine->pen.DeleteObject();
				PLine->pen.CreatePen(PLine->m_Lpatt,PLine->m_Lthin,	PLine->m_Lcolor);
				//bool Grouped;
				ar.Read(&(PLine->m_Grouped),sizeof(bool));
				PLine->GroupList.Serialize(ar);
				PLine->List.Serialize(ar);
				view->Ob_PtrList.AddTail(PLine);
			}else if(obnum == 3){
				Ob_Rectangle *RLine = new Ob_Rectangle;
				int obCount ;
				ar.Read(&obCount,sizeof(int));
				RLine->SetObCount(obCount);
				//style
				int patt;
				ar.Read(&patt,sizeof(int));
				RLine->m_Lpatt = patt;
				int thin ;
				ar.Read(&thin,sizeof(int));
				RLine->m_Lthin = thin;
				COLORREF lcolor;
				ar.Read(&lcolor,sizeof(COLORREF));
				RLine->m_Lcolor = lcolor;
				ar.Read(&(RLine->pen),sizeof(CPen));
				RLine->pen.DeleteObject();
				RLine->pen.CreatePen(RLine->m_Lpatt,RLine->m_Lthin,	RLine->m_Lcolor);
				//style-brush
				int mpatt ;
				ar.Read(&mpatt,sizeof(int));
				RLine->m_patt = mpatt;
				COLORREF mcolor;
				ar.Read(&mcolor,sizeof(COLORREF));
				RLine->m_color = mcolor;
				ar.Read(&(RLine->brush),sizeof(CBrush));
				RLine->brush.DeleteObject();
			switch(patt){
				case 0:
					RLine->brush.CreateSolidBrush(RLine->m_color);
					break;
				case 1:	case 2:
					RLine->brush.CreateHatchBrush(RLine->m_patt,RLine->m_color);
					break;
			}
				//int m_x1, m_x2, m_y1,m_y2;
				ar.Read(&(RLine->m_x1),sizeof(int));
				ar.Read(&(RLine->m_x2),sizeof(int));
				ar.Read(&(RLine->m_y1),sizeof(int));
				ar.Read(&(RLine->m_y2),sizeof(int));
				//bool Grouped;
				ar.Read(&(RLine->m_Grouped),sizeof(bool));
				RLine->GroupList.Serialize(ar);
				view->Ob_PtrList.AddTail(RLine);
			}else if(obnum == 4){
				Ob_Elipse *ELine= new Ob_Elipse;
				int obCount ;
				ar.Read(&obCount,sizeof(int));
				ELine->SetObCount(obCount);
				//style
				int patt;
				ar.Read(&patt,sizeof(int));
				ELine->m_Lpatt = patt;
				int thin ;
				ar.Write(&thin,sizeof(int));
				ELine->m_Lthin = thin;
				COLORREF lcolor;
				ar.Read(&lcolor,sizeof(COLORREF));
				ELine->m_Lcolor = lcolor;
				ar.Read(&(ELine->pen),sizeof(CPen));
				ELine->pen.DeleteObject();
				ELine->pen.CreatePen(ELine->m_Lpatt,ELine->m_Lthin,ELine->m_Lcolor);
				//style-brush
				int mpatt ;
				ar.Read(&mpatt,sizeof(int));
				ELine->m_patt = mpatt;
				COLORREF mcolor;
				ar.Read(&mcolor,sizeof(COLORREF));
				ELine->m_color = mcolor;
				ar.Read(&(ELine->brush),sizeof(CBrush));
				ELine->brush.DeleteObject();
				switch(patt){
					case 0:
						ELine->brush.CreateSolidBrush(ELine->m_color);
						break;
					case 1:	case 2:
						ELine->brush.CreateHatchBrush(ELine->m_patt,ELine->m_color);
						break;
				}
				//int m_x1, m_x2, m_y1,m_y2;
				ar.Read(&(ELine->m_x1),sizeof(int));
				ar.Read(&(ELine->m_x2),sizeof(int));
				ar.Read(&(ELine->m_y1),sizeof(int));
				ar.Read(&(ELine->m_y2),sizeof(int));
				//bool Grouped;
				ar.Read(&(ELine->m_Grouped),sizeof(bool));
				ELine->GroupList.Serialize(ar);
				view->Ob_PtrList.AddTail(ELine);
			}else if(obnum == 5){
				Ob_Text *TLine= new Ob_Text;

				int obCount ;
				ar.Read(&obCount,sizeof(int));
				TLine->SetObCount(obCount);
				
				//style-font
				int sfont;
				ar.Read(&sfont,sizeof(int));
				TLine->m_font = sfont;
				int fontsize ;
				ar.Read(&fontsize,sizeof(int));
				TLine->m_fsize = fontsize;
				ar.Read(&(TLine->font),sizeof(CFont));
				TLine->font.DeleteObject();
				CString fstr;
				switch(TLine->m_font){
					case 1: fstr = "궁서";
					break;
					case 2: fstr = "돋움";
					break;
					case 3: fstr = "굴림";
					break;
				}
				TLine->font.CreateFontA(fontsize,0,0,0,0,0,0,0,0,0,0,0,0,fstr);

				//tyle-etc
				COLORREF mcolor ;
				ar.Read(&mcolor,sizeof(COLORREF));
				TLine->m_fontcolor = mcolor;
				COLORREF bkcolor;
				ar.Read(&bkcolor,sizeof(COLORREF));
				TLine->m_bkcolor = bkcolor;
				//int m_x1, m_x2, m_y1,m_y2;
				ar.Read(&(TLine->m_x1),sizeof(int));
				ar.Read(&(TLine->m_x2),sizeof(int));
				ar.Read(&(TLine->m_y1),sizeof(int));
				ar.Read(&(TLine->m_y2),sizeof(int));
				//bool Grouped;
				ar.Read(&(TLine->m_Grouped),sizeof(bool));
				TLine->GroupList.Serialize(ar);
				TLine->m_str.Serialize(ar);
				view->Ob_PtrList.AddTail(TLine);
			}
	
		}


		ar.Read(&(view->m_Mode),sizeof(int));
		ar.Read(&(view->m_TargetCount),sizeof(int));
		ar.Read(&(view->m_ObjectCount),sizeof(int));
		ar.Read(&(view->m_MoveMode),sizeof(bool));
		ar.Read(&(view->m_Delete_Ready),sizeof(int));
		ar.Read(&(view->m_bDrawMode),sizeof(bool));
		ar.Read(&(view->m_CopyObNUm),sizeof(int));
		ar.Read(&(view->m_GroupCount),sizeof(int));
		ar.Read(&(view->m_SpacePushed),sizeof(bool));
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGraphicEditToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGraphicEditToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGraphicEditToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGraphicEditToolDoc 진단

#ifdef _DEBUG
void CGraphicEditToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicEditToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphicEditToolDoc 명령
