#ifndef __COMMONLIB_H__
#define __COMMONLIB_H__

void SAFE_DELETE_ARRAY(void *p);
void SAFE_DELETE(void *p);

#define SAFE_DELETE_ARRAY(p)									\
	if(p!=NULL && p!=(void*)0xcdcdcdcd && p!=(void*)0xcccccccc)	\
	{															\
		delete []p;												\
		p=NULL;													\
	}

#define SAFE_DELETE(p)											\
	if(p!=NULL && p!=(void*)0xcdcdcdcd && p!=(void*)0xcccccccc)	\
	{															\
		delete p;												\
		p=NULL;													\
	}

#endif