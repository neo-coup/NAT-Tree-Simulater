#include "network.h"

int main() {
    Network network;
    network.init();
    network.buildTree();
    network.countNegativeNode();
    return 1;
}
