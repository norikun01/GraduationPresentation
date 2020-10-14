//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "inputController.h"
#include "scene2D.h"
#include "camera.h"
#include "collider.h"
#include "light.h"
#include "sound.h"
#include "sceneX.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;											// �����_���[ �|�C���^��������
CInputKeyboard *CManager::m_pInputKeyboard = NULL;									// �L�[�{�[�h �|�C���^��������
CInputMouse *CManager::m_pInputMouse = NULL;										// �}�E�X �|�C���^��������
CInputController *CManager::m_pInputController = NULL;								// �R���g���[���[ �|�C���^��������
CManager::MODE CManager::m_mode = CManager::MODE_NONE;								// ���[�h �ϐ��̏�����

CCamera *CManager::m_pCamera = NULL;												// �J���� �|�C���^��������
CLight *CManager::m_pLight = NULL;													// ���C�g �|�C���^��������

CGame *CManager::m_pGame = NULL;													// �Q�[�� �|�C���^��������
CTitle *CManager::m_pTitle = NULL;													// �^�C�g�� �|�C���^��������
CResult *CManager::m_pResult = NULL;												// ���U���g �|�C���^��������
CRanking *CManager::m_pRanking = NULL;												// �����L���O �|�C���^��������

CSound *CManager::m_pSound = NULL;													// �T�E���h �|�C���^��������

std::map<std::string, LPDIRECT3DTEXTURE9> CManager::m_TexMap = {};
std::map<std::string, MODEL_INFO> CManager::m_ModelMap = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �l���Z�b�g
	srand((unsigned int)time(NULL));

	m_pRenderer = new CRenderer;																//�����_���[�̃N���G�C�g
	if (m_pRenderer != NULL)
	{// �����_���[�����݂��Ă����Ƃ�
	 // �����_���[�̏�����
		if (FAILED(m_pRenderer->Init(hInstance, hWnd, bWindow)))
		{
			MessageBox(hWnd, "�����_���[�̏������Ɏ��s", "�x��", MB_ICONWARNING);
			return E_FAIL;
		}
	}

	m_pInputKeyboard = new CInputKeyboard;														//�L�[�{�[�h�̃N���G�C�g

	if (m_pInputKeyboard != NULL)
	{// �L�[�{�[�h�����݂��Ă����Ƃ�
	 // �L�[�{�[�h�̏�����
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			MessageBox(hWnd, "�L�[�{�[�h�̏������Ɏ��s", "�x��", MB_ICONWARNING);
			return E_FAIL;
		}
	}

	m_pInputMouse = new CInputMouse;															//�}�E�X�̃N���G�C�g

	if (m_pInputMouse != NULL)
	{// �}�E�X�����݂��Ă����Ƃ�
		// �}�E�X�̏�����
		if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
		{
			MessageBox(hWnd, "�}�E�X�̏������Ɏ��s", "�x��", MB_ICONWARNING);
			return E_FAIL;
		}
	}

	m_pInputController = new CInputController;													// �R���g���[���[�̐���

	if (m_pInputController != NULL)
	{// �R���g���[���[�����݂��Ă����Ƃ�
		// �R���g���[���[�̏�����
		if (FAILED(m_pInputController->Init(hInstance, hWnd)))
		{
			MessageBox(hWnd, "�R���g���[���[�̏������Ɏ��s", "�x��", MB_ICONWARNING);
			return E_FAIL;
		}
	}

	CSceneX::InitShader();

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = m_pRenderer->GetDevice();

	m_pCamera = new CCamera;
	m_pCamera->Init();

	m_pLight = new CLight;																		//���C�g�̃N���G�C�g
	m_pLight->Init();

	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	CTitle::LoadAsset();
	CGame::LoadAsset();
	CResult::LoadAsset();

	Load("data/model/akazukin/clothes.jpg");
	Load("data/model/akazukin/hair.jpg");
	Load("data/model/akazukin/skin.jpg");
	Load("data/model/akazukin/skirt.png");

	SetMode(MODE_GAME);																		//���[�h�Z���N�g

	return S_OK;
}

//=============================================================================
// �J������
//=============================================================================
void CManager::Uninit(void)
{
	// �e�N�X�`���̊J��
	TexRelease();

	// ���f���f�[�^�̊J��
	ModelRelease();

	CSceneX::UninitShader();

	// �L�[�{�[�h�̊J������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();																	// �L�[�{�[�h�̏I������
		delete m_pInputKeyboard;																	// �L�[�{�[�h�̃��������
		m_pInputKeyboard = NULL;																	// �|�C���^��NULL�ɂ���
	}

	// �}�E�X�̊J������
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();																	// �}�E�X�̏I������
		delete m_pInputMouse;																		// �}�E�X�̃��������
		m_pInputMouse = NULL;																		// �|�C���^��NULL�ɂ���
	}

	// �R���g���[���[�̊J������
	if (m_pInputController != NULL)
	{
		m_pInputController->Uninit();																// �R���g���[���[�̏I������
		delete m_pInputController;																	// �R���g���[���[�̃��������
		m_pInputController = NULL;																	// �|�C���^��NULL�ɂ���
	}

	// �T�E���h�̊J������
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();																			// Sound�̏I������
		delete m_pSound;																			// Sound�̃��������
		m_pSound = NULL;																			// �|�C���^��NULL�ɂ���
	}

	// �J�����̊J������
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();																		// �J�����̏I������
		delete m_pCamera;																			// �J�����̃��������
		m_pCamera = NULL;																			// �|�C���^��NULL�ɂ���
	}

	// ���C�g�̊J������
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();																			// ���C�g�̏I������
		delete m_pLight;																			// ���C�g�̃��������
		m_pLight = NULL;																			// �|�C���^��NULL�ɂ���
	}

	// �^�C�g���̊J������
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();																			// �^�C�g���̏I������
		delete m_pTitle;																			// �^�C�g���̃��������
		m_pTitle = NULL;																			// �|�C���^��NULL�ɂ���
	}

	// �Q�[���̊J������
	if (m_pGame != NULL)
	{
		m_pGame->Uninit();																			// �Q�[���̏I������
		delete m_pGame;																				// �Q�[���̃��������
		m_pGame = NULL;																				// �|�C���^��NULL�ɂ���
	}

	// ���U���g�̊J������
	if (m_pResult != NULL)
	{
		m_pResult->Uninit();																		// ���U���g�̏I������
		delete m_pResult;																			// ���U���g�̃��������
		m_pResult = NULL;																			// �|�C���^��NULL�ɂ���
	}

	// �����L���O�̊J������
	if (m_pRanking != NULL)
	{
		m_pRanking->Uninit();																		// �����L���O�̏I������
		delete m_pRanking;																			// �����L���O�̃��������
		m_pRanking = NULL;																			// �|�C���^��NULL�ɂ���
	}

	// Scene�̉������
	CScene::ReleaseAll();

	// �����_���[�̊J������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();																		// Renderer�̏I������
		delete m_pRenderer;																			// Renderer�̃��������
		m_pRenderer = NULL;																			// �|�C���^��NULL�ɂ���
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	if (m_pInputController != NULL)
	{
		m_pInputController->Update();
	}

	switch (m_mode)
	{
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case CManager::MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Update();
		}
		break;
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	if (m_pSound != NULL)
	{
		m_pSound->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
#ifdef _DEBUG
	ImGui::EndFrame();
#endif

	// �`��
	m_pRenderer->Draw();
}

//========================================================================================
// ���[�h�̐ݒ�
//========================================================================================
void CManager::SetMode(MODE mode)
{
	m_pSound->StopSound();
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
		break;

	case MODE_GAME:
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
		break;

	case MODE_RESULT:
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;
		break;

	case MODE_RANKING:
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
		break;
	}

	//���݂̃��[�h����
	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = new CTitle;
		m_pTitle->Init();
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		m_pGame->Init();
		break;
	case MODE_RESULT:
		m_pResult = new CResult;
		m_pResult->Init();
		break;

	case MODE_RANKING:
		m_pRanking = new CRanking;
		m_pRanking->Init();
		break;
	}
}

//=============================================================================
// �`���ϊ�(float)�֐�
//=============================================================================
void CManager::ConvertStringToFloat(char* text, char* delimiter, float* pResult)
{
	char* tp;
	char* ctx;
	int nTemp = 1;

	tp = strtok_s(text, delimiter, &ctx);
	pResult[0] = (float)atof(tp);

	while (tp = strtok_s(NULL, ",", &ctx))
	{
		pResult[nTemp++] = (float)atof(tp);
	}
}

//=============================================================================
// 2�_�Ԃ̋����Z�o����
//=============================================================================
float CManager::GetDistance(D3DXVECTOR3 FirstTarget, D3DXVECTOR3 SecondTarget)
{
	return ((FirstTarget.x - SecondTarget.x) * (FirstTarget.x - SecondTarget.x) +
		(FirstTarget.y - SecondTarget.y) * (FirstTarget.y - SecondTarget.y) +
		(FirstTarget.z - SecondTarget.z) * (FirstTarget.z - SecondTarget.z));
}

//=============================================================================
// Rand�֐�
//=============================================================================
int CManager::GetRand(int nValue)
{
	for (int nCount = 0; nCount < 5; nCount++)
	{
		rand();						//rand�̋���s
	}

	//�����_���Ȓl��Ԃ�
	int nAnswer = rand() % (nValue);

	int Wrok = ((int)rand() + 1) / ((int)RAND_MAX + 2);

	//float frand(unsigned v) {
	unsigned res = (1 >> 9) | 0x3f800000;
	float work = (*(float*)&res) - 1.0f;
	//}
	return nAnswer;
}

//=============================================================================
// �C�[�W���O(Out)
//=============================================================================
float CManager::easeOut(float fValue)
{
	return fValue * (2 - fValue);
}

//=============================================================================
// �C�[�W���O(In)
//=============================================================================
float CManager::easeIn(float fTime, float fStart, float fDifference, float fTotal)
{
	fTime /= fTotal;
	return fDifference * fTime * fTime * fTime + fStart;
}

//=============================================================================
// �C�[�W���O(InAndOut)
//=============================================================================
float CManager::easeInAndOut(float fTime, float fStart, float fDifference, float fTotal)
{
	fTime /= fTotal / 2.0f;

	if (fTime < 1)
	{
		return fDifference / 2.0f * fTime * fTime * fTime + fStart;
	}

	fTime = fTime - 2;
	return fDifference / 2.0f * (fTime * fTime * fTime + 2) + fDifference;
}

//=============================================================================
// �w�肵���e�N�X�`�����g�����Ԃɂ��鏈��
//=============================================================================
HRESULT CManager::Load(std::string Add)
{
	std::map<std::string, LPDIRECT3DTEXTURE9>::const_iterator it = m_TexMap.find(Add);

	if (it == m_TexMap.end())
	{// ������Ȃ������Ƃ�
	 // ����������������L�[�Ƃ���
	 // �V�����}�b�v�Ƀe�N�X�`����ǉ�����
		CRenderer *pRenderer = m_pRenderer;
		LPDIRECT3DDEVICE9 pDevice;
		HRESULT hr;
		LPDIRECT3DTEXTURE9 tex = NULL;

		//�f�o�C�X���擾����
		pDevice = pRenderer->GetDevice();

		hr = D3DXCreateTextureFromFile(pDevice, Add.c_str(), &tex);


		if (FAILED(hr))
		{// �����ł��Ȃ������Ƃ���NULL��Ԃ�
			MessageBox(NULL, Add.c_str(), "LOAD ERROR", MB_OK);
			return hr;			// ���ʂ�Ԃ�
		}

		// �}�b�v�֑}������
		m_TexMap.insert(std::map<std::string, LPDIRECT3DTEXTURE9>::value_type(Add, tex));
		return hr;				// ���ʂ�Ԃ�
	}

	return E_FAIL;
}

//=============================================================================
// �w�肵���e�N�X�`�������炤����
//=============================================================================
LPDIRECT3DTEXTURE9 CManager::GetResource(std::string Add)
{
	std::map<std::string, LPDIRECT3DTEXTURE9>::const_iterator it = m_TexMap.find(Add);

	if (it == m_TexMap.end())
	{// ������Ȃ������Ƃ�
	 // ����������������L�[�Ƃ���
	 // �V�����}�b�v�Ƀe�N�X�`����ǉ�����
		CRenderer *pRenderer = m_pRenderer;
		LPDIRECT3DDEVICE9 pDevice;
		HRESULT hr;
		LPDIRECT3DTEXTURE9 tex = NULL;

		//�f�o�C�X���擾����
		pDevice = pRenderer->GetDevice();

		hr = D3DXCreateTextureFromFile(pDevice, Add.c_str(), &tex);


		if (FAILED(hr))
		{// �����ł��Ȃ������Ƃ���NULL��Ԃ�
			//MessageBox(NULL, Add.c_str(), "LOAD ERROR", MB_OK);
			return NULL;
		}

		// �}�b�v�֑}������
		m_TexMap.insert(std::map<std::string, LPDIRECT3DTEXTURE9>::value_type(Add, tex));
		return tex;
	}
	else
	{
		return it->second;
	}
}

//=============================================================================
// �w�肵�����f������ǂݍ��ޏ���
//=============================================================================
HRESULT CManager::LoadModel(std::string &Add)
{
	std::map<std::string, MODEL_INFO>::const_iterator it = m_ModelMap.find(Add);

	if (it == m_ModelMap.end())
	{// ������Ȃ������Ƃ�
	 // ����������������L�[�Ƃ���
	 // �V�����}�b�v�Ƀe�N�X�`����ǉ�����
		CRenderer *pRenderer = m_pRenderer;
		LPDIRECT3DDEVICE9 pDevice;
		HRESULT hr;
		MODEL_INFO info = {};

		//�f�o�C�X���擾����
		pDevice = pRenderer->GetDevice();

		hr = D3DXLoadMeshFromX(Add.c_str(), D3DXMESH_SYSTEMMEM, pDevice, NULL, &info.pBuffMat, NULL, &info.nNumMat, &info.pMesh);

		if (FAILED(hr))
		{// �����ł��Ȃ������Ƃ���NULL��Ԃ�
			MessageBox(NULL, Add.c_str(), "LOAD ERROR", MB_OK);
			return hr;			// ���ʂ�Ԃ�
		}

		// �}�b�v�֑}������
		m_ModelMap.insert(std::map<std::string, MODEL_INFO>::value_type(Add, info));
		return hr;				// ���ʂ�Ԃ�
	}

	return E_FAIL;
}

//=============================================================================
// �w�肵�����f�������炤����
//=============================================================================
bool CManager::GetModelResource(std::string &Add, LPD3DXBUFFER &pBuffMat, DWORD &nNumMat, LPD3DXMESH &pMesh)
{
	std::map<std::string, MODEL_INFO>::const_iterator it = m_ModelMap.find(Add);

	if (it == m_ModelMap.end())
	{// ������Ȃ������Ƃ�
	 // ����������������L�[�Ƃ���
	 // �V�����}�b�v�Ƀe�N�X�`����ǉ�����
		CRenderer *pRenderer = m_pRenderer;
		LPDIRECT3DDEVICE9 pDevice;
		HRESULT hr;
		MODEL_INFO info = {};

		//�f�o�C�X���擾����
		pDevice = pRenderer->GetDevice();

		const char* add = Add.c_str();

		hr = D3DXLoadMeshFromX(Add.c_str(), D3DXMESH_SYSTEMMEM, pDevice, NULL, &info.pBuffMat, NULL, &info.nNumMat, &info.pMesh);

		if (FAILED(hr))
		{// �����ł��Ȃ������Ƃ���NULL��Ԃ�
			MessageBox(NULL, Add.c_str(), "GetModelResource : LOAD ERROR", MB_OK);
			pBuffMat = NULL;
			nNumMat = NULL;
			pMesh = NULL;
			return false;
		}

		D3DXMATERIAL	*pMat;							//���݂̃}�e���A���ۑ��p
		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)info.pBuffMat->GetBufferPointer();

		// �}�e���A���̃e�N�X�`���ǂݍ���
		for (int nCntMat = 0; nCntMat < (int)info.nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`�����������Ƃ�
				char *pFileName = NULL;
				pFileName = pMat[nCntMat].pTextureFilename;			// �e�N�X�`���̃A�h���X���擾
				CManager::Load(pFileName);		// �e�N�X�`���̓ǂݍ���
			}
		}


		// �}�b�v�֑}������
		m_ModelMap.insert(std::map<std::string, MODEL_INFO>::value_type(Add, info));
		pBuffMat = info.pBuffMat;
		nNumMat = info.nNumMat;
		pMesh = info.pMesh;
		return true;
	}
	else
	{
		pBuffMat = it->second.pBuffMat;
		nNumMat = it->second.nNumMat;
		pMesh = it->second.pMesh;
		return true;
	}
}

//=============================================================================
// �E�B���h�E�̒��S�ʒu�Ń}�E�X�J�[�\���̈ʒu���擾
//=============================================================================
D3DXVECTOR3 CManager::GetCursorPosWithCenter(void)
{
	//�}�E�X���W���X�N���[���̒��S�����_�ɂȂ�悤�ɕ␳�i���K���j
	D3DXMATRIX mProj;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;

	// �����_���[�����݂��Ă��Ȃ��Ƃ�
	if(pRenderer == NULL) return pos;

	// �}�E�X�����݂��Ă��Ȃ��Ƃ�
	if(m_pInputMouse == NULL) return pos;

	//�f�o�C�X���擾����
	pDevice = pRenderer->GetDevice();

	pDevice->GetTransform(D3DTS_PROJECTION, &mProj);					// �v���W�F�N�V�����}�g���b�N�X�̎擾
	pos.x = (((2.0 * m_pInputMouse->GetMouseX()) / (float)SCREEN_WIDTH) - 1) / mProj._11;
	pos.y = -(((2.0 * m_pInputMouse->GetMouseY()) / (float)SCREEN_HEIGHT) - 1) / mProj._22;
	pos.z = 1.0;

	return pos;
}

//=============================================================================
// �V�X�e���ݒ�t�@�C���Ǎ�
//=============================================================================
void CManager::LoadSystemFile(void)
{
	FILE *pFile;																	// �t�@�C��
	char cReadText[128];															// ����
	char cHeadText[128];															// ��r

	pFile = fopen("data/system.ini", "r");											// �t�@�C�����J���܂��͍��

	if (pFile != NULL)																// �t�@�C�����ǂݍ��߂��ꍇ
	{
		if (pFile != NULL)
		{
			//�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
			}

			//�X�N���v�g��������
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//�G���h�X�N���v�g������܂�
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//���s
					if (strcmp(cReadText, "\n") != 0)
					{

					}
					else if (strcmp(cHeadText, "CameraOffset") == 0)
					{// �ǐՂ���J�����̃I�t�Z�b�g

					}
				}
			}
			fclose(pFile);																// �t�@�C�������

			MessageBox(NULL, "���f�����̓Ǎ��ɐ����I", "SUCCESS", MB_ICONASTERISK);		// ���b�Z�[�W�{�b�N�X�̐���
		}
		else
		{
			MessageBox(NULL, "���f�����̃A�N�Z�X���s�I", "WARNING", MB_ICONWARNING);	// ���b�Z�[�W�{�b�N�X�̐���
		}
	}
}

//=============================================================================
// �e�N�X�`���̊J��
//=============================================================================
void CManager::TexRelease(void)
{
	for (auto itr = m_TexMap.begin(); itr != m_TexMap.end(); itr++)
	{
		// �e�N�X�`���̊J��
		if (itr->second != NULL)
		{
			itr->second->Release();
			itr->second = NULL;
		}
	}

	m_TexMap.clear();
}

//=============================================================================
// ���f���f�[�^�̊J��
//=============================================================================
void CManager::ModelRelease(void)
{
	for (auto itr = m_ModelMap.begin(); itr != m_ModelMap.end(); itr++)
	{
		// �}�e���A���̊J��
		if (itr->second.pBuffMat != NULL)
		{
			itr->second.pBuffMat->Release();
			itr->second.pBuffMat = NULL;
		}

		// ���b�V�����̊J��
		if (itr->second.pMesh != NULL)
		{
			itr->second.pMesh->Release();
			itr->second.pMesh = NULL;
		}
	}

	m_ModelMap.clear();
}

//=============================================================================
// ���������̋�؂育�ƂɎ擾����(1�s����)
//=============================================================================
std::vector<std::string> CManager::split(
	std::string& input,		// 1�s�̃X�g���[��
	char delimiter		// ��؂蕶��
)
{
	// �ϐ��錾
	std::istringstream iss_Line(input);	// ������X�g���[��
	std::string sRead;					// ������ǂݍ��ݗp
	std::vector<std::string> vec_Result;		// 1�s�ǂݍ��ݗp

	// �w�肵����؂肪������胋�[�v����
	while (std::getline(iss_Line, sRead, delimiter))
	{
		// �ǂݎ������������i�[����
		vec_Result.push_back(sRead);
	}
	// �m�ۂ��������񕪕Ԃ�
	return vec_Result;
}

//=============================================================================
// �e�L�X�g�f�[�^�̒��g�𐮗����鏈��
//=============================================================================
std::vector<std::vector<std::string>> CManager::FileContens(
	char const * cns_cFile,
	char delimiter
)
{
	// �ϐ��錾
	std::ifstream				ifs_file;	// �t�@�C���p�X�g���[��
	std::string					s_Line;		// 1���I��1�s�ǂݍ���
	std::vector<std::vector<std::string>>	svec_Char;	// �t�@�C���̒��g�i�[�p

	// �t�@�C�����J��
	ifs_file.open(cns_cFile);
	// �ǂݍ��݂Ɏ��s������G���[�����o���֐��𔲂���
	if (ifs_file.fail())
	{
#ifdef _DEBUG
		MessageBox(NULL, "CCalculation::FileContens�̊֐��̃t�@�C���ǂݎ��G���[", "�x��", MB_ICONWARNING);
#endif // _DEBUG
		return svec_Char;
	}
	// �����񂪂Ȃ��Ȃ�܂Ń��[�v
	while (getline(ifs_file, s_Line))
	{
		// �P�s���ƕ�������擾����
		svec_Char.push_back(split(s_Line, delimiter));
	}
	// �t�@�C�������
	ifs_file.close();

	// �t�@�C���̒��g��Ԃ�
	return svec_Char;
}