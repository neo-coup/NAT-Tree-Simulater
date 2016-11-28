#include "network.h"
#include "node.h"
#include <iostream>
#include <stdlib.h>

void Network::init() {

    node_list = (Node *)calloc(NODE_MAX, sizeof(Node));
    Node root(0);
    root.setConnectionType(0);
    *node_list = root;

    for(int i=1; i<NODE_MAX; i++) {
        Node node(i);
        node_list[i] = node;
    }

    std::cout << "Initializing has done!\n";
};

void Network::simulate() {
    free(node_list);
    std::cout << "Simulation has done!\n";
}
