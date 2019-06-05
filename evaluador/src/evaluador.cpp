#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h>
#include <algorithm>
#include <vector> 
#include "parser.h"
#include "init.h"
#include "reg.h"
#include "ctrl.h"
#include "rep.h"
#include "stop.h"
#include "memory_elements.h"

using namespace std;

int main(int argc, char* argv[])
{
    Parser parser;
    int i = 5;
    int ie = 6, q = 6;
    int oe = 10;
    int d = 100, b = 100, s = 100;
    bool listen = true;
    string n = "evaluator";
    vector<string> argumentos{"-i", "-ie", "-oe", "-n", "-d", "-b", "-s", "-q"};

    if(!strcmp(argv[1], "init"))
    {

        for (int x = 2; x < argc; ++x){
            string t_argument(argv[x]);

            bool exists = find(begin(argumentos), end(argumentos), t_argument) != end(argumentos);

            if (!exists){
                cout << "Argumento invalido" << endl;
                cout << "El argumento invalido es: " << argv[x] << endl;
                return 1;
            }

            if(!strcmp(argv[x], "-i")) {
                i = stoi(argv[x + 1]);
                ++x;

                if(i == 0){
                    cout << "Valor no autorizado para i" << endl;
                    return 1;            
                }
            }

            if(!strcmp(argv[x], "-ie")) {
                ie = stoi(argv[x + 1]);
                ++x;

                if(ie == 0){
                    cout << "Valor no autorizado para ie" << endl;
                    return 1;            
                }
            }

            if(!strcmp(argv[x], "-oe")) {
                oe = stoi(argv[x + 1]);
                ++x;

                if(oe == 0){
                    cout << "Valor no autorizado para oe" << endl;
                    return 1;            
                }
            }

            if(!strcmp(argv[x], "-n")) {
                string temp(argv[x + 1]);
                n = temp;

                ++x;
            }

            if(!strcmp(argv[x], "-d")) {
                d = stoi(argv[x + 1]);
                ++x;

                if(d == 0 || d > 100){
                    cout << "Valor no autorizado para d" << endl;
                    return 1;            
                }
            }      

            if(!strcmp(argv[x], "-b")) {
                b = stoi(argv[x + 1]);
                ++x;

                if(b == 0 || b > 100){
                    cout << "Valor no autorizado para b" << endl;
                    return 1;            
                }
            }

            if(!strcmp(argv[x], "-s")) {
                s = stoi(argv[x + 1]);
                ++x;

                if(s == 0 || s > 100){
                    cout << "Valor no autorizado para s" << endl;
                    return 1;            
                }
            }

            if(!strcmp(argv[x], "-q")) {
                q = stoi(argv[x + 1]);
                ++x;

                if(q == 0){
                    cout << "Valor no autorizado para q" << endl;
                    return 1;            
                }
            }                                                                
        }

        Init init;
        init.init(i, ie, oe, n, b, d, s, q);

    } else if(!strcmp(argv[1], "reg")) {

        Reg reg;
        bool listen = true;

        string memory_name(argv[3]);

        cout << argc << endl;

        if(!strcmp(argv[4], "-"))
        {

            cout << "Ingresando a modo interactivo" << endl;
            
            string user_input;

            while(listen)
            {
                cout << ">";
                getline(cin, user_input);
                cout << "El usuario ingreso: ";
                cout << user_input << endl;

                if(user_input == "exit"){
                    listen = false;
                }

                string *parsed_user_input = parser.parser(user_input);

                reg.agregar(memory_name, stoi(parsed_user_input[0]), parsed_user_input[1], stoi(parsed_user_input[2]));

            }

        } else {
            
            string file_name(argv[4]);
            ifstream file(file_name);
            if(file.fail())
            {
                cout << "No se puede abrir el archivo" << endl;
            } else {
                cout << "El archivo se abrio con exito" << endl;
            }

            for(string line; getline(file, line); )
            {
                cout << line << endl;

                string *args = parser.parser(line);

                reg.agregar(memory_name, stoi(args[0]), args[1], stoi(args[2]));            

            }
        }

    } else if(!strcmp(argv[1], "ctrl")) {

        Ctrl ctrl;
        string memory_space(argv[3]);
        string command;
        int valor;

        while(listen)
        {
            cout << ">";
            getline(cin, command);
            string *second_input = parser.parser(command);

            if(second_input[0] == "list"){
                ctrl.list(memory_space, second_input[1]);

            } else if(second_input[0] == "update"){
                string tipo = second_input[1];
                valor = stoi(second_input[2].c_str());

                ctrl.update(memory_space, tipo, valor);
            } 
        }

    } else if(!strcmp(argv[1], "rep")){

        Rep rep;
        string memory_space(argv[3]);

        if(!strcmp(argv[4], "-i")){
            rep.mensajei(memory_space, stoi(argv[5]));

        } else if(!strcmp(argv[4], "-m")){
            rep.mensajej(memory_space, stoi(argv[5]));

        }
    } else if(!strcmp(argv[1], "stop")){
        
        Stop stop;
        string memory_space(argv[3]);

        stop.stop(memory_space);

    }


    return 0;
}