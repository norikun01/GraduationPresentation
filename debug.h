//=============================================================================
//
// �f�o�b�O���� [debug.h]
// Author : masayasu wakita
//
//=============================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx9.h"
#include "imgui\imgui_impl_win32.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FLOOR_LIMIT 20

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	DEBUGMODE_NONE = 0,
	DEBUGMODE_RAND,
	DEBUGMODE_MANY,
	DEBUGMODE_INDIVIDUAL,
	DEBUGMODE_DELETE,
	DEBUGMODE_PAINT,
	DEBUGMODE_ENEMY,
	DEBUGMODE_MAX
} DEBUGMODE;

//=============================================================================
// �O���錾
//=============================================================================
class CCircle;
class CScene;
class CObject;
class CEnemy;
class CMeshField;

//=============================================================================
// �N���X��`
//=============================================================================
class CDebugProc
{
public:
	CDebugProc();						// �R���X�g���N�^
	~CDebugProc();						// �f�X�g���N�^
	HRESULT Init(HWND hWnd);			// ����������
	void Uninit(void);					// �J������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static void Log(char* fmt, ...);	// �f�o�b�O���O�̏���

	static CCircle *GetCircle(void) { return m_pCircle; }	// �~�͈͓̔��ɂ��邩
	static bool GetDebugState(void) { return m_bDebug; }	// �f�o�b�O���g�p����
	static void SelectModel(void);

private:
	static void Debug(void);								// �f�o�b�O����
	static void LandScape(D3DXVECTOR3 &worldPos);			// �����h�X�P�[�v����
	static void Paint(D3DXVECTOR3 &worldPos);				// �y�C���g����
	static void CreateEnemy(D3DXVECTOR3 &worldPos);			// �G�l�~�[�z�u����
	static void CreateObject(D3DXVECTOR3 &worldPos);		// �ؔz�u����
	static void CreateIndividual(D3DXVECTOR3 &worldPos);	// �P�̔z�u����
	static void	DeleteObject(D3DXVECTOR3 &worldPos);		// �I�u�W�F�N�g�͈͓��폜����
	static void CreateParticle(void);						// �p�[�e�B�N���쐬
	static void DebugFloorCreate(const int &nWide, const int &nDepth, D3DXVECTOR3 &createPos);
	static void ShowInspector(void);

	LPD3DXFONT	m_pFont;									// �t�H���g�ւ̃|�C���^
	static char m_aStr[1024];								// ������
	static CObject *m_pSample;								// ���{�p�I�u�W�F�N�g�|�C���^
	static CScene *m_pSelect;								// �I�������I�u�W�F�N�g
	static CEnemy *m_pEnemy;								// ���{�p�G�|�C���^
	static float m_fPaintSize;								// �n�`�ҏW�u���V�̑傫��
	static int m_nCreateIndex;								// 1�t���[���̐�����
	static bool m_bDebug;									// �f�o�b�O���[�h�̐؂�ւ�
	static bool m_bInspectorWind;							// �C���X�y�N�^�[�E�B���h�E�̕\���ؑ�
	static bool m_bHeightCalculation;						// �����v�Z�g�p�t���O
	static int m_nCntGeneration;							// ������
	static int m_nMode;										// ���[�h�I��
	static D3DXVECTOR3 m_mouseOld;							// �}�E�X�̑O�̃��[���h���W
	static int m_nCntContinue;								// �ĉ��Z��
	static CCircle *m_pCircle;								// �~�̃|�C���^
	static D3DXVECTOR2 m_CreateRand;						// ���̗�
	static D3DXVECTOR2 m_CreateRandOld;						// ���̗�
	static CMeshField *m_apMeshField[FLOOR_LIMIT * FLOOR_LIMIT];
	static D3DXVECTOR3 m_createPos;
	static float m_fSliderPow;
	static std::string m_currentItem;
	static HWND m_hWnd;										// �E�B���h�E�n���h��

	// �G�t�F�N�g�쐬�֘A
	static int m_nParticleShape;							// �p�[�e�B�N���`��
	static int m_particleLife;								// �p�[�e�B�N���̐�������
	static int m_nCreate;									// ������
	static int m_nInterval;									// �C���^�[�o��
	static float m_fStartRadius;							// �n�܂��
	static float m_fRadius;									// ���a
	static float m_fMinSpeed;								// �Œ�X�s�[�h
	static float m_fSpeed;									// �X�s�[�h

	static bool m_bLoop;									// �������J��Ԃ�
	static bool m_bGravity;									// �d�̗͂L��
	static bool m_bRandomSpeed;								// �X�s�[�h�����_�����̗L��
};
#endif