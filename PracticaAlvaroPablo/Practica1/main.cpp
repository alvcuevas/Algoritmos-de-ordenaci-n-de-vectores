/* 
 * PRACTICA 1 · COMPLEJIDAD COMPUTACIONAL · ALGORTIMOS DE ORDENACIÓN
 * File:   main.cpp
 * Author: Alvaro Cuevas y Pablo Dubikin
 * Created on 12 de octubre de 2015, 12:27
 */
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <algorithm> // for std::partition
#include <functional> // for std::less
#include "Util.h"
#include "Opciones.h"
#include "LogCoco.h"
#include "Algoritmo.h"
#include <windows.h>
#include <limits>


#define BUFSIZE 4096

using namespace std;

vector<int> vectorPrincipal, vectorSecundario;
Opciones op;

int programa();
void inicializarOpciones();
 
int main() {
    programa();
    return 0;
}

int programa(){
      
    char c;
    cout << "*************************\n";
    cout << "****** BIENVENIDO *******\n";
    cout << "*************************\n\n";

    cout << "Pulsa 'e' para empezar, o bien 'o' para ver las opciones.\n";
    Util::leerDeUsuario(c);
    
    inicializarOpciones();
    
    do{
        if(c == 'c' && op.pasoAPaso) {// Si presiona c, cerrar la consola 
            LogCoco::sendLineToOtherConsole("q", op); 
            op.readerOpen = false;
            c = 0;
        } else {
        
            if(c == 'q') break;

            if(c == 'o') Util::eligeOpciones(op);

            Util::llena_vector(vectorPrincipal, vectorSecundario, op);

            Util::elegirOrdenacion(vectorPrincipal, op);

            op.contadorPasos = 0;
            op.primeraVez = false;
            op.saltar = false;
        }
        vectorPrincipal.clear();
        cout << "\nPulsa 'e' letra para continuar, " << (op.pasoAPaso?"'c' para cerrar la consola externa, ":"") << "'o' para ver las opciones, o bien 'q' para terminar:\n";
        Util::leerDeUsuario(c);
    
    }while(c != 'q');
    
    if(op.pasoAPaso) LogCoco::sendLineToOtherConsole("q", op);
    
    cout << "\nHasta Luego!\n\n";
    return 0;
}

void inicializarOpciones(){
    op.pasoAPaso = false;
    op.mostrarAlgoritmo = false;
    op.mostrarTiempos = true;
    op.readerOpen = false;
    op.contadorPasos = 0;
    op.primeraVez = true;
    op.saltar = false;
    op.imprimirEnArchivo = false;
}
