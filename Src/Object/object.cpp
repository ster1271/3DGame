#include "object.h"

//�R���X�g���N�^
CObject::CObject()
{
	memset(&cPos, 0, sizeof(VECTOR));
	memset(&cRotate, 0, sizeof(VECTOR));
	iHndl = -1;
}

//�f�X�g���N�^
CObject::~CObject()
{
	if (iHndl != -1)
	{
		MV1DeleteModel(iHndl);
	}
}


