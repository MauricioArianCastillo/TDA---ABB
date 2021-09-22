#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

#define OK 0
#define ERROR -1


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	abb_t* arbol=calloc(1,sizeof(abb_t));
	if(!arbol) return NULL;
	arbol->comparador=comparador;
	arbol->destructor=destructor;
	return arbol;
}


nodo_abb_t* insertar_nodo(nodo_abb_t* raiz,void* elemento,abb_comparador comparador){
	if(!raiz){
		nodo_abb_t* nodo=calloc(1,sizeof(nodo_abb_t));
		if(!nodo) return NULL;
		nodo->elemento=elemento;
		return nodo;
	}
	if(comparador(elemento,raiz->elemento)>0)
		raiz->derecha=insertar_nodo(raiz->derecha,elemento,comparador);

	if(comparador(elemento,raiz->elemento)<=0)
		raiz->izquierda=insertar_nodo(raiz->izquierda,elemento,comparador);
	
	return raiz;
}

int arbol_insertar(abb_t* arbol, void* elemento){
	if(!arbol) return ERROR;
	if(!arbol->nodo_raiz){
		nodo_abb_t* nodo=calloc(1,sizeof(nodo_abb_t));
		if(!nodo) return ERROR;
		nodo->elemento=elemento;
		arbol->nodo_raiz=nodo;
		return OK;
	}
	arbol->nodo_raiz=insertar_nodo(arbol->nodo_raiz,elemento,arbol->comparador);
	if(!arbol->nodo_raiz){
		arbol_insertar(arbol,elemento);
		return OK;
	}
	return OK;
}

nodo_abb_t* nodo_buscar(nodo_abb_t* raiz, void* elemento,abb_comparador comparador){
	if(!raiz || !raiz->elemento || !elemento) return NULL;
	if(comparador(elemento,raiz->elemento)>0)
		return nodo_buscar(raiz->derecha,elemento,comparador);
	if(comparador(elemento,raiz->elemento)<0)
		return nodo_buscar(raiz->izquierda,elemento,comparador);
	return raiz;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if (!arbol || !arbol->nodo_raiz || !arbol->nodo_raiz->elemento) return NULL;
	nodo_abb_t* nodo = nodo_buscar(arbol->nodo_raiz,elemento,arbol->comparador);
	if(!nodo || !nodo->elemento) return NULL;
	return nodo->elemento;
}

nodo_abb_t* predecesor_inorden(nodo_abb_t* raiz){
	if(raiz->derecha==NULL) return raiz;
	else raiz=predecesor_inorden(raiz->derecha);
	return raiz;
}

nodo_abb_t* actualizar_predecesor_inorden(nodo_abb_t* raiz,bool tiene_hijos, abb_liberar_elemento destructor){
	if(raiz->derecha==NULL && tiene_hijos) {
		nodo_abb_t* nueva_raiz=raiz->izquierda;				
		if (destructor!=NULL) destructor(raiz->elemento);
		free(raiz);
		return nueva_raiz;
	}
	if(raiz->derecha==NULL && !tiene_hijos){
		if(destructor!=NULL) destructor(raiz->elemento);					
		free(raiz);
		return NULL;
	}
	raiz->derecha=actualizar_predecesor_inorden(raiz->derecha,tiene_hijos,destructor);
	return raiz;
}

nodo_abb_t* eliminar_nodo_mayor_y_devolver_raiz(nodo_abb_t* raiz ,abb_liberar_elemento destructor){
	nodo_abb_t* nodo=predecesor_inorden(raiz->izquierda);
	bool tiene_hijos=true;
	if(!nodo->izquierda && !nodo->derecha){
		tiene_hijos=false;
		void* aux=raiz->elemento;
		raiz->elemento=nodo->elemento;
		nodo->elemento=aux;
	 	raiz->izquierda=actualizar_predecesor_inorden(raiz->izquierda,tiene_hijos,destructor);
	 	return raiz;
	}
	if(nodo->izquierda){
		tiene_hijos=true;
		void* aux=raiz->elemento;
		raiz->elemento=nodo->elemento;
		nodo->elemento=aux;
	 	raiz->izquierda=actualizar_predecesor_inorden(raiz->izquierda,tiene_hijos,destructor);
		return raiz;
	}
	return raiz;
}


nodo_abb_t* nodo_borrar(nodo_abb_t* raiz,void* elemento, abb_comparador comparador, abb_liberar_elemento destructor){

	if(!raiz) return NULL;
	if(!comparador) return NULL;

	if(comparador(elemento,raiz->elemento)==0){

		if(!raiz->izquierda && !raiz->derecha){															//es hoja

			if (destructor!=NULL) destructor(raiz->elemento);

			free(raiz);

			return NULL;

		}

		if(raiz->izquierda && raiz->derecha){

			raiz=eliminar_nodo_mayor_y_devolver_raiz(raiz, destructor);			//tiene 2 hijos

			return raiz;

		}
		nodo_abb_t* nueva_raiz=raiz->derecha?raiz->derecha:raiz->izquierda;								//tiene 1 hijo
		if (destructor!=NULL) destructor(raiz->elemento);
		free(raiz);
		return nueva_raiz;
	}

	if(comparador(elemento,raiz->elemento)>0){
		raiz->derecha=nodo_borrar(raiz->derecha,elemento,comparador,destructor);
	}
	else{
		raiz->izquierda=nodo_borrar(raiz->izquierda,elemento,comparador,destructor);
	}
	return raiz;

}

int arbol_borrar(abb_t* arbol, void* elemento){
	
	if(!arbol || !arbol->nodo_raiz) return ERROR;
	arbol->nodo_raiz=nodo_borrar(arbol->nodo_raiz,elemento,arbol->comparador,arbol->destructor);
	return OK;
	
}

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool arbol_vacio(abb_t* arbol){
	if(!arbol || !arbol->nodo_raiz || !arbol->nodo_raiz->elemento) return true;
	else return false;
}


/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
void* arbol_raiz(abb_t* arbol){
	if (arbol_vacio(arbol)) return NULL;
	return arbol->nodo_raiz->elemento;
}


size_t insertar_inorden(void** array, size_t tamanio_array, nodo_abb_t* raiz,size_t cantidad_elementos){
	if(cantidad_elementos>= tamanio_array) return cantidad_elementos;
	if(raiz->izquierda)
		cantidad_elementos=insertar_inorden(array,tamanio_array,raiz->izquierda,cantidad_elementos);

	array[cantidad_elementos]=raiz->elemento;
	cantidad_elementos=cantidad_elementos+1;

	if(raiz->derecha)
		cantidad_elementos=insertar_inorden(array,tamanio_array,raiz->derecha,cantidad_elementos);
	return cantidad_elementos;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){

	size_t cantidad_elementos=0;
	cantidad_elementos=insertar_inorden(array,tamanio_array,arbol->nodo_raiz,cantidad_elementos);
	return cantidad_elementos;

}

size_t insertar_preorden(void** array, size_t tamanio_array, nodo_abb_t* raiz,size_t cantidad_elementos){
	if(cantidad_elementos >= tamanio_array) return cantidad_elementos;

	array[cantidad_elementos]=raiz->elemento;
	cantidad_elementos=cantidad_elementos+1;

	if(raiz->izquierda)
		cantidad_elementos=insertar_preorden(array,tamanio_array,raiz->izquierda,cantidad_elementos);

	if(raiz->derecha)
		cantidad_elementos=insertar_preorden(array,tamanio_array,raiz->derecha,cantidad_elementos);

	return cantidad_elementos;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){

	size_t cantidad_elementos=0;
	cantidad_elementos=insertar_preorden(array,tamanio_array,arbol->nodo_raiz,cantidad_elementos);
	return cantidad_elementos;

}

size_t insertar_postorden(void** array, size_t tamanio_array, nodo_abb_t* raiz,size_t cantidad_elementos){
	if(!raiz) return cantidad_elementos;

	if(raiz->izquierda) 
		cantidad_elementos=insertar_postorden(array,tamanio_array,raiz->izquierda,cantidad_elementos);

	if(raiz->derecha)
		cantidad_elementos=insertar_postorden(array,tamanio_array,raiz->derecha,cantidad_elementos);

	if(cantidad_elementos >= tamanio_array) return cantidad_elementos;

	array[cantidad_elementos]=raiz->elemento;
	cantidad_elementos=cantidad_elementos+1;

	return cantidad_elementos;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){

	size_t cantidad_elementos=0;
	cantidad_elementos=insertar_postorden(array,tamanio_array,arbol->nodo_raiz,cantidad_elementos);
	return cantidad_elementos;
}

void nodo_destruir(abb_t* arbol, nodo_abb_t* nodo){

    if(!nodo)

        return;

    if(nodo->izquierda)

        nodo_destruir(arbol, nodo->izquierda);

    if(nodo->derecha)

        nodo_destruir(arbol, nodo->derecha);

       if(nodo && arbol->destructor)

        arbol->destructor(nodo->elemento);

    free(nodo);

}


void arbol_destruir(abb_t* arbol){

 if(!arbol) return;

    if (arbol->nodo_raiz) 

        nodo_destruir(arbol, arbol->nodo_raiz);

    free(arbol);

}


size_t recorrer_inorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),bool* termina,size_t cantidad_elementos,void* extra){
	if(!raiz || (*termina)) return cantidad_elementos;
	
	if(raiz->izquierda)
		cantidad_elementos=recorrer_inorden(raiz->izquierda,funcion,termina,cantidad_elementos,extra);

	if((*termina)) return cantidad_elementos;

	(*termina)=funcion(raiz->elemento,extra);
	cantidad_elementos=cantidad_elementos+1;

	if((*termina)) return cantidad_elementos;

	if(raiz->derecha)
		cantidad_elementos=recorrer_inorden(raiz->derecha,funcion,termina,cantidad_elementos,extra);

	return cantidad_elementos;
}

size_t recorrer_preorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),bool* termina,size_t cantidad_elementos,void* extra){

	if(!raiz || (*termina)) return cantidad_elementos;

	(*termina)=funcion(raiz->elemento,extra);
	cantidad_elementos=cantidad_elementos+1;

	if((*termina)) return cantidad_elementos;

	if(raiz->izquierda)
		cantidad_elementos=recorrer_preorden(raiz->izquierda,funcion,termina,cantidad_elementos,extra);

	if(raiz->derecha)
		cantidad_elementos=recorrer_preorden(raiz->derecha,funcion,termina,cantidad_elementos,extra);
	
	return cantidad_elementos;
}

size_t recorrer_postorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),bool *termina,size_t cantidad_elementos,void* extra){

		if(!raiz || (*termina)) return cantidad_elementos;

		if(raiz->izquierda)
			cantidad_elementos=recorrer_postorden(raiz->izquierda,funcion,termina,cantidad_elementos,extra);

		if(raiz->derecha)
			cantidad_elementos=recorrer_postorden(raiz->derecha,funcion,termina,cantidad_elementos,extra);

		if((*termina)) return cantidad_elementos;
		
		cantidad_elementos=cantidad_elementos+1;
		(*termina)=funcion(raiz->elemento,extra);
		
		if((*termina)) return cantidad_elementos;
		

		return cantidad_elementos;
}


size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(arbol_vacio(arbol) || funcion==NULL) return 0;
	bool* termina=NULL;
	bool falso=false;
	termina=&falso;
	size_t cantidad_elementos=0;
	switch(recorrido){

		case 0: return cantidad_elementos=recorrer_inorden(arbol->nodo_raiz,funcion,termina,cantidad_elementos,extra);
				break;

		case 1: return cantidad_elementos=recorrer_preorden(arbol->nodo_raiz,funcion,termina,cantidad_elementos,extra);
				break;

		case 2: return cantidad_elementos=recorrer_postorden(arbol->nodo_raiz,funcion,termina,cantidad_elementos,extra);
				break;
	}
	return cantidad_elementos;
}