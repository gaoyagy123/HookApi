// MyApi.h : main header file for the MYAPI DLL
//

#if !defined(AFX_MYAPI_H__DE40B59C_21C8_4862_822E_4C80E0518A4A__INCLUDED_)
#define AFX_MYAPI_H__DE40B59C_21C8_4862_822E_4C80E0518A4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


class CMyApiApp : public CWinApp
{
public:
	CMyApiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyApiApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMyApiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYAPI_H__DE40B59C_21C8_4862_822E_4C80E0518A4A__INCLUDED_)
