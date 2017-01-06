#include "node.h"
#include <stdlib.h>
#include <random>

Node::Node()  {
    this->connect = false;
    this->parent = NULL;
    for(int i=0; i<CHILDREN_MAX; i++) this->children[i] = NULL;
};
