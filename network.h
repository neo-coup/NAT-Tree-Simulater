#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"

class Network {
public:
    bool extend;
    bool chain;
    bool restruct;
    Node* node_list;
    int node_max;

    Network(bool, bool, int);
    void init();
    void buildTree();
    void entryTree(Node*);
    void searchRestrictedNode(Node*, Node*);
    void searchChainOpenNode(Node*, Node*);
    void searchExtraPatternNode(Node*, Node*);
    void countNegativeNode();
};

#endif
