

                                        Read Me
                                -------------------------------


Sobre el trabajo:
----------------

Para compilarlo la linea es: gcc -g -O0 abb.c  pruebas_abb.c -o pruebas 

Y para correrlo: ./pruebas

El trabajo consta de la implementacion de un arbol binario en abb.c, el cual debe funcionar correctamente. Para asegurarme de eso, implemente las pruebas para verificar que cada funcion no tenga errores.

En abb.c implemento la funcion de arbol crear reservando memoria para el arbol inicializando sus campos en NULL. Luego en insertar inserto la raiz, seguido de los nodos, comparando sus valores para que se ubiquen correctamente en el arbol. 

En arbol_buscar busco el nodo recursivamente, comparando el elemento con los que tengo insertados en el arbol hasta encontrar el elemento pedido, si no lo encuentra devuelve NULL. 

Despues en arbol_borrar actualizo el nodo_raiz igualandolo a una funcion llamada "nodo_borrar" que recorre el arbol comparando el elemento a borrar con los elementos del arbol hasta que lo encuentra. Cuando lo encuentra se pregunta 3 casos: 
*En el 1ro pregunta si es una hoja, entonces libera su elemento y la raiz, y devuelve NULL (para que su padre sepa que ya se elimino a su hijo). 

*En el 2do pregunta si tiene 2 hijos, en ese caso actualiza la raiz llamando a la funcion "eliminar_nodo_mayor_y_devolver_raiz". Esta funcion tiene como objetivo borrar el elemento actual y reemplazarlo por su predecesor inorden. Para ello se llama a la funcion "predecesor_inorden" que devuelve el predecesor inorden. Ahora lo que sigue es destruir el elemento pedido en arbol_borrar y reemplazarlo por el predecesor inorden, y luego borrar el predecesor inorden. Para este ultimo paso me planteo si el predecesor inorden es hoja o tiene un hijo (a la izquierda), ya que al ser predecesor inorden no puede tener un hijo a la derecha, y si no tiene hijos actualizo la parte izquierda de el nodo del elemento pedido en arbol borrar, igualandolo a una funcion llamada "actualizar_predecesor_inorden" que lo que hace es borrar el predecesor inorden liberandolo y devolviendo NULL, y asi actualizar el arbol. En el caso de que el predecesor inorden tenga un hijo, en "eliminar_nodo_mayor_y_devolver_raiz" destruyo el elemento pedido en arbol_borrar, le asigno el elemento del predecesor inorden, y actualizo la parte izquierda del nodo actualizado (destruyendo el predecesor inorden).

*En el 3er caso pregunta si tiene 1 hijo, entonces crea una nueva raiz con el hijo que tenga, elimina la raiz anterior con su elemento y devuelve la nueva raiz.
Luego las funciones de recorrido del arbol son recursivas, y estan ordenadas de acuerdo al orden de prioridad de cada recorrido.

Finalmente en el iterador interno se utliza un switch para cada caso que el usuario quiera recorrer (inorden, preorden o postorden), y segun cada caso recorre sumando los elementos del arbol, junto con la funcion, hasta que la funcion devuelva true. Para la condicion de corte del iterador use de puntero un bool, que apunta a la funcion que determina la iteracion. De esta manera no uso de condicion de corte a la funcion, sino a una variable que guarda el resultado de la misma. 


Conceptos:
------------------

*El ABB es un TDA que esta intimamente relacionado con las operaciones de busqueda. A diferencia del arbol binario, que uno debe saber donde seguir buscando (si a la izquierda o derecha de un valor) y que no tiene ninguna regla en particular para poder insertar elementos, el ABB permite tener las ventajas de las listas enlazadas y la velocidad de la busqueda binaria a traves de sus reglas, las cuales son que en el sub-arbol izquierdo de la raiz o de cualquier nodo se van a encontrar las claves con menor valor menor a la clave del nodo padre. En cambio, en el sub-arbol derecho del nodo padre se van a encontrar las claves con mayor valor a la clave del mismo.

*El objetivo de tener una funcion de destruccion en el TDA es una vez utilizado el ABB, liberar toda la memoria reservada en el Heap, destruyendo los nodos y sus elementos para evitar justamente la perdida de memoria, ya que ademas de causar serios problemas en el comportamiento del programa, dependiendo de la cantidad de memoria perdida y el tiempo que el programa siga en ejecucion podria agotar la memoria disponible en el sistema.

*
-Arbol_crear = O(1) ya que todas las operaciones son O(1).
-Arbol_insertar = O(log n) ya que en cada llamada recursiva el problema se va dividiendo en 2.. Y utilizando el Teorema Maestro: a=1 b=2, termina dando como resultado O(log n).
-Arbol_buscar = O(log n) ya que en cada llamada recursiva el problema se va dividiendo en 2.. Y utilizando el Teorema Maestro: a=1 b=2, termina dando como resultado O(log n).
-Arbol_borrar = O(log n * n) ya que en cada llamada recursiva el problema se va dividiendo en 2.. Y utilizando el Teorema Maestro: a=2 b=2, termina dando como resultado O((log n)*n).
-Arbol_vacio = O(1) ya que todas las operaciones son O(1).
-Arbol_raiz = O(1) ya que todas las operaciones son O(1).
-Arbol_recorrido_inorden = O(n) ya que en el peor caso recorreria todo el arbol insertando los elementos en el array en el orden correspondiente.
-Arbol_recorrido_preorden = O(n) ya que en el peor caso recorreria todo el arbol insertando los elementos en el array en el orden correspondiente.
-Arbol_recorrido_postorden = O(n) ya que en el peor caso recorreria todo el arbol insertando los elementos en el array en el orden correspondiente.
-Arbol_destruir = O(n) ya que se recorre todo el arbol, liberando todos los elementos con sus nodos.
-abb_con_cada_elemento = O(n) ya que el peor de los casos itera el numero total de elementos del arbol.








