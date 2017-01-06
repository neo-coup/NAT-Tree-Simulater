#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"
#include <vector>

class Network {
public:
    bool debug;
    bool extend;
    Node* node_list;
    int node_max;

    Network(bool, bool, int);
    void init(std::vector<Node*>&);
    void buildTree();
    void entryTree(Node*);
    bool canConnect(Node*, Node*);
    void showResult();
};

#endif
