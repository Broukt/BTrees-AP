#pragma once
#include "BTreeNode.h"

/// <summary>
/// Entidad que representa un árbol B
/// </summary>
class BTree
{
public:
    /// <summary>
	/// Raíz del árbol
    /// </summary>
    BTreeNode* root;
    /// <summary>
	/// Grado mínimo del árbol
    /// </summary>
    int t;

    /// <summary>
	/// Constructor de la clase BTree
    /// </summary>
    /// <param name="t">Grado mínimo del árbol</param>
    BTree(int t);
    /// <summary>
	/// Función para recorrer el árbol
    /// </summary>
    void traverse();
	/// <summary>
	/// Función para buscar una clave en el árbol
	/// </summary>
	/// <param name="k">Clave a buscar</param>
	/// <returns>Retorna el nodo que contiene la clave</returns>
    BTreeNode* search(int k);
	/// <summary>
	/// Función para insertar una clave en el árbol
	/// </summary>
	/// <param name="k">Clave a insertar</param>
    void insert(int k);
	/// <summary>
	/// Función para eliminar una clave del árbol
	/// </summary>
	/// <param name="k">Clave a eliminar</param>
    void remove(int k);
};

