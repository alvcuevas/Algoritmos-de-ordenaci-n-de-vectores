/* 
 * File:   Algoritmo.h
 * Author: nestor
 *
 * Created on 26 de octubre de 2015, 20:34
 */
#include <vector>
#include "Opciones.h"

using namespace std;

#ifndef ALGORITMO_H
#define	ALGORITMO_H

class Algoritmo {
public:
    Algoritmo();
    Algoritmo(const Algoritmo& orig);
    virtual ~Algoritmo();
    static vector<int> insertion_sort(vector<int> &vec, Opciones &op);
    static vector<int> bubble_sort(vector<int> &vec, Opciones &op);
    static vector<int> mergesort(vector<int> &listaDesordenada, int pinicio, int pfin, Opciones &op);
    static void sortSubarray(vector<int> &listaDesordenada, int pInicio, int pFin, Opciones &op);
    static void mergE(vector<int> &lista, int r, int p, int q, Opciones &op);
    static vector<int> quicksort(vector<int> &q, Opciones &op);
    
    // Nuevos
    static vector<int> insertion_sort_rapido(vector<int> &vec, Opciones &op);
    static vector<int> bubble_sort_rapido(vector<int> &vec, Opciones &op);
    
    
    static vector<int> quicksort_rapido(vector<int> &a, Opciones &op);
    
    //masnuevos
    static vector<int> mergesort_rapido(vector<int> &listaDesordenada, int pinicio, int pfin, Opciones &op);
    static void sortSubarray_rapido(vector<int> &listaDesordenada, int pInicio, int pFin, Opciones &op);
    static void mergE_rapido(vector<int> &lista, int r, int p, int q, Opciones &op);
private:

};

#endif	/* ALGORITMO_H */

