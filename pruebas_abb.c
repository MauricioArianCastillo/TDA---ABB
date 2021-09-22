#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include "pa2m.h"

#define OK 0
#define ERROR -1

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
        c->clave = clave;
    return c;
}

int comparador(void*elemento, void*elemento2){
	if(!elemento || !elemento2)
        return 0;
	if(((cosa*)elemento)->clave==((cosa*)elemento2)->clave) return 0;
	if(((cosa*)elemento)->clave>((cosa*)elemento2)->clave) return 1;
	return -1; 
}

void liberar_elemento(void*elemento){
	if(!elemento) return;
	free((cosa*)elemento);
}

void pruebas_crear_arbol(){

	abb_t* arbol=arbol_crear(comparador,liberar_elemento);
	pa2m_afirmar(arbol!=NULL, "Se pudo crear el arbol.");
	pa2m_afirmar(arbol->nodo_raiz==NULL, "El arbol se crea vacio y el elemento raiz es NULL.");
	arbol_destruir(arbol);
}

void pruebas_insercion(){

	abb_t* arbol=NULL;
	cosa* c100=crear_cosa(100);
	pa2m_afirmar(arbol_insertar(arbol,c100)==ERROR,"No se puede insertar en un arbol nulo");
	liberar_elemento(c100);

	arbol=arbol_crear(comparador,liberar_elemento);


	cosa* c3=crear_cosa(3);
	cosa* c2=crear_cosa(2);
	cosa* c0=crear_cosa(0);
	cosa* c1=crear_cosa(1);
	cosa* c6=crear_cosa(6);
	cosa* c4=crear_cosa(4);
	cosa* c5=crear_cosa(5);


	pa2m_afirmar(arbol_insertar(arbol,c3)==OK,"Se pudo insertar un elemento");
	pa2m_afirmar(arbol_insertar(arbol,c2)==OK,"Se pudo insertar un elemento");
	pa2m_afirmar(arbol_insertar(arbol,c0)==OK,"Se pudo insertar un elemento");
	pa2m_afirmar(arbol_insertar(arbol,c1)==OK,"Se pudo insertar un elemento");
	pa2m_afirmar(arbol_insertar(arbol,c6)==OK,"Se pudo insertar un elemento");
	pa2m_afirmar(arbol_insertar(arbol,c4)==OK,"Se pudo insertar un elemento");
	pa2m_afirmar(arbol_insertar(arbol,c5)==OK,"Se pudo insertar un elemento");

	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento==c3->clave,"EL 1 elemento es el correcto");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->izquierda->elemento==c2->clave,"EL 2 elemento es el correcto");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->izquierda->izquierda->elemento==c0->clave,"EL 3 elemento es el correcto");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->izquierda->izquierda->derecha->elemento==c1->clave,"EL 4 elemento es el correcto");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->derecha->elemento==c6->clave,"EL 5 elemento es el correcto");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->derecha->izquierda->elemento==c4->clave,"EL 6 elemento es el correcto");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->derecha->izquierda->derecha->elemento==c5->clave,"EL 7 elemento es el correcto");

	arbol_destruir(arbol);
}

void pruebas_busqueda(){

	abb_t* arbol=arbol_crear(comparador,liberar_elemento);


	cosa* c3=crear_cosa(3);
	cosa* c2=crear_cosa(2);
	cosa* c0=crear_cosa(0);
	cosa* c1=crear_cosa(1);
	cosa* c6=crear_cosa(6);
	cosa* c4=crear_cosa(4);
	cosa* c5=crear_cosa(5);

	arbol_insertar(arbol,c3);
	arbol_insertar(arbol,c2);
	arbol_insertar(arbol,c0);
	arbol_insertar(arbol,c1);
	arbol_insertar(arbol,c6);
	arbol_insertar(arbol,c4);
	arbol_insertar(arbol,c5);

	pa2m_afirmar(*(int*)arbol_buscar(arbol,&c0->clave)==c0->clave,"Busco el elemento insertado y lo devuelve.");
	pa2m_afirmar(*(int*)arbol_buscar(arbol,&c1->clave)==c1->clave,"Busco el elemento insertado y lo devuelve.");
	pa2m_afirmar(*(int*)arbol_buscar(arbol,&c2->clave)==c2->clave,"Busco el elemento insertado y lo devuelve.");
	pa2m_afirmar(*(int*)arbol_buscar(arbol,&c3->clave)==c3->clave,"Busco el elemento insertado y lo devuelve.");
	pa2m_afirmar(*(int*)arbol_buscar(arbol,&c4->clave)==c4->clave,"Busco el elemento insertado y lo devuelve.");
	pa2m_afirmar(*(int*)arbol_buscar(arbol,&c5->clave)==c5->clave,"Busco el elemento insertado y lo devuelve.");
	pa2m_afirmar(*(int*)arbol_buscar(arbol,&c6->clave)==c6->clave,"Busco el elemento insertado y lo devuelve.");

	arbol_destruir(arbol);



}


void pruebas_borrar(){

	abb_t* arbol=arbol_crear(comparador,liberar_elemento);

	cosa* c3=crear_cosa(3);
	cosa* c2=crear_cosa(2);
	cosa* c0=crear_cosa(0);
	cosa* c1=crear_cosa(1);
	cosa* c6=crear_cosa(6);
	cosa* c4=crear_cosa(4);
	cosa* c5=crear_cosa(5);
	cosa* c7=crear_cosa(7);
	cosa* c56=crear_cosa(56);
	cosa* aux=crear_cosa(100);

	arbol_insertar(arbol,c3);
	arbol_insertar(arbol,c2);
	arbol_insertar(arbol,c0);
	arbol_insertar(arbol,c1);
	arbol_insertar(arbol,c6);
	arbol_insertar(arbol,c4);
	arbol_insertar(arbol,c5);
	arbol_insertar(arbol,c7);
	arbol_insertar(arbol,c56);

	aux->clave=6;

	pa2m_afirmar(arbol_borrar(arbol,&c6->clave)==OK,"Se pudo borrar un elemento con dos hijos del arbol.");			
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento==&c5->clave,"La posicion del elemento borrado fue reemplazada correctamente por su predecesor inorden.");	

	aux->clave=2;
	
	pa2m_afirmar(arbol_borrar(arbol,&c2->clave)==OK,"Se pudo borrar un elemento con un hijo del arbol.");			
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento==&c0->clave,"La posicion del elemento borrado fue reemplazada correctamente por su predecesor inorden.");

	aux->clave=3;
	
	pa2m_afirmar(arbol_borrar(arbol,&c3->clave)==OK,"Se pudo borrar la raiz del arbol.");							
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->elemento==&c1->clave,"La posicion del elemento borrado fue reemplazada correctamente por su predecesor inorden.");	

	aux->clave=5;

	pa2m_afirmar(arbol_borrar(arbol,&c5->clave)==OK,"Se pudo borrar un elemento con dos hijos del arbol.");			
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento==&c4->clave,"La posicion del elemento borrado fue reemplazada correctamente por su predecesor inorden.");	

	aux->clave=0;


	pa2m_afirmar(arbol_borrar(arbol,&c0->clave)==OK,"Se pudo borrar una hoja del arbol.");							
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->izquierda==NULL,"La hoja borrada ahora es NULL.");

	aux->clave=1;

	pa2m_afirmar(arbol_borrar(arbol,&c1->clave)==OK,"Se pudo borrar la raiz.");										
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->elemento==&c4->clave,"La raiz ahora es el hijo de la raiz borrada.");				

	aux->clave=4;

	pa2m_afirmar(arbol_borrar(arbol,&c4->clave)==OK,"Se pudo borrar la raiz.");										
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->elemento==&c7->clave,"La raiz ahora es el hijo de la raiz borrada.");				

	aux->clave=7;

	pa2m_afirmar(arbol_borrar(arbol,&c7->clave)==OK,"Se pudo borrar la raiz.");										
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");				
	pa2m_afirmar(arbol->nodo_raiz->elemento==&c56->clave,"La raiz ahora es el hijo de la raiz borrada.");				

	aux->clave=56;

	pa2m_afirmar(arbol_borrar(arbol,&c56->clave)==OK,"Se pudo borrar la raiz.");										
	pa2m_afirmar(arbol_buscar(arbol,&aux->clave)==NULL,"El elemento borrado ya no esta en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz==NULL,"Se pudo borrar el arbol");

	liberar_elemento(aux);

	arbol_destruir(arbol);
}

void pruebas_inorden(){

	abb_t* arbol=arbol_crear(comparador,liberar_elemento);

	cosa* c3=crear_cosa(3);
	cosa* c2=crear_cosa(2);
	cosa* c0=crear_cosa(0);
	cosa* c1=crear_cosa(1);
	cosa* c6=crear_cosa(6);
	cosa* c4=crear_cosa(4);
	cosa* c5=crear_cosa(5);
	cosa* c7=crear_cosa(7);
	cosa* c56=crear_cosa(56);

	arbol_insertar(arbol,c3);
	arbol_insertar(arbol,c2);
	arbol_insertar(arbol,c0);
	arbol_insertar(arbol,c1);
	arbol_insertar(arbol,c6);
	arbol_insertar(arbol,c4);
	arbol_insertar(arbol,c5);
	arbol_insertar(arbol,c7);
	arbol_insertar(arbol,c56);


	size_t tamanio_array=9;
	void* array[tamanio_array];
	size_t elementos=arbol_recorrido_inorden(arbol,array,tamanio_array);
	pa2m_afirmar(elementos==tamanio_array,"Se inserto en el array la cantidad de veces correcta");
	bool es_igual=true;

	if((*(int*)array[0]!=c0->clave)) es_igual=false;
	if((*(int*)array[1]!=c1->clave)) es_igual=false;
	if((*(int*)array[2]!=c2->clave)) es_igual=false;
	if((*(int*)array[3]!=c3->clave)) es_igual=false;
	if((*(int*)array[4]!=c4->clave)) es_igual=false;
	if((*(int*)array[5]!=c5->clave)) es_igual=false;
	if((*(int*)array[6]!=c6->clave)) es_igual=false;
	if((*(int*)array[7]!=c7->clave)) es_igual=false;
	if((*(int*)array[8]!=c56->clave)) es_igual=false;

	pa2m_afirmar(es_igual,"Los elementos se insertaron correctamente en inorden.");

	size_t tamanio_array2=7;
	void* array2[tamanio_array2];
	elementos=arbol_recorrido_inorden(arbol,array2,tamanio_array2);
	pa2m_afirmar(elementos==tamanio_array2,"Si el espacio del array es menor,llena hasta donde puede y devuelve la cantidad de elementos que pudo poner");

	if((*(int*)array2[0]!=c0->clave)) es_igual=false;
	if((*(int*)array2[1]!=c1->clave)) es_igual=false;
	if((*(int*)array2[2]!=c2->clave)) es_igual=false;
	if((*(int*)array2[3]!=c3->clave)) es_igual=false;
	if((*(int*)array2[4]!=c4->clave)) es_igual=false;
	if((*(int*)array2[5]!=c5->clave)) es_igual=false;
	if((*(int*)array2[6]!=c6->clave)) es_igual=false;

	pa2m_afirmar(es_igual,"Los elementos se insertaron correctamente en inorden.");
	arbol_destruir(arbol);
}

void pruebas_preorden(){

	abb_t* arbol=arbol_crear(comparador,liberar_elemento);

	cosa* c3=crear_cosa(3);
	cosa* c2=crear_cosa(2);
	cosa* c0=crear_cosa(0);
	cosa* c1=crear_cosa(1);
	cosa* c6=crear_cosa(6);
	cosa* c4=crear_cosa(4);
	cosa* c5=crear_cosa(5);
	cosa* c7=crear_cosa(7);
	cosa* c56=crear_cosa(56);

	arbol_insertar(arbol,c3);
	arbol_insertar(arbol,c2);
	arbol_insertar(arbol,c0);
	arbol_insertar(arbol,c1);
	arbol_insertar(arbol,c6);
	arbol_insertar(arbol,c4);
	arbol_insertar(arbol,c5);
	arbol_insertar(arbol,c7);
	arbol_insertar(arbol,c56);

	size_t tamanio_array=9;
	void* array[tamanio_array];
	size_t elementos=arbol_recorrido_preorden(arbol,array,tamanio_array);
	pa2m_afirmar(elementos==tamanio_array,"Se inserto en el array la cantidad de veces correcta");
	bool es_igual=true;
	
	if((*(int*)array[0]!=c3->clave)) es_igual=false;
	if((*(int*)array[1]!=c2->clave)) es_igual=false;
	if((*(int*)array[2]!=c0->clave)) es_igual=false;
	if((*(int*)array[3]!=c1->clave)) es_igual=false;
	if((*(int*)array[4]!=c6->clave)) es_igual=false;
	if((*(int*)array[5]!=c4->clave)) es_igual=false;
	if((*(int*)array[6]!=c5->clave)) es_igual=false;
	if((*(int*)array[7]!=c7->clave)) es_igual=false;
	if((*(int*)array[8]!=c56->clave)) es_igual=false;

	pa2m_afirmar(es_igual,"Los elementos se insertaron correctamente en preorden.");
	size_t tamanio_array2=7;
	void* array2[tamanio_array2];
	elementos=arbol_recorrido_preorden(arbol,array2,tamanio_array2);
	pa2m_afirmar(elementos==tamanio_array2,"Si el espacio del array es menor,llena hasta donde puede y devuelve la cantidad de elementos que pudo poner");

	if((*(int*)array2[0]!=c3->clave)) es_igual=false;
	if((*(int*)array2[1]!=c2->clave)) es_igual=false;
	if((*(int*)array2[2]!=c0->clave)) es_igual=false;
	if((*(int*)array2[3]!=c1->clave)) es_igual=false;
	if((*(int*)array2[4]!=c6->clave)) es_igual=false;
	if((*(int*)array2[5]!=c4->clave)) es_igual=false;
	if((*(int*)array2[6]!=c5->clave)) es_igual=false;

	pa2m_afirmar(es_igual,"Los elementos se insertaron correctamente en preorden.");

	arbol_destruir(arbol);
}

void pruebas_postorden(){

	abb_t* arbol=arbol_crear(comparador,liberar_elemento);

	cosa* c3=crear_cosa(3);
	cosa* c2=crear_cosa(2);
	cosa* c0=crear_cosa(0);
	cosa* c1=crear_cosa(1);
	cosa* c6=crear_cosa(6);
	cosa* c4=crear_cosa(4);
	cosa* c5=crear_cosa(5);
	cosa* c7=crear_cosa(7);
	cosa* c56=crear_cosa(56);

	arbol_insertar(arbol,c3);
	arbol_insertar(arbol,c2);
	arbol_insertar(arbol,c0);
	arbol_insertar(arbol,c1);
	arbol_insertar(arbol,c6);
	arbol_insertar(arbol,c4);
	arbol_insertar(arbol,c5);
	arbol_insertar(arbol,c7);
	arbol_insertar(arbol,c56);

	size_t tamanio_array=9;
	void* array[tamanio_array];
	size_t elementos=arbol_recorrido_postorden(arbol,array,tamanio_array);
	pa2m_afirmar(elementos==tamanio_array,"Se inserto en el array la cantidad de veces correcta");
	bool es_igual=true;

	if((*(int*)array[0]!=c1->clave)) es_igual=false;
	if((*(int*)array[1]!=c0->clave)) es_igual=false;
	if((*(int*)array[2]!=c2->clave)) es_igual=false;
	if((*(int*)array[3]!=c5->clave)) es_igual=false;
	if((*(int*)array[4]!=c4->clave)) es_igual=false;
	if((*(int*)array[5]!=c56->clave)) es_igual=false;
	if((*(int*)array[6]!=c7->clave)) es_igual=false;
	if((*(int*)array[7]!=c6->clave)) es_igual=false;
	if((*(int*)array[8]!=c3->clave)) es_igual=false;

	pa2m_afirmar(es_igual,"Los elementos se insertaron correctamente en postorden.");
	size_t tamanio_array2=7;
	void* array2[tamanio_array2];
	elementos=arbol_recorrido_postorden(arbol,array2,tamanio_array2);
	pa2m_afirmar(elementos==tamanio_array2,"Si el espacio del array es menor,llena hasta donde puede y devuelve la cantidad de elementos que pudo poner");

	if((*(int*)array2[0]!=c1->clave)) es_igual=false;
	if((*(int*)array2[1]!=c0->clave)) es_igual=false;
	if((*(int*)array2[2]!=c2->clave)) es_igual=false;
	if((*(int*)array2[3]!=c5->clave)) es_igual=false;
	if((*(int*)array2[4]!=c4->clave)) es_igual=false;
	if((*(int*)array2[5]!=c56->clave)) es_igual=false;
	if((*(int*)array2[6]!=c7->clave)) es_igual=false;


	pa2m_afirmar(es_igual,"Los elementos se insertaron correctamente en postorden.");

	arbol_destruir(arbol);

}

bool leer_menores_a_n_e_imprimir(void*elemento,void*corte){
	if(!elemento || !corte) return true;

	if(*(int*)elemento<(int*)corte){ 
		printf(" %d -",*(int*)elemento);

		return false;
	}
	return true;
}


void pruebas_iterador(){

	abb_t* arbol=NULL;
	size_t cantidad=0;
	void* condicion=(int*)10;

	cantidad=abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,leer_menores_a_n_e_imprimir,condicion);
	pa2m_afirmar(cantidad==0,"No se puede iterar con un arbol nulo.");



	arbol=arbol_crear(comparador,liberar_elemento);

	cosa* c3=crear_cosa(3);
	cosa* c2=crear_cosa(2);
	cosa* c0=crear_cosa(0);
	cosa* c1=crear_cosa(1);
	cosa* c6=crear_cosa(6);
	cosa* c4=crear_cosa(4);
	cosa* c5=crear_cosa(5);
	cosa* c7=crear_cosa(7);
	cosa* c56=crear_cosa(56);

	arbol_insertar(arbol,c3);
	arbol_insertar(arbol,c2);
	arbol_insertar(arbol,c0);
	arbol_insertar(arbol,c1);
	arbol_insertar(arbol,c6);
	arbol_insertar(arbol,c4);
	arbol_insertar(arbol,c5);
	arbol_insertar(arbol,c7);
	arbol_insertar(arbol,c56);

	cantidad=abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,NULL,condicion);

	pa2m_afirmar(cantidad==0,"No se puede iterar con una funcion nula.");

	printf("Leer menores a 10 e imprimir inorden: ");
	cantidad=abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,leer_menores_a_n_e_imprimir,condicion);
	printf("\nEl orden es el esperado.");
	printf("\n");
	pa2m_afirmar(cantidad==9,"El iterador devuelve la cantidad correcta");
	


	printf("Leer menores a 10 e imprimir preorden: ");
	cantidad=abb_con_cada_elemento(arbol,ABB_RECORRER_PREORDEN,leer_menores_a_n_e_imprimir,condicion);
	printf("\nEl orden es el esperado.");
	printf("\n");
	pa2m_afirmar(cantidad==9,"El iterador devuelve la cantidad correcta");
	

	printf("Leer menores a 10 e imprimir postorden: ");
	cantidad=abb_con_cada_elemento(arbol,ABB_RECORRER_POSTORDEN,leer_menores_a_n_e_imprimir,condicion);
	printf("\nEl orden es el esperado.");
	printf("\n");
	pa2m_afirmar(cantidad==6,"El iterador devuelve la cantidad correcta");
	



	arbol_destruir(arbol);
}


void main(){
	pa2m_nuevo_grupo("PRUEBAS DE CREACION");
	pruebas_crear_arbol();
	pa2m_nuevo_grupo("PRUEBAS DE INSERCION");
	pruebas_insercion();
	pa2m_nuevo_grupo("PRUEBAS DE BUSQUEDA");
	pruebas_busqueda();
	pa2m_nuevo_grupo("PRUEBAS BORRAR");
	pruebas_borrar();
	pa2m_nuevo_grupo("PRUEBAS RECORRER INORDEN");
	pruebas_inorden();
	pa2m_nuevo_grupo("PRUEBAS RECORRER PREORDEN");
	pruebas_preorden();
	pa2m_nuevo_grupo("PRUEBAS RECORRER POSTORDEN");
	pruebas_postorden();
	pa2m_nuevo_grupo("PRUEBAS ITERADOR");
	pruebas_iterador();
	pa2m_mostrar_reporte();

}
