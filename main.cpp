#include <iostream>
#include <string.h>

using namespace std;

#include "sqlite3test.h"

int main(int argc, char *argv[])
{

    HANDLE handle = InitDB("1.db");
	
    image img;
    img.name = "test123";
    AddImage(handle, img);
	
    CloseDB(handle);

    return 0;
}
