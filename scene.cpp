//=============================================================================
//
// scene���� [scene.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "scene.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "light.h"
#include "meshField.h"
#include "meshCube.h"
#include "meshSphere.h"
#include "enemy.h"
#include "player.h"
#include "camera.h"
#include "debug.h"
#include "object.h"
#include "write.h"
#include "colliderBox.h"
#include "colliderSphere.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScene *CScene::m_apTop[CScene::PRIORITY_MAX] = {};
CScene *CScene::m_apCur[CScene::PRIORITY_MAX] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(CScene::PRIORITY Type)
{
	if (m_apTop[Type] == NULL)
	{
		m_apTop[Type] = this;																	//�������g�b�v�ɐݒ�
	}

	if (m_apCur[Type] != NULL)
	{
		m_apCur[Type]->m_pNext[Type] = this;													//�Ō���̎���������
	}

	m_pPrev[Type] = m_apCur[Type];																//�����̑O�ɍŌ��������
	m_apCur[Type] = this;																		//�Ō���������ɂ���
	m_pNext[Type] = NULL;																		//�����̎���NULL
	m_Obj = Type;																				//�I�u�W�F�N�g�^�C�v���`
	m_nNumAll++;																				//�V�[�������v���X����
	m_bActive = true;
	m_bDie = false;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene::Init(void)
{
	return S_OK;
}

//=============================================================================
// �J������
//=============================================================================
void CScene::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CScene::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene::Draw(void)
{

}

//====================================================================
// �S�ẴI�u�W�F�N�g��j�J��
//====================================================================
void CScene::ReleaseAll(void)
{
	CScene *pSceneNext = NULL;																	//����폜�Ώ�
	CScene *pSceneNow = NULL;

	CCollider::ReleaseAll();

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pSceneNow = m_apTop[nCount];

		//���S�t���O���m�F
		while (pSceneNow != NULL)
		{
			pSceneNext = pSceneNow->m_pNext[nCount];											//����t���O�m�F�Ώۂ��T����

			pSceneNow->Delete();																//�폜
			pSceneNow = NULL;

			pSceneNow = pSceneNext;																//����t���O�m�F�Ώۂ��i�[
		}
	}
}

//====================================================================
// �S�ẴI�u�W�F�N�g���X�V
//====================================================================
void CScene::UpdateAll(void)
{
	CScene *pSceneNext = NULL;																	//����A�b�v�f�[�g�Ώ�
	CScene *pSceneNow = NULL;

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pSceneNow = m_apTop[nCount];

		//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (pSceneNow != NULL)
		{
			pSceneNext = pSceneNow->m_pNext[nCount];											// ����A�b�v�f�[�g�Ώۂ��T����

			if (pSceneNow->GetActive())
			{
				pSceneNow->Update();																// �A�b�v�f�[�g
			}
			pSceneNow = pSceneNext;																// ����A�b�v�f�[�g�Ώۂ��i�[
		}
	}

	// �����蔻��
	CCollider::UpdateAll();

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pSceneNow = m_apTop[nCount];

		//���S�t���O���m�F
		while (pSceneNow != NULL)
		{
			pSceneNext = pSceneNow->m_pNext[nCount];											// ����t���O�m�F�Ώۂ��T����

			if (pSceneNow->m_bDie)
			{
				pSceneNow->Delete();															// �폜
				pSceneNow = NULL;																// NULL����
			}

			pSceneNow = pSceneNext;																// ����t���O�m�F�Ώۂ��i�[
		}
	}
}

//====================================================================
// �S�ẴI�u�W�F�N�g��`��
//====================================================================
void CScene::DrawAll(void)
{
	CScene *pSceneNext = NULL;																	// ����`��Ώ�
	CScene *pSceneNow = NULL;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pSceneNow = m_apTop[nCount];

		//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (pSceneNow != NULL)
		{
			CCamera *pCamera = CManager::GetCamera();
			pSceneNext = pSceneNow->m_pNext[nCount];											//����`��Ώۂ��T����

			if (pSceneNow->GetActive())
			{
				pSceneNow->Draw();																	//�`��
			}
			pSceneNow = pSceneNext;																//����`��Ώۂ��i�[
		}
	}
}

//====================================================================
// �����̍폜�\��
//====================================================================
void CScene::Release(void)
{
	if (!m_bDie)
	{
		m_bDie = true;
	}
}

//====================================================================
// �I�u�W�F�N�g�^�C�v�̐ݒ�
//====================================================================
void CScene::SetObjType(PRIORITY obj)
{
	m_Obj = obj;
}

//====================================================================
// �X�V�`��Ώېݒ�
//====================================================================
void CScene::SetActive(bool bValue)
{
	m_bActive = bValue;
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CScene::SetShadow(LPDIRECT3DDEVICE9 pDevice, D3DXMATRIX mtxWorld, LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh, D3DXVECTOR3 pos)
{
	D3DXMATRIX mtxShadow;
	D3DMATERIAL9 matShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 workPos, normal;

	D3DXMATERIAL	*pMat;							//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9	matDef;							//�}�e���A���f�[�^�ւ̃|�C���^

	CLight *pLight = CManager::GetLight();
	D3DLIGHT9 light = pLight->GetLight(0);
	D3DXVECTOR3 lightDef = light.Direction;

	lightDef *= -1;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = D3DXVECTOR4(lightDef.x, lightDef.y, lightDef.z, 0.0f);

	workPos = D3DXVECTOR3(pos.x, 85.0f, pos.z);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &workPos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// �|���S���ɂ������������e���v�Z����
	D3DXMatrixMultiply(&mtxShadow, &mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);					//���ׂẴf�[�^���^

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)nNumMat; nCntMat++)
	{
		matShadow = pMat[nCntMat].MatD3D;

		matShadow.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&matShadow);

		// �`��
		pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
// ���ݗ����Ă��鏰�̖�
//====================================================================
CScene *CScene::NowFloor(D3DXVECTOR3 pos)
{
	CScene *pSceneNext = NULL;														//����A�b�v�f�[�g�Ώ�
	CScene *pSceneNow = NULL;

	pSceneNow = m_apTop[PRIORITY_FLOOR];

	//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (pSceneNow != NULL)
	{
		pSceneNext = pSceneNow->m_pNext[PRIORITY_FLOOR];							//����A�b�v�f�[�g�Ώۂ��T����

		CMeshField *pField = (CMeshField*)pSceneNow;								// �N���X�`�F���W(��)

		if (pField->CollisionRange(pos))
		{// �v���C���[ �����ɏ���Ă����Ƃ�
			return pField;
		}

		pSceneNow = pSceneNext;														//����A�b�v�f�[�g�Ώۂ��i�[
	}

	return NULL;
}

//====================================================================
// ���̍��������Z�b�g
//====================================================================
void CScene::ResetFloor(void)
{
	CScene *pSceneNext = NULL;														//����A�b�v�f�[�g�Ώ�
	CScene *pSceneNow = NULL;

	pSceneNow = m_apTop[PRIORITY_FLOOR];

	//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (pSceneNow != NULL)
	{
		pSceneNext = pSceneNow->m_pNext[PRIORITY_FLOOR];							//����A�b�v�f�[�g�Ώۂ��T����

		CMeshField *pField = (CMeshField*)pSceneNow;								// �N���X�`�F���W(��)

		if (pField != NULL)
		{// �v���C���[ �����ɏ���Ă����Ƃ�
			pField->Reset();
		}

		pSceneNow = pSceneNext;														//����A�b�v�f�[�g�Ώۂ��i�[
	}
}

//====================================================================
// �ʒu�̎擾
//====================================================================
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	SetPosOld(m_pos);
	m_pos = pos;
}

//====================================================================
// �O��ʒu�̎擾
//====================================================================
void CScene::SetPosOld(D3DXVECTOR3 pos)
{
	m_posOld = pos;
}

//====================================================================
// �V�[�����擾
//====================================================================
CScene *CScene::GetScene(CScene::PRIORITY obj)
{
	return m_apTop[obj];
}

//====================================================================
// ���̃V�[�����擾
//====================================================================
CScene *CScene::GetSceneNext(CScene *pScene, PRIORITY type)
{
	return pScene->m_pNext[type];
}

//=============================================================================
// �����蔻�� �g���K�[
//=============================================================================
void CScene::OnTriggerEnter(CCollider *col)
{

}

//=============================================================================
// �����蔻�� �R���W����
//=============================================================================
void CScene::OnCollisionEnter(CCollider *col)
{

}

//=============================================================================
// �C���X�y�N�^�[��\��
//=============================================================================
void CScene::ShowInspector(void)
{
	if (ImGui::BeginMenuBar())
	{// ���j���[�o�[�̐���
		if (ImGui::BeginMenu("Add Component"))
		{// �t�@�C���^�u�̐���
			if (ImGui::BeginMenu("Physic 2D"))
			{// 2D���������}�e���A�����j���[
				if (ImGui::MenuItem("Box Collider"))
				{// �l�p�`�̓����蔻�萶��
					CCollider *pCollider = CColliderBox::Create(false, D3DXVECTOR3(550.0f, 120.0f, 50.0f));		// ����

					if (pCollider != NULL)
					{// �{�b�N�X�R���C�_�[�����݂��Ă����Ƃ�
						pCollider->SetScene(this);									// �������ݒ�
						pCollider->SetTag("none");									// fence��ݒ�
						pCollider->SetPosition(m_pos);								// �ʒu�̐ݒ�
						pCollider->SetOffset(D3DXVECTOR3(0.0f, 60.0f, 0.0f));		// �I�t�Z�b�g�l�̐ݒ�
						m_apCollider.push_back(pCollider);							// ������R���C�_�[��z��̍Ō�ɒǉ�����
					}
				}
				else if (ImGui::MenuItem("Circle Collider"))
				{// �~�̓����蔻�萶��
				}
				else if (ImGui::MenuItem("RigitBody"))
				{// �������Z�̓K��
				}

				ImGui::EndMenu();			// ���j���[�̍X�V�I��
			}

			if (ImGui::BeginMenu("Physic"))
			{// ���������}�e���A�����j���[
				if (ImGui::MenuItem("Box Collider"))
				{// �����̂̓����蔻�萶��
					CCollider *pCollider = CColliderBox::Create(false, D3DXVECTOR3(550.0f, 120.0f, 50.0f));		// ����

					if (pCollider != NULL)
					{// �{�b�N�X�R���C�_�[�����݂��Ă����Ƃ�
						pCollider->SetScene(this);									// �������ݒ�
						pCollider->SetTag("none");									// fence��ݒ�
						pCollider->SetPosition(m_pos);								// �ʒu�̐ݒ�
						pCollider->SetOffset(D3DXVECTOR3(0.0f, 60.0f, 0.0f));		// �I�t�Z�b�g�l�̐ݒ�
						m_apCollider.push_back(pCollider);							// ������R���C�_�[��z��̍Ō�ɒǉ�����
					}
				}
				else if (ImGui::MenuItem("Sphere Collider"))
				{// ���̂̓����蔻�萶��
					CCollider *pCollider = CColliderSphere::Create(false, 100.0f);		// ����

					if (pCollider != NULL)
					{// �{�b�N�X�R���C�_�[�����݂��Ă����Ƃ�
						pCollider->SetScene(this);									// �������ݒ�
						pCollider->SetTag("none");									// fence��ݒ�
						pCollider->SetPosition(m_pos);								// �ʒu�̐ݒ�
						pCollider->SetOffset(D3DXVECTOR3(0.0f, 60.0f, 0.0f));		// �I�t�Z�b�g�l�̐ݒ�
						m_apCollider.push_back(pCollider);							// ������R���C�_�[��z��̍Ō�ɒǉ�����
					}
				}
				else if (ImGui::MenuItem("RigitBody"))
				{// �������Z�̓K��
				}

				ImGui::EndMenu();			// ���j���[�̍X�V�I��
			}

			ImGui::EndMenu();			// ���j���[�̍X�V�I��
		}
		ImGui::EndMenuBar();		// ���j���[�o�[�̍X�V�I��
	}

	for (int nCount = 0; nCount < (int)m_apCollider.size(); nCount++)
	{
		switch (m_apCollider[nCount]->GetColliderType())
		{
		case COLLISIONTYPE_BOX:
			if (ImGui::CollapsingHeader("Box Collider"))
			{
				CColliderBox *pColliderBox = (CColliderBox*)m_apCollider[nCount];

				// �I�t�Z�b�g�l�̐ݒ�
				D3DXVECTOR3 offset = pColliderBox->GetOffset();
				ImGui::DragFloat3("Center", (float*)&offset);
				pColliderBox->SetOffset(offset);

				// �T�C�Y�̐ݒ�
				D3DXVECTOR3 size = pColliderBox->GetSize();
				ImGui::DragFloat3("Size", (float*)&size);
				pColliderBox->SetSize(size);
				ImGui::Text("");
			}
			break;
		case COLLISIONTYPE_SPHERE:
			if (ImGui::CollapsingHeader("Sphere Collider"))
			{
				CColliderSphere *pColliderSphere = (CColliderSphere*)m_apCollider[nCount];

				// �I�t�Z�b�g�l�̐ݒ�
				D3DXVECTOR3 offset = pColliderSphere->GetOffset();
				ImGui::DragFloat3("Center", (float*)&offset);
				pColliderSphere->SetOffset(offset);

				// �T�C�Y�̐ݒ�
				float radius = pColliderSphere->GetRadius();
				ImGui::DragFloat("Radius", (float*)&radius);
				pColliderSphere->SetRadius(radius);
				ImGui::Text("");
			}
			break;
		}
	}
}

//====================================================================
// �����̍폜
//====================================================================
void CScene::Delete(void)
{
	if (this != NULL)
	{
		//�I�������y�у��������
		this->Uninit();

		if (this->m_pPrev[m_Obj] == NULL)
		{//�������擪�������Ƃ�

			if (this->m_pNext[m_Obj] != NULL)
			{//�����̎��̃I�u�W�F�N�g������Ƃ�
				m_apTop[m_Obj] = this->m_pNext[m_Obj];											//�擪�����̃I�u�W�F�N�g�ɏ��n����

				if (m_apTop[m_Obj]->m_pPrev[m_Obj] != NULL)
				{//�O�̐l�̏�񂪂���ꍇ
					m_apTop[m_Obj]->m_pPrev[m_Obj] = NULL;										//�O�ɂ���I�u�W�F�N�g���� NULL �ɂ���
				}
			}
			else
			{//�����̎��̃I�u�W�F�N�g���Ȃ������Ƃ�
				m_apTop[m_Obj] = NULL;
				m_apCur[m_Obj] = NULL;
			}
		}
		else if (this->m_pNext[m_Obj] == NULL)
		{//�������Ō���������Ƃ�
			m_apCur[m_Obj] = m_pPrev[m_Obj];													//�Ō����O�̃I�u�W�F�N�g�ɏ��n����

			if (m_apCur[m_Obj]->m_pNext[m_Obj] != NULL)
			{
				m_apCur[m_Obj]->m_pNext[m_Obj] = NULL;											//���ɂ���I�u�W�F�N�g���� NULL �ɂ���
			}
		}
		else
		{//�ǂ���ł��Ȃ��ꍇ
			m_pNext[m_Obj]->m_pPrev[m_Obj] = m_pPrev[m_Obj];									//���̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g���Ɏ����̑O�̃I�u�W�F�N�g�����i�[����
			m_pPrev[m_Obj]->m_pNext[m_Obj] = m_pNext[m_Obj];									//�O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���Ɏ����̎��̃I�u�W�F�N�g�����i�[����
		}

		delete this;
		m_nNumAll--;																			//������������炷
	}
}

//=============================================================================
// �G�z�u�ۑ��֐�
//=============================================================================
void CScene::SaveEnemy(void)
{
	FILE *pFile;																	// �t�@�C��
	char cWriteText[128];															// �����Ƃ��ď������ݗp
	CScene *pSceneNext = NULL;														//����A�b�v�f�[�g�Ώ�
	CScene *pSceneNow = NULL;
	D3DXVECTOR3 pos;

	pFile = fopen("data/stage/enemy.csv", "w");									// �t�@�C�����J���܂��͍��

	if (pFile != NULL)																// �t�@�C�����ǂݍ��߂��ꍇ
	{
		sprintf(cWriteText, "enemy\n");
		fputs(cWriteText, pFile);													// ��������
		sprintf(cWriteText, "�ʒu X��, Y��, Z��\n");
		fputs(cWriteText, pFile);													// ��������

		// tree�̃I�u�W�F�N�g�̃|�W�V�������Q��
		pSceneNow = m_apTop[PRIORITY_ENEMY];

		//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (pSceneNow != NULL)
		{
			pSceneNext = pSceneNow->m_pNext[PRIORITY_ENEMY];							//����A�b�v�f�[�g�Ώۂ��T����
			CEnemy *pEnemy = (CEnemy*)pSceneNow;
			pos = pEnemy->GetPosition();
			sprintf(cWriteText, "%.2f, %.2f, %.2f\n", pos.x, pos.y, pos.z);
			fputs(cWriteText, pFile);												// ��������
			pSceneNow = pSceneNext;													//����A�b�v�f�[�g�Ώۂ��i�[
		}

		sprintf(cWriteText, "End");
		fputs(cWriteText, pFile);												// ��������

		//�t�@�C����
		fclose(pFile);

		MessageBox(NULL, "�G���̏����ɐ����I", "SUCCESS", MB_ICONASTERISK);
	}
	else
	{
		MessageBox(NULL, "�G�t�@�C���̃A�N�Z�X���s�I", "WARNING", MB_ICONWARNING);
	}
}

//=============================================================================
// ���N���������ݏ���
//=============================================================================
void CScene::SaveRand(void)
{
	//�ϐ��錾
	int nCntLoad = 0;			//���[�h�J�E���g
	char text[64];				// �e�L�X�g
	char cEqual[8] = { "=" };	//�C�R�[���p
	CScene *pSceneNext = NULL;	//����A�b�v�f�[�g�Ώ�
	CScene *pSceneNow = NULL;


	//�J����
	if (CWrite::Open("data/text/rand.txt"))
	{
		strcpy(text, "# �V�[���f�[�^�X�N���v�g\n");
		strcat(text, "# Author : masayasu wakita\n");

		CWrite::TitleWrite(text);				// �^�C�g���̌`���ŏ�������
		CWrite::Write("SCRIPT\n");			// �X�N���v�g�̏I���錾
		CWrite::Write("\n");

		// ���̏�� //
			// tree�̃I�u�W�F�N�g�̃|�W�V�������Q��
		pSceneNow = m_apTop[PRIORITY_FLOOR];

		//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (pSceneNow != NULL)
		{
			pSceneNext = pSceneNow->m_pNext[PRIORITY_FLOOR];						//����A�b�v�f�[�g�Ώۂ��T����
			CMeshField *pMeshField = (CMeshField*)pSceneNow;

			if (!pMeshField->GetDebugRand())
			{// �f�o�b�O�p�̏��ł͂Ȃ��Ƃ�
				CWrite::Write("FIELDSET\n");					// ���_���̏������݊J�n�錾

				D3DXVECTOR3 pos = pMeshField->GetPosition();
				CWrite::Write("	POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);		// ���S�ʒu�̏�������

				CWrite::Write("	VERTEXINFO\n");					// ���_���̏������݊J�n�錾
				pMeshField->SaveRand();							// ���_���̏�������
				CWrite::Write("	END_VERTEXINFO\n");				// ���_���̏������ݏI���錾
				CWrite::Write("END_FIELDSET\n");					// ���_���̏������݊J�n�錾
				CWrite::Write("\n");							// ���s
			}

			pSceneNow = pSceneNext;													// ����A�b�v�f�[�g�Ώۂ��i�[
		}
		CWrite::Write("END_SCRIPT\n");			// �X�N���v�g�̏I���錾
		CWrite::End();
	}
}

//=============================================================================
// ���f����񏑂����ݏ���
//=============================================================================
void CScene::SaveModel(void)
{
	//�ϐ��錾
	int nCntLoad = 0;			//���[�h�J�E���g
	char text[64];				// �e�L�X�g
	char cEqual[8] = { "=" };	//�C�R�[���p
	CScene *pSceneNext = NULL;	//����A�b�v�f�[�g�Ώ�
	CScene *pSceneNow = NULL;


	//�J����
	if (CWrite::Open("data/text/model.txt"))
	{
		strcpy(text, "# �V�[���f�[�^�X�N���v�g\n");
		strcat(text, "# Author : masayasu wakita\n");

		CWrite::TitleWrite(text);				// �^�C�g���̌`���ŏ�������
		CWrite::Write("SCRIPT\n");			// �X�N���v�g�̏I���錾
		CWrite::Write("\n");

		// ���f���̏�� //
		CWrite::IndexWrite("���f���̏��\n");

		// object�̃I�u�W�F�N�g�̃|�W�V�������Q��
		pSceneNow = m_apTop[PRIORITY_MODEL];

		//�����Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (pSceneNow != NULL)
		{
			pSceneNext = pSceneNow->m_pNext[PRIORITY_MODEL];						//����A�b�v�f�[�g�Ώۂ��T����
			CObject *pObject = (CObject*)pSceneNow;

			CWrite::Write("MODELSET\n");					// ���_���̏������݊J�n�錾

			D3DXVECTOR3 pos = pObject->GetPosition();		// �ʒu������������
			D3DXVECTOR3 rot = pObject->GetRotation();		// ��]������������

			CWrite::Write("	MODEL_FILENAME = %s\n", pObject->GetAdd().c_str());	// �A�h���X������������
			CWrite::Write("	POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);			// �ʒu������������
			CWrite::Write("	ROT = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);			// �ʒu������������

			CWrite::Write("END_MODELSET\n");				// ���_���̏������݊J�n�錾
			CWrite::Write("\n");							// ���s

			pSceneNow = pSceneNext;													// ����A�b�v�f�[�g�Ώۂ��i�[
		}
		CWrite::Write("END_SCRIPT\n");			// �X�N���v�g�̏I���錾
		CWrite::End();
	}
}