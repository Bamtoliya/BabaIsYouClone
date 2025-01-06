#pragma once
#include "CBlock.h"
class CRule
{
	enum class RULETYPE {
		SIMPLE,  // 단순 규칙 (예: BABA IS YOU)
		AND,     // AND 연결 규칙 (예: BABA IS YOU AND FLAG IS WIN)
		ON,      // ON 연결 규칙 (예: BABA IS YOU ON FLAG)
		NEAR     // NEAR 연결 규칙 (예: BABA IS YOU NEAR FLAG)
	};
	
public:
	CRule() : m_bSubject(nullptr), m_bVerb(nullptr), m_bObject(nullptr), m_eType(RULETYPE::SIMPLE) {}
	~CRule() {};
	void SetSubject(CBlock* s) { m_bSubject = s; }
	void SetVerb(CBlock* v) { m_bVerb = v; }
	void SetObject(CBlock* o) { m_bObject = o; }
	CBlock* GetSubjectBlock() { return m_bSubject; }
	CBlock* GetVerbBlock() { return  m_bVerb; }
	CBlock* GetObjectBlock() { return m_bObject; }
	void SetType(RULETYPE t) { m_eType = t; }
	RULETYPE GetType() { return m_eType; }
private:
	CBlock* m_bSubject;
	CBlock* m_bVerb;
	CBlock* m_bObject;
	RULETYPE m_eType;
};

