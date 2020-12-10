#pragma once
//=============================================================================
//
// �L�����I������ [characterSelect.h]
// Author : Noriyuki Hanzawa
//
//=============================================================================
#ifndef _CHARACTERSELECT_H_
#define _CHARACTERSELECT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

#define MAX_UI (8)
//=============================================================================
// �O���錾
//=============================================================================
class CTitlelogo;

//=============================================================================
// �N���X��`
//=============================================================================
class CCharacterSelect
{
public:
	CCharacterSelect();									// �R���X�g���N�^
	~CCharacterSelect();								// �f�X�g���N�^
	HRESULT Init(void);									// ����������
	void Uninit(void);									// �J������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	void SetCarType(int type)	 { m_nCarType = type; };// �Z�b�g
	int GetCarType(void)		 {return m_nCarType; };	// �Ԃ̎�ގ擾
	static void LoadAsset(void);						// �A�Z�b�g�̓ǂݍ��ݏ���

private:
	static CTitlelogo *m_pTitleLogo;			// �^�C�g�����S�̃|�C���^
	CScene2D *pBack[MAX_UI];					// UI
	int m_nCarType;								// �Ԃ̎��

};
#endif