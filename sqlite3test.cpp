#include "sqlite3test.h"

HANDLE InitDB(const char* dbName){
    CppRes *cppRes = new CppRes();
    if (cppRes == nullptr){
        DEBUG("cppRes create faild!");
        return nullptr;
    }
    int ret = sqlite3_open(dbName,&cppRes->db);
    if (ret != SQLITE_OK){
        DEBUG("open db fail:%s",sqlite3_errmsg(cppRes->db));
        delete cppRes;
        cppRes = nullptr;
        return nullptr;
    }
    return cppRes;
}

int CloseDB(HANDLE pHandle){
    CppRes *cppRes = static_cast<CppRes*>(pHandle);
    int ret = sqlite3_close(cppRes->db);
    if (ret != SQLITE_OK){
        DEBUG("close db fail! ret=%d,%s",ret,sqlite3_errmsg(cppRes->db));
        return ret;
    }
    return 0;
}

int AddImage(HANDLE pHandle, image img)
{
    CppRes *cppRes = static_cast<CppRes*>(pHandle);
    const char* sql = "INSERT INTO image(name,pic1,pic2,pic3) VALUES(?,?,?,?);";
    int ret = sqlite3_prepare_v2(cppRes->db, sql, -1, &cppRes->stmt, nullptr);
    sqlite3_bind_text(cppRes->stmt, 1, img.name.c_str(), -1, nullptr);

    FILE* fp1 = fopen("/home/cppfiles/sqlite3-demo/1.jpg","rb");
    long size = 0;
    if (fp1 != nullptr){
        fseek(fp1, 0, SEEK_END);
        size = ftell(fp1);
        DEBUG("size=%ld",size);
        fseek(fp1, 0, SEEK_SET);
    }else{
        DEBUG("fp1 is NULL!");
        sqlite3_finalize(cppRes->stmt);
        return -1;
    }
    char* image1 = new char[size + 1];
    size_t sz = fread(image1, sizeof(char), size+1, fp1);
    DEBUG("sz=%lu",sz);
    fclose(fp1);

    sqlite3_bind_blob(cppRes->stmt, 2, image1, size, nullptr);
    sqlite3_bind_blob(cppRes->stmt, 3, image1, size, nullptr);
    sqlite3_bind_blob(cppRes->stmt, 4, image1, size, nullptr);
    ret = sqlite3_step(cppRes->stmt);

    delete[] image1;
    image1 = nullptr;

    sqlite3_finalize(cppRes->stmt);
    if (ret != SQLITE_DONE){
        DEBUG("ret=%d, %s",ret,sqlite3_errmsg(cppRes->db));
        return -1;
    }
    return 0;
}


