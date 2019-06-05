#pragma once

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

class Ctrl {
    public:
    void update(string tipo, int carga);
    void list(string subcomando);
};