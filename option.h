#ifndef __OPTION_H__
#define __OPTION_H__

#include <iostream>
#include <string>

class Option {
    private:
    int argc;
    char** argv;
    bool debug = false;
    bool extend = false;    // 拡張フラグ
    bool restruct = false;  // 再構築フラグ
    int node_num = 100;     // ノード数
    // int child_num = 2;      // ノードの持てる子ノードの数
    std::string nodes_file_name = "nodes/nodes.0.00.csv";

    public:
    Option(int, char**);
    bool checkFormat();
    void showHelp();
    bool getDebug() { return this->debug; };
    bool getExtend() { return this->extend; };
    bool getRestruct() { return this->restruct; };
    int getNodeNum() { return this->node_num; };
    // int getChildNum() { return this->child_num };
    std::string getNodesFileName() { return this->nodes_file_name; };
};

#endif
