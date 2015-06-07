
// GraphicEditToolView.h : CGraphicEditToolView 클래스의 인터페이스
//

#pragma once
#include "Ob_PolyLine.h"
#include "Ob_Rectangle.h"
#include "Ob_elipse.h"
#include "Ob_Text.h"
class CGraphicEditToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditToolView();
	DECLARE_DYNCREATE(CGraphicEditToolView)

// 특성입니다.
public:
	CGraphicEditToolDoc* GetDocument() const;

// 작업입니다.
public:


// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	HCURSOR hCursor;
protected:

//-----------------도형의 모드 플래그
public:
	int m_Mode; //0:Arrow 1: Line 2: PolyLine 3: Rect 4: Ellipse 5: Text
	int m_Current_think;
	int m_TargetCount; // 현재 타겟중인 카운터
	int m_ObjectCount; // 1부터 저장 (n 개 )
	int m_SubTargetCount; // 폴리라이에서 사용할 서브타켓 카운트
	CPoint SubTarget;
	bool m_MoveMode ;
	bool m_bDrawMode ;
	int m_Delete_Ready; // 지울 수 있는 subPoint 저장
	int m_CopyObNUm; // -1 : 카피 되지 않음, 1~5 잘라내기 됨, n1~n5 복사 됨 n:같은 복사물 붙여넣기 횟수
	CPoint pr_Movepoint;//움직일 시 사용할 move포인트 
	CPoint p1,p2;// 그룹화시 rect를 이루는 두 점
	void CGraphicEditToolView::OptionSetting(int thin, int linepatt,int patt, int font, int fontsize, COLORREF LineColor, COLORREF color, COLORREF fontcolor);
//-----------------------------
// 구현입니다.
public:
	virtual ~CGraphicEditToolView();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
private:	


protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelect();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPolyline();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool GetObTarget(CPoint point);
	afx_msg void OnDeletekey();
	afx_msg int GetObSubTarget(CPoint point);
	afx_msg void OnRedOb();
	afx_msg void OnBlueOb();
	afx_msg void OnGreenOb();
	afx_msg void OnRedLine();
	afx_msg void OnGreenLine();
	afx_msg void OnBlueLine();
	afx_msg void OnNormalPatton();
	afx_msg void OnDotPatton();
	afx_msg void OnDoublePatton();
	afx_msg void On3ptThink();
	afx_msg void On6ptThink();
	afx_msg void On10ptThink();
	afx_msg void OnElipse();
	afx_msg void OnRectangle();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	
	afx_msg void OnLine();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTextbutton();
	int m_GroupCount;
	CList <int,int&> m_MultySelect;
	bool m_SpacePushed;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool GetMultyRgnRect(CPoint *p1, CPoint* p2);
	//도형의 주소 객체
	CPtrList Ob_PtrList;
	afx_msg void Onpatt1();
	afx_msg void OnPatt2();
	afx_msg void OnPatt3();
	afx_msg void OnFsize10();
	afx_msg void OnFsize20();
	afx_msg void OnFsize30();
	afx_msg void OnFred();
	afx_msg void OnFgreen();
	afx_msg void OnFblue();
	afx_msg void OnFontstyle1();
	afx_msg void OnFontstyle2();
	afx_msg void OnFontstyle3();
};

#ifndef _DEBUG  // GraphicEditToolView.cpp의 디버그 버전
inline CGraphicEditToolDoc* CGraphicEditToolView::GetDocument() const
   { return reinterpret_cast<CGraphicEditToolDoc*>(m_pDocument); }
#endif

