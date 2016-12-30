#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"

class Network {
public:
    bool debug;
    bool extend;
    bool restruct;
    Node* node_list;
    int node_max;

    struct count {
        int s;  // snatchMobileLocate
    };

    struct count cnt;

    Network(bool, bool, bool, int);
    void init();
    void buildTree();
    void entryTree(Node*);
    bool canConnect(Node*, Node*);
    bool snatchMobileLocate(Node*, Node*);
    void showResult();
};

#endif
