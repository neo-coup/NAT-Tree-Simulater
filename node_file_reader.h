#ifndef __NODE_FILE_READER__
#define __NODE_FILE_READER__

#include "node.h"
#include <vector>
#include <string>

class NodeFileReader {
public:
    bool read(std::string);
    bool s_to_bool(const std::string&);
    std::vector<Node*> list;
    int node_num = 0;
};

#endif
