/* 
 * File:   Log.h
 * Author: nestor
 *
 * Created on 27 de octubre de 2015, 11:38
 */
#include <string>
#include "Opciones.h"

#ifndef LOG_H
#define	LOG_H

using namespace std;

class LogCoco {
public:
    LogCoco();
    LogCoco(const LogCoco& orig);
    virtual ~LogCoco();
    static void imprimirAlgoritmoEnConsolaExterna(int algoritmo);
    static void sendLineToOtherConsole(string line, Opciones &op);
    
    static void sendLineToFile(string line, Opciones &op);
    
    static void escribirCabeceraDeAlgoritmo(int algor, Opciones &op, int arrSize);
    static void escribirLineaDeAlgoritmo(Opciones &op, int nArgs, string strList[], int vecSize, bool lastLine);
    
    static void escribirIntroMerge(Opciones &op);
    static void escribirIntroInsertion(Opciones &op);
    static void escribirIntroBubble(Opciones &op);
    static void escribirIntroQuick(Opciones &op);
    
    
private:

};

#endif	/* LOG_H */

