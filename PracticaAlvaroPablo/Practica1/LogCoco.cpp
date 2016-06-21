#include <iostream>
#include <ios>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "LogCoco.h"
#include "Util.h"
#include <sstream>
#include "Opciones.h"
#include <fstream>

using namespace std;

void LogCoco::imprimirAlgoritmoEnConsolaExterna(int algoritmo){
    //cout << (char *)Util::intToStr(algoritmo).c_str() << " st\n";
    ShellExecute(NULL, "open", "\"..\\readFile.exe\"", (char *)("\"" + Util::intToStr(algoritmo) + "\"").c_str(), NULL, SW_SHOWDEFAULT);
}

// Escribe una línea que se le pase
void LogCoco::sendLineToOtherConsole(string line, Opciones &op){

    // Esto lo hacemos porque si es la primera vez que lo vmaos a hacer, hay que abrir la consola externa
    if(!op.readerOpen) {
        ShellExecute(NULL, "open", "\"..\\reader.exe\"", NULL, NULL, SW_SHOWDEFAULT);
        op.readerOpen = true; // Lo ponemos a true purque ya lo hemos abierto
    }
    
    int fd;
    // En este named_pipe (es un archivo temporal) se escribe la línea que queremos escribir 
    // en la consola externa. Esa consola lo leerá y lo imprimirá en su pantalla.
    char *myfifo = "/tmp/myfifo"; 

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);
    
    // Pasamos de string a char array porque es como lo necesitamos para escribir en el archivo tmp.
    char tab2[1024];
    strncpy(tab2, line.c_str(), sizeof(tab2));
    tab2[sizeof(tab2) - 1] = 0;

    fd = open(myfifo, O_WRONLY);

    write(fd, tab2, sizeof(tab2));
    close(fd);
}

// Escribe una línea que se le pase
void LogCoco::sendLineToFile(string line, Opciones &op){
    
    std::ofstream out;

    char fName[1024];
    strncpy(fName, op.nombreArchivo.c_str(), sizeof(fName));
    fName[sizeof(fName) - 1] = 0;
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    out.open(fName, std::ios::app);

    out << line << "\r\n" ;
    out.close();
}


// Escribe en la consola externa la cabecera de la tabla para el algoritmo que se le indique.
// Por ahora sólo está implementado el caso 1 que es el Insertion Sort
void LogCoco::escribirCabeceraDeAlgoritmo(int algor, Opciones &op, int arrSize){
    arrSize = arrSize*3 + 1; // El numero de espacios a escribir para que la tabla quede alineada
    string cabeceraColArrayStr = "";
    string cabeceraLineaInferiorStr = "";
    
    for(int i=0; i<arrSize; i++){
        cabeceraLineaInferiorStr += "-";
        if(i!=(arrSize/2)) 
            cabeceraColArrayStr += " ";
        else
            cabeceraColArrayStr += "a";
    }
    
    switch(algor){
        case 1: // INSERTION 
            
            LogCoco::escribirIntroInsertion(op);
            if(op.pasoAPaso){
                LogCoco::sendLineToOtherConsole("N |" + cabeceraColArrayStr + "| i| x| j| C| Acción realizada", op);
                LogCoco::sendLineToOtherConsole("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            } 
            if(op.imprimirEnArchivo){
                LogCoco::sendLineToFile("N |" + cabeceraColArrayStr + "| i| x| j| C| Acción realizada", op);
                LogCoco::sendLineToFile("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            break;
        case 2: // BUBBLE
            
            LogCoco::escribirIntroBubble(op);
            
            if(op.pasoAPaso){
                LogCoco::sendLineToOtherConsole("N |" + cabeceraColArrayStr + "| i| j| C| Acción realizada", op);
                LogCoco::sendLineToOtherConsole("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            if(op.imprimirEnArchivo){
                LogCoco::sendLineToFile("N |" + cabeceraColArrayStr + "| i| j| C| Acción realizada", op);
                LogCoco::sendLineToFile("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            break;
        case 3: // MERGE
            
            LogCoco::escribirIntroMerge(op);
            
            if(op.pasoAPaso){
                LogCoco::sendLineToOtherConsole("N |" + cabeceraColArrayStr + "| r| p| q|c1| Acción realizada", op);
                LogCoco::sendLineToOtherConsole("---" + cabeceraLineaInferiorStr + "------------------------------", op);
            }
            if(op.imprimirEnArchivo){
                LogCoco::sendLineToFile("N |" + cabeceraColArrayStr + "| r| p| q|c1| Acción realizada", op);
                LogCoco::sendLineToFile("---" + cabeceraLineaInferiorStr + "------------------------------", op);
            }
            break;
        case 4: // QUICK
            
            LogCoco::escribirIntroQuick(op);
            if(op.pasoAPaso){
                LogCoco::sendLineToOtherConsole("N |" + cabeceraColArrayStr + "| p| q| i| x| Acción realizada", op);
                LogCoco::sendLineToOtherConsole("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            if(op.imprimirEnArchivo){
                LogCoco::sendLineToFile("N |" + cabeceraColArrayStr + "| p| q| i| x| Acción realizada", op);
                LogCoco::sendLineToFile("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            break;
        case 5: // Segundo método del merge (sortSubarray)
                                    
            if(op.pasoAPaso){
                LogCoco::sendLineToOtherConsole("\nMétodo sortSubarray:", op);
                LogCoco::sendLineToOtherConsole("N |" + cabeceraColArrayStr + "| i| f|qt|ot|c1| Acción realizada", op);
                LogCoco::sendLineToOtherConsole("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            if(op.imprimirEnArchivo){
                LogCoco::sendLineToFile("\nMétodo sortSubarray:", op);
                LogCoco::sendLineToFile("N |" + cabeceraColArrayStr + "| i| f|qt|ot|c1| Acción realizada", op);
                LogCoco::sendLineToFile("---" + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            break;
        case 6: // Tercer método del merge (mergE)
            
            if(op.pasoAPaso){
                LogCoco::sendLineToOtherConsole("\nMétodo mergE:\n", op);
                LogCoco::sendLineToOtherConsole("N |" + cabeceraColArrayStr + "| i| j| k|c1|c2|c3|c4| Acción realizada", op);
                LogCoco::sendLineToOtherConsole("---" + cabeceraLineaInferiorStr + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            if(op.imprimirEnArchivo){
                LogCoco::sendLineToFile("\nMétodo mergE:\n", op);
                LogCoco::sendLineToFile("N |" + cabeceraColArrayStr + "| i| j| k|c1|c2|c3|c4| Acción realizada", op);
                LogCoco::sendLineToFile("---" + cabeceraLineaInferiorStr + cabeceraLineaInferiorStr + "-------------------------------", op);
            }
            break;
        case 7: // MERGE
            
            if(op.pasoAPaso){
                LogCoco::sendLineToOtherConsole("\nVuelta a método mergesort:", op);
                LogCoco::sendLineToOtherConsole("N |" + cabeceraColArrayStr + "| r| p| q|c1| Acción realizada", op);
                LogCoco::sendLineToOtherConsole("---" + cabeceraLineaInferiorStr + "------------------------------", op);
            }
            if(op.imprimirEnArchivo){
                LogCoco::sendLineToFile("\nVuelta a método mergesort:", op);
                LogCoco::sendLineToFile("N |" + cabeceraColArrayStr + "| r| p| q|c1| Acción realizada", op);
                LogCoco::sendLineToFile("---" + cabeceraLineaInferiorStr + "------------------------------", op);
            }
            break;
        default:
            break;
    }
}

/**
 * Escribe una línea (strList que luego concatena dentro de este método) en la consola externa de Paso a Paso
 * 
 * @param op: las Opciones. Las utilizamos para comprobar si el modo paso a paso está activado. Si no está, salimos de aquí
 * @param nArgs: el numero de strings que contiene strList (para concatenarlas luego)
 * @param strList: la lista de strings que queremos imprimir. Equivale a una línea de la consola externa.
 * @param vecSize: el tamaño del vector que estamos ordenando (¿creo..?)
 * @param lastLine: si es la ultimaLinea a escribir en la consola, escribimos también un enter. (Todavía funciona raro)
 */
void LogCoco::escribirLineaDeAlgoritmo(Opciones &op, int nArgs, string strList[], int vecSize, bool lastLine){
    
    string logStr = Util::concatenarStrings(strList, nArgs);
    if(op.pasoAPaso) { // La opcion está activada. Vamos a escribir en la consola externa la línea.
        
        char ch = op.saltar? 's':'n';
        LogCoco::sendLineToOtherConsole(logStr, op);
        if(!op.saltar) cout << "Presiona 'c' +Enter para continuar, o 's' +Enter para saltar al final.";
        if(!op.saltar) Util::leerDeUsuario(ch);
        if(!op.saltar && ch == 's'){op.saltar = true;} // guardo el cin en nArgs porque me da igual. (se pone a 7 al principio del metodo)
        if(lastLine) { cout << "\n"; op.saltar = false; }
    }
    if(op.imprimirEnArchivo && logStr != "q"){ 
        LogCoco::sendLineToFile(logStr, op);
    }
}
        
void LogCoco::escribirIntroMerge(Opciones &op){
    
    if(op.pasoAPaso){
        LogCoco::sendLineToOtherConsole("En esta consola se mostrará la tabla de valores en cada paso del algoritmo. Para pasar al siguiente paso, presione Enter en la consola principal.\n",op);
        LogCoco::sendLineToOtherConsole("Definicion de la tabla:",op);
        LogCoco::sendLineToOtherConsole(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToOtherConsole(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToOtherConsole(" - b: valor actual de la variable beg (begin).",op);
        LogCoco::sendLineToOtherConsole(" - e: valor actual de la variable end.",op);
        LogCoco::sendLineToOtherConsole(" - m: valor actual de la variable m (middle).",op);
        LogCoco::sendLineToOtherConsole(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToOtherConsole(" - l: valor actual de la variable l.",op);
        LogCoco::sendLineToOtherConsole(" - j: valor actual de la variable j.",op);
        LogCoco::sendLineToOtherConsole(" - k: valor actual de la variable k.",op);
        LogCoco::sendLineToOtherConsole(" - *c: valor de la condición j>end || (i<=mid && array[i]<array[j]).\n",op);
    }
    
    if(op.imprimirEnArchivo){
        LogCoco::sendLineToFile("Definicion de la tabla:",op);
        LogCoco::sendLineToFile(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToFile(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToFile(" - b: valor actual de la variable beg (begin).",op);
        LogCoco::sendLineToFile(" - e: valor actual de la variable end.",op);
        LogCoco::sendLineToFile(" - m: valor actual de la variable m (middle).",op);
        LogCoco::sendLineToFile(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToFile(" - l: valor actual de la variable l.",op);
        LogCoco::sendLineToFile(" - j: valor actual de la variable j.",op);
        LogCoco::sendLineToFile(" - k: valor actual de la variable k.",op);
        LogCoco::sendLineToFile(" - *c: valor de la condición j>end || (i<=mid && array[i]<array[j]).\n",op);
    }
}

void LogCoco::escribirIntroInsertion(Opciones &op){
    
    if(op.pasoAPaso){
        LogCoco::sendLineToOtherConsole("En esta consola se mostrará la tabla de valores en cada paso del algoritmo. Para pasar al siguiente paso, presione Enter en la consola principal.\n",op);
        LogCoco::sendLineToOtherConsole("Definicion de la tabla:",op);
        LogCoco::sendLineToOtherConsole(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToOtherConsole(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToOtherConsole(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToOtherConsole(" - x: valor actual de la variable x.",op);
        LogCoco::sendLineToOtherConsole(" - j: valor actual de la variable j.",op);
        LogCoco::sendLineToOtherConsole(" - *c: valor actual de la condición j>=0 && vec[j]>x.",op);
        LogCoco::sendLineToOtherConsole(" - Accion realizada: breve descripción de la línea que se acaba de ejecutar.\n",op);
    }
    
    if(op.imprimirEnArchivo){
        LogCoco::sendLineToFile("Definicion de la tabla:",op);
        LogCoco::sendLineToFile(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToFile(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToFile(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToFile(" - x: valor actual de la variable x.",op);
        LogCoco::sendLineToFile(" - j: valor actual de la variable j.",op);
        LogCoco::sendLineToFile(" - *c: valor actual de la condición j>=0 && vec[j]>x.",op);
        LogCoco::sendLineToFile(" - Accion realizada: breve descripción de la línea que se acaba de ejecutar.\n",op);
    }
}

void LogCoco::escribirIntroBubble(Opciones &op){
    
    if(op.pasoAPaso){
        LogCoco::sendLineToOtherConsole("En esta consola se mostrará la tabla de valores en cada paso del algoritmo. Para pasar al siguiente paso, presione Enter en la consola principal.\n",op);
        LogCoco::sendLineToOtherConsole("Definicion de la tabla:",op);
        LogCoco::sendLineToOtherConsole(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToOtherConsole(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToOtherConsole(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToOtherConsole(" - j: valor actual de la variable j.",op);
        LogCoco::sendLineToOtherConsole(" - C: valor actual de la condición a[j]>a[j+1].",op);
        LogCoco::sendLineToOtherConsole(" - Accion realizada: breve descripción de la línea que se acaba de ejecutar.\n",op);
    }
    
    if(op.imprimirEnArchivo){
        
        LogCoco::sendLineToFile("Definicion de la tabla:",op);
        LogCoco::sendLineToFile(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToFile(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToFile(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToFile(" - j: valor actual de la variable j.",op);
        LogCoco::sendLineToFile(" - C: valor actual de la condición a[j]>a[j+1].",op);
        LogCoco::sendLineToFile(" - Accion realizada: breve descripción de la línea que se acaba de ejecutar.\n",op);
    }
}

void LogCoco::escribirIntroQuick(Opciones &op){
    
    if(op.pasoAPaso){
        LogCoco::sendLineToOtherConsole("En esta consola se mostrará la tabla de valores en cada paso del algoritmo. Para pasar al siguiente paso, presione Enter en la consola principal.\n",op);
        LogCoco::sendLineToOtherConsole("Definicion de la tabla:",op);
        LogCoco::sendLineToOtherConsole(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToOtherConsole(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToOtherConsole(" - p: valor actual de la variable p.",op);
        LogCoco::sendLineToOtherConsole(" - q: valor actual de la variable q.",op);
        LogCoco::sendLineToOtherConsole(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToOtherConsole(" - x: valor actual de la variable x.",op);
        LogCoco::sendLineToOtherConsole(" - Accion realizada: breve descripción de la línea que se acaba de ejecutar.\n",op);
    }
    
    if(op.imprimirEnArchivo){

        LogCoco::sendLineToFile("Definicion de la tabla:",op);
        LogCoco::sendLineToFile(" - N: el número de línea que se acaba de ejecutar (o se va a ejecutar).",op);
        LogCoco::sendLineToFile(" - a: el estado actual del array principal a.",op);
        LogCoco::sendLineToFile(" - p: valor actual de la variable p.",op);
        LogCoco::sendLineToFile(" - q: valor actual de la variable q.",op);
        LogCoco::sendLineToFile(" - i: valor actual de la variable i.",op);
        LogCoco::sendLineToFile(" - x: valor actual de la variable x.",op);
        LogCoco::sendLineToFile(" - Accion realizada: breve descripción de la línea que se acaba de ejecutar.\n",op);
    }
}