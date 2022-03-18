
class CFieldDecoration
{
public:
	CFieldDecoration(FloorDecorationType type);
	~CFieldDecoration();

	FloorDecorationType GetDecoType();
	int GetState();
	void SetState(int state);

private:
	FloorDecorationType m_Type;
	int m_State;
};
