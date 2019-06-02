#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

using namespace std;

string * parser(string line)
{
    int i = 0;
    static string arr[3];
    stringstream ssin(line);

    while (ssin.good() && i < 3)
    {
        ssin >> arr[i];
        ++i;
    }

    return arr;
}

int main(int argc, char* argv[])
{
    bool listen = true;

    if(strcmp(argv[i], "-n"))
    {
        cout << "No se especifica segmento de memoria" << endl;
        return 1;
    }

    string memory_name(argv[2]);

    cout << argc << endl;

    if(argc == 4)
    {
        string file_name(argv[3]);
        ifstream file(file_name);
        if(file.fail())
        {
            cout << "No se puede abrir el archivo" << endl;
        } else {
            count << "El archivo se abrio con exito" << endl;
        }

        for(string line; getline(file, line); )
        {
            cout << line << endl;

            string *args = parser(line);

            cout << args[0] << endl;

            //FUNCION QUE RECIBE LOS 0, 1, 2

            //FIN DE ESTA FUNCION
        }
    } else {
        
        cout << "Ingresando a modo interactivo" << endl;
        
        string user_user;

        while(listen)
        {
            cout << ">";
            getline(cin, user_input);
            cout << "El usuario ingreso: ";
            cout << user_input << endl;

            if(user_input == "exit"){
                listen = false;
            }

            string *parsed_user_input = parser(user_input);
            cout << parsed_user_input[0] << endl;
            cout << parsed_user_input[1] << endl;
            cout << parsed_user_input[2] << endl;
        }
    }

    return 0;
}