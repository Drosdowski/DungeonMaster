#pragma once
class CDelayedTile
{
public:
	CDelayedTile();
	bool openDelayDone() { return m_openingDelay == 0; }
	void decreaseOpenDelay() { m_openingDelay--; }
	bool closeDelayDone() { return m_closingDelay == 0; }
	void decreaseCloseDelay() { m_closingDelay--; }

	void Open(int delay) { m_openingDelay = delay; }
	void Close(int delay) { m_closingDelay = delay; }

private:
	int m_openingDelay;
	int m_closingDelay;
};

