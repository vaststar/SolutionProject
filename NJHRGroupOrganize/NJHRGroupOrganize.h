#ifndef NJHRGroupOrganize_h__
#define NJHRGroupOrganize_h__

#include "njhrgrouporganize_global.h"
//////////////////////////////////////////////////////////////////////////
///<summary> 编组管理软件 </summary>
///
///<remarks> 朱正天,2017/11/2. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class NJHRGROUPORGANIZE_EXPORT NJHRGroupOrganize
{
public:
	NJHRGroupOrganize();
	virtual ~NJHRGroupOrganize();
public:
	void startApp();
private:
	class NJHRGroupOrganizePrivate;
	NJHRGroupOrganizePrivate *_p;
};
#endif // NJHRGroupOrganize_h__
