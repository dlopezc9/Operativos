#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <semaphore.h>
#include "stop.h"

using namespace std;

void Stop::stop(string n){
  string slash = "/";
  slash += n;
  slash += '\n';

  cout << "Cerrando memoria " << slash << endl;

  shm_unlink(n.c_str());

  return;
}