///////////////////////////////////////////////////////////////////////////////
// nav.h
// �v���[���[�̈ړ�����������֐��̃v���g�^�C�v�Ȃ�

// ���{�̔z��̑傫��
#define MAX_ROW	18
#define MAX_COL 22

// ���݂������Ă��镔���́A���̍\���̂ŕ\������
struct GoldLocations
{
	LPDIRECT3DRMFRAME lpGoldFrame;
	int nRow;
	int nCol;
	BOOL bFound;
};

// �֐��̃v���g�^�C�v
void SetupNavigator(void);
float TurnLeft(void);
float TurnRight(void);
float SwingLeft(void);
float SwingRight(void);
float fGetXPos(void);
float fGetZPos(void);
float fGetAngle(void);
void StepForward(void);
void StepBackward(void);
void RunForward(void);
void RunBackward(void);
void Move(float fRowDelta, float fColDelta);

BOOL bCheckForScore(int row, int column);
