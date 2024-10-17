//========================================================
// 
// �^�C�}�[����[Time.h]
// Author:Rio Ohno
// 
//========================================================

#include"Time.h"

//�}�N����`
#define MAX_POLY (6)														//�ő�|���S����(Time)
#define MAX_TIME (90)														//��������(�b)
#define WIDTH_TIME (50)														//�|���S���̕�
#define HEIGHT_TIME (80)													//�|���S���̍���

//�O���[�o���錾
D3DXVECTOR3 g_pos[MAX_POLY];												//�ʒu
TIMETYPE g_TimeType;
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;								//���_�o�b�t�@�ւ̃|�C���^
int g_nCntFrame;															//�t���[���J�E���^
int g_nTime[3];																//����(����)(0=60����1�b,1=�b,2=��)
int g_TimeLim = MAX_TIME;													//��������(�b)

//========================================================
// �^�C�}�[�̏���������
//========================================================
void InitTime(TIMETYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;												//�f�o�C�X�̎擾
	int nCntTime = 0;

	//�f�o�C�X�Ɏ擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureTime);

	//���_�o�b�t�@�̂̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	for (nCntTime = 0; nCntTime < MAX_POLY; nCntTime++)
	{
		g_pos[nCntTime] = D3DXVECTOR3((WIDTH_TIME * 6) - (nCntTime * WIDTH_TIME), HEIGHT_TIME / 2, 0.0f);//�ʒu�̏�����
	}

	for (nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		g_nTime[nCntTime] = 0;												//���Ԃ̏�����(0=60����1�b,1=�b,2=��)
	}

	g_nCntFrame = 0;														//�t���[���J�E���^�̏�����
	g_TimeType=type;														//�^�C�v�̐ݒ�
	g_TimeLim = MAX_TIME;													//��������(�b)

	VERTEX_2D* pVtx = {};

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntTime = 0; nCntTime < MAX_POLY; nCntTime++)
	{
		//���_���W�̏�����
		pVtx[0].pos.x = g_pos[nCntTime].x - WIDTH_TIME / 2;
		pVtx[0].pos.y = g_pos[nCntTime].y - HEIGHT_TIME / 2;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_pos[nCntTime].x + WIDTH_TIME / 2;
		pVtx[1].pos.y = g_pos[nCntTime].y - HEIGHT_TIME / 2;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_pos[nCntTime].x - WIDTH_TIME / 2;
		pVtx[2].pos.y = g_pos[nCntTime].y + HEIGHT_TIME / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_pos[nCntTime].x + WIDTH_TIME / 2;
		pVtx[3].pos.y = g_pos[nCntTime].y + HEIGHT_TIME / 2;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏�����
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//========================================================
// �^�C�}�[�̏I������
//========================================================
void UninitTime()
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{			  
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{			  
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//========================================================
// �^�C�}�[�̍X�V����
//========================================================
void UpdateTime()
{

	switch (g_TimeType)
	{

	case TIME_CNTUP:

		//���ԃJ�E���g
		g_nCntFrame++;

		g_nTime[0] = g_nCntFrame;

		if (g_nTime[0] == 60)
		{
			g_nTime[1]++;
			g_nTime[0] = 0;
			g_nCntFrame = 0;
		}
		if (g_nTime[1] == 60)
		{
			g_nTime[2]++;
			g_nTime[1] = 0;
		}

		break;

	case TIME_CNTDOWN:

		//���ԃJ�E���g
		g_nCntFrame--;

		if (g_nCntFrame == 60)
		{
			//��b���炷
			g_TimeLim--;

			//�t���[���J�E���^�̏�����
			g_nCntFrame = 0;
		}


		break;

	default:

		break;
	}

	SetTime();
}

//========================================================
// �^�C�}�[�̐ݒ�
//========================================================
void SetTime()
{
	VERTEX_2D* pVtx = {};

	int NumTime[MAX_POLY] = {};														//�e�����i�[�p			
	int nCntTime1, nCntTime2 = 0;
	int Time[3];

	for (nCntTime1 = 0; nCntTime1 < 3; nCntTime1++)
	{
		Time[nCntTime1] = g_nTime[nCntTime1];
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime1 = 0; nCntTime1 < MAX_POLY; nCntTime1++)
	{
		NumTime[nCntTime1] = Time[nCntTime2] % 10;
		Time[nCntTime2] /= 10;

		//�e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * NumTime[nCntTime1], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * NumTime[nCntTime1], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * NumTime[nCntTime1], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * NumTime[nCntTime1], 1.0f);

		pVtx += 4;

		if (((nCntTime1+1) % 2) == 0)
		{
			nCntTime2++;
		}

	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//========================================================
// �^�C�}�[�̕`�揈��
//========================================================
void DrawTime()
{
	int nCntBlock;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (nCntBlock = MAX_POLY-1; nCntBlock >=0; nCntBlock--)
	{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTime);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
	}

}