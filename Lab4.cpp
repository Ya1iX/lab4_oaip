/*
Найти среднее значение всех ключей дерева и узел, имеющий ближайший к этому значению ключ.
*/

#include <iostream>
#include "CTree.h"

int main()
{
	CTree* tree = new CTree("in.txt", "tree");
	tree->view_all();
	printf("Nearest key to %f is %i", tree->average(), tree->findNearest());
}