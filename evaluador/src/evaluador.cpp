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

    // Se crea un objeto parser y string para darselo a todas las funciones
    // que necesiten hacer parser de los argumentos que ingrese el usuario o el fichero.

    Parser parser;
    string memory_name;

    if(!strcmp(argv[1], "init"))
    {
        
        // Se declaran las variables iniciales con las que empieza el espacio
        // de memoria en caso que no se pase ninguna variable.

        int i = 5;
        int ie = 6, q = 6;
        int oe = 10;
        int d = 100, b = 100, s = 100;
        bool listen = true;
        string n = "evaluator";
        vector<string> argumentos{"-i", "-ie", "-oe", "-n", "-d", "-b", "-s", "-q"};        

        // Se lee cada uno de los argumentos que vienen con el Init
        for (int x = 2; x < argc; ++x){

            // Se verifica que si esten entrando solo argumentos que se encuentren en el vector argumentos.
            string t_argument(argv[x]);
            bool exists = find(begin(argumentos), end(argumentos), t_argument) != end(argumentos);

            // Error que muestra el arg invalido.
            if (!exists){
                cout << "Argumento invalido" << endl;
                cout << "El argumento invalido es: " << argv[x] << endl;
                return 1;
            }

            // Se asigna valor -i.
            if(!strcmp(argv[x], "-i")) {
                i = stoi(argv[x + 1]);
                ++x;

                if(i == 0){
                    cout << "Valor no autorizado para i" << endl;
                    return 1;            
                }
            }

            // Se asigna valor -ie.
            if(!strcmp(argv[x], "-ie")) {
                ie = stoi(argv[x + 1]);
                ++x;

                if(ie == 0){
                    cout << "Valor no autorizado para ie" << endl;
                    return 1;            
                }
            }

            // Se asigna valor -oe.
            if(!strcmp(argv[x], "-oe")) {
                oe = stoi(argv[x + 1]);
                ++x;

                if(oe == 0){
                    cout << "Valor no autorizado para oe" << endl;
                    return 1;            
                }
            }

            // Se asigna valor -n.
            if(!strcmp(argv[x], "-n")) {
                string temp(argv[x + 1]);
                n = temp;
                ++x;
            }

            // Se asigna valor -d.
            if(!strcmp(argv[x], "-d")) {
                d = stoi(argv[x + 1]);
                ++x;

                // Doble restriccion de valor para D/B/S
                if(d == 0 || d > 100){
                    cout << "Valor no autorizado para d" << endl;
                    return 1;            
                }
            }      

            // Se asigna valor -b.
            if(!strcmp(argv[x], "-b")) {
                b = stoi(argv[x + 1]);
                ++x;

                // Doble restriccion de valor para D/B/S
                if(b == 0 || b > 100){
                    cout << "Valor no autorizado para b" << endl;
                    return 1;            
                }
            }

            // Se asigna valor -s.
            if(!strcmp(argv[x], "-s")) {
                s = stoi(argv[x + 1]);
                ++x;

                // Doble restriccion de valor para D/B/S
                if(s == 0 || s > 100){
                    cout << "Valor no autorizado para s" << endl;
                    return 1;            
                }
            }

            // Se asigna valor -q.
            if(!strcmp(argv[x], "-q")) {
                q = stoi(argv[x + 1]);
                ++x;

                if(q == 0){
                    cout << "Valor no autorizado para q" << endl;
                    return 1;            
                }
            }                                                                
        }

        // Se crea un objeto Init, donde se asignara la memoria.
        Init init;
        init.init(i, ie, oe, n, b, d, s, q);

    // Verifica si el comando principal es reg
    } else if(!strcmp(argv[1], "reg")) {

        // Crea un objeto reg, y crea una var listen para el ciclo donde escucha al usuario.
        // Si la flag -n es correcta, asigna la memoria a la varible memory_name
        // En caso contrario, cierra el programa.
        Reg reg;
        bool listen = true;
        vector<int> id_existentes;

        if(!strcmp(argv[2], "-n"))
        {
            string temp(argv[3]);
            memory_name = temp;
        } else {
            cout << "Variable invalida" << endl;
            return 1;
        }

        // Verifica si el argumento 4 es '-' para entrar en modo interactivo.
        if(!strcmp(argv[4], "-"))
        {

            cout << "Ingresando a modo interactivo" << endl;            
            string user_input;

            // Ciclo donde se escucha hasta que el usuario ingrese 'exit'
            while(listen)
            {
                cout << ">";
                getline(cin, user_input);
                cout << "El usuario ingreso: ";
                cout << user_input << endl;

                if(user_input == "exit"){
                    listen = false;
                }

                // Se parsea el input del usuario.
                string *parsed_user_input = parser.parser(user_input);

                // Se llama al metodo agregar para ingresar en la memoria el registro.
                id_existentes =reg.agregar(memory_name, stoi(parsed_user_input[0]), parsed_user_input[1], stoi(parsed_user_input[2]), id_existentes);

            }

        // Si el cuarto argumento es un path.
        } else {
            
            // Forma estandar de abrir files.
            string file_name(argv[4]);
            ifstream file(file_name);
            if(file.fail())
            {
                cout << "No se puede abrir el archivo" << endl;
            } else {
                cout << "El archivo se abrio con exito" << endl;
            }

            // Forma estandar de recibir lineas de texto de un fichero.
            for(string line; getline(file, line); )
            {
                cout << line << endl;

                // Se parsea el input del fichero.
                string *args = parser.parser(line);

                // Se llama al metodo agregar para ingresar en la memoria el registro.
                id_existentes = reg.agregar(memory_name, stoi(args[0]), args[1], stoi(args[2]), id_existentes);            

            }
        }

    } else if(!strcmp(argv[1], "ctrl")) {

        // Crea un objeto ctrl, y crea una var listen para el ciclo donde escucha los subcomandos.
        // Si la flag -n es correcta, asigna la memoria a la varible memory_name
        // En caso contrario, cierra el programa.
        // La string command almacena el comando del usuario.

        Ctrl ctrl;
        string command;
        bool listen = true;

        if(!strcmp(argv[2], "-n"))
        {
            string temp(argv[3]);
            memory_name = temp;
        } else {
            cout << "Variable invalida" << endl;
            return 1;
        }


        while(listen)
        {
            cout << ">";
            getline(cin, command);

            // Se parsea el comando introducido por el usuario.
            string *second_input = parser.parser(command);

            // Si el comando es 'list', se llama el metodo list junto con el nombre del espacio de memoria
            // y el comando que lo acompana.
            if(second_input[0] == "list"){
                ctrl.list(memory_name, second_input[1]);

            // Si el comando es 'update', asigna las siguientes variables y las manda al metodo update.
            } else if(second_input[0] == "update"){
                string tipo = second_input[1];
                int valor = stoi(second_input[2].c_str());

                ctrl.update(memory_name, tipo, valor);
            } 
        }

    // Verifica si el argumento principal es rep
    } else if(!strcmp(argv[1], "rep")){

        // Crea un objeto rep. Si la flag -n es correcta, asigna la memoria a la varible memory_name
        // En caso contrario, cierra el programa.
        Rep rep;

        if(!strcmp(argv[2], "-n"))
        {
            string temp(argv[3]);
            memory_name = temp;
        } else {
            cout << "Variable invalida" << endl;
            return 1;
        }

        // Revisa si el comando '-i' y manda al metodo mensajei junto con la cantidad de segundos.
        if(!strcmp(argv[4], "-i")){
            rep.mensajei(memory_name, stoi(argv[5]));

        // Revisa si el comando '-m' y manda al metodo mensajej junto con la cantidad de examenes.
        } else if(!strcmp(argv[4], "-m")){
            rep.mensajej(memory_name, stoi(argv[5]));
        }

    // Revisa si el comando principal es stop.
    } else if(!strcmp(argv[1], "stop")){
        
        // Crea un objeto stop. Si la flag -n es correcta, asigna la memoria a la varible memory_name
        // En caso contrario, cierra el programa.
        Stop stop;
        if(!strcmp(argv[2], "-n"))
        {
            string temp(argv[3]);
            memory_name = temp;

        } else {
            cout << "Variable invalida" << endl;
            return 1;
        }

        // Recibe el nombre de la memoria que va borrar.
        stop.stop(memory_name);

    }


    return 0;
}