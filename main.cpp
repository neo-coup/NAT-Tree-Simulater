#include "option.h"
#include "network.h"

int main(int argc, char** argv) {
    Option option(argc, argv);
    if(option.checkFormat()) {
        option.showHelp();
        return 0;
    }

    Network network(option.getExtend(), option.getRestruct(), option.getNodeNum());
    network.init();
    network.buildTree();
    network.countNegativeNode();
    return 1;
}
