//=============================================================================
//
// �f�o�b�O���� [debug.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "inputMouse.h"
#include "camera.h"
#include "scene.h"
#include "circle.h"
#include "inputKeyboard.h"
#include "meshField.h"
#include "game.h"
#include "object.h"
#include "sceneX.h"
#include "collider.h"
#include "enemy.h"
#include "inputMouse.h"
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CONTINUE_MAX 10													// �Čv�Z��

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
char CDebugProc::m_aStr[1024] = {};										// ������
D3DXVECTOR3 CDebugProc::m_mouseOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �}�E�X�̑O�̃��[���h���W
CCircle	*CDebugProc::m_pCircle = NULL;									// �~�̃|�C���^
CObject	*CDebugProc::m_pSample = NULL;									// �؂̃|�C���^
CScene *CDebugProc::m_pSelect = NULL;									// �I�������V�[���̃|�C���^
CEnemy *CDebugProc::m_pEnemy = NULL;									// �G�̃|�C���^
float CDebugProc::m_fPaintSize = 1;										// �n�`�ҏW�u���V�̑傫��
int CDebugProc::m_nCreateIndex = 0;										// 1�t���[���̐�����
bool CDebugProc::m_bDebug = false;										// �f�o�b�O���[�h�̐ؑ�
bool CDebugProc::m_bInspectorWind = false;								// �C���X�y�N�^�[�E�B���h�E�̕\���ؑ�
int CDebugProc::m_nCntGeneration = 0;									// ������
int	CDebugProc::m_nMode = 0;											// ���[�h�I��
int CDebugProc::m_nParticleShape = PARTICLESHAPE_CONE;					// �p�[�e�B�N���`��
int	CDebugProc::m_nCntContinue = 0;										// �Ċm�F��
D3DXVECTOR2 CDebugProc::m_CreateRand = D3DXVECTOR2(0.0f, 0.0f);			// ���̗�
D3DXVECTOR2 CDebugProc::m_CreateRandOld = D3DXVECTOR2(0.0f, 0.0f);			// ���̗�
CMeshField *CDebugProc::m_apMeshField[FLOOR_LIMIT * FLOOR_LIMIT] = {};
D3DXVECTOR3 CDebugProc::m_createPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float CDebugProc::m_fSliderPow = 1.0f;
std::string CDebugProc::m_currentItem = {};
bool CDebugProc::m_bHeightCalculation = false;
HWND CDebugProc::m_hWnd = NULL;											// �E�B���h�E�n���h��

// �G�t�F�N�g�쐬�֘A
int CDebugProc::m_particleLife = 0;								// �p�[�e�B�N���̐�������
int CDebugProc::m_nCreate = 0;									// ������
int CDebugProc::m_nInterval = 0;									// �C���^�[�o��
float CDebugProc::m_fStartRadius = 0.0f;							// �n�܂��
float CDebugProc::m_fRadius = 0.0f;									// ���a
float CDebugProc::m_fMinSpeed = 0.0f;								// �Œ�X�s�[�h
float CDebugProc::m_fSpeed = 0.0f;									// �X�s�[�h

bool CDebugProc::m_bLoop = false;									// �������J��Ԃ�
bool CDebugProc::m_bGravity = false;									// �d�̗͂L��
bool CDebugProc::m_bRandomSpeed = false;								// �X�s�[�h�����_�����̗L��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CDebugProc::Init(HWND hWnd)
{
	CRenderer *Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = Renderer->GetDevice();

	// �E�B���h�E�n���h����ۊ�
	m_hWnd = hWnd;

	// �f�o�b�O�\���p�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r �S�V�b�N", &m_pFont);

	//IMGUI�̏�����
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.Fonts->AddFontFromFileTTF("data\\fonts\\Meiryo.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	// �f�o�b�O�p���|�C���^�̏�����
	for (int nCount = 0; nCount < FLOOR_LIMIT * FLOOR_LIMIT; nCount++)
	{
		m_apMeshField[nCount] = NULL;
	}

	// �~�̍쐬
	m_pCircle = CCircle::Create();
	return S_OK;
}

//=============================================================================
// �J������
//=============================================================================
void CDebugProc::Uninit(void)
{
	if (m_pCircle != NULL)
	{// �~�̃|�C���^���J������Ă��Ȃ��Ƃ�
		m_pCircle->Uninit();														// �J������
		delete m_pCircle;															// �~�̊J��
		m_pCircle = NULL;															// �~�̃|�C���^��NULL��
	}

	// ���|�C���^�̊J������
	for (int nCount = 0; nCount < FLOOR_LIMIT * FLOOR_LIMIT; nCount++)
	{
		if (m_apMeshField[nCount] != NULL)
		{// �f�o�b�O�p�̏������݂��Ă����Ƃ�
			m_apMeshField[nCount] = NULL;
		}
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (m_pFont != NULL)
	{// �f�o�b�O�\���p�t�H���g�̊J��
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CDebugProc::Update(void)
{
	// �t���[���J�n
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �����ō쐬�����ȒP�ȃE�B���h�E��\�����܂��B Begin / End�y�A���g�p���āA���O�t���E�B���h�E���쐬���܂��B
	ImGui::Begin("System");                          // �uSystem�v�Ƃ����E�B���h�E���쐬���܂�����ɒǉ����܂��B

	ImGui::SameLine();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::Text("rand = %d", CManager::GetRand(10));								// �v���C���[�̌��݈ʒu��\��

	if (m_pSelect != NULL)
	{
		if (m_bInspectorWind)
		{
			//ShowInspector();
		}
	}

	CInputMouse *pMouse = CManager::GetInputMouse();
	if (pMouse->GetTriggerMouse(MOUSE_LEFT))
	{
		SelectModel();
	}

	ImGui::End();

	Debug();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDebugProc::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// �f�o�C�X�̎擾

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nTime = 0;

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �~�̕`��
	if (m_bDebug && m_nMode != DEBUGMODE_INDIVIDUAL)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ����(�����)���J�����O����
		m_pCircle->Draw();
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����
	}

	//ImGui�̕`��
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	*m_aStr = NULL;
}

//=============================================================================
// ���O�\������
//=============================================================================
void CDebugProc::Log(char* frm, ...)
{
	va_list args;			// ���X�g�̎擾
	char* c = "\n";			// ���s�p

	va_start(args, frm);		// ���X�g�̐擪���擾

	vsprintf(&m_aStr[strlen(m_aStr)], frm, args);		// �����ɓ��Ă͂߂�

	va_end(args);						// ���X�g���J������
}

//=============================================================================
// �f�o�b�O����
//=============================================================================
void CDebugProc::SelectModel(void)
{
	CScene *pSceneNext = NULL;														//����A�b�v�f�[�g�Ώ�
	CScene *pSceneNow = NULL;
	CScene *pSelect = NULL;
	float fDistance = 10000000.0f;

	//for (int nCount = 0; nCount < CScene::PRIORITY_MODEL; nCount++)
	{
		// tree�̃I�u�W�F�N�g�̃|�W�V�������Q��
		pSceneNow = CScene::GetScene(CScene::PRIORITY_MODEL);

		//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (pSceneNow != NULL)
		{
			pSceneNext = CScene::GetSceneNext(pSceneNow, (CScene::PRIORITY_MODEL));							//����A�b�v�f�[�g�Ώۂ��T����
			CObject *pObj = (CObject*)pSceneNow;

			D3DXMATRIX mWorldView;
			D3DXMATRIX m;
			D3DXVECTOR3 vRayDir;
			D3DXVECTOR3 vStartPoint;
			D3DXVECTOR3 v = CManager::GetCursorPosWithCenter();
			D3DXMATRIX mtxWorld, view;
			D3DXVECTOR3 pos = pObj->GetPosition();

			CRenderer *pRenderer = CManager::GetRenderer();
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// �f�o�C�X�̎擾
			D3DXMatrixTranslation(&mtxWorld, pos.x, pos.y, pos.z);

			pDevice->GetTransform(D3DTS_VIEW, &view);
			mWorldView = mtxWorld * view;
			D3DXMatrixInverse(&m, NULL, &mWorldView);

			//��RayDir�̓��C���΂������x�N�g��
			vRayDir.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
			vRayDir.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
			vRayDir.z = v.x * m._13 + v.y * m._23 + v.z * m._33;

			//vStartPoint�̓X�N���[����̂QD���W�i�N���b�N�ʒu�j��3D��ԍ��W�ɕϊ���������
			vStartPoint.x = m._41;
			vStartPoint.y = m._42;
			vStartPoint.z = m._43;

			//���C��������
			BOOL bHit;
			FLOAT fDist;
			LPD3DXMESH mesh = pObj->GetMesh();
			D3DXIntersect(mesh, &vStartPoint, &vRayDir, &bHit, NULL, NULL, NULL, &fDist, NULL, NULL);
			if (bHit)//���b�V���ɓ���������A���̃��b�V�������C���[�t���[�����[�h��
			{
				float fWork = CManager::GetDistance(vStartPoint, pObj->GetPosition());
				if (fDistance > fWork)
				{
					// �I�������I�u�W�F�N�g���i�[
					m_pSelect = pObj;
					m_bInspectorWind = true;
					fDistance = fWork;
				}
			}

			pSceneNow = pSceneNext;													//����A�b�v�f�[�g�Ώۂ��i�[
		}
	}
}

//=============================================================================
// �f�o�b�O����
//=============================================================================
void CDebugProc::Debug(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();		// �L�[�{�[�h�̎擾
	CCamera *pCamera = CManager::GetCamera();		// �J���� �̎擾

	ImGui::Begin("System");			// System�E�B���h�E �̐����܂��̓A�N�Z�X

	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();

	const char* listbox_items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
	static int listbox_item_current = 1;
	ImGui::ListBox("listbox\n(single select)", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);

	if (pKeyboard->GetTriggerKeyboard(DIK_D))
	{
		m_bDebug = !m_bDebug;
	}

	if (ImGui::Checkbox("DebugMode", &m_bDebug))		// �n�`�ҏW���[�h�؂�ւ�
	{
		for (int nCount = 0; nCount < FLOOR_LIMIT * FLOOR_LIMIT; nCount++)
		{
			if (m_apMeshField[nCount] == NULL)
			{// �������݂��Ă����Ƃ�
				m_apMeshField[nCount] = CMeshField::Create();
			}

			if (m_apMeshField[nCount] != NULL)
			{
				if (m_apMeshField[nCount]->GetActive())
				{// �\�����Ă����Ƃ�
					m_apMeshField[nCount]->SetDebugRand(true);
					m_apMeshField[nCount]->SetActive(false);
				}
			}
		}

		// �I�u�W�F�N�g�}�b�v
		std::map<std::string, MODEL_INFO> modelMap = CManager::GetModelMap();
		auto itr = modelMap.begin();
		m_currentItem = itr->first.c_str();
	}

	//�f�o�b�O�������I��
	ImGui::End();

	// �f�o�b�O�E�B���h�E�̐���
	if (m_bDebug)
	{
		D3DXVECTOR3 worldPos = pCamera->GetWorldPos();			// �}�E�X�̃��[���h���W���擾
		m_pCircle->SetPosition(worldPos);						// �����͈͂̈ʒu��ݒ�
		m_pCircle->SetRadius(m_fPaintSize);						// �����͈͂̑傫����ݒ�
		m_pCircle->MakeVertex();								// �~�̒��_����

		ImGui::Begin("Debug", &m_bDebug, ImGuiWindowFlags_MenuBar);   // �f�o�b�O�E�B���h�E����

		CRenderer *pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// �f�o�C�X�̎擾

		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

		if (ImGui::BeginMenuBar())
		{// ���j���[�o�[�̐���
			if (ImGui::BeginMenu("File"))
			{// �t�@�C���^�u�̐���
				if (ImGui::MenuItem("Load"))
				{// ���[�h
					// �����̓ǂݍ���
					CMeshField::LoadRand("data/stage/rand.txt", false);

					// ���f�����̓ǂݍ���
					CObject::LoadModelTest("data/text/model.txt");
				}
				if (ImGui::MenuItem("Save"))
				{// �Z�[�u
					// �����̏�������
					CScene::SaveRand();

					// ���f�����̏�������
					CScene::SaveModel();
				}

				ImGui::EndMenu();			// ���j���[�̍X�V�I��
			}
			ImGui::EndMenuBar();		// ���j���[�o�[�̍X�V�I��
		}
		ImGui::Text("[R]Press is Create");			// �f�o�b�O���[�h�e�L�X�g�\��

		ImGui::BeginTabBar("General");

		if (ImGui::BeginTabItem(u8"�����h�X�P�[�v"))
		{// �����h�X�P�[�v���[�h
			if (m_nMode != DEBUGMODE_RAND)
			{
				m_nMode = DEBUGMODE_RAND;
			}

			LandScape(worldPos);
			ImGui::Text(u8"�����h�X�P�[�v");				// ���݂̃f�o�b�O���[�h�̕\��
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem(u8"�t�H���b�W"))
		{// �t�H���b�W���[�h
			if (m_nMode != DEBUGMODE_MANY)
			{
				m_nMode = DEBUGMODE_MANY;
			}

			ImGui::SliderInt("Generation", &m_nCntGeneration, 0, 50);
			CreateObject(worldPos);					// �����z�u���[�h�̎��s
			ImGui::Text("Many Debug");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem(u8"�X�z�u"))
		{// �X�z�u���[�h
			if (m_nMode != DEBUGMODE_INDIVIDUAL)
			{
				m_nMode = DEBUGMODE_INDIVIDUAL;
			}

			CreateIndividual(worldPos);				// �X�z�u���[�h�̎��s

			if (m_pSample == NULL)
			{
				m_pSample = CObject::Create();						// ���{�p�I�u�W�F�N�g���쐬

				if (m_pSample != NULL)
				{
					m_pSample->BindModel(m_currentItem);
					m_pSample->SetPosition(worldPos);								// �ʒu���}�E�X�̃��[���h���W�ɐݒ�
					m_pSample->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));			// �F�̕ύX
				}
			}
			ImGui::SameLine();															// ���s���
			ImGui::RadioButton("delete", &m_nMode, DEBUGMODE_DELETE);					// �I���� �͈͓������������[�h ��ǉ�

			// ���݂̃f�o�b�O�^�C�v��\��
			ImGui::Text("individual Debug");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("delete"))
		{// �I�u�W�F�N�g�폜���[�h
			if (m_nMode != DEBUGMODE_DELETE)
			{
				m_nMode = DEBUGMODE_DELETE;
			}

			DeleteObject(worldPos);					// �폜���[�h�̎��s
			// ���݂̃f�o�b�O�^�C�v��\��
			ImGui::Text("individual Debug");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Randpaint"))
		{// ���_�J���[�̕ύX���[�h
			if (m_nMode != DEBUGMODE_PAINT)
			{
				m_nMode = DEBUGMODE_PAINT;
			}

			Paint(worldPos);
			ImGui::Text("Paint Debug");				// ���݂̃f�o�b�O���[�h�̕\��
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Enemy"))
		{// ���_�J���[�̕ύX���[�h
			if (m_nMode != DEBUGMODE_ENEMY)
			{
				m_nMode = DEBUGMODE_ENEMY;
			}

			if (m_pEnemy == NULL)
			{
				m_pEnemy = CEnemy::Create();			// ���{�p�I�u�W�F�N�g���쐬

				if (m_pEnemy != NULL)
				{
					m_pEnemy->SetPosition(worldPos);								// �ʒu���}�E�X�̃��[���h���W�ɐݒ�
				}
			}

			CreateEnemy(worldPos);
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();				// �^�u�̏I������

		if (pKeyboard->GetTriggerKeyboard(DIK_RCONTROL))
		{
			m_nMode = DEBUGMODE_NONE;
		}

		ImGui::Text("Rand DebugMode");			// �f�o�b�O���[�h�e�L�X�g�\��

		CDebugProc::Log("�}�E�X�̃��[���h���W : %f, %f, %f\n",			// �}�E�X�̃��[���h���W���o��
			worldPos.x,
			worldPos.y,
			worldPos.z);

		if (m_nMode != DEBUGMODE_INDIVIDUAL)
		{// �X�z�u���[�h����Ȃ��Ƃ�
			ImGui::SliderFloat("paintSize", &m_fPaintSize, 1.0f, 10000.0f);			// �X���C�_�[���g�p����1�̃t���[�g��ҏW���܂�
		}

		if (m_nMode != DEBUGMODE_RAND)
		{// �n�`�ҏW���[�h����Ȃ��Ƃ�
			if (ImGui::BeginCombo(u8"�I�u�W�F�N�g�̎��", m_currentItem.c_str()))
			{
				// �I�u�W�F�N�g�}�b�v
				std::map<std::string, MODEL_INFO> modelMap = CManager::GetModelMap();
				for (auto itr = modelMap.begin(); itr != modelMap.end(); itr++)
				{
					bool is_selected = (m_currentItem == itr->first.c_str());
					if (ImGui::Selectable(itr->first.c_str()))
					{
						m_currentItem = itr->first.c_str();
					}
				}

				ImGui::EndCombo();
			}
		}

		if (m_nMode != DEBUGMODE_INDIVIDUAL)
		{// �X�z�u���[�h�ł͂Ȃ������Ƃ�
			if (m_pSample != NULL)
			{// �|�C���^�����݂��Ă����Ƃ�
				m_pSample->Release();				// �J���\��
				m_pSample = NULL;
			}
		}

		if (m_nMode != DEBUGMODE_ENEMY)
		{// �G�l�~�[�z�u���[�h�ł͂Ȃ������Ƃ�
			if (m_pEnemy != NULL)
			{// �|�C���^�����݂��Ă����Ƃ�
				m_pEnemy->Release();
				m_pEnemy = NULL;
			}
		}

		if (ImGui::Button("Reset"))
		{// Reset �{�^���������ꂽ�Ƃ�
			CScene::ResetFloor();					// ���̍�������Z�b�g
		}

		if (m_nMode == DEBUGMODE_NONE)
		{// �������Ȃ����[�h�������Ƃ�
			ImGui::Text("None");

			// �f�o�b�O�I���{�^��
			if (ImGui::Button("Debug End"))
			{
				m_bDebug = false;

				if (m_pSample != NULL)
				{// ���{�p�̃��f�����������Ƃ�
					m_pSample->Uninit();		// �I������
					m_pSample->Release();		// �������̊J��
					m_pSample = NULL;			// NULL����
				}

				// �f�o�b�O�p���̊J������
				for (int nCount = 0; nCount < FLOOR_LIMIT * FLOOR_LIMIT; nCount++)
				{
					if (m_apMeshField[nCount] != NULL)
					{// �f�o�b�O�p�̏������݂��Ă����Ƃ�
						m_apMeshField[nCount]->Release();
						m_apMeshField[nCount] = NULL;
					}
				}
			}
		}
		else if (m_nMode == DEBUGMODE_RAND)
		{// �n�`�ҏW���[�h�������Ƃ�
		}
		else if (m_nMode == DEBUGMODE_MANY)
		{// �͈͓������������[�h�������Ƃ�
		}
		else if (m_nMode == DEBUGMODE_INDIVIDUAL)
		{// �X�z�u���[�h�������Ƃ�
		}
		else if (m_nMode == DEBUGMODE_DELETE)
		{// �폜���[�h�������Ƃ�
		}
		else if (m_nMode == DEBUGMODE_PAINT)
		{// �n�`�ҏW���[�h�������Ƃ�
		}
		else if (m_nMode == DEBUGMODE_ENEMY)
		{
		}
		// �X�V�I��
		ImGui::End();
	}
}

//=============================================================================
// �����h�X�P�[�v����
//=============================================================================
void CDebugProc::LandScape(D3DXVECTOR3 &worldPos)
{
	CInputMouse *pMouse = CManager::GetInputMouse();								// �}�E�X�̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();						// �L�[�{�[�h�̎擾

	// ���݃}�E�X�̍��W�͈͓̔��ɂ��鏰���擾����
	CScene *pSceneNext = NULL;														// ������
	CScene *pSceneNow = CScene::GetScene(CScene::PRIORITY_FLOOR);					// ���̐擪�A�h���X�̎擾

	//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (pSceneNow != NULL)
	{
		pSceneNext = CScene::GetSceneNext(pSceneNow, CScene::PRIORITY_FLOOR);		//����A�b�v�f�[�g�Ώۂ��T����
		CMeshField *pField = (CMeshField*)pSceneNow;
		if (!pField->GetDebugRand())
		{
			if (pField->CollisionRangeToCircle(worldPos, m_fPaintSize))					// �~�����͈͓̔��ɓ����Ă��邩�ǂ���
			{
				if (m_mouseOld != worldPos)
				{// �O�̍��W�ƍ���̍��W���Ⴄ�Ƃ�
					pField->CreateRand(worldPos, m_fPaintSize);
				}
			}
		}
		pSceneNow = pSceneNext;														//����A�b�v�f�[�g�Ώۂ��i�[
	}

	m_CreateRandOld = m_CreateRand;						// �O�̃f�[�^����

	// �e��X���C�_�[�̐ݒ�
	ImGui::DragFloat(u8"�����ʒu�̃X���C�h�p���[", &m_fSliderPow, 0.5f, 0.1f, 50.0f, "%.1f", 0.5f);

	if (ImGui::DragFloat3(u8"�����ʒu", (float*)&m_createPos, m_fSliderPow))
	{
		DebugFloorCreate((int)m_CreateRand.x, (int)m_CreateRand.y, m_createPos);		// �f�o�b�O�p�̏��̍Ĕz�u
	}

	if (ImGui::DragFloat2(u8"��������", (float*)&m_CreateRand, 1.0f, 0.0f, 20.0f, "%.0f", 1.0f))
	{
		DebugFloorCreate((int)m_CreateRand.x, (int)m_CreateRand.y, m_createPos);		// �f�o�b�O�p�̏��̍Ĕz�u
	}

	if (ImGui::Button(u8"����"))
	{// �����{�^���������ꂽ�Ƃ�
		CMeshField::CreateRand((int)m_CreateRand.x, (int)m_CreateRand.y, m_createPos);	// �����Ƃ������𐶐�
	}

	if (!pKeyboard->GetPressKeyboard(DIK_LALT))
	{// ��Alt�L�[��������Ă��Ȃ��Ƃ�
		if (pKeyboard->GetPressKeyboard(DIK_R))
		{// R�L�[��������Ă���Ƃ�
			if (pMouse->GetReleaseMouse(MOUSE_RIGHT))
			{// �}�E�X�̉E�{�^���������ꂽ�Ƃ�
				pSceneNow = CScene::GetScene(CScene::PRIORITY_FLOOR);					// ���̐擪�A�h���X�̎擾

				//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
				while (pSceneNow != NULL)
				{
					pSceneNext = CScene::GetSceneNext(pSceneNow, CScene::PRIORITY_FLOOR);		//����A�b�v�f�[�g�Ώۂ��T����
					CMeshField *pField = (CMeshField*)pSceneNow;

					if (!pField->GetDebugRand())
					{
						pField->CalculationNormalize();
					}

					pSceneNow = pSceneNext;														//����A�b�v�f�[�g�Ώۂ��i�[
				}
			}
			else if (pMouse->GetReleaseMouse(MOUSE_LEFT))
			{// �}�E�X�̍��{�^���������ꂽ�Ƃ�
				pSceneNow = CScene::GetScene(CScene::PRIORITY_FLOOR);					// ���̐擪�A�h���X�̎擾

				//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
				while (pSceneNow != NULL)
				{
					pSceneNext = CScene::GetSceneNext(pSceneNow, CScene::PRIORITY_FLOOR);		//����A�b�v�f�[�g�Ώۂ��T����
					CMeshField *pField = (CMeshField*)pSceneNow;

					if (!pField->GetDebugRand())
					{
						pField->CalculationNormalize();
					}

					pSceneNow = pSceneNext;														//����A�b�v�f�[�g�Ώۂ��i�[
				}
			}
		}
	}

	m_mouseOld = worldPos;
}

//=============================================================================
// ���_�F�ύX����
//=============================================================================
void CDebugProc::Paint(D3DXVECTOR3 & worldPos)
{
	CInputMouse *pMouse = CManager::GetInputMouse();								// �}�E�X�̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();						// �L�[�{�[�h�̎擾

	// ���݃}�E�X�̍��W�͈͓̔��ɂ��鏰���擾����
	CScene *pSceneNext = NULL;														// ������
	CScene *pSceneNow = CScene::GetScene(CScene::PRIORITY_FLOOR);					// ���̐擪�A�h���X�̎擾

	// �����Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (pSceneNow != NULL)
	{
		pSceneNext = CScene::GetSceneNext(pSceneNow, CScene::PRIORITY_FLOOR);		// ����A�b�v�f�[�g�Ώۂ��T����
		CMeshField *pField = (CMeshField*)pSceneNow;
		if (pField->CollisionRangeToCircle(worldPos, m_fPaintSize))					// �~�����͈͓̔��ɓ����Ă��邩�ǂ���
		{
			if (m_mouseOld != worldPos)
			{// �O�̍��W�ƍ���̍��W���Ⴄ�Ƃ�
				pField->Paint(worldPos, m_fPaintSize);
			}
		}
		pSceneNow = pSceneNext;														// ����A�b�v�f�[�g�Ώۂ��i�[
	}

	m_mouseOld = worldPos;
}

//=============================================================================
// �G�z�u����
//=============================================================================
void CDebugProc::CreateEnemy(D3DXVECTOR3 &worldPos)
{
	CInputMouse *pMouse = CManager::GetInputMouse();			// �}�E�X�̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h�̎擾
	CScene *pScene = CScene::NowFloor(worldPos);				// ���݂���ꏊ�̃t�B�[���h���擾

	D3DXVECTOR3 pos = worldPos;

	if (pScene != NULL)
	{// �������݂��Ă����Ƃ�
		CMeshField *pMeshField = (CMeshField*)pScene;			// ���̎擾
		pos.y = pMeshField->GetHeight(worldPos);				// ���̍������擾
	}

	if (m_pEnemy != NULL)
	{
		m_pEnemy->SetPosition(pos);								// ���{�p���f���̈ʒu�����݂̃}�E�X���W�ɐݒ�
	}

	if (!pKeyboard->GetPressKeyboard(DIK_LALT))
	{// Alt�L�[ ��������Ă��Ȃ��Ƃ�
		if (pKeyboard->GetPressKeyboard(DIK_R))
		{
			if (pMouse->GetTriggerMouse(MOUSE_LEFT))
			{// �}�E�X�̍��{�^���������ꂽ�Ƃ�
				CEnemy *pEnemy = CEnemy::Create();				// ���݂̌��{���쐬
				pEnemy->SetPosition(worldPos);					// ���{�̏ꏊ�ɐݒu
			}
		}
	}
}

//=============================================================================
// �����z�u����
//=============================================================================
void CDebugProc::CreateObject(D3DXVECTOR3 &worldPos)
{
	CInputMouse *pMouse = CManager::GetInputMouse();				// �}�E�X�̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();		// �L�[�{�[�h�̎擾
	CCamera *pCamera = CManager::GetCamera();						// �J�����̎擾
	CMeshField *pMeshField = CGame::GetMesh();
	CObject *pObject = NULL;

	if (!pKeyboard->GetPressKeyboard(DIK_LALT))
	{// ��Alt�L�[��������Ă��Ȃ��Ƃ�
		if (pKeyboard->GetPressKeyboard(DIK_R))
		{
			if (pMouse->GetPressMouse(MOUSE_LEFT))
			{// �}�E�X�̍��{�^����������Ă���Ƃ�
				D3DXVECTOR3 Difference;				// ����
				float fDistance;					// ����

				// �O�̈ʒu�ƌ��݂̈ʒu�Ƃ̋������Z�o
				Difference.x = m_mouseOld.x - worldPos.x;
				Difference.z = m_mouseOld.z - worldPos.z;
				fDistance = (float)sqrt(Difference.x * Difference.x + Difference.z * Difference.z);

				if (fDistance > m_fPaintSize)
				{// �O�̍��W�ƍ���̍��W���Ⴄ�Ƃ�
					// ���f���͈͔̔z�u
					for (int nCount = 0; nCount < m_nCntGeneration; nCount++)
					{
						float fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
						D3DXVECTOR3 pos = D3DXVECTOR3(sinf(D3DX_PI + 6.28f * fAngle) * ((float)CManager::GetRand((int)m_fPaintSize * 10) * 0.1f) + worldPos.x,
							0.0f,
							cosf(D3DX_PI + 6.28f * fAngle) * ((float)CManager::GetRand((int)m_fPaintSize * 10) * 0.1f) + worldPos.z);

						//���̍������擾����
						CScene *pSceneNext = NULL;			// ������
						CScene *pSceneNow = CScene::GetScene(CScene::PRIORITY_MODEL);			// �V�[���̐擪�A�h���X���擾

						//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
						while (pSceneNow != NULL)
						{
							pSceneNext = CScene::GetSceneNext(pSceneNow, CScene::PRIORITY_MODEL);		// ����A�b�v�f�[�g�Ώۂ��T����
							CMeshField *pField = (CMeshField*)pSceneNow;								// �N���X�`�F���W(��)

							if (m_nCntContinue > CONTINUE_MAX)
							{// �Čv�Z�񐔂�10��𒴂����Ƃ�
								break;
							}
							else if (50.0f > CManager::GetDistance(pSceneNow->GetPosition(), pos))
							{
								// �l�̍Ď擾
								float fAngle = float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f;
								D3DXVECTOR3 pos = D3DXVECTOR3(sinf(D3DX_PI + 6.28f * fAngle) * ((float)CManager::GetRand((int)m_fPaintSize * 10) * 0.1f) + worldPos.x,
									0.0f,
									cosf(D3DX_PI + 6.28f * fAngle) * ((float)CManager::GetRand((int)m_fPaintSize * 10) * 0.1f) + worldPos.z);

								pSceneNext = CScene::GetScene(CScene::PRIORITY_MODEL);			// �V�[���̐擪�A�h���X���擾
								m_nCntContinue++;					// �Ċm�F�񐔂Ƀv���X����
							}

							pSceneNow = pSceneNext;				//����A�b�v�f�[�g�Ώۂ��i�[
						}

						if (m_nCntContinue < CONTINUE_MAX)
						{
							// �I�u�W�F�N�g�̍쐬
							pObject = CObject::Create();
							if (pObject != NULL)
							{
								pObject->BindModel(m_currentItem);
							}
						}

						m_nCntContinue = 0;

						if (pObject != NULL)
						{
							//���̍������擾����
							CScene *pSceneNext = NULL;			// ������
							CScene *pSceneNow = CScene::GetScene(CScene::PRIORITY_FLOOR);			// �V�[���̐擪�A�h���X���擾

							//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
							while (pSceneNow != NULL)
							{
								pSceneNext = CScene::GetSceneNext(pSceneNow, CScene::PRIORITY_FLOOR);		// ����A�b�v�f�[�g�Ώۂ��T����
								CMeshField *pField = (CMeshField*)pSceneNow;								// �N���X�`�F���W(��)

								if (pField->CollisionRange(pos))
								{// �I�u�W�F�N�g �����ɏ���Ă����Ƃ�
									pos.y = pField->GetHeight(pos);										// ���̍��������߂�
									pObject->SetPosition(pos);
									break;
								}

								pSceneNow = pSceneNext;				//����A�b�v�f�[�g�Ώۂ��i�[
							}
						}
					}

					m_mouseOld = worldPos;					// �Ō�̉��H�ʒu��ۑ�
				}
			}
		}
	}
}

//=============================================================================
// �P�̔z�u����
//=============================================================================
void CDebugProc::CreateIndividual(D3DXVECTOR3 &worldPos)
{
	CInputMouse *pMouse = CManager::GetInputMouse();								// �}�E�X�̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();						// �L�[�{�[�h�̎擾
	CScene *pScene = CScene::NowFloor(worldPos);									// ���݂���ꏊ�̃t�B�[���h���擾

	D3DXVECTOR3 pos = worldPos;
	D3DXVECTOR3 rot;

	if (m_pSample != NULL)
	{// ���{�p�I�u�W�F�N�g�����݂��Ă����Ƃ�
		rot = m_pSample->GetRotation();					// ��]�l�̎擾
	}

	ImGui::DragFloat3("rot", (float*)&rot, 0.01f);

	if (pScene != NULL)
	{// �������݂��Ă����Ƃ�
		CMeshField *pMeshField = (CMeshField*)pScene;								// ���̎擾
		pos.y = pMeshField->GetHeight(worldPos);									// ���̍������擾
	}

	if (m_pSample != NULL)
	{
		if (strcmp(m_pSample->GetAdd().c_str(), m_currentItem.c_str()) != 0)
		{// ���݂̃��f���^�C�v���O��̃��f���ƈႤ�Ƃ�
			m_pSample->Uninit();															// �O�̃��f�����J��
			m_pSample->Release();															// �O�̃��f���̊J���t���O�𗧂Ă�
			m_pSample = NULL;																// �O�̃��f���̃A�h���X���̂Ă�

			m_pSample = CObject::Create();								// �V�������f���𐶐�

			if (m_pSample != NULL)
			{
				m_pSample->BindModel(m_currentItem);
			}
		}
	}

	if (m_pSample != NULL)
	{// ���{�p�I�u�W�F�N�g�����݂��Ă����Ƃ�
		m_pSample->SetPosition(pos);														// ���{�p���f���̈ʒu�����݂̃}�E�X���W�ɐݒ�
		m_pSample->SetRotation(rot);					// ��]�l�̎擾
	}

	if (!pKeyboard->GetPressKeyboard(DIK_LALT))
	{// Alt�L�[ ��������Ă��Ȃ��Ƃ�
		if (pKeyboard->GetPressKeyboard(DIK_R))
		{
			if (pMouse->GetTriggerMouse(MOUSE_LEFT))
			{// �}�E�X�̍��{�^���������ꂽ�Ƃ�
				CObject *pObject = CObject::Create();							// ���݂̌��{���쐬

				if (pObject != NULL)
				{
					pObject->BindModel(m_currentItem);
					pObject->SetPosition(worldPos);												// ���{�̏ꏊ�ɐݒu
					pObject->SetRotation(rot);
				}
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�͈͓��폜����
//=============================================================================
void CDebugProc::DeleteObject(D3DXVECTOR3 &worldPos)
{
	CInputMouse *pMouse = CManager::GetInputMouse();								// �}�E�X�̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();						// �L�[�{�[�h�̎擾

	// ���݃}�E�X�̍��W�͈͓̔��ɂ��鏰���擾����
	CScene *pSceneNext = NULL;														// ������
	CScene *pSceneNow = CScene::GetScene(CScene::PRIORITY_MODEL);					// ���̐擪�A�h���X�̎擾

	if (pKeyboard->GetPressKeyboard(DIK_R))
	{
		if (pMouse->GetPressMouse(MOUSE_LEFT))
		{// �}�E�X�̉E�{�^���������ꂽ�Ƃ�
		// �����Ȃ��Ȃ�܂ŌJ��Ԃ�
			while (pSceneNow != NULL)
			{
				pSceneNext = CScene::GetSceneNext(pSceneNow, CScene::PRIORITY_MODEL);		//����A�b�v�f�[�g�Ώۂ��T����
				CSceneX *pObject = (CSceneX*)pSceneNow;

				if (CMeshField::SphereModel(pObject->GetPosition(), worldPos, m_fPaintSize))					// �~�����͈͓̔��ɓ����Ă��邩�ǂ���
				{
					pObject->Release();
				}
				pSceneNow = pSceneNext;														//����A�b�v�f�[�g�Ώۂ��i�[
			}
		}
	}
}

//=============================================================================
// �p�[�e�B�N���쐬
//=============================================================================
void CDebugProc::CreateParticle(void)
{
	// ====================== �p�[�e�B�N���n ======================//
	ImGui::Begin("Particle");													// �p�[�e�B�N��

	ImGui::RadioButton("CONE", &m_nParticleShape, PARTICLESHAPE_CONE);							// �͈�
	ImGui::SameLine();															// ���s���
	ImGui::RadioButton("SPHERE", &m_nParticleShape, PARTICLESHAPE_SPHERE);						// ����
	ImGui::SameLine();															// ���s���
	ImGui::RadioButton("BOX", &m_nParticleShape, PARTICLESHAPE_BOX);							// ��

	ImGui::Checkbox("Loop", &m_bLoop);											// ��������
	ImGui::SameLine();															// ���s���
	ImGui::Checkbox("Gravity", &m_bGravity);									// �d��
	ImGui::SameLine();															// ���s���
	ImGui::Checkbox("Speed is Random", &m_bRandomSpeed);						// �X�s�[�h�̒l�̃����_����

	ImGui::InputInt("Life", &m_particleLife);
	ImGui::InputInt("create", &m_nCreate);
	ImGui::InputInt("Interval", &m_nInterval);
	ImGui::DragFloat("StartRadius", &m_fStartRadius, 0.5f);
	ImGui::DragFloat("Radius", &m_fRadius, 0.5f);

	if (m_bRandomSpeed)
	{
		ImGui::DragFloat("MinSpeed", &m_fMinSpeed, 0.25f);
		ImGui::DragFloat("MaxSpeed", &m_fSpeed, 0.25f);
	}
	else
	{
		ImGui::DragFloat("speed", &m_fSpeed, 0.25f);
	}

	//ImGui::DragFloat3("move", (float*)&g_move);											// �R���C�_�[�̑傫����ݒ�
	//ImGui::DragFloat3("pos", (float*)&m_ParticlePos);
	//ImGui::DragFloat3("rot", (float*)&m_particleRot, 0.001f);
	//ImGui::DragFloat3("size", (float*)&m_particleSize);

	//if (ImGui::Button("Play"))
}

//=============================================================================
// �f�o�b�O�p����������
//=============================================================================
void CDebugProc::DebugFloorCreate(const int &nWide, const int &nDepth, D3DXVECTOR3 &createPos)
{
	// �f�o�b�O�p���|�C���^�̏�����
	for (int nCount = 0; nCount < FLOOR_LIMIT * FLOOR_LIMIT; nCount++)
	{
		if (m_apMeshField[nCount] == NULL)
		{// �������݂��Ă����Ƃ�
			continue;
		}

		if (m_apMeshField[nCount]->GetActive())
		{// �\�����Ă����Ƃ�
			m_apMeshField[nCount]->SetActive(false);
		}
	}

	for (int nCntDepth = 0; nCntDepth < nDepth; nCntDepth++)
	{
		for (int nCntWide = 0; nCntWide < nWide; nCntWide++)
		{
			D3DXVECTOR3 pos;

			pos.x = (WIDE_FIELD * SIZE) * nCntWide - (((WIDE_FIELD * SIZE) * nWide) / 2) + ((WIDE_FIELD * SIZE) / 2) + createPos.x;
			pos.y = createPos.y;
			pos.z = (DEPTH_FIELD * SIZE) * nCntDepth - (((DEPTH_FIELD * SIZE) * nDepth) / 2) + ((DEPTH_FIELD * SIZE) / 2) + createPos.z;

			for (int nCount = 0; nCount < FLOOR_LIMIT * FLOOR_LIMIT; nCount++)
			{
				if (m_apMeshField[nCount] == NULL)
				{
					continue;
				}

				if (m_apMeshField[nCount]->GetActive())
				{
					continue;
				}

				m_apMeshField[nCount]->SetPosition(pos);
				m_apMeshField[nCount]->MakeVertex(NULL, true);
				m_apMeshField[nCount]->SetActive(true);
				break;
			}
		}
	}
}

//=============================================================================
// �C���X�y�N�^�[��\��
//=============================================================================
void CDebugProc::ShowInspector(void)
{
	// �����ō쐬�����ȒP�ȃE�B���h�E��\�����܂��B Begin / End�y�A���g�p���āA���O�t���E�B���h�E���쐬���܂��B
	ImGui::Begin("Inspector", &m_bInspectorWind, ImGuiWindowFlags_MenuBar);   // �C���X�y�N�^�[�E�B���h�E����

	m_pSelect->ShowInspector();							// �C���X�y�N�^�[��\��

	ImGui::End();
}