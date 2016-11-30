#include "network.h"
#include "node.h"
#include <iostream>
#include <stdlib.h>
#include <queue>

using namespace std;

void Network::init() {

    node_list = new Node[NODE_MAX];
    if(node_list == NULL) return;

    // root を追加
    Node root;
    root.setId(0);
    root.setConnectionType(0);
    root.setConnect(true);
    node_list[0] = root;

    // 全ノード追加
    for(int i=1; i<NODE_MAX; i++) {
        Node node;
        node.setId(i);
        node_list[i] = node;
    }

    cout << "Initializing has done!" << endl;
};

void Network::buildTree() {
    for(int i=1; i<NODE_MAX; i++) {
        Network::entryTree(&(node_list[i]));
    }

    cout << "Tree Building has done!" << endl;
}

void Network::entryTree(Node* v) {
    queue<Node*> queue;

    // root ノードを queue に追加
    Node *root = &(node_list[0]);
    queue.push(root);

    // 幅優先探索で参加先を決定
    while( !queue.empty() ) {
        Node *p = queue.front();
        queue.pop();
        for(int i=0; i<CHILDREN_MAX; i++) {
            // 子ノードの接続先がある場合
            if(p->children[i] == NULL) {
                // 接続可能な相性な場合
                if(p->canConnect(v->getConnectionType())) {
                    p->children[i] = v;
                    v->parent = p;
                    v->setConnect(true);
                    cout << "parent's ID is " << p->getId() << " The location is " << i << " I'm " << v->getId() << endl;
                    return;
                }
            } else {
                queue.push(p->children[i]);
            }
        }
    }
}

void Network::countNegativeNode() {
    int cnt = 0;
    for(int i=0; i<NODE_MAX; i++) {
        if(node_list[i].parent != NULL)
            cout << node_list[i].getId() << "'s parent is " << node_list[i].parent->getId() << " My type is " << node_list[i].getConnectionType() << endl;
        if(node_list[i].getConnect()) cnt++;
    }

    free(node_list);
    cout << cnt << " nodes joined in the Tree." << endl;
}
