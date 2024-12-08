#pragma once
#include "BTreeNode.h"

/// <summary>
/// Entidad que representa un �rbol B
/// </summary>
class BTree
{
public:
    /// <summary>
	/// Ra�z del �rbol
    /// </summary>
    BTreeNode* root;
    /// <summary>
	/// Grado m�nimo del �rbol
    /// </summary>
    int t;

    /// <summary>
	/// Constructor de la clase BTree
    /// </summary>
    /// <param name="t">Grado m�nimo del �rbol</param>
    BTree(int t);
    /// <summary>
	/// Funci�n para recorrer el �rbol
    /// </summary>
    void traverse();
	/// <summary>
	/// Funci�n para buscar una clave en el �rbol
	/// </summary>
	/// <param name="k">Clave a buscar</param>
	/// <returns>Retorna el nodo que contiene la clave</returns>
    BTreeNode* search(int k);
	/// <summary>
	/// Funci�n para insertar una clave en el �rbol
	/// </summary>
	/// <param name="k">Clave a insertar</param>
    void insert(int k);
	/// <summary>
	/// Funci�n para eliminar una clave del �rbol
	/// </summary>
	/// <param name="k">Clave a eliminar</param>
    void remove(int k);
};

