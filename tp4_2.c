#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tarea Tarea;
struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
};

typedef struct Nodo Nodo;
struct Nodo{
    Tarea T;
    Nodo *Siguiente;
};

Nodo* crearListaDeTareas();
void mostrarTareasRealizadasPendientes(Nodo **tareasPendientes, Nodo **tareasRealizadas);
Nodo* quitarNodo(Nodo** cabecera);
void insertarNodo(Nodo **cabecera, Nodo* nodo);
void filtrarTareasSegunID(Nodo **cabecera, Nodo **cabecera1);
int buscarPalabraClave(Nodo *cabecera, char palabra[]);
int buscarPorID(Nodo *cabecera, int ID);

void indicarTareaSegunPalabraClaveOID(Nodo *cabecera, Nodo *cabecera2);

//Cuando vea un puntero tengo que ver en asignarle memoria dinámica!!!!!!!!!!!

int main()
{
    srand(time(NULL));
    int seguirIngresando = 1, ID = 1000;
    int contador=1;
    Nodo* tareasPendientes, *tareasRealizadas;
    char *buffer;
    buffer = (char*)malloc(100*sizeof(char));

    tareasPendientes = crearListaDeTareas();
    tareasRealizadas = crearListaDeTareas();
    
    printf("--------------Ingreso de Tareas Pendientes--------------\n");
    while (seguirIngresando == 1)
    {
        Nodo *nuevo;
        nuevo = (Nodo*)malloc(sizeof(Nodo));

        nuevo->T.TareaID = ID;

        fflush(stdin);
        printf("Ingresar descripcion de la %d° tarea: ",contador);
        gets(buffer);
        nuevo->T.Descripcion = (char*)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(nuevo->T.Descripcion, buffer);
        do
        {
            printf("Ingrese la duracion de la tarea(entre 10-100): ");
            scanf("%d", &nuevo->T.Duracion);
        } while (nuevo->T.Duracion < 10 || nuevo->T.Duracion >100);
                
        nuevo->Siguiente = tareasPendientes;
        tareasPendientes = nuevo;
        ID++;

        printf("Desea seguir ingresando tareas pendientes? (1:si, 0:no): ");
        scanf("%d", &seguirIngresando);
        printf("\n");
    }

    do
    {        
        printf("--------------Menu--------------\n");
        printf("1 - Realizar una tarea\n");
        printf("2 - Listar tareas pendientes y tareas realizadas\n");
        printf("3 - Consultar tarea mediante id o palabra clave\n");
        printf("4 - Salir\n");

        do
        {
            printf("Ingrese una opcion:");
            scanf("%d", &seguirIngresando);

        } while(seguirIngresando < 1 || seguirIngresando > 4);
        
        switch (seguirIngresando)// MENU DE TAREAS
        {
            case 1:
                filtrarTareasSegunID(&tareasPendientes, &tareasRealizadas);
                break;
            case 2:
                mostrarTareasRealizadasPendientes(&tareasPendientes, &tareasRealizadas);
                break;
            case 3:
                indicarTareaSegunPalabraClaveOID(tareasRealizadas, tareasPendientes);
                break;
            default:
                break;
        }
    } while (seguirIngresando != 4);


    free(tareasPendientes);
    free(buffer);
    
    return 0;
}

Nodo *crearListaDeTareas(){
    return NULL;
}

void mostrarTareasRealizadasPendientes(Nodo **tareasPendientes, Nodo **tareasRealizadas)
{
    Nodo *Aux;
    Aux = *tareasPendientes;
    printf("\n--------------Tareas Pendientes--------------\n");
    while(Aux != NULL)
    {
        printf("\tID de la Tarea: %d\n", Aux->T.TareaID);
        printf("\tDescripcion: ");
        puts(Aux->T.Descripcion);
        printf("\tDuracion de la tarea: %d", Aux->T.Duracion);
        printf("\n\n");
        Aux = Aux->Siguiente;
    }

    Aux = *tareasRealizadas;
    printf("\n--------------Tareas Realizadas--------------\n");
    while(Aux != NULL)
    {
        printf("\tID de la Tarea: %d\n", Aux->T.TareaID);
        printf("\tDescripcion: ");
        puts(Aux->T.Descripcion);
        printf("\tDuracion de la tarea: %d", Aux->T.Duracion);
        printf("\n\n");
        Aux = Aux->Siguiente;
    }
}

Nodo* quitarNodo(Nodo** cabecera)
{
    Nodo *nodoQuitar = *cabecera;
    *cabecera = (*cabecera)->Siguiente;
    nodoQuitar->Siguiente = NULL;
    return(nodoQuitar);
}

void insertarNodo(Nodo **cabecera, Nodo* nodo)
{
    nodo->Siguiente = (*cabecera);
    (*cabecera) = nodo;
}

void filtrarTareasSegunID(Nodo **cabecera, Nodo **cabecera1)
{
    int ID;
    printf("Ingrese el ID de la tarea a realizar: ");
    scanf("%d", &ID);
    Nodo** NodoActual, *NodoQuitado;
    NodoActual = cabecera;
    while((*NodoActual))
    {
        if ((*NodoActual)->T.TareaID == ID)
        {
            NodoQuitado = quitarNodo(NodoActual);
            insertarNodo(cabecera1, NodoQuitado);
        }else{
            NodoActual = &(*NodoActual)->Siguiente;
        }
    }
}

void indicarTareaSegunPalabraClaveOID(Nodo *cabecera, Nodo *cabecera2)
{
    char palabra[100];
    int opcion, ID, resultadoListaPendientes, resultadoListaRealizadas;
    printf("Ingrese 1 si quere buscar una tarea por ID, o 2 si quiere buscar una tarea por palabra clave: ");
    scanf("%d", &opcion);
    fflush(stdin);
    switch(opcion)
    {
    case(1):
        printf("ID:");
        scanf("%d", &ID);
        resultadoListaRealizadas = buscarPorID(cabecera, ID);
        resultadoListaPendientes = buscarPorID(cabecera2, ID);
        break;
    case(2):
        gets(palabra);
        resultadoListaRealizadas = buscarPalabraClave(cabecera, palabra);
        resultadoListaPendientes = buscarPalabraClave(cabecera2, palabra);
        break;
    default:
        break;
    }

    if (resultadoListaRealizadas)
    {
        printf("La tarea se encontro en tareas realizadas\n");
    }else if(resultadoListaPendientes)
    {
        printf("La tarea se encontro en tareas pendientes\n");
    }else
    {
            printf("NO se encontro la tarea\n");
    }
}

int buscarPalabraClave(Nodo *cabecera, char palabra[])
{
    while (cabecera)
    {
        if(strstr(cabecera->T.Descripcion, palabra) != NULL)
        {
            return 1;
        }
        cabecera = cabecera->Siguiente;
    }
    return 0;
}

int buscarPorID(Nodo *cabecera, int ID)
{
    while (cabecera)
    {
        if(cabecera->T.TareaID == ID)
        {
            return 1;
        }
        cabecera = cabecera->Siguiente;
    }
    return 0;
}