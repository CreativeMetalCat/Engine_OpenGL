#pragma once

#ifndef MACROS

#ifndef LOG_ERROR
#define LOG_ERROR(error,errorCode,func,objName) unsigned int err = errorCode ; if(err != 0) {printf("Error( Func: %s Obj: %s): %s. Code: %i \n",#func, objName, error,err);}
#endif//!LOG_ERROR

#endif // !MACROS
