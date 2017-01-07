#include "node_file_reader.h"
#include "node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool NodeFileReader::read(string file_path) {

    ifstream ifs(file_path);
    if(!ifs) {
        cout << "入力エラー";
        return false;
    }

    // csvファイルを1行ずつ読み込む
    string str;
    while(getline(ifs,str)){
        string i, t, m;
        istringstream stream(str);

        getline(stream, i, ',');
        getline(stream, t, ',');
        getline(stream, m, ',');
        Node* n = new Node();
        n->setId(stoi(i));
        n->setConnectionType(stoi(t));
        n->setMobile(s_to_bool(m));

        this->list.push_back(n);
        this->node_num++;
    }
    return true;
}

bool NodeFileReader::s_to_bool(string const& s) {
     return s == "1";
}
