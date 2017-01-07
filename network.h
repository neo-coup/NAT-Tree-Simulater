#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"
#include "option.h"
#include <vector>
#include <string>

class Network {
public:
    bool debug;
    bool extend;
    Node* node_list;
    int node_max;
    std::string result_file_name;

    Network(Option&, int);
    void init(std::vector<Node*>&);
    void buildTree();
    void entryTree(Node*);
    bool canConnect(Node*, Node*);
    void fileOutput(int);
    void showResult();
};

#endif
