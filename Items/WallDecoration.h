#pragma once
class CWallDecoration
{
public:
	CWallDecoration(WallDecorationType type) { m_type = type; }
	~CWallDecoration() {};

	WallDecorationType GetDecoType() { return m_type; }


private:
	WallDecorationType m_type;
};

