
// SailorGraphDoc.h : CSailorGraphDoc ��Ľӿ�
//


#pragma once

class CSailorGraphDoc : public CDocument
{
protected: // �������л�����
	CSailorGraphDoc();
	DECLARE_DYNCREATE(CSailorGraphDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);


// ʵ��
public:
	virtual ~CSailorGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

};


