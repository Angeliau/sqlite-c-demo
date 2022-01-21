#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <time.h>

#ifndef _DEBUG_
#define _DEBUG_ 1  /* DEBUG信息开关， 0关1开 */
#endif
#if _DEBUG_
#define DEBUG(...) (printf("%s (%d) - <%s>", __FILE__, __LINE__, __FUNCTION__), printf(__VA_ARGS__), printf(("\n")))
#else
#define DEBUG(...)
#endif

#define logPrint(file, format, ...) \
    do { \
        FILE* OTAfp = NULL;\
        time_t timer;\
        struct tm *timeInfo;\
        timer = time(NULL);\
        timeInfo = localtime(&timer);\
        OTAfp = fopen(file,"a+");\
        if(OTAfp != NULL){\
                fprintf(OTAfp,"[%04d-%02d-%02d,%02d:%02d:%02d]",1900+timeInfo->tm_year,1+timeInfo->tm_mon,timeInfo->tm_mday,\
                timeInfo->tm_hour,timeInfo->tm_min,timeInfo->tm_sec);\
                fprintf(OTAfp, "[%s@%s,%d] " format, __func__, __FILE__, __LINE__, ##__VA_ARGS__ ); \
                fprintf(OTAfp, "\n");\
        }\
        fclose(OTAfp);\
    } while (0)

#endif // BASE_H
