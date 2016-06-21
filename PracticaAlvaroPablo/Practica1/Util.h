/* 
 * File:   Util.h
 * Author: nestor
 *
 * Created on 26 de octubre de 2015, 20:15
 */
#include <vector>
#include "Opciones.h"

using namespace std;

#ifndef UTIL_H
#define	UTIL_H

class Util {
public:
    Util();
    Util(const Util& orig);
    virtual ~Util();
    static void appendVectors(vector<int>& dest, vector<int> less, vector<int> equal, vector<int> greater);
    static void llena_vector_manual(vector<int> &v, vector<int> &v2, int tamano);
    static void llena_vector_aleatorio(vector<int> &v, vector<int> &v2, int tamano, Opciones &op);
    static void muestra_vector(vector<int> vec, int start, int end);
    static void llena_vector(vector<int> &vec,  vector<int> &vec2, Opciones &op);
    static void elegirOrdenacion(vector<int> &vectorPrincipal, Opciones &op);
    static void eligeOpciones(Opciones &op);
    static string ExePath();
    static string intToStr(int n);
    static string vectorToStr(vector<int> n);
    static string concatenarStrings(string n[], int size);
    static void leerDeUsuario(int &ret);
    static void leerDeUsuario(char &ch);
    static void pulsaEnterParacontinuar();
    static string getArrayLineCabecera(int nElemen);
    static bool ordenado(vector<int> vec);
    static bool escribirAyuda();
    
    static string _nuevoNombreArchivo();
private:

};

#endif	/* UTIL_H */

