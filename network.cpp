#include "network.h"
#include "node.h"
#include "utility.h"
#include "option.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>

using namespace std;

Network::Network(Option& opt, int n) {
    this->debug = opt.getDebug();
    this->extend = opt.getExtend();
    this->restruct = opt.getRestruct();
    this->result_file_name = opt.getResultFileName();
    this->node_max = n;
    this->cnt.s = 0;
}

void Network::init(vector<Node*>& list) {

    node_list = new Node[this->node_max];
    if(node_list == NULL) return;

    // root を追加
    Node root;
    root.setId(0);
    root.setConnectionType(0);
    root.setMobile(false);
    root.setConnect(true);
    node_list[0] = root;

    // 全ノード追加
    // ここでは、 deep copy だが、node_listは元から vector にするべき
    for(int i=1; i<this->node_max; i++) {
        Node node;
        node.setId(list[i]->getId());
        node.setConnectionType(list[i]->getConnectionType());
        node.setMobile(list[i]->getMobile());
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
                        v->setLocate(i);
                        v->setConnect(true);
                        if(this->debug) printf("I'm %5d.     My Type is %d. And mobile is %d    My parent's ID is %5d.     The location is %d.\n", v->getId(), v->getConnectionType(), v->getMobile(), p->getId(), i);
                        return;
                    }
                } else if(this->restruct && p->children[i]->getMobile()){
                    if(snatchMobileLocate(v, p->children[i])) return;
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

    if(p->getMobile()) ret = false;
    else if(c->getConnectionType() <= 1 || p->getConnectionType() <= 1) ret = true;
    else if(c->getConnectionType() <= 3 && p->getConnectionType() <= 3 && this->extend) ret = true;

    return ret;
}

bool Network::snatchMobileLocate(Node* v, Node* d) {
    bool ret = false;
    // 再帰処理の為、見つかっていた場合ここで処理終了
    if(v->getConnect()) return ret;

    // 参加者が Mobile 又は、交換先が不参加なら検索終了
    if(v->getMobile() || !d->getConnect()) return ret;

    // 交換先が Mobile 且つ、交換先の親ノードと接続可能
    if(d->getMobile() &&  canConnect(v, d->parent)) {
        if(this->debug) printf("Detect Snatch   >>> v:%5d     d:%5d\n", v->getId(), d->getId());
        Node* p = d->parent;

        p->children[d->getLocate()] = v;
        v->parent = p;
        // for(int i=0; i<CHILDREN_MAX; i++) v->children[i] = d->children[i];
        v->setLocate(d->getLocate());
        v->setConnect(true);
        d->setConnect(false);
        this->cnt.s++;

        ret = true;

        // 追加先再検索
        entryTree(d);
    } else {
        for(int i=0; i<CHILDREN_MAX; i++) {
            if(d->children[i] != NULL) {
                ret = snatchMobileLocate(v, d->children[i]);
                if(ret) break;
            }
        }
    }
    return ret;
}

void Network::fileOutput(int num) {
    ofstream result_file;
    result_file.open(this->result_file_name, ios::app);

    int cnt = 0;
    int hops = 0;

    for(int i=0; i<=num; i++) {
        if(node_list[i].getConnect()) {
            cnt++;
            hops += getNodeHeight(&node_list[i]);
        }
    }

    double hop_avg = (double)hops / cnt;
    double b_hop_avg = getBalancedTreeHops(cnt);

    result_file << cnt << "," << num << "," << hop_avg << "," << b_hop_avg << endl;
}

void Network::showResult() {
    int cnt = 0;
    int hops = 0;

    for(int i=0; i<this->node_max; i++) {
        if(this->debug) {
            if(node_list[i].parent != NULL ) printf("I'm %5d.     My type is %d. And mobile is %d    My parent is %5d\n", node_list[i].getId(), node_list[i].getConnectionType(), node_list[i].getMobile(), node_list[i].parent->getId());
            else printf("I'm %5d.     My type is %d. And mobile is %d     I have no parent.\n", node_list[i].getId(), node_list[i].getConnectionType(), node_list[i].getMobile());
        }
        if(node_list[i].getConnect()) {
            cnt++;
            hops += getNodeHeight(&node_list[i]);
        }
    }

    double hop_avg = (double)hops / cnt;
    double b_hop_avg = getBalancedTreeHops(cnt);

    free(node_list);
    if(this->restruct) cout << "\nRESTRUCTION >>>  S:" << this->cnt.s << endl;
    cout << cnt << " of " << this->node_max << " nodes joined in the Tree." << endl;
    printf("\nHop T : B     %f : %f\n", hop_avg , b_hop_avg );
    if(cnt == this->node_max) cout << "perfect !!!111" << endl;
}
