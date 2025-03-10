﻿// CMenuEditCtrl.cpp: 实现文件
//

#include "stdafx.h"
#include "MenuEditCtrl.h"
#include "MusicPlayer2.h"
#include "DrawCommon.h"

// CMenuEditCtrl

IMPLEMENT_DYNAMIC(CMenuEditCtrl, CMFCEditBrowseCtrl)

CMenuEditCtrl::CMenuEditCtrl()
    : m_theme_color(theApp.m_app_setting_data.theme_color)
{
}

CMenuEditCtrl::~CMenuEditCtrl()
{
}

void CMenuEditCtrl::OnBrowse()
{
    PostMessage(WM_KILLFOCUS, 0, 0);
    if (theApp.m_menu_set.m_recent_folder_playlist_menu.m_hMenu != 0)
    {
        CRect rect;
        GetWindowRect(rect);
        //ClientToScreen(rect);
        theApp.m_menu_set.m_recent_folder_playlist_menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, rect.left, rect.bottom, AfxGetMainWnd());
    }
}

void CMenuEditCtrl::OnDrawBrowseButton(CDC* pDC, CRect rect, BOOL bIsButtonPressed, BOOL bIsButtonHot)
{
    COLORREF back_color;
    if (bIsButtonPressed)
        back_color = m_theme_color.light1_5;
    else if (bIsButtonHot)
        back_color = m_theme_color.light2_5;
    else
        back_color = CColorConvert::m_gray_color.light3;
    pDC->FillSolidRect(rect, back_color);

    CSize icon_size(theApp.DPI(16), theApp.DPI(16));
    CPoint icon_top_left;
    icon_top_left.x = rect.left + (rect.Width() - icon_size.cx) / 2;
    icon_top_left.y = rect.top + (rect.Height() - icon_size.cy) / 2;
    CDrawCommon drawer;
    drawer.Create(pDC, this);
    drawer.DrawIcon(theApp.m_icon_set.expand, icon_top_left, icon_size);
}


void CMenuEditCtrl::OnChangeLayout()
{
    ASSERT_VALID(this);
    ENSURE(GetSafeHwnd() != NULL);

    m_nBrowseButtonWidth = max(theApp.DPI(20), m_sizeImage.cx + 8);

    SetWindowPos(NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);

    if (m_Mode != BrowseMode_None)
    {
        GetWindowRect(m_rectBtn);
        m_rectBtn.left = m_rectBtn.right - m_nBrowseButtonWidth;

        ScreenToClient(&m_rectBtn);
    }
    else
    {
        m_rectBtn.SetRectEmpty();
    }

}

BEGIN_MESSAGE_MAP(CMenuEditCtrl, CMFCEditBrowseCtrl)
    ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()



void CMenuEditCtrl::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    if (HTCAPTION == nHitTest)
    {
        return;
    }
    CMFCEditBrowseCtrl::OnNcLButtonDown(nHitTest, point);
}
