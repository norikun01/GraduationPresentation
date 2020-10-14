//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : masayasu wakita
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "sceneX.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DEPTH	20											// ���s��
#define WIDE 20												// ��

//=============================================================================
// �O���錾
//=============================================================================
class CColliderBox;
class CColliderSphere;

//=============================================================================
// �N���X��`
//=============================================================================
class CObject : public CSceneX
{
public:
	// �񋓑̒�`
	typedef enum
	{
		LOADTYPE_ADD = 0,
		LOADTYPE_POS_X,
		LOADTYPE_POS_Y,
		LOADTYPE_POS_Z,
		LOADTYPE_ROT_X,
		LOADTYPE_ROT_Y,
		LOADTYPE_ROT_Z,
		LOADTYPE_MAX
	} LOADTYPE;

	CObject(PRIORITY obj);							// �R���X�g���N�^
	~CObject();										// �f�X�g���N�^
	HRESULT Init(void);								// ����������
	void Uninit(void);								// �J������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static CObject *Create(void);			// �N���G�C�g����
	static HRESULT Load(void);						// ���[�h����
	static void Unload(void);						// �e�N�X�`���̊J������
	static void LoadScript(void);					// �I�u�W�F�N�g�A�Z�b�g�̃��[�h����

	static void LoadModel(char *add);				// ���f���̃��[�h����
	static void LoadModelTest(char *add);			// ���f���̃��[�h����

	void BindModel(std::string add);

	std::string GetAdd(void) { return m_Add; }
	LPD3DXMESH GetMesh(void) { return m_pMesh; }	// ���b�V�����̎擾

	void OnTriggerEnter(CCollider *col) {};
	void OnCollisionEnter(CCollider *col) {};
	void ShowInspector(void);

private:
#ifdef _DEBUG
	void Debug(void);								// �f�o�b�O����
#endif
	void SetAdd(std::string &Add) { m_Add = Add; }

	LPD3DXMESH		m_pMesh;							// ���b�V�����ւ̃|�C���^
	DWORD			m_nNumMat;							// �}�e���A�����̐�
	LPD3DXBUFFER		m_pBuffMat;						// �}�e���A�����ւ̃|�C���^

	CColliderBox *m_ColliderBox;											// �{�b�N�X�R���C�_�[�ւ̃|�C���^
	CColliderSphere *m_ColliderSphere;										// �X�t�B�A�R���C�_�[�ւ̃|�C���^
	std::string m_Add;														// ���f���̃A�h���X
};
#endif