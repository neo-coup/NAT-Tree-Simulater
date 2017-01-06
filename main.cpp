#include "option.h"
#include "node_file_reader.h"
#include "network.h"
#include <vector>

int main(int argc, char** argv) {
    Option option(argc, argv);
    if(option.checkFormat()) {
        option.showHelp();
        return 0;
    }

    NodeFileReader nfr;
    nfr.read("nodes/nodes.0.00.csv");
    Network network(option.getDebug(), option.getExtend(), nfr.node_num);
    network.init(nfr.list);
    network.buildTree();
    network.showResult();
    return 1;
}
