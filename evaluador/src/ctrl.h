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
    void update(string n, string tipo, int carga);
    void list(string n, string subcomando);
};