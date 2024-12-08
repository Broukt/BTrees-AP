#pragma once
#include <iostream>

/// <summary>
/// Entidad que representa un nodo de un �rbol B
/// </summary>
class BTreeNode {
public:
    /// <summary>
	/// Arreglo de claves
    /// </summary>
    int* keys;
    /// <summary>
	/// Grado m�nimo del �rbol
    /// </summary>
    int t;
	/// <summary>
	/// Arreglo de punteros a los hijos
	/// </summary>
    BTreeNode** C;
	/// <summary>
	/// N�mero de claves actuales
	/// </summary>
    int n;
    /// <summary>
	/// Indica si el nodo es una hoja
    /// </summary>
    bool leaf;

    /// <summary>
	/// Constructor de la clase
    /// </summary>
    /// <param name="t">Grado m�nimo del �rbol</param>
    /// <param name="leaf">Indica si el nodo es una hoja</param>
    BTreeNode(int t, bool leaf);
    /// <summary>
	/// Recorre el sub�rbol en orden
    /// </summary>
    void traverse();
	/// <summary>
	/// Busca una clave en el sub�rbol
	/// </summary>
	/// <param name="k">Clave a buscar</param>
	/// <returns>Nodo que contiene la clave</returns>
    BTreeNode* search(int k);
    /// <summary>
	/// Funci�n para insertar una nueva clave en el sub�rbol enraizado con este nodo.
    /// </summary>
    /// <param name="k">Clave a insertar</param>
    void insertNonFull(int k);
	/// <summary>
	/// Funci�n para dividir el hijo y del nodo en dos hijos
	/// </summary>
	/// <param name="i">�ndice del hijo a dividir</param>
	/// <param name="y">Puntero al hijo a dividir</param>
    void splitChild(int i, BTreeNode* y);
	/// <summary>
	/// Funci�n para eliminar la clave k en el sub�rbol enraizado con este nodo
	/// </summary>
	/// <param name="k">Clave a eliminar</param>
    void remove(int k);
    /// <summary>
	/// Funci�n auxiliar para eliminar la clave k en el sub�rbol enraizado con este nodo
    /// </summary>
	/// <param name="idx">�ndice de la clave a eliminar en este nodo</param>
    void removeFromLeaf(int idx);
    /// <summary>
	/// Funci�n auxiliar para eliminar la clave k en el sub�rbol enraizado con este nodo
    /// </summary>
	/// <param name="idx">�ndice de la clave a eliminar en este nodo</param>
    void removeFromNonLeaf(int idx);
	/// <summary>
	/// Funci�n para obtener el predecesor de la clave en el �ndice idx en el sub�rbol enraizado con este nodo
	/// </summary>
	/// <param name="idx">�ndice de la clave</param>
	/// <returns>Predecesor de la clave</returns>
    int getPredecessor(int idx);
    /// <summary>
	/// Funci�n para obtener el sucesor de la clave en el �ndice idx en el sub�rbol enraizado con este nodo
    /// </summary>
    /// <param name="idx">�ndice de la clave</param>
    /// <returns>Sucesor de la clave</returns>
    int getSuccessor(int idx);
	/// <summary>
	/// Funci�n para rellenar el hijo en el �ndice idx en el sub�rbol enraizado con este nodo
	/// </summary>
	/// <param name="idx">�ndice del hijo a rellenar</param>
    void fill(int idx);
	/// <summary>
	/// Funci�n para prestar una clave del hijo en el �ndice idx-1 e insertarla en el hijo en el �ndice idx
	/// </summary>
	/// <param name="idx">�ndice del hijo</param>
    void borrowFromPrev(int idx);
    /// <summary>
	/// Funci�n para prestar una clave del hijo en el �ndice idx+1 e insertarla en el hijo en el �ndice idx
    /// </summary>
    /// <param name="idx">�ndice del hijo</param>
    void borrowFromNext(int idx);
	/// <summary>
	/// Funci�n para fusionar el hijo en el �ndice idx con el hijo en el �ndice idx+1 del sub�rbol enraizado con este nodo
	/// </summary>
	/// <param name="idx">�ndice del hijo</param>
	void merge(int idx);
    friend class BTree;
};