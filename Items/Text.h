#pragma once
#include <Attributes/TextAttributes.h>

class CText
{

	public:
		CText(int index, CTextAttributes attribute);
		~CText();

		CString GetText() { return m_attribute.text; }
		bool isVisible() { return m_attribute.visible == 1; }
		int textPos() { return m_attribute.text_data; }

private:
	CTextAttributes m_attribute;
};

