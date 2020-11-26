#include <iostream>
#include <string>
using namespace std;

//------ Creacion de nodo y de arbol ------

enum Colores{Verde,Amarillo,Naranja,Rojo};

struct scoville
{
    string Nombre;
    int SHU;
    Colores Color;
};


typedef struct scoville T;

struct Nodo{
    T info;
    struct Nodo *izq;
    struct Nodo *der;
};
typedef struct Nodo *Arbol;

Arbol crearArbol(T x);

// Funciones que dependen del tipo de dato de los nodos
T solicitarDato(){
    scoville DTemp;
    cout << "\nIngrese el nombre del chile: "; getline(cin,DTemp.Nombre,'\n');
    bool continuar = true;
    do{
        cout << "Ingrese las Scoville Heat Units del chile: "; 
        cin >> DTemp.SHU; cin.ignore();
        if(DTemp.SHU < 0){
            cout << "Debe ingresar un numero mayor o igual a 0" << endl;
        }else{
            continuar = false;
        }
    }while(continuar);
    continuar = true;
    do{
        char opcion = 0;
        cout << "Ingrese el Color (v-verde|a-amarillo|n-naranja|r-rojo): ";
        cin >> opcion;
        switch(opcion){
            case 'v': DTemp.Color = Verde; continuar = false; break;
            case 'a': DTemp.Color = Amarillo; continuar = false; break;
            case 'n': DTemp.Color = Naranja; continuar = false; break;
            case 'r': DTemp.Color = Rojo; continuar = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(continuar);
    return DTemp;
}
void mostrar(T &Dato){
    cout << "\nNombre: " << Dato.Nombre << endl;
    cout << "Scoville Heat Units: " << Dato.SHU << endl;
    cout << "Color: ";
    switch(Dato.Color){
        case Verde: cout << "Verde" << endl; break;
        case Amarillo: cout << "Amarillo" << endl; break;
        case Naranja: cout << "Naranja" << endl; break;
        case Rojo: cout << "Rojo" << endl; break;
    }
}


void mostrarDato(T unDato, string orden){
    if(orden == "inorden"){
        mostrar(unDato);
    }else if(orden == "preorden"){
        if(unDato.Color == Rojo){
            mostrar(unDato);
        }
    }else if(orden == "postorden"){
        if(unDato.SHU > 50000){
            mostrar(unDato);
        }
    }
}

enum comparacion{menorque,mayorque,igualque};

bool comparar(int a, comparacion operador, int b){
    bool resultado = false;
    switch(operador){
        case menorque: resultado = a < b; break;
        case mayorque: resultado = a > b; break;
        case igualque: resultado = a == b; break;
    }
    return resultado;
}



//------ Agregar nodos a un arbol ------
void asignarIzq(Arbol a, T unDato);
void asignarDer(Arbol a, T unDato);
void agregarNodo(Arbol a);

//------ Recorrer un arbol (in, pre y post orden) ------
void preorden(Arbol a);
void inorden(Arbol a);
void postorden(Arbol a);
void recorrerArbol(Arbol a);

int main(){
    cout<<"Inicializando arbol...\nValor contenido en la raiz: ";
    Arbol arbol = crearArbol(solicitarDato());
    
    bool continuar = true;
    do{
        int opcion = 0;
        cout << "\nMenu: \n";
        cout << "\t1) Agregar\n";
        cout << "\t2) Recorrer\n";
        cout << "\t3) Salir\n";
        cout << "\tOpcion elegida: ";
        cin >> opcion;
        cin.ignore();
        switch(opcion){
            case 1: agregarNodo(arbol); break;
            case 2: recorrerArbol(arbol); break;
            case 3: continuar = false; break;
            default: cout << "Opcion erronea!" << endl; break;
        }
    }while(continuar);
    
    return 0;
}

// Implementacion de funciones de arboles
Arbol crearArbol(T x){
    Arbol p = new Nodo;
    p->info = x;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

//------ Agregar nodos a un arbol ------
void asignarIzq(Arbol a, T unDato){
    if(a == NULL)
        cout << "Error: arbol vacio" << endl;
    else if(a->izq != NULL)
        cout << "Error: subarbol IZQ ya existe" << endl;
    else
        a->izq = crearArbol(unDato);
}

void asignarDer(Arbol a, T unDato){
    if(a == NULL)
        cout << "Error: arbol vacio" << endl;
    else if(a->der != NULL)
        cout << "Error: subarbol DER ya existe" << endl;
    else
        a->der = crearArbol(unDato);
}

void agregarNodo(Arbol a){
    //solicitar informacion (dato a agregar)
    cout << "Dato a agregar: ";
    T unDato = solicitarDato();
    
    Arbol p = a;
    
    //desplazarse hasta el lugar adecuado
    while(true){
        if(comparar(unDato.SHU, igualque, p->info.SHU)){
            cout << "Error: dato ya existe!" << endl;
            return;
        }
        else if(comparar(unDato.SHU, menorque, p->info.SHU)){//ir a la izquierda
            if(p->izq == NULL)
                break;
            else
                p = p->izq;
        }
        else{//ir a la derecha
            if(p->der == NULL)
                break;
            else
                p = p->der;
        }
    }
    
    //agregar el nuevo nodo
    if(comparar(unDato.SHU, menorque, p->info.SHU))
        asignarIzq(p, unDato);
    else
        asignarDer(p, unDato);
}

//------ Recorrer un arbol (in, pre y post orden) ------
void preorden(Arbol a){
    if(a != NULL){
        cout << " "; mostrarDato(a->info,"preorden");
        preorden(a->izq);
        preorden(a->der);
    }
}
void inorden(Arbol a){
    if(a != NULL){
        inorden(a->izq);
        cout << " "; mostrarDato(a->info,"inorden");
        inorden(a->der);
    }
}
void postorden(Arbol a){
    if(a != NULL){
        postorden(a->izq);
        postorden(a->der);
        cout << " "; mostrarDato(a->info,"postorden");
    }
}

void recorrerArbol(Arbol a){
    cout << "Recorrido PRE orden:"; preorden(a); cout << endl;
    cout << "Recorrido IN orden:"; inorden(a); cout << endl;
    cout << "Recorrido POST orden:"; postorden(a); cout << endl;
}
