#ifndef SQLITE3TEST_H
#define SQLITE3TEST_H

#include <iostream>
#include <string.h>
#include "sqlite3.h"
#include "base.h"

using namespace std;

typedef void* HANDLE;

extern "C"{

struct image{
    std::string name;
    std::string pic1;
    std::string pic2;
    std::string pic3;
};

struct CppRes{
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;
};
//初始化db对象
HANDLE InitDB(const char* dbName);
//关闭数据库
int CloseDB(HANDLE pHandle);
//添加一条记录到数据库
int AddImage(HANDLE pHandle, image img);


}

#endif // SQLITE3TEST_H
