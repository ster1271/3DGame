#include "object.h"

//コンストラクタ
CObject::CObject()
{
	memset(&cPos, 0, sizeof(VECTOR));
	memset(&cRotate, 0, sizeof(VECTOR));
	iHndl = -1;
}

//デストラクタ
CObject::~CObject()
{
	if (iHndl != -1)
	{
		MV1DeleteModel(iHndl);
	}
}


