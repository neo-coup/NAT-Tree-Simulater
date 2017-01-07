#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "node.h"
#include "node_file_reader.h"
#include <vector>
#include <string>

class Network {
public:
    bool debug;
    bool extend;
    bool restruct;
    bool output;
    Node* node_list;
    int node_max;
    std::string file_name = "result/result.txt";

    struct count {
        int s;  // snatchMobileLocate
    };

    struct count cnt;

    Network(bool, bool, bool, bool, int);
    void init(std::vector<Node*>&);
    void buildTree();
    void entryTree(Node*);
    bool canConnect(Node*, Node*);
    bool snatchMobileLocate(Node*, Node*);
    void fileOutput(int);
    void showResult();
};

#endif
