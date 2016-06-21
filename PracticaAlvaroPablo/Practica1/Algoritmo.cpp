/* 
 * File:   Algoritmo.cpp
 * Author: nestor
 * 
 * Created on 26 de octubre de 2015, 20:34
 */
#include <iostream>
#include "Algoritmo.h"
#include "Util.h"
#include <stdlib.h>
#include "Opciones.h"
#include "LogCoco.h"
#include <string.h>
#include <windows.h>
#include <limits>

Algoritmo::Algoritmo() {
}

Algoritmo::Algoritmo(const Algoritmo& orig) {
}

Algoritmo::~Algoritmo() {
}

vector<int> Algoritmo::insertion_sort_rapido(vector<int>& vec, Opciones &op) {
    
    //Recorre el vector desde el elemento 1 hasta el fin
    for (int i=1; i<vec.size(); i++) { op.contadorPasos += 4; 
            
        int x = vec[i]; op.contadorPasos+=2; //Elemento a mover
        int j = i-1; op.contadorPasos+=2; //Posicion del elemento situado a la izquierda
        
        //Compara el elemento a mover con el elemento de su izquierda, en caso de ser menor, se reemplazan.
        while(j>=0 && vec[j]>x){ op.contadorPasos+=4;       
       
            vec[j+1] = vec[j]; op.contadorPasos+=4;
            j = j-1; op.contadorPasos+=2;
        }
        // Coloca el elemento en la posición que le corresponde e imprime el vector por pantalla
        vec[j+1] = x; op.contadorPasos+=3;
    }
    return vec;
}

vector<int> Algoritmo::bubble_sort_rapido(vector<int>& vec, Opciones &op) {
    int aux;
    
    //Recorre el vector desde el principio hasta el fin - 1
    for (int i=1; i<vec.size(); i++){ op.contadorPasos += 4;
        
        //Recorro a la vez el vector menos aquello ya recorrido previamente
        for (int j=0; j<vec.size()-i; j++){ op.contadorPasos += 5; 
            
            //Comparo elementos del vector dos a dos, si un elemento es mayor que su consecutivo, se intercambian haciendo uso de una variable auxiliar
            if(vec[j] > vec[j+1]){ op.contadorPasos += 4; 
                
                aux = vec[j]; op.contadorPasos += 2; 
                vec[j] = vec[j+1]; op.contadorPasos += 4; 
                vec[j+1] = aux; op.contadorPasos += 3; 
            }
        }
    }
    
    return vec;
}

// Algoritmo de quicksort
vector<int> Algoritmo::quicksort_rapido(vector<int> &q, Opciones &op){
    vector<int> less, equal, greater;
    
    if(q.size() > 1){ op.contadorPasos+=2;
        // Pivote random entre los q.size() elementos del array.
        int pivot = q[rand()%q.size()]; op.contadorPasos+=4;
        
        // Colocamos los numeros en el vector que correspondan.
        for (int i=0; i<q.size(); i++){ op.contadorPasos+=4;
            int curr = q[i]; op.contadorPasos+=2;
            if(curr < pivot) {less.push_back(curr); op.contadorPasos+=2;}
            if(curr == pivot) {equal.push_back(curr); op.contadorPasos+=2;}
            if(curr > pivot) {greater.push_back(curr); op.contadorPasos+=2;}
        }
        
        // Hacemos la llamada recursiva con las dos partes (izquierda y luego derecha).
        quicksort_rapido(less, op); op.contadorPasos++;
        quicksort_rapido(greater, op); op.contadorPasos++;
        
        op.contadorPasos++;
        // Al final, juntamos todos los array y los metemos en q.
        Util::appendVectors(q, less, equal, greater);
    }
    return q;
}


vector<int> Algoritmo::mergesort_rapido(vector<int> &listaDesordenada, int pinicio, int pfin, Opciones &op) {
	
    int r,p,q;
    r=pinicio; op.contadorPasos++;
    p=pfin; op.contadorPasos++;
    q=(p-r) / 2; op.contadorPasos+=3;

    // voy partiendo los subarray hasta que los trozos sean de 1 Ã³ 2 elementos
    if (q>1) { op.contadorPasos++;
        
        mergesort_rapido(listaDesordenada, r,r+q, op); op.contadorPasos+=2;
        mergesort_rapido(listaDesordenada, r+q+1,p, op); op.contadorPasos+=2;
    } else {
        
        sortSubarray_rapido(listaDesordenada, r, r+q, op); op.contadorPasos+=2;
        sortSubarray_rapido(listaDesordenada, r+q+1, p, op); op.contadorPasos+=2;
    }

    // merge final con las dos mitades del array
    mergE_rapido(listaDesordenada, r, p, q, op); op.contadorPasos++;

    return listaDesordenada; // que ya está ordenada
}
	
// sortea subarray de uno o dos elementos (el mínimo)
void Algoritmo::sortSubarray_rapido(vector<int> &listaDesordenada, int pInicio, int pFin, Opciones &op) {

    int qty=pFin-pInicio; op.contadorPasos+=2;
    int otro;
    if (qty>0){ op.contadorPasos++;
        if (listaDesordenada[pInicio]>listaDesordenada[pFin]) { op.contadorPasos+=3;
            otro=listaDesordenada[pInicio]; op.contadorPasos+=2;
            listaDesordenada[pInicio]=listaDesordenada[pFin]; op.contadorPasos+=3;
            listaDesordenada[pFin]=otro; op.contadorPasos+=2;
        }
    }
}
	
// intercala dos subarrays
void Algoritmo::mergE_rapido(vector<int> &lista, int r, int p, int q, Opciones &op) {
    
    vector<int> ldef(p-r+1); op.contadorPasos+=3;
    int i=r,j=r+q+1, k=0; op.contadorPasos+=5;
    while (i<=r+q) { op.contadorPasos+=2;
        while (j<=p) { op.contadorPasos++;
            if (i <= r+q && lista[i]<lista[j] ) { op.contadorPasos+=6;
                ldef[k]=lista[i]; op.contadorPasos+=3;
                k++; op.contadorPasos++;
                i++; op.contadorPasos++;
            } else {
                ldef[k]=lista[j]; op.contadorPasos+=3;
                k++; op.contadorPasos++;
                j++; op.contadorPasos++;
            }
        }
        if (j>=p && k < ldef.size()) { op.contadorPasos+=4;
            ldef[k]=lista[i]; op.contadorPasos+=3;
            k++; op.contadorPasos++;
            i++; op.contadorPasos++;
        }
    } 
    i=0;j=r; op.contadorPasos+=2;
    for (i=0;i<ldef.size();i++,r++){  
        lista[r]=ldef[i];
    }
}

//Algoritmo de Insertion Sort
vector<int> Algoritmo::insertion_sort(vector<int> &vec, Opciones &op) {        
    int nArgs = 7;    
    
    //Recorre el vector desde el elemento 1 hasta el fin
    for (int i=1; i<vec.size(); i++) { op.contadorPasos += 4;  
    
        string strList1[nArgs] = {Util::intToStr(1) + " ", // N
                    Util::vectorToStr(vec), // Array
                    (i>9?"":" ") + Util::intToStr(i), // i
                    "  ", // x
                    "  ", // j
                    "  ", // *c
                    "Analizar si entrar en el para."};
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList1, vec.size(), false);
        
        int x = vec[i]; op.contadorPasos+=2;  //Elemento a mover 
        
        string strList2[nArgs] = {Util::intToStr(2) + " ", // N
                    Util::vectorToStr(vec), // Array
                    "  ", // i
                    (x>9?"":" ") + Util::intToStr(x), // x
                    "  ", // j
                    "  ", // *c
                    "Guardar el valor de a[i]" + Util::intToStr(vec[i]) +  " en la variable x."};
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList2, vec.size(), false);
        
        int j = i-1; op.contadorPasos++;    //Posicion del elemento situado a la izquierda
        
        string strList3[nArgs] = {Util::intToStr(3) + " ", // N
                    Util::vectorToStr(vec), // Array
                    "  ", // i
                    "  ", // x
                    (j>9?"":" ") + Util::intToStr(j), // j
                    "  ", // *c
                    "Asignar el valor de i-1 (" + Util::intToStr(i-1) + ") a la variable j."};
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList3, vec.size(), false);
        
        //Compara el elemento a mover con el elemento de su izquierda, en caso de ser menor, se reemplazan.
        while(j>=0 && vec[j]>x){ op.contadorPasos+=3;         
            string strList4[nArgs] = {Util::intToStr(4) + " ", // N
                        Util::vectorToStr(vec), // Array
                        "  ", // i
                        "  ", // x
                        "  ", // j
                        " V", // *c
                        "Se cumple la condicion. Entrando en el mientras."};
            
            LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList4, vec.size(), false);

            vec[j+1] = vec[j]; op.contadorPasos+=4;
            
            string strList5[nArgs] = {Util::intToStr(5) + " ", // N
                        Util::vectorToStr(vec), // Array
                        "  ", // i
                        "  ", // x
                        "  ", // j
                        "  ", // *c
                        "Se ha asignado a a[j+1] el a[j]."};
            
            LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList5, vec.size(), false);

            j--; op.contadorPasos++;
            
            string strList6[nArgs] = {Util::intToStr(6) + " ", // N
                        Util::vectorToStr(vec), // Array
                        "  ", // i
                        "  ", // x
                        (j>9?"":" ") + Util::intToStr(j), // j
                        "  ", // *c
                        "Se ha hecho j--."};
            
            LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList6, vec.size(), false);

        }

        string strList7[nArgs] = {Util::intToStr(7) + " ", // N
                    Util::vectorToStr(vec), // Array
                    "  ", // i
                    "  ", // x
                    "  ", // j
                    " F", // *c
                    "No se cumple la condición.. Saliendo del para."};

        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList7, vec.size(), false);
        
        // Coloca el elemento en la posición que le corresponde e imprime el vector por pantalla
        vec[j+1] = x; op.contadorPasos+=2;

        string strList8[nArgs] = {Util::intToStr(8) + " ", // N
                    Util::vectorToStr(vec), // Array
                    "  ", // i
                    "  ", // x
                    "  ", // j
                    "  ", // *c
                    "Se ha colocado el valor de la x (" + Util::intToStr(x) + ") en la posicion j+1."};

        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList8, vec.size(), (i==vec.size()-1));
    }
    return vec;
}


//Algoritmo de Bubble Sort
vector<int> Algoritmo::bubble_sort(vector<int> &vec, Opciones &op) {
    
    int aux;
    int nArgs = 6;
    
    //Recorre el vector desde el principio hasta el fin - 1
    for (int i=1; i<vec.size()-1; i++){ op.contadorPasos += 3;
        
        string strList1[nArgs] = {Util::intToStr(1) + " ", // N
                        Util::vectorToStr(vec), // Array
                        (i>9?"":" ") + Util::intToStr(i), // i
                        "  ", // j
                        "  ", // vec[j] > vec[j+1]
                        "Recorre el vector siendo la i."};
            
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList1, vec.size(), (i==vec.size()-1));
        
        //Recorro a la vez el vector menos aquello ya recorrido previamente
        for (int j=0; j<vec.size()-i; j++){ op.contadorPasos += 3;
            
            string strList2[nArgs] = {Util::intToStr(2) + " ", // N
                        Util::vectorToStr(vec), // Array
                        "  ", // i
                        (j>9?"":" ") + Util::intToStr(i), // j
                        "  ", // vec[j] > vec[j+1]
                        "Recorre el vector siendo la j."};
            
            LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList2, vec.size(), (i==vec.size()-1));
            
            //Comparo elementos del vector dos a dos, si un elemento es mayor que su consecutivo, se intercambian haciendo uso de una variable auxiliar
            if(vec[j] > vec[j+1]){ op.contadorPasos += 3;
                
                string strList3[nArgs] = {Util::intToStr(3) + " ", // N
                        Util::vectorToStr(vec), // Array
                        "  ", // i
                        "  ", // j
                        "SI", // vec[j] > vec[j+1]
                        "El elemento es mayor que su consecutivo."};
            
                LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList3, vec.size(), (i==vec.size()-1));
                 
                aux = vec[j]; op.contadorPasos += 2; 
                vec[j] = vec[j+1]; op.contadorPasos += 3; 
                vec[j+1] = aux; op.contadorPasos += 2; 
            }
            
            
        }
    }
    
    return vec;
}

// Algoritmo de quicksort
vector<int> Algoritmo::quicksort(vector<int> &q, Opciones &op){
    
    int nArgs=7;
    vector<int> less, equal, greater;
    
    if(q.size() > 1){ op.contadorPasos+=2;
    
        // Pivote random entre los q.size() elementos del array.
        int pivot = q[rand()%q.size()]; op.contadorPasos+=4;
        
        string strList1[nArgs] = {Util::intToStr(1) + " ", // N
                        Util::vectorToStr(q), // Array
                        (pivot>9?"":" ") + Util::intToStr(pivot), // p
                        "  ", // j
                        " <", // < = > 
                        " V", // c1
                        "Entra en el primer if. Setea pivote-"};
            
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList1, q.size(), false);
        
        // Colocamos los numeros en el vector que correspondan.
        for (int i=0; i<q.size(); i++){ op.contadorPasos+=4;
            
            int curr = q[i]; op.contadorPasos+=2;
            if(curr < pivot) {
                less.push_back(curr);
                string strList2[nArgs] = {Util::intToStr(2) + " ", // N
                        Util::vectorToStr(q), // Array
                        "  ", // p
                        (curr>9?"":" ") + Util::intToStr(curr), // cu
                        " <", // < = > 
                        "  ", // c1
                        " curr < pivot. Metiendo el valor de curr en less."};
            
                LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList2, q.size(), false);
                op.contadorPasos+=2;
            }
            if(curr == pivot) {
                equal.push_back(curr);
                string strList3[nArgs] = {Util::intToStr(3) + " ", // N
                        Util::vectorToStr(q), // Array
                        "  ", // p
                        (curr>9?"":" ") + Util::intToStr(curr), // cu
                        " =", // < = > 
                        "  ", // c1
                        " curr = pivot. Metiendo el valor de curr en equal."};
            
                LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList3, q.size(), false);
                op.contadorPasos+=2;
            }
            if(curr > pivot) {
                greater.push_back(curr);
                string strList4[nArgs] = {Util::intToStr(4) + " ", // N
                        Util::vectorToStr(q), // Array
                        "  ", // p
                        (curr>9?"":" ") + Util::intToStr(curr), // cu
                        " >", // < = > 
                        "  ", // c1
                        " curr > pivot. Metiendo el valor de curr en greater."};
            
                LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList4, q.size(), false);
                op.contadorPasos+=2;
            }
        }
        
        string strList5[nArgs] = {Util::intToStr(5) + " ", // N
                        Util::vectorToStr(q), // Array
                        "  ", // p
                        "  ", // cu
                        "  ", // < = > 
                        "  ", // c1
                        " Va a hacer la llamada recursiva con el vector less."};
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList5, q.size(), false);
        // Hacemos la llamada recursiva con las dos partes (izquierda y luego derecha).
        quicksort(less, op); op.contadorPasos++;
        
        string strList6[nArgs] = {Util::intToStr(6) + " ", // N
                        Util::vectorToStr(q), // Array
                        "  ", // p
                        "  ", // cu
                        "  ", // < = > 
                        "  ", // c1
                        " Va a hacer la llamada recursiva con el vector greater."};
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList6, q.size(), false);
        quicksort(greater, op); op.contadorPasos++;
        
        string strList7[nArgs] = {Util::intToStr(7) + " ", // N
                        Util::vectorToStr(q), // Array
                        "  ", // p
                        "  ", // cu
                        "  ", // < = > 
                        "  ", // c1
                        " Va a hacer append con los tres vectores."};
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList7, q.size(), false);
        
        op.contadorPasos++;
        // Al final, juntamos todos los array y los metemos en q.
        Util::appendVectors(q, less, equal, greater);
    }
    return q;
}

vector<int> Algoritmo::mergesort(vector<int> &listaDesordenada, int pinicio, int pfin, Opciones &op) {

    // Ha cambiado dentro de método (dentro del sort) entonces escribimos la línea
    if(op.contadorPasos>0)LogCoco::escribirCabeceraDeAlgoritmo(7,op,listaDesordenada.size());
    
    int nArgs = 7;
    int r,p,q;
    r=pinicio; op.contadorPasos++;
    p=pfin; op.contadorPasos++;
    q=(p-r) / 2; op.contadorPasos+=3;

    string strList1[nArgs] = {Util::intToStr(1) + " ",
                           Util::vectorToStr(listaDesordenada),
                           (r<9?" ":"") + Util::intToStr(r), // r
                           (p<9?" ":"") + Util::intToStr(p), // p
                           (q<9?" ":"") + Util::intToStr(q), // q
                           "  ", // c1 (q>1)
                           " Seteando los valores de r, p y q."}; // Acción
    LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList1, listaDesordenada.size(), false);
    
    // voy partiendo los subarray hasta que los trozos sean de 1 o 2 elementos
    if (q>1) { op.contadorPasos++;
        
        string strList2[nArgs] = {Util::intToStr(2) + " ",
                               Util::vectorToStr(listaDesordenada),
                               "  ", // r
                               "  ", // p
                               "  ", // q
                               " V", // c1 (q>1)
                               " Llamada recursiva desde r(" + Util::intToStr(r) + ") hasta r+q(" + Util::intToStr(r+q) + ")."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList2, listaDesordenada.size(), false);
        mergesort(listaDesordenada, r,r+q, op); op.contadorPasos+=2;
        
        string strList3[nArgs] = {Util::intToStr(3) + " ",
                               Util::vectorToStr(listaDesordenada),
                               "  ", // r
                               "  ", // p
                               "  ", // q
                               " V", // c1 (q>1)
                               " Llamada recursiva desde r+q+1(" + Util::intToStr(r+q+1) + ") hasta p(" + Util::intToStr(p) + ")."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList3, listaDesordenada.size(), false);
        mergesort(listaDesordenada, r+q+1,p, op); op.contadorPasos+=2;
    } else {
        
        string strList4[nArgs] = {Util::intToStr(4) + " ",
                               Util::vectorToStr(listaDesordenada),
                               "  ", // r
                               "  ", // p
                               "  ", // q
                               " F", // c1 (q>1)
                               " Va a ordenar el vector izq desde r(" + Util::intToStr(r) + ") hasta r+q(" + Util::intToStr(r+q) + ")."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList4, listaDesordenada.size(), false);
        sortSubarray(listaDesordenada, r, r+q, op); op.contadorPasos+=2;
        
        LogCoco::escribirCabeceraDeAlgoritmo(7,op,listaDesordenada.size()); // Escribimos la cabecera de nuevo porque vuelve a este método justo aquí
        string strList5[nArgs] = {Util::intToStr(5) + " ",
                               Util::vectorToStr(listaDesordenada),
                               "  ", // r
                               "  ", // p
                               "  ", // q
                               " F", // c1 (q>1)
                               " Va a ordenar el vector der desde r+q+1(" + Util::intToStr(r+q+1) + ") hasta p(" + Util::intToStr(p) + ")."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList5, listaDesordenada.size(), false);
        sortSubarray(listaDesordenada, r+q+1, p, op); op.contadorPasos+=2;
    }

    LogCoco::escribirCabeceraDeAlgoritmo(7,op,listaDesordenada.size()); // Escribimos la cabecera de nuevo porque vuelve a este método justo aquí
    string strList6[nArgs] = {Util::intToStr(6) + " ",
                               Util::vectorToStr(listaDesordenada),
                               "  ", // r
                               "  ", // p
                               "  ", // q
                               "  ", // c1 (q>1)
                               " Vamos a hacer mergE entre las dos partes del array."}; // Acción
    LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList6, listaDesordenada.size(), false);    
    // merge final con las dos mitades del array
    mergE(listaDesordenada, r, p, q, op); op.contadorPasos++;
    
    return listaDesordenada; // que ya está ordenada
}

// sortea subarray de uno o dos elementos (el mínimo)
void Algoritmo::sortSubarray(vector<int> &listaDesordenada, int pInicio, int pFin, Opciones &op) {

    LogCoco::escribirCabeceraDeAlgoritmo(5,op,listaDesordenada.size());
    
    int nArgs = 8;
    int qty=pFin-pInicio; op.contadorPasos+=2;
    int otro;
    string strList7[nArgs] = {Util::intToStr(7) + " ",
                              Util::vectorToStr(listaDesordenada),
                              (pInicio<9?" ":"") + Util::intToStr(pInicio), // i
                              (pFin<9?" ":"") + Util::intToStr(pFin), // f
                              (qty<9?" ":"") + Util::intToStr(qty), // qt
                              "  ", // ot
                              "  ", // c1
                              " Inicializamos qty=pFin-pInicio."}; // Acción
    LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList7, listaDesordenada.size(), false);
    
    
    if (qty>0 && listaDesordenada[pInicio]>listaDesordenada[pFin]){ op.contadorPasos++;
        
        otro=listaDesordenada[pInicio]; op.contadorPasos+=2;
        string strList8[nArgs] = {Util::intToStr(8) + " ",
                                  Util::vectorToStr(listaDesordenada),
                                  "  ", // i
                                  "  ", // f
                                  "  ", // qt
                                  (otro<9?" ":"") + Util::intToStr(otro), // ot
                                  " V", // c
                                  " Condición verdadera, seteamos otro=listaDesordenada[pInicio]."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList8, listaDesordenada.size(), false);
        
        listaDesordenada[pInicio]=listaDesordenada[pFin]; op.contadorPasos+=3;
        string strList9[nArgs] = {Util::intToStr(9) + " ",
                                  Util::vectorToStr(listaDesordenada),
                                  "  ", // i
                                  "  ", // f
                                  "  ", // qt
                                  "  ", // ot
                                  "  ", // c
                                  " Seteamos listaDesordenada[pInicio]=listaDesordenada[pFin]."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList9, listaDesordenada.size(), false);
        
        listaDesordenada[pFin]=otro; op.contadorPasos+=2;
        string strList10[nArgs] = {Util::intToStr(10),
                                  Util::vectorToStr(listaDesordenada),
                                  "  ", // i
                                  "  ", // f
                                  "  ", // qt
                                  "  ", // ot
                                  "  ", // c
                                  " Seteamos listaDesordenada[pFin]=otro."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList10, listaDesordenada.size(), false);
        
    }
}

// intercala dos subarrays
void Algoritmo::mergE(vector<int> &lista, int r, int p, int q, Opciones &op) {
    
    LogCoco::escribirCabeceraDeAlgoritmo(6,op,lista.size());
    int nArgs = 11;
    
    vector<int> ldef(p-r+1); op.contadorPasos+=3;
    int i=r,j=r+q+1, k=0; op.contadorPasos+=5;
    
    string strList11[nArgs] = {Util::intToStr(11),
                                  Util::vectorToStr(lista),
                                  Util::vectorToStr(ldef),
                                  "  ", // i
                                  "  ", // j
                                  "  ", // k
                                  "  ", // c1
                                  "  ", // c2
                                  "  ", // c3
                                  "  ", // c4
                                  " Seteadas variables i,j,k. Inicializado vector ldef con " + Util::intToStr(p-r+1) + " espacios."}; // Acción
    LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList11, lista.size(), false);
    
    while (i<=r+q) { op.contadorPasos+=2;
        string strList12[nArgs] = {Util::intToStr(12),
                                        Util::vectorToStr(lista),
                                        Util::vectorToStr(ldef),
                                        "  ", // i
                                        "  ", // j
                                        "  ", // k
                                        " V", // c1
                                        "  ", // c2
                                        "  ", // c3
                                        "  ", // c4
                                        " Condición 1 verdadero (i<=r+q). Entra en el while."}; // Acción
        LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList12, lista.size(), false);

        while (j<=p) { op.contadorPasos++;
            
            string strList13[nArgs] = {Util::intToStr(13),
                                        Util::vectorToStr(lista),
                                        Util::vectorToStr(ldef),
                                        "  ", // i
                                        "  ", // j
                                        "  ", // k
                                        "  ", // c1
                                        " V", // c2
                                        "  ", // c3
                                        "  ", // c4
                                        " Condición 2 verdadero (j<=p). Entra en el while."}; // Acción
            LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList13, lista.size(), false);
            
            if (i <= r+q && lista[i]<lista[j] ) { op.contadorPasos+=6;
                ldef[k]=lista[i]; op.contadorPasos+=3;
                k++; op.contadorPasos++;
                i++; op.contadorPasos++;
                
                string strList14[nArgs] = {Util::intToStr(14),
                                        Util::vectorToStr(lista),
                                        Util::vectorToStr(ldef),
                                        (i<9?" ":"") + Util::intToStr(i), // i
                                        "  ", // j
                                        (k<9?" ":"") + Util::intToStr(k), // k
                                        "  ", // c1
                                        "  ", // c2
                                        " V", // c3
                                        "  ", // c4
                                        " Condición 3 verdadero (i <= r+q && lista[i]<lista[j]). Alternando ldef[k]=lista[i]. i++, k++"}; // Acción
                LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList14, lista.size(), false);
                
            } else {
                ldef[k]=lista[j]; op.contadorPasos+=3;
                k++; op.contadorPasos++;
                j++; op.contadorPasos++;
                string strList15[nArgs] = {Util::intToStr(15),
                                        Util::vectorToStr(lista),
                                        Util::vectorToStr(ldef),
                                        "  ", // i
                                        (j<9?" ":"") + Util::intToStr(j), // j
                                        (k<9?" ":"") + Util::intToStr(k), // k
                                        "  ", // c1
                                        "  ", // c2
                                        " F", // c3
                                        "  ", // c4
                                        " Condición 3 falso (i <= r+q && lista[i]<lista[j]). Alternando ldef[k]=lista[j]. j++, k++"}; // Acción
                LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList15, lista.size(), false);
            }
        }
        if (j>=p && k < ldef.size()) { op.contadorPasos+=4;
            ldef[k]=lista[i]; op.contadorPasos+=3;
            k++; op.contadorPasos++;
            i++; op.contadorPasos++;
            string strList16[nArgs] = {Util::intToStr(16),
                                        Util::vectorToStr(lista),
                                        Util::vectorToStr(ldef),
                                        (k<9?" ":"") + Util::intToStr(k), // i
                                        (j<9?" ":"") + Util::intToStr(j), // j
                                        "  ", // k
                                        "  ", // c1
                                        "  ", // c2
                                        "  ", // c3
                                        " V", // c4
                                        " Condición 4 verdadero (j>=p && k < ldef.size()). Haciendo ldef[k]=lista[i]. j++, i++"}; // Acción
            LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList16, lista.size(), false);
        }
    } 
    i=0;j=r; op.contadorPasos+=2;
    for (i=0;i<ldef.size();i++,r++){  
        lista[r]=ldef[i];
    }
    string strList17[nArgs] = {Util::intToStr(17),
                                        Util::vectorToStr(lista),
                                        Util::vectorToStr(ldef),
                                        "  ", // i
                                        "  ", // j
                                        "  ", // k
                                        "  ", // c1
                                        "  ", // c2
                                        "  ", // c3
                                        "  ", // c4
                                        " Volcado ldef en lista."}; // Acción
    LogCoco::escribirLineaDeAlgoritmo(op, nArgs, strList17, lista.size(), false);
}
