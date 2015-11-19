// ClientiTransferDoc.h : interface of the CClientiTransferDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTITRANSFERDOC_H__86068F0C_2FC1_11D8_B754_00C026108782__INCLUDED_)
#define AFX_CLIENTITRANSFERDOC_H__86068F0C_2FC1_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ClientiTransferSet.h"


class CClientiTransferDoc : public CDocument
{
protected: // create from serialization only
	CClientiTransferDoc();
	DECLARE_DYNCREATE(CClientiTransferDoc)

// Attributes
public:
	CClientiTransferSet m_clientiTransferSet;
	CDatabase m_db;
	CDatabase m_db_old;
	CString m_csDefaultConnect;
	CString m_csDefaultConnect_old;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientiTransferDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClientiTransferDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientiTransferDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTITRANSFERDOC_H__86068F0C_2FC1_11D8_B754_00C026108782__INCLUDED_)
