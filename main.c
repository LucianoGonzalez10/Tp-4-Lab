#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

typedef struct
{
    char nombre[20];
    int edad;
} Persona; /// Creamos la estructura comun.

typedef struct nodo
{
    Persona dato;
    struct nodo * siguiente;
} nodo; /// Creamos la estructura nodo la cual contiene la estructura de datos y la direccion de memoria del siguiente nodo.

Persona cargarAlumno(Persona personita);
void cargarArchivo(char nombre[]);
nodo * crearNodo(dato);
nodo * iniclista();
nodo * cargarNodo(char nombre[], nodo * lista);
void recorrerYMostrar(nodo * lista);
void escribir(nodo * aux);
Persona buscandoL (char nombre[], nodo * lista);
nodo * agregarEnOrden(nodo * lista, nodo * nuevoNodo);
nodo * buscarUltimo(nodo * lista);
nodo * agregarFinal(nodo * lista, nodo * nuevoNodo);
nodo * buscarElemento(nodo * lista, int dato);
int sumarEdades(nodo * lista);
int multiplicarEdades(nodo * lista);
float calcularPromedio(nodo * lista);

int main()
{
    char nombreArchi[30];
    printf("Dime el nombre del archivo \n");
    fflush(stdin);
    scanf("%s", &nombreArchi);
    cargarArchivo(nombreArchi);

    nodo * lista;
    lista = iniclista();
    lista = cargarNodo(nombreArchi, lista);
    recorrerYMostrar(lista);
    Persona Nuevo = cargarAlumno(Nuevo);
    nodo *nuevoNodo = crearNodo(Nuevo);
    lista = agregarEnOrden(lista, nuevoNodo);
    recorrerYMostrar(lista);
    int edad;
    printf("Ingrese los datos a buscar: \n");
    scanf("%d", &edad);
    nodo * encontrado = buscarElemento(lista, edad);

    if(encontrado==NULL)
    {
        printf("No se encontro el dato \n");
    }
    else
    {
        printf("SE ENCONTRO EL DATO, CONGRATULATIONS \n");
    }

    int suma = sumarEdades(lista);
    printf("El resultado de la suma de edades es de: %i \n", suma);

    int multi = multiplicarEdades(lista);
    printf("El resultado de la multiplicacion de las edades es de: %i", multi);

    float promedio = calcularPromedio(lista);
    printf("El promedio de edad es: %.2f", promedio);
    return 0;
}

Persona cargarAlumno(Persona personita)
{
    printf("Dime el nombre de la persona: \n");
    fflush(stdin);
    scanf("%s", &personita.nombre);

    printf("Dime la edad de la persona: \n");
    scanf("%i", &personita.edad);

    return personita;
}

void cargarArchivo(char nombre[])
{
    Persona personita;
    char s = 's';
    FILE * buffer = fopen(nombre, "ab");
    if(buffer)
    {
        printf("Quieres cargar datos? \n");
        fflush(stdin);
        scanf("%c", &s);
        while(s=='s'|| s == 'S')
        {
            personita = cargarAlumno(personita);
            fwrite(&personita, sizeof(Persona),1, buffer);
            printf("Quieres seguir cargando datos? \n");
            fflush(stdin);
            scanf("%c", &s);
        }
        fclose(buffer);
    }
}

nodo * iniclista() /// Inicializamos la lista, importante llamarla arriba del main.
{
    return NULL;
}

nodo * crearNodo (Persona dato) /// Creamos el dato, pasamos la estructura de los datos por parametros.
{

    nodo * aux = (nodo*) malloc(sizeof(nodo));  /// Crea un puntero de tipo nodo y se le asigna un espacio de memoria.
    aux ->dato = dato; /// Se le asigna el dato al puntero.
    aux -> siguiente = NULL; /// Se agrega NULL a la vsariable siguiente.
    return aux; /// Retorna el puntero.
}

nodo * agregarPpio(nodo * lista, nodo * nuevoNodo)
{
    if(lista == NULL) /// Si la lista esta vacia, apunta a un nuevo nodo.
    {
        lista = nuevoNodo;
    }
    else /// Si lista no esta vacia, inserta el nuevo nodo al principio, y el viejo primer nodo pasa a ser el segundo.
    {
        nuevoNodo -> siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodo * cargarNodo(char nombre[], nodo * lista)
{
    nodo * nuevo;
    Persona aux;
    FILE * buffer = fopen(nombre, "rb");
    if(buffer)
    {
        while(fread(&aux, sizeof(Persona),1, buffer) > 0)
        {
            nuevo = crearNodo(aux);
            lista = agregarFinal(lista, nuevo);
        }
        fclose(buffer);
    }

    return lista;
}

void recorrerYMostrar(nodo * lista)
{
    nodo * seg = lista;
    while(seg != NULL)
    {
        escribir(seg);
        seg = seg->siguiente;
    }
}
void escribir(nodo * aux)
{
    printf("Nombre: %s \n", aux->dato.nombre);
    printf("edad: %d \n",  aux->dato.edad);
}

nodo * agregarEnOrden(nodo * lista, nodo * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if(strcmp(nuevoNodo->dato.nombre,lista->dato.nombre)<=0)
        {
            lista = agregarPpio(lista, nuevoNodo);
        }
        else
        {
            nodo * ante = lista;
            nodo * seg = lista->siguiente;
            while((seg != NULL)
                    &&(strcmp(nuevoNodo->dato.nombre,seg->dato.nombre)>0))
            {
                ante = seg;
                seg = seg->siguiente;
            }
            nuevoNodo->siguiente = seg;
            ante->siguiente = nuevoNodo;
        }
    }
    return lista;
}

nodo * buscarUltimo(nodo * lista)
{
    nodo * seg = lista;
    if(seg != NULL)
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    return seg;
}

nodo * agregarFinal(nodo * lista, nodo * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodo * ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

nodo * buscarElemento(nodo * lista, int dato)
{
    nodo * seg = lista;
    while((seg != NULL) && (seg ->dato.edad != dato))
    {
        seg = seg->siguiente;
    }
    return seg;
}

int sumarEdades(nodo * lista){
    int suma = 0;
    nodo * seg = lista;
    while(seg != NULL){
        suma = suma+ seg->dato.edad;
        seg = seg-> siguiente;
    }
    return suma;
}

int multiplicarEdades(nodo * lista){
    int resultado = 1;
    nodo * seg = lista;
    while(seg != NULL){
        resultado = resultado * seg->dato.edad;
        seg = seg->siguiente;
    }
    return resultado;
}

float calcularPromedio(nodo * lista){
    int suma = sumarEdades(lista);
    nodo * seg = lista;
    int totales = 0;
    while(seg != NULL){
        totales = totales + 1;
        seg = seg->siguiente;
    }

    float promedio = (float) suma/totales;
    return promedio;
}

/// NODO LISTAS SIMPLES CON PUNTERO DOBLE
nodo * iniclista() /// Inicializamos la lista, importante llamarla arriba del main.
{
    return NULL;
}

nodo * crearNodo (Persona dato) /// Creamos el dato, pasamos la estructura de los datos por parametros.
{

    nodo * aux = (nodo*) malloc(sizeof(nodo));  /// Crea un puntero de tipo nodo y se le asigna un espacio de memoria.
    aux ->dato = dato; /// Se le asigna el dato al puntero.
    aux -> siguiente = NULL; /// Se agrega NULL a la vsariable siguiente.
    return aux; /// Retorna el puntero.
}

nodo * agregarPpio(nodo** lista, nodo * nuevoNodo)
{
    if(*lista == NULL) /// Si la lista esta vacia, apunta a un nuevo nodo.
    {
        *lista = nuevoNodo;
    }
    else /// Si lista no esta vacia, inserta el nuevo nodo al principio, y el viejo primer nodo pasa a ser el segundo.
    {
        nuevoNodo -> siguiente = *lista;
        *lista = nuevoNodo;
    }
}

nodo * cargarNodo(char nombre[], nodo** lista)
{
    nodo * nuevo;
    Persona aux;
    FILE * buffer = fopen(nombre, "rb");
    if(buffer)
    {
        while(fread(&aux, sizeof(Persona),1, buffer) > 0)
        {
            nuevo = crearNodo(aux);
            *lista = agregarFinal(*lista, nuevo);
        }
        fclose(buffer);
    }
}

void recorrerYMostrar(nodo** lista)
{
    nodo * seg = *lista;
    while(seg != NULL)
    {
        escribir(seg);
        seg = seg->siguiente;
    }
}
void escribir(nodo * aux)
{
    printf("Nombre: %s \n", aux->dato.nombre);
    printf("edad: %d \n",  aux->dato.edad);
}

nodo * agregarEnOrden(nodo** lista, nodo * nuevoNodo)
{
    if(*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        if(strcmp(nuevoNodo->dato.nombre,*lista->dato.nombre)<=0)
        {
            *lista = agregarPpio(*lista, nuevoNodo);
        }
        else
        {
            nodo * ante = *lista;
            nodo * seg = *lista->siguiente;
            while((seg != NULL)
                    &&(strcmp(nuevoNodo->dato.nombre,seg->dato.nombre)>0))
            {
                ante = seg;
                seg = seg->siguiente;
            }
            nuevoNodo->siguiente = seg;
            ante->siguiente = nuevoNodo;
        }
    }
}

nodo * buscarUltimo(nodo** lista)
{
    nodo * seg = *lista;
    if(seg != NULL)
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    return seg;
}

nodo * agregarFinal(nodo** lista, nodo * nuevoNodo)
{
    if(*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        nodo * ultimo = buscarUltimo(*lista);
        ultimo->siguiente = nuevoNodo;
    }
}

nodo * buscarElemento(nodo** lista, int dato)
{
    nodo * seg = *lista;
    while((seg != NULL) && (seg ->dato.edad != dato))
    {
        seg = seg->siguiente;
    }
    return seg;
}

int sumarEdades(nodo * lista){
    int suma = 0;
    nodo * seg = lista;
    while(seg != NULL){
        suma = suma+ seg->dato.edad;
        seg = seg-> siguiente;
    }
    return suma;
}

int multiplicarEdades(nodo * lista){
    int resultado = 1;
    nodo * seg = lista;
    while(seg != NULL){
        resultado = resultado * seg->dato.edad;
        seg = seg->siguiente;
    }
    return resultado;
}

float calcularPromedio(nodo * lista){
    int suma = sumarEdades(lista);
    nodo * seg = lista;
    int totales = 0;
    while(seg != NULL){
        totales = totales + 1;
        seg = seg->siguiente;
    }

    float promedio = (float) suma/totales;
    return promedio;
}

