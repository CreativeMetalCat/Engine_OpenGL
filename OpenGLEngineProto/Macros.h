#pragma once

#ifndef MACROS

#ifndef LOG_ERROR
#define LOG_ERROR(error,errorCode,func,objName) if(true){unsigned int err = errorCode ; if(err != 0) {printf("Error( Func: %s Obj: %s): %s. Code: %i \n",#func, objName, error,err);}}
#endif//!LOG_ERROR

#ifndef LOG
#define LOG(what,whereFunc,whereObj) printf("%s %s %s \n",what,#whereFunc,#whereObj);
#endif
#endif // !MACROS
