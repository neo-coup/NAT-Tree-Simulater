#include "network.h"
#include "node.h"
#include "option.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>

using namespace std;

Network::Network(Option& opt, int n) {
    this->debug = opt.getDebug();
    this->extend = opt.getExtend();
    this->result_file_name = opt.getResultFileName();
    this->node_max = n;
}

void Network::init(vector<Node*>& list) {

    node_list = new Node[this->node_max];
    if(node_list == NULL) return;

    // root を追加
    Node root;
    root.setId(0);
    root.setConnectionType(0);
    root.setConnect(true);
    node_list[0] = root;

    // 全ノード追加
    // ここでは、 deep copy だが、node_listは元から vector にするべき
    for(int i=1; i<this->node_max; i++) {
        Node node;
        node.setId(list[i]->getId());
        node.setConnectionType(list[i]->getConnectionType());
        node_list[i] = node;
    }
    cout << "\nInitializing has done!\n" << endl;
};

void Network::buildTree() {
    for(int i=1; i<this->node_max; i++) {
        Network::entryTree(&(node_list[i]));
        if((this->result_file_name != "") && (i%1000 == 999)) fileOutput(i);
    }

    cout << "\nTree Building has done!\n" << endl;
}

void Network::entryTree(Node* v) {
    queue<Node*> queue;

    // root ノードを queue に追加
    Node* root = &(node_list[0]);
    queue.push(root);

    // 幅優先探索で参加先を決定
    while( !queue.empty() ) {
        Node* p = queue.front();
        queue.pop();
        for(int i=0; i<CHILDREN_MAX; i++) {
            // 子ノードの接続先がある場合
            if(p->children[i] == NULL) {
                // 接続可能な相性な場合
                if(canConnect(v, p)) {
                    p->children[i] = v;
                    v->parent = p;
                    v->setConnect(true);
                    if(this->debug) printf("I'm %5d.     My Type is %d.     My parent's ID is %5d.     The location is %d.\n", v->getId(), v->getConnectionType(), p->getId(), i);
                    return;
                }
            } else {
                queue.push(p->children[i]);
            }
        }
    }
    if(this->debug) if(!v->getConnect()) printf("%d failed to join.\n", v->getId());
}

/**
*canConnect
*c: child  子となるノード
*p: parent 親となるノード
*/

bool Network::canConnect(Node* c, Node* p) {
    bool ret = false;
    if(c->getConnectionType() <= 1 || p->getConnectionType() <= 1) ret = true;
    if(c->getConnectionType() <= 3 && p->getConnectionType() <= 3 && this->extend) ret = true;

    return ret;
}

void Network::fileOutput(int num) {
    ofstream result_file;
    result_file.open(this->result_file_name, ios::app);

    int cnt = 0;
    for(int i=0; i<=num; i++) {
        if(node_list[i].getConnect()) cnt++;
    }
    result_file << cnt << "," << num << endl;
}

void Network::showResult() {
    int cnt = 0;

    for(int i=0; i<this->node_max; i++) {
        if(this->debug) {
            if(node_list[i].parent != NULL ) printf("I'm %5d.     My type is %d.     My parent is %5d\n", node_list[i].getId(), node_list[i].getConnectionType(), node_list[i].parent->getId());
            else  printf("I'm %5d.     My type is %d.     I have no parent.\n", node_list[i].getId(), node_list[i].getConnectionType());
        }
        if(node_list[i].getConnect()) cnt++;
    }

    free(node_list);
    cout << cnt << " of " << this->node_max << " nodes joined in the Tree." << endl;
    if(cnt == this->node_max) cout << "perfect !!!111" << endl;
}
