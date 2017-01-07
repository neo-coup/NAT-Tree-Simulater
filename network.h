#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"
#include "node_file_reader.h"
#include "option.h"
#include <vector>
#include <string>

class Network {
public:
    bool debug;
    bool extend;
    bool restruct;
    Node* node_list;
    int node_max;
    std::string result_file_name;

    struct count {
        int s;  // snatchMobileLocate
    };

    struct count cnt;

    Network(Option&, int);
    void init(std::vector<Node*>&);
    void buildTree();
    void entryTree(Node*);
    bool canConnect(Node*, Node*);
    void snatchMobileLocate(Node*, Node*);
    void fileOutput(int);
    void showResult();
};

#endif
