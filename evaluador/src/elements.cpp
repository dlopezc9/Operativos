#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include "elements.h"

using namespace std;

int Elements::generar_id() 
{
    int id = rand() % 10000;
    return id;
}