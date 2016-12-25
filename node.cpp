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
    // 小数点第一位まで残し、パーセント単位計算
    double n = (rnd() % 1000) / 10;

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
