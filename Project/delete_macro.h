#pragma once

#ifndef DELETE_MACRO_H_
#define DELETE_MACRO_H_

#define NULLPTR_CHECK_DELETE(object)					\
if(object != nullptr)												\
{																		\
	delete object;													\
	object = nullptr;												\
}																		\

#define NULLPTR_CHECK_DELETE_ARRAY(object, num)	\
for(int x = 0; x < num; x++)									\
{																		\
	if (object[x] != nullptr)										\
	{																	\
		delete object[x];											\
		object[x] = nullptr;										\
	}																	\
}																		\

#endif // !DELETE_MACRO_H_
