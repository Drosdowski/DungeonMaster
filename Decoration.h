
class CFieldDecoration
{
public:
	CFieldDecoration(DecorationType type);
	~CFieldDecoration();

	DecorationType GetDecoType();
	int GetState();
	void SetState(int state);

private:
	DecorationType m_Type;
	int m_State;
};
