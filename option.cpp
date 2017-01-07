#include "option.h"
#include <iostream>
#include <stdlib.h>
#include <regex>

using namespace std;

Option::Option(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
};

bool Option::checkFormat() {
    bool ret = false;

    regex nodes("nodes/nodes.[0-9].[0-9]{2}.csv");
    regex result("result/result.[0-9].[0-9]{2}.csv");
    regex help("-h|--help");
    regex debug("-d|--debug");
    regex ext("-e|--extend");
    regex rest("-r|--restruct");
    // regex ch("-c");
    regex fig("\\d+");

    for(int i=1; i<argc; i++) {
        if(i==1 && regex_match(argv[i], nodes)) {
            this->nodes_file_name = argv[i];
        } else if(i<2 && regex_match(argv[i], result)) {
            this->result_file_name = argv[i];
        } else if(regex_match(argv[i], help)) {
            ret = true;
        } else if(regex_match(argv[i], debug)) {
            this->debug = true;
        } else if(regex_match(argv[i], ext)) {
            this->extend = true;
        } else if(regex_match(argv[i], rest)) {
            this->restruct = true;
        // } else if(i+1 < argc && regex_match(argv[i], ch)) {
        //     if(regex_match(argv[i+1], fig)) {
        //         this->child_num = atoi(argv[++i]);
        //     } else {
        //         ret = true;
        //     }
        } else {
            ret = true;
        }
    }
    return ret;
};

void Option::showHelp() {
    cout << endl;
    cout << "Usage:                 " << endl;
    cout << "./[file name] [node file] [result file] [options]" << endl;
    cout << "                                           " << endl;
    cout << " [node file]                               " << endl;
    cout << " eg. ### nodes/nodes.0.00.csv ###          " << endl;
    cout << " If node file is unselected, the above will be read." << endl;
    cout << "                                           " << endl;
    cout << " [result file]                             " << endl;
    cout << " eg. ### result/result.0.00.csv ###        " << endl;
    cout << " If result file is unspecified, neither file will be written.(only Standard Output)" << endl;
    cout << "                                           " << endl;
    cout << " [options]                                 " << endl;
    cout << " -h, --help                show this help  " << endl;
    cout << " -d, --debug               show progress   " << endl;
    cout << " -e, --extend              extend NAT's combinaton table" << endl;
    cout << " -r, --restruct            restruct Tree   " << endl;
    // cout << " -c                <num>   number of child limit" << endl;
    cout << endl;
};
