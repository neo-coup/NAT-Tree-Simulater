#include "network.h"
#include "node.h"
#include <iostream>
#include <stdlib.h>
#include <queue>

using namespace std;

Network::Network(bool e, bool r, int n) {
    this->extend = e;
    this->restruct = r;
    this->node_max = n;
}

void Network::init() {

    node_list = new Node[this->node_max];
    if(node_list == NULL) return;

    // root を追加
    Node root;
    root.setId(0);
    root.setConnectionType(0);
    root.setConnect(true);
    node_list[0] = root;

    // 全ノード追加
    for(int i=1; i<this->node_max; i++) {
        Node node;
        node.setId(i);
        node_list[i] = node;
    }

    cout << "Initializing has done!" << endl;
};

void Network::buildTree() {
    for(int i=1; i<this->node_max; i++) {
        Network::entryTree(&(node_list[i]));
    }

    cout << "Tree Building has done!" << endl;
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
                if(p->canConnect(v->getConnectionType(), this->extend)) {
                    p->children[i] = v;
                    v->parent = p;
                    v->setConnect(true);
                    // cout << "I'm " << v->getId() << " My Type is " << v->getConnectionType() << " parent's ID is " << p->getId() << " The location is " << i << endl;
                    return;
                }
            } else {
                queue.push(p->children[i]);
            }
        }
    }

    // 接続先が無かった場合、木の再構築を行い参加を試みる
    if(this->restruct) searchRestrictedNode(v, &(node_list[0]));
    if(this->restruct) searchChainOpenNode(v, &(node_list[0]));
    if(this->restruct) searchExtraPatternNode(v, &(node_list[0]));

    // if(!v->getConnect()) cout << v->getId() << " failed to join." << endl;
}

void Network::searchRestrictedNode(Node* v, Node* p) {
    // 再帰処理の為、見つかっていた場合ここで処理終了
    if(v->getConnect()) return;

    // option で拡張されていなければ終了
    if(!this->extend) return;

    // Restricted cone・Port Restricted cone 以外は検索終了
    if(!(v->getConnectionType() == 2 || v->getConnectionType() == 3)) return;

    // 親が Restricted cone 又は、Port Restricted cone だった場合、その子供との間に該当ノードを入れる
    if(!(p->getConnectionType() == 2 || p->getConnectionType() == 3)) {
        // cout << "\nDetect RestRest >>> v:" << v->getId() << " p:" << p->getId() << " c:" << p->children[0]->getId() << "\n" << endl;
        v->children[0] = p->children[0];
        p->children[0]->parent = v;
        p->children[0] = v;
        v->parent = p;
        v->setConnect(true);
    }
    for(int i=0; i<CHILDREN_MAX; i++) {
        searchRestrictedNode(v, p->children[i]);
    }
}

void Network::searchChainOpenNode(Node* v, Node* p) {
    // 再帰処理の為、見つかっていた場合ここで処理終了
    if(v->getConnect()) return;

    for(int i=0; i<CHILDREN_MAX; i++) {
        if(p->children[i] == NULL) break;

        // 親子共に Open Internet 又は Full cone だった場合、その間に該当ノードを入れる
        if(p->getConnectionType() <= 1 && p->children[i]->getConnectionType() <= 1) {
            // cout << "\nDetect Chain >>> v:" << v->getId() << " - " << v->getConnectionType() << " p:" << p->getId() << " - " << p->getConnectionType() << " c:" << p->children[i]->getId() << " - " <<p->children[i]->getConnectionType() << "\n" << endl;
            v->children[0] = p->children[i];
            p->children[i]->parent = v;
            p->children[i] = v;
            v->parent = p;
            v->setConnect(true);
            break;
        }
        searchChainOpenNode(v, p->children[i]);
    }
}

/**
* ExtraPattern
* 参加者           Symmetric・UDP Blocked
* 親ノード          Open Internet・Full cone
* 交換先ノード       Restricted cone・Port Restricted cone
* 子ノード           Open Internet・Full cone
* 上記条件が全て揃っていた場合、参加者と交換先を入れ替え、交換先ノードの追加先を再検索
*/
void Network::searchExtraPatternNode(Node* v, Node* d) {
    // 再帰処理の為、見つかっていた場合ここで処理終了
    if(v->getConnect()) return;

    // 参加者が Symmetric・UDP Blocked 以外は検索終了
    if(!(v->getConnectionType() == 4 || v->getConnectionType() == 5)) return;

    Node* p = d->parent;

    // 交換先が Restricted・Port Restricted 以外
    if(!(d->getConnectionType() == 2 || d->getConnectionType() == 3)) {}

    // 親が Open Internet・Full cone 以外
    else if(!(p->getConnectionType() == 0 || p->getConnectionType() == 1)) {}

    else {
        for(int i=0; i<CHILDREN_MAX; i++) {
            Node* c = d->children[i];
            if(!(c->getConnectionType() == 0 || c->getConnectionType() == 1)) {
                cout << "\nDetect Extra >>> v:" << v->getId() << " - " << v->getConnectionType() << " d:" << d->getId() << " - " << d->getConnectionType() << endl;
                v->parent = d->parent;
                d->parent = NULL;
                for(int i=0; i<CHILDREN_MAX; i++) {
                    v->children[i] = c->children[i];
                    c->children[i] = NULL;
                }
                v->setConnect(true);
                d->setConnect(false);

                searchRestrictedNode(d, &node_list[0]);
            }
        }
    }
    for(int i=0; i<CHILDREN_MAX; i++) {
        searchRestrictedNode(v, d->children[i]);
    }
}

void Network::countNegativeNode() {
    int cnt = 0;
    for(int i=0; i<this->node_max; i++) {
        // if(node_list[i].parent != NULL) cout << node_list[i].getId() << "'s parent is " << node_list[i].parent->getId() << " My type is " << node_list[i].getConnectionType() << endl;
        // cout << "I'm " << node_list[i].getId() << " My type is " << node_list[i].getConnectionType() << endl;
        if(node_list[i].getConnect()) cnt++;
        // else cout << "I'm alone!!!" << endl;
    }

    free(node_list);
    cout << cnt << " of " << this->node_max << " nodes joined in the Tree." << endl;
    if(cnt == this->node_max) cout << "perfect !!!111" << endl;
}
