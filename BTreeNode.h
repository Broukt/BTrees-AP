#pragma once
#include <iostream>

/// <summary>
/// Entidad que representa un nodo de un árbol B
/// </summary>
class BTreeNode {
public:
    /// <summary>
	/// Arreglo de claves
    /// </summary>
    int* keys;
    /// <summary>
	/// Grado mínimo del árbol
    /// </summary>
    int t;
	/// <summary>
	/// Arreglo de punteros a los hijos
	/// </summary>
    BTreeNode** C;
	/// <summary>
	/// Número de claves actuales
	/// </summary>
    int n;
    /// <summary>
	/// Indica si el nodo es una hoja
    /// </summary>
    bool leaf;

    /// <summary>
	/// Constructor de la clase
    /// </summary>
    /// <param name="t">Grado mínimo del árbol</param>
    /// <param name="leaf">Indica si el nodo es una hoja</param>
    BTreeNode(int t, bool leaf);
    /// <summary>
	/// Recorre el subárbol en orden
    /// </summary>
    void traverse();
	/// <summary>
	/// Busca una clave en el subárbol
	/// </summary>
	/// <param name="k">Clave a buscar</param>
	/// <returns>Nodo que contiene la clave</returns>
    BTreeNode* search(int k);
    /// <summary>
	/// Función para insertar una nueva clave en el subárbol enraizado con este nodo.
    /// </summary>
    /// <param name="k">Clave a insertar</param>
    void insertNonFull(int k);
	/// <summary>
	/// Función para dividir el hijo y del nodo en dos hijos
	/// </summary>
	/// <param name="i">Índice del hijo a dividir</param>
	/// <param name="y">Puntero al hijo a dividir</param>
    void splitChild(int i, BTreeNode* y);
	/// <summary>
	/// Función para eliminar la clave k en el subárbol enraizado con este nodo
	/// </summary>
	/// <param name="k">Clave a eliminar</param>
    void remove(int k);
    /// <summary>
	/// Función auxiliar para eliminar la clave k en el subárbol enraizado con este nodo
    /// </summary>
	/// <param name="idx">Índice de la clave a eliminar en este nodo</param>
    void removeFromLeaf(int idx);
    /// <summary>
	/// Función auxiliar para eliminar la clave k en el subárbol enraizado con este nodo
    /// </summary>
	/// <param name="idx">Índice de la clave a eliminar en este nodo</param>
    void removeFromNonLeaf(int idx);
	/// <summary>
	/// Función para obtener el predecesor de la clave en el índice idx en el subárbol enraizado con este nodo
	/// </summary>
	/// <param name="idx">Índice de la clave</param>
	/// <returns>Predecesor de la clave</returns>
    int getPredecessor(int idx);
    /// <summary>
	/// Función para obtener el sucesor de la clave en el índice idx en el subárbol enraizado con este nodo
    /// </summary>
    /// <param name="idx">Índice de la clave</param>
    /// <returns>Sucesor de la clave</returns>
    int getSuccessor(int idx);
	/// <summary>
	/// Función para rellenar el hijo en el índice idx en el subárbol enraizado con este nodo
	/// </summary>
	/// <param name="idx">Índice del hijo a rellenar</param>
    void fill(int idx);
	/// <summary>
	/// Función para prestar una clave del hijo en el índice idx-1 e insertarla en el hijo en el índice idx
	/// </summary>
	/// <param name="idx">Índice del hijo</param>
    void borrowFromPrev(int idx);
    /// <summary>
	/// Función para prestar una clave del hijo en el índice idx+1 e insertarla en el hijo en el índice idx
    /// </summary>
    /// <param name="idx">Índice del hijo</param>
    void borrowFromNext(int idx);
	/// <summary>
	/// Función para fusionar el hijo en el índice idx con el hijo en el índice idx+1 del subárbol enraizado con este nodo
	/// </summary>
	/// <param name="idx">Índice del hijo</param>
	void merge(int idx);
    friend class BTree;
};