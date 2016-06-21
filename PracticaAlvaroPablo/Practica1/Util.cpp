/* 
 * File:   Util.cpp
 * Author: nestor
 * 
 * Created on 26 de octubre de 2015, 20:15
 */
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <algorithm> // for std::partition
#include <functional> // for std::less
#include "Util.h"
#include "Algoritmo.h"
#include "LogCoco.h"
#include <limits>
#include <windows.h>
#include <sstream>
#include <limits>
#include <climits>
#include <time.h>
#include <ctime>
#include <cstdlib>

#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <streambuf>

using namespace std;

Util::Util() {
}

Util::Util(const Util& orig) {
}

Util::~Util() {
}

// Metodo de ayuda para meter tres vectores en órden en el vector dest.
void Util::appendVectors(vector<int>& dest, vector<int> less, vector<int> equal, vector<int> greater){
    vector<int> result;
    result.insert(result.end(),less.begin(),less.end());
    result.insert(result.end(), equal.begin(), equal.end());
    result.insert(result.end(), greater.begin(), greater.end());
    dest.clear();
    dest.insert(dest.begin(), result.begin(), result.end());
}

void Util::llena_vector_aleatorio(vector<int> &v, vector<int> &vec2, int tamano, Opciones &op){
    int i, aleatorio;
    
    cout << "\n|*** MODO ALEATORIO ***|\n" << endl;
            
    //Se piden los elementos que tendrá el vector
    cout << "¿Cuántos números quieres en tu vector?" << endl; 
    if(op.pasoAPaso) cout << "\n(Aviso: Estás en modo paso a paso. Te recomendamos elegir un número pequeño para seguir mejor la traza).\n";
    Util::leerDeUsuario(tamano);

    //Se ajusta el vector al tamaño escogido
    v.resize(tamano);
    vec2.resize(tamano);
    
    //Inicio una semilla llamando a la función 'time' para generar numeros aleatorios distintos en cada petición
    srand(time(NULL));
    
    //Recorre hasta el final del tamaño deseado para ir añadiendo los números aleatorios
    for (i=0; i<tamano; i++){
        //Genera el número aleatorio comprendido entre 1 y 99
        aleatorio = rand()%(tamano>50?tamano:100);
        //Inserta dicho número en la capacidad del vector
        v[i]=aleatorio;
        vec2[i]=aleatorio;
    }
    
    //Muestra el vector final sin haber sido ordenado
    cout << "\n¡Listo! Tu vector está formado por los siguientes aleatorios: \n" << endl;
    muestra_vector(v, 0, 0);
    
    cout << "\nPulsa enter para continuar...";
    Util::pulsaEnterParacontinuar();
    
}

void Util::llena_vector_manual(vector<int> &v, vector<int> &vec2,  int tamano){
    int i, num;
    
    cout << "\n|*** MODO MANUAL ***|\n" << endl;

    //Se piden los elementos que tendrá el vector
    cout << "¿Cuántos números quieres en tu vector?" << endl;         
    Util::leerDeUsuario(tamano);

    //Se ajusta el vector al tamaño escogido
    v.resize(tamano);
    vec2.resize(tamano);
    
    //Recorre hasta el final del tamaño deseado para ir agregando cada número escogido
    for (i=0; i<tamano; i++){
        //Pide por pantalla el número a ser insertado
        cout << "¿Qué número quieres añadir al vector?" << endl;
        Util::leerDeUsuario(num);
        //Inserta dicho número en la capacidad del vector
        v[i]=num;
        vec2[i]=num;
    }
    
    //Muestra el vector final sin haber sido ordenado
    cout << "¡Listo! Tu vector está formado por los siguientes: \n" << endl;
    muestra_vector(v ,0 ,0);
    cout << '\n';
}

// Método muestra_vector
// Este método lo usamos en varios sitios para imprimir un vector en consola.
// 
// @param start: la primera posicion a imprimir.
// @param end: la última posicion a imprimir.
//
// Por defecto los valores serán 0 y por lo tanto se imprimirá todo el vector.
void Util::muestra_vector(vector<int> vec, int start, int end){
    int contador = 0;
    
    cout << "[";
    //Mediante iteradores recorro el vector de principio a fin sumando posiciones
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++, contador++){
        
        // Con este if, imprimimos solo la parte que queremos del vector (desde start hasta end)
        // si las variables son distintas de 0. De lo contrario se imprime el vector entero.
        if((start==0 || (start!=0 && start<=contador))
                && (end==0 || (end!=0 && end>=contador))){
            
            //Muestro por pantalla el elemento en cada iteración
            cout << vec.at(contador);
            
            //Mientras no haya terminado el vector, imprimo una coma para separar elementos
            if (it != vec.end()-1){
                cout << "][";
            }
        }
    }
    cout << "]" << endl;
}

/**
 * Este método se encarga de que el usuario elija el modo de relleno del array, y lo rellena.
 * 
 * @param vec
 */
void Util::llena_vector(vector<int> &vec, vector<int> &vec2, Opciones &op){
    int eleccionRelleno = 0;
    int tamano;
    
    //Inicio del menú para escoger un modo de asignar los elementos al vector
    cout << "\n# ESCOGE UN MODO PARA RELLENAR TU VECTOR #" << endl;
    cout << "1. Modo Manual" << endl;
    cout << "2. Modo Aleatorio" << endl;
    if(!op.primeraVez) cout << "3. Conservar el último vector utilizado." << endl;
    
    while(eleccionRelleno != 1 && eleccionRelleno != 2 && eleccionRelleno != 3){
        
        //Pide al usuario el número del modo escogido
        Util::leerDeUsuario(eleccionRelleno);
        
        //Mediante un switch se distribuye cada modo de relleno en los distintos casos
        switch(eleccionRelleno){

            case 1:
                vec2.clear();
                //Mediante el nº1 se activa el modo manual de relleno del vector
                Util::llena_vector_manual(vec, vec2, tamano);
                break;

            case 2:
                vec2.clear();
                //Mediante el nº2 se activa el modo aleatorio de relleno del vector
                Util::llena_vector_aleatorio(vec, vec2, tamano, op);
                break;
                
            case 3: 
                
                vec = vec2;
                
                cout << "¡Listo! Tu vector está formado por los siguientes: \n" << endl;
                muestra_vector(vec ,0 ,0);
                cout << '\n';
                break;

            default:

                //Caso genérico en el caso de no pulsar ninguno de los números correspondientes
                cout << "¡¡¡No has pulsado el número adecuado para iniciar un modo!!!\nPor favor, escoge un numero de los siguientes para continuar:\n";
                cout << "1. Modo Manual\n";
                cout << "2. Modo Aleatorio\n";
                if(!op.primeraVez) cout << "3. Conservar el último vector utilizado.\n";
                Util::leerDeUsuario(eleccionRelleno);
                break;
        }
    }
    op.nElementsOriginalVector = vec.size();
}

void Util::elegirOrdenacion(vector<int> &vectorPrincipal, Opciones &op){
    int eleccionOrdenacion = 0;
    
    //Menú para escoger un modo de ordenar los elementos del vector
    cout << "\n# ESCOGE UN MODO PARA ORDENAR TU VECTOR #" << endl;
    cout << "1. Insertion Sort" << endl;
    cout << "2. Bubble Sort" << endl;
    cout << "3. Merge Sort" << endl;
    cout << "4. Quick Sort" << endl;
    
    if(op.imprimirEnArchivo) {
        op.nombreArchivo = _nuevoNombreArchivo();
    }
    
    while(eleccionOrdenacion<1 || eleccionOrdenacion>4){
        
        
        //Pide al usuario el número del modo escogido
        Util::leerDeUsuario(eleccionOrdenacion);
        cout << "\n";

        if(op.mostrarAlgoritmo) LogCoco::imprimirAlgoritmoEnConsolaExterna(eleccionOrdenacion);
        
        //Cuenta el tiempo transcurrido
        clock_t cuentaTiempo;
        long double duracion;

        //Mediante un switch se distribuye cada modo de ordenación en los distintos casos
        switch(eleccionOrdenacion){
            case 1:
                if(op.pasoAPaso || op.imprimirEnArchivo){
                    LogCoco::escribirCabeceraDeAlgoritmo(1,op,vectorPrincipal.size());
                    Algoritmo::insertion_sort(vectorPrincipal, op);
                } else {
                    cuentaTiempo = clock();
                    Algoritmo::insertion_sort_rapido(vectorPrincipal, op);
                }
                cout << "||| Vector ordenado mediante Insertion Sort |||\n";
                break;
            case 2:
                            
                if(op.pasoAPaso || op.imprimirEnArchivo) {
                    LogCoco::escribirCabeceraDeAlgoritmo(2,op,vectorPrincipal.size());
                    Algoritmo::bubble_sort(vectorPrincipal, op);
                } else {
                    cuentaTiempo = clock();
                    Algoritmo::bubble_sort_rapido(vectorPrincipal, op);
                }
                cout << "||| Vector ordenado mediante Bubble Sort |||\n";
                break;
            case 3:
                
                if(op.pasoAPaso || op.imprimirEnArchivo) {
                    LogCoco::escribirCabeceraDeAlgoritmo(3,op,vectorPrincipal.size());
                    Algoritmo::mergesort(vectorPrincipal,0, vectorPrincipal.size()-1, op);
                } else {
                    cuentaTiempo = clock();
                    Algoritmo::mergesort_rapido(vectorPrincipal,0, vectorPrincipal.size()-1, op);
                }
                cout << "||| Vector ordenado mediante Merge Sort |||\n";
                break;
            case 4:
                if(op.pasoAPaso || op.imprimirEnArchivo) {
                    LogCoco::escribirCabeceraDeAlgoritmo(4,op,vectorPrincipal.size());
                    Algoritmo::quicksort(vectorPrincipal,op);
                } else {
                    cuentaTiempo = clock();
                    Algoritmo::quicksort_rapido(vectorPrincipal,op);
                }          
                cout << "||| Vector ordenado mediante Quick Sort |||\n";
                
                break;
            default:
                
                cout << "# Has introducido un valor no válido. Inténtalo de nuevo. Las opciones son:" << endl;
                cout << "1. Insertion Sort" << endl;
                cout << "2. Bubble Sort" << endl;
                cout << "3. Merge Sort" << endl;
                cout << "4. Quick Sort" << endl;
                Util::leerDeUsuario(eleccionOrdenacion);
                break;
        }
        muestra_vector(vectorPrincipal,0,0);
        
        cout << "\nNumero de pasos: " << op.contadorPasos << "\n";
        op.contadorPasos = 0;
        
        duracion = (clock() - cuentaTiempo) / (double) CLOCKS_PER_SEC;
        if(op.mostrarTiempos) {cout << "\nTiempo transcurrido durante la ordenacion: " << duracion << "\n";}
    }
}

/**
 * Elegir las opciones.
 * 
 * @param op
 */
void Util::eligeOpciones(Opciones &op){
    cout << "\n# MENU DE OPCIONES DEL PROGRAMA #\n";
    cout << "1. Modo paso a paso. (Actualmente " << (op.pasoAPaso?"VERDADERO":"FALSO") << ")\n";
    cout << "2. Mostrar el algoritmo elegido. (Actualmente " << (op.mostrarAlgoritmo?"VERDADERO":"FALSO") << ")\n";
    cout << "3. Mostrar los tiempos utilizados en ordenar cada vector. (Actualmente " << (op.mostrarTiempos?"VERDADERO":"FALSO") << ")\n";
    cout << "4. Imprimir tabla en un txt. (Actualmente " << (op.imprimirEnArchivo?"VERDADERO":"FALSO") << ")\n";
    cout << "5. Ayuda.\n";
    cout << "6. Salir de las opciones.\n";
    
    int c = 0;
    Util::leerDeUsuario(c);
    
    switch(c){
        // Cambiar la opcion que se haya pulsado a su contrario
        case 1:
            
            op.pasoAPaso = !op.pasoAPaso;
            if(op.mostrarTiempos) op.mostrarTiempos = !op.mostrarTiempos;
            Util::eligeOpciones(op);
            break;
        case 2:
            
            op.mostrarAlgoritmo = !op.mostrarAlgoritmo;
            Util::eligeOpciones(op);
            break;
        case 3:
            
            op.mostrarTiempos = !op.mostrarTiempos;
            if(op.pasoAPaso) op.pasoAPaso = !op.pasoAPaso;
            Util::eligeOpciones(op);
            break;
        case 4:
            
            op.imprimirEnArchivo = !op.imprimirEnArchivo;
            Util::eligeOpciones(op);
            break;
        case 5:
            Util::escribirAyuda();
            cout << "\nPulsa Enter para salir de la ayuda.";
            Util::pulsaEnterParacontinuar();
            Util::eligeOpciones(op);
            break;
        case 6:
            break;
        default:
            break;
    }  
}

string Util::_nuevoNombreArchivo(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"\\txts\\%Y%m%d%H%M%S.txt",timeinfo);
    return Util::ExePath() + string(buffer);
}

string Util::ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

string Util::intToStr(int n){
    stringstream sstm;
    sstm << n;
    return sstm.str(); 
}

string Util::vectorToStr(vector<int> n){
    string output = "[";
    for(int i=0; i<n.size(); i++){
        output += (n[i]>9?"":" ");
        output += Util::intToStr(n[i]);
        if(i<n.size()-1) output += ",";
    }
    output += "]";
    return output;
}

string Util::concatenarStrings(string n[], int size){
    string output = "";
    for(int i=0; i<size; i++){
        output += n[i];
        if(i!=size-1) output += "|";
    }
    return output;
}

// Guarda el contenido de cin en la variable ret. Y limpia a fondo el cin para poder seguir sin problemas
// con el programa.
void Util::leerDeUsuario(int& ret){
    
    while(!(cin >> ret)){
        cout << "\nEl valor que has introducido no es válido. Inténtalo de nuevo:\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Lo mismo que el anterior pero con un char. 
void Util::leerDeUsuario(char &ch){
    
    ch = cin.get();
    cin.clear();
    cin.ignore();
}

// Espera que el usuario pulse enter para continuar. También limpia el cin.
void Util::pulsaEnterParacontinuar(){
    cin.clear();
    cin.ignore(); 
}

bool Util::ordenado(vector<int> v){
    for(int i=1;i<v.size();i++){
        if(v[i-1]>=v[i])
            return false;
    }
    return true;
}

bool Util::escribirAyuda(){
    ifstream t("ayuda.txt");
	
    string str((istreambuf_iterator<char>(t)),
                 istreambuf_iterator<char>());
    cout << str;
}
