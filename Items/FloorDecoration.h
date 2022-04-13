
class CFloorDecoration
{
public:
	CFloorDecoration(FloorDecorationType type);
	~CFloorDecoration();

	FloorDecorationType GetDecoType();
	int GetState();
	void SetState(int state);

private:
	FloorDecorationType m_Type;
	int m_State;
};
