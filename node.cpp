#include "node.h"
#include <stdlib.h>
#include <random>

Node::Node()  {
    this->connect = false;
    this->parent = NULL;
    for(int i=0; i<CHILDREN_MAX; i++) this->children[i] = NULL;
    this->connection_type = selectConnectionType();
 };

int Node::selectConnectionType() {

    std::random_device rnd;
    int n = rnd() % 1000;

    if(n < TYPE_0) return  0;
    n -= TYPE_0;
    if(n < TYPE_1) return  1;
    n -= TYPE_1;
    if(n < TYPE_2) return  2;
    n -= TYPE_2;
    if(n < TYPE_3) return  3;
    n -= TYPE_3;
    if(n < TYPE_4) return  4;
    n -= TYPE_4;
    if(n < TYPE_5) return  5;
    // n -= TYPE_5;
    return 0;
};

bool Node::canConnect(int opp) {
    bool ret = false;
    int a = this->getConnectionType();
    int b = opp;
    if(a <= 1 || b <= 1) ret = true;
    if(a <= 3 && b <= 3) ret = true;
    return ret;
}
