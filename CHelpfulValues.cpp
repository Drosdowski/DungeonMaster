#include "stdafx.h"
#include "CHelpfulValues.h"

CHelpfulValues::CHelpfulValues() {
	for (int i = 0; i < 4; i++)
	{
		m_stx[i] = int(cos(i * PI / 2));  // 0,  1, 0, -1
		m_sty[i] = int(sin(i * PI / 2));  // 1, 0, -1, 0
	}
}

int CHelpfulValues::OppositeDirection(int direction) {
	return (direction + 2) % 4;
}
