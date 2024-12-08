#include "BTreeNode.h"

BTreeNode::BTreeNode(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;

	// Asigna memoria para la cantidad máxima de claves y punteros a hijos
    this->keys = new int[2 * this->t - 1];
    this->C = new BTreeNode * [2 * this->t];

    this->n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < this->n; i++) {
		// Si no es hoja, entonces antes de imprimir keys[i],
		// recorre el subárbol enraizado con el hijo C[i]
        if (!this->leaf)
            this->C[i]->traverse();
        std::cout << " " << this->keys[i];
    }

	// Recorre el subárbol enraizado con el último hijo
    if (!this->leaf)
        this->C[i]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
	// Encuentra la primera clave mayor o igual a k
    int i = 0;
    while (i < this->n && k > this->keys[i])
        i++;

	// Si la clave encontrada es igual a k, devuelve este nodo
    if (this->keys[i] == k)
        return this;

	// Si la clave no está presente y este es un nodo hoja
	// entonces la clave no está en el árbol
    if (this->leaf)
        return nullptr;

	// Ir al hijo apropiado
    return this->C[i]->search(k);
}

void BTreeNode::insertNonFull(int k) {
    int i = this->n - 1;

	// Si el nodo actual es una hoja
    if (this->leaf) {
		// Encuentra la ubicación de la nueva clave a insertar
		// y mueve todas las claves mayores a una posición adelante
        while (i >= 0 && this->keys[i] > k) {
            this->keys[i + 1] = this->keys[i];
            i--;
        }

		// Inserta la nueva clave en la ubicación encontrada
        this->keys[i + 1] = k;
        this->n++;
    }
    else {
		// Encuentra el hijo que tendrá la nueva clave
        while (i >= 0 && this->keys[i] > k)
            i--;

		// Verifica si el hijo encontrado está lleno
        if (this->C[i + 1]->n == 2 * t - 1) {
			// Si el hijo está lleno, entonces se divide
            splitChild(i + 1, this->C[i + 1]);

			// Después de la división, la clave del medio de C[i] sube
			// y C[i] se divide en dos . Luego, verifica cuál de los dos
			// va a tener la nueva clave
            if (this->keys[i + 1] < k)
                i++;
        }
        this->C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
	// Crea un nuevo nodo que almacenará (t-1) claves de y
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = this->t - 1;

	// Copia las últimas (t-1) claves de y a z
    for (int j = 0; j < this->t - 1; j++)
        z->keys[j] = y->keys[j + this->t];

	// Copia los últimos t hijos de y a z
    if (y->leaf == false) {
        for (int j = 0; j < this->t; j++)
            z->C[j] = y->C[j + this->t];
    }

	// Reduce el número de claves en y
    y->n = this->t - 1;

	// Dado que este nodo tendrá un nuevo hijo, crea espacio para el nuevo hijo
    for (int j = this->n; j >= i + 1; j--)
        this->C[j + 1] = this->C[j];

	// Enlaza el nuevo hijo al nodo actual
    this->C[i + 1] = z;

	// Una clave de y se mueve al nodo actual. Encuentra la ubicación de la nueva clave
	// y mueve todas las claves mayores una posición adelante
    for (int j = this->n - 1; j >= i; j--)
        this->keys[j + 1] = this->keys[j];

	// Copia la clave del medio de y al nodo actual
    this->keys[i] = y->keys[this->t - 1];

	// Incrementa el número de claves en el nodo actual
    this->n++;
}

void BTreeNode::remove(int k) {
	// Busca la clave en el nodo actual
    int idx = 0;
    while (idx < this->n && this->keys[idx] < k)
        ++idx;

	// La clave a eliminar está presente en el nodo actual
    if (idx < this->n && this->keys[idx] == k) {
        if (this->leaf)
            this->removeFromLeaf(idx);
        else
            this->removeFromNonLeaf(idx);
    }
    else {
		// Si el nodo actual es una hoja, entonces la clave no está presente en el árbol
        if (this->leaf) {
            std::cout << "The key " << k << " is not present in the tree\n";
            return;
        }

		// La clave a eliminar puede estar presente en el subárbol enraizado con el último hijo de este nodo
		// Esta bandera indica si la clave está presente en el subárbol enraizado
		// con el último hijo de este nodo
        bool flag = ((idx == this->n) ? true : false);

		// Si el hijo donde debería estar la clave tiene menos de t claves, llenamos ese hijo
        if (C[idx]->n < this->t)
            this->fill(idx);

		// Si el último hijo ha sido fusionado, debe haberse fusionado con el hijo anterior
		// y por lo tanto, recursivamente eliminamos la clave k del (idx-1)th hijo. De lo contrario,
		// recursivamente eliminamos la clave k del (idx)th hijo que ahora tiene al menos t claves
        if (flag && idx > this->n)
            this->C[idx - 1]->remove(k);
        else
            this->C[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
	// Mueve todas las claves después de idx una posición atrás
    for (int i = idx + 1; i < this->n; ++i)
        this->keys[i - 1] = this->keys[i];

	// Reduce el número de claves
    this->n--;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = this->keys[idx];

	// Si el hijo que precede a k (C[idx]) tiene al menos t claves,
	// encuentra el predecesor 'pred' de k en el subárbol enraizado en C[idx]
	// Reemplaza k por pred y recursivamente elimina pred en C[idx]
    if (this->C[idx]->n >= this->t) {
        int pred = this->getPredecessor(idx);
        this->keys[idx] = pred;
        this->C[idx]->remove(pred);
    }

	// Si el hijo C[idx] tiene menos de t claves, examina C[idx+1]
	// Si C[idx+1] tiene al menos t claves, encuentra el sucesor 'succ' de k en C[idx+1]
	// Reemplaza k por succ y recursivamente elimina succ en C[idx+1]
	else if (this->C[idx + 1]->n >= t) {
		int succ = this->getSuccessor(idx);
		this->keys[idx] = succ;
		this->C[idx + 1]->remove(succ);
	}

	// Si ambos C[idx] y C[idx+1] tienen menos de t claves, fusiona k y todos los de C[idx+1] en C[idx]
	// Ahora C[idx] contiene 2t - 1 claves. Libera C[idx+1] y elimina recursivamente k de C[idx]
	else {
		this->merge(idx);
		C[idx]->remove(k);
	}
}

int BTreeNode::getPredecessor(int idx) {
	// Nos movemos al nodo más a la derecha hasta que lleguemos a una hoja
    BTreeNode* cur = this->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

	// Devuelve la última clave de la hoja
    return cur->keys[cur->n - 1];
}

int BTreeNode::getSuccessor(int idx) {
	// Nos movemos al nodo más a la izquierda desde el nodo C[idx+1] hasta que lleguemos a una hoja
    BTreeNode* cur = this->C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

	// Devuelve la primera clave de la hoja
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
	// Si el hijo anterior (C[idx-1]) tiene más de t-1 claves, presta una clave
    if (idx != 0 && C[idx - 1]->n >= t)
        this->borrowFromPrev(idx);

	// Si el siguiente hijo (C[idx+1]) tiene más de t-1 claves, presta una clave
    else if (idx != n && C[idx + 1]->n >= t)
        this->borrowFromNext(idx);

	// Combina C[idx] con su hermano
    else {
        if (idx != this->n)
            this->merge(idx);
        else
            this->merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = this->C[idx];
    BTreeNode* sibling = this->C[idx - 1];

	// Moviendo todas las claves en C[idx] una posición adelante
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

	// Si C[idx] no es una hoja, mueve todos sus punteros de hijo una posición adelante
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

	// Estableciendo la primera clave de C[idx] igual a keys[idx-1] del nodo actual
    child->keys[0] = this->keys[idx - 1];

	// Si el hijo no es hoja, establece como primer hijo de C[idx] al último hijo de C[idx-1]
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

	// Moviendo la clave del hermano al nodo actual
    this->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = this->C[idx];
    BTreeNode* sibling = this->C[idx + 1];

	// La clave en la posición idx es insertada como la última clave en C[idx]
    child->keys[child->n] = this->keys[idx];

	// El primer hijo del hermano es insertado como el último hijo en C[idx]
    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];

	// La primera clave del hermano es insertada en keys[idx]
    this->keys[idx] = sibling->keys[0];

	// Moviendo todas las claves del hermano una posición atrás
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

	// Moviendo los punteros del hermano una posición atrás
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = this->C[idx];
    BTreeNode* sibling = this->C[idx + 1];

	// Insertando la clave del nodo actual de la posición idx en la posición (t-1) de C[idx]
    child->keys[t - 1] = this->keys[idx];

	// Copiando las claves del nodo hermano a C[idx] al final
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

	// Copiando los punteros del hermano a C[idx]
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

	// Moviendo todas las claves después de idx en el nodo actual una posición atrás
    for (int i = idx + 1; i < n; ++i)
        this->keys[i - 1] = this->keys[i];

	// Moviendo los punteros después (idx+1) en el nodo actual una posición atrás
    for (int i = idx + 2; i <= n; ++i)
        this->C[i - 1] = this->C[i];

	// Actualizando el número de claves en el nodo actual y el hijo fusionado
    child->n += sibling->n + 1;
    this->n--;

	// Liberando la memoria ocupada por el hermano
    delete sibling;
}