#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"

class Network {
public:
    bool debug;
    bool extend;
    Node* node_list;
    int node_max;

    struct count_restruct {
        int r;
        int o;
        int e;
    };

    struct count_restruct cnt;

    Network(bool, bool, int);
    void init();
    void buildTree();
    void entryTree(Node*);
    bool canConnect(Node*, Node*);
    void showResult();
};

#endif
