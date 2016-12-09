#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"

#define NODE_MAX 100

class Network {
    Node* node_list;
public:
    Network() {};
    void init();
    void buildTree();
    void entryTree(Node*);
    void searchChainOpenNode(Node*, Node*);
    void searchRestrictedNode(Node*);
    void searchExtraPatternNode(Node*);
    void countNegativeNode();
};
#endif
