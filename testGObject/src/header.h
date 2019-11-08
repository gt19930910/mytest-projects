#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#if 0
#define LOGD(...) printf("[%s] ",__FUNCTION__);printf(__VA_ARGS__);printf("\n");
#else
#define LOGD(...) fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");
#endif



#endif // HEADER_H

