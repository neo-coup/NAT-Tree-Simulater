#ifndef __HEIGHT_NODE__
#define __HEIGHT_NODE__

#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getBalancedTreeHops(int);
double logn(int, double);
int getTreeHeight(Node*, int);
int maxValue(int[], int);
int getNodeHeight(Node* node);

double getBalancedTreeHops(int num) {
    int hops = 0;

    for(int i=1; i<=num; i++) {
        hops += (int)logn(CHILDREN_MAX, (double)i);
    }

    return (double)hops / num;
}

double logn(int base, double antilog) {
    if(base == 1) return antilog;
    return log(antilog) / log((double)base);
}

int getTreeHeight(Node* node, int child_num) {
    if(node == NULL) return 0;
    int c[child_num];

    for(int i=0; i<child_num; i++) {
        c[i] = getTreeHeight(node->children[i], child_num);
    }

    int max = maxValue(c, child_num);

    return max + 1;
}

int maxValue(int arr[], int len) {
    int ret = arr[0];
    for(int i=0; i<len; i++) {
        if(arr[i] > ret) ret = arr[i];
    }
    return ret;
}

int getNodeHeight(Node* node) {
    if(node == NULL) return 0;
    return 1 + getNodeHeight(node->parent);
}

#endif
