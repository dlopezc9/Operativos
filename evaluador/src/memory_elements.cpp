#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include "memory_elements.h"

using namespace std;

char* abrir_memoria(string n) 
{
    n = "/" + n;
    int fd = shm_open(n.c_str(), O_RDWR, 0660);

    if (fd < 0) 
    {
        cerr << "Error abriendo la memoria compartida: 4"
	    << errno << strerror(errno) << endl;
        exit(1);
    }

    char *dir;
  
    if ((dir = (char *)(mmap(NULL, sizeof(struct header), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) == MAP_FAILED)
    {
      cerr << "Error mapeando la memoria compartida: 5"
	         << errno << strerror(errno) << endl;
           exit(1);
    }

    struct header *pHeader = (struct header *) dir;
  
    int i  = pHeader->i;
    int ie = pHeader->ie;
    int oe = pHeader->oe;
    int q  = pHeader->q;

    munmap((void *) pHeader, sizeof(struct header));
    size_t memorysize = sizeof(struct header) + (sizeof(struct registroentrada)* i * ie) + (sizeof(struct registrosalida) * oe);

    if ((dir = (char *)(mmap(NULL, memorysize, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0))) == MAP_FAILED) 
    {
        cerr << "Error mapeando la memoria compartida: 6" << errno << strerror(errno) << endl;
        exit(1);
    }

    return dir;
}