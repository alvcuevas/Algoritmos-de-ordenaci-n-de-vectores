/* 
 * File:   Opciones.h
 * Author: pab
 * 
 * Esta clase sirve para controlar qué opciones están activadas o desactivadas durante
 * una sesión del programa (y para cambiarlas).
 *
 * Created on 28 de octubre de 2015, 15:59
 */
#include <string>

using namespace std;

#ifndef OPCIONES_H
#define	OPCIONES_H

class Opciones {
public:
    Opciones();
    Opciones(const Opciones& orig);
    string nombreArchivo;
    virtual ~Opciones();
    bool pasoAPaso, mostrarTiempos, mostrarAlgoritmo, readerOpen, conservarVector, primeraVez, saltar, imprimirEnArchivo;
    int nElementsOriginalVector;
    unsigned long int contadorPasos;
private:

};

#endif	/* OPCIONES_H */

