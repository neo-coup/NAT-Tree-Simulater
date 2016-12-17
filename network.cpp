#include "network.h"
#include "node.h"
#include <iostream>
#include <stdlib.h>
#include <queue>

using namespace std;

Network::Network(bool d, bool e, bool r, int n) {
    this->debug = d;
    this->extend = e;
    this->restruct = r;
    this->node_max = n;
    this->cnt_r = 0;
    this->cnt_o = 0;
    this->cnt_e = 0;
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
    if(this->debug) printf("nodes:%d, extend:%d, restruct:%d", this->node_max, this->extend, this->restruct);
    cout << "\nInitializing has done!\n" << endl;
};

void Network::buildTree() {
    for(int i=1; i<this->node_max; i++) {
        Network::entryTree(&(node_list[i]));
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
                if(p->canConnect(v->getConnectionType(), this->extend)) {
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

    // 接続先が無かった場合、木の再構築を行い参加を試みる
    if(this->restruct) searchRestrictedNode(v, &(node_list[0]));
    if(this->restruct) searchChainOpenNode(v, &(node_list[0]));
    if(this->restruct) searchExtraPatternNode(v, &(node_list[0]));

    if(this->debug) if(!v->getConnect()) printf("%d failed to join.\n", v->getId());
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
        if(this->debug) printf("Detect RestRest >>> v:%5d     p:%5d     c:%5d\n", v->getId(), p->getId(), p->children[0]->getId());
        v->children[0] = p->children[0];
        p->children[0]->parent = v;
        p->children[0] = v;
        v->parent = p;
        v->setConnect(true);
        this->cnt_r++;
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
            if(this->debug) printf("Detect Chain >>> v:%5d     p:%5d     c:%5d\n", v->getId(), p->getId(), p->children[i]->getId());
            v->children[0] = p->children[i];
            p->children[i]->parent = v;
            p->children[i] = v;
            v->parent = p;
            v->setConnect(true);
            this->cnt_o++;
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
                if(this->debug) printf("Detect Extra >>> v:%5d     d:%5d     p:%5d\n", v->getId(), d->getId(), p->getId());
                v->parent = d->parent;
                d->parent = NULL;
                for(int i=0; i<CHILDREN_MAX; i++) {
                    v->children[i] = c->children[i];
                    c->children[i] = NULL;
                }
                v->setConnect(true);
                d->setConnect(false);
                this->cnt_e++;

                searchRestrictedNode(d, &node_list[0]);
            }
        }
    }
    for(int i=0; i<CHILDREN_MAX; i++) {
        searchRestrictedNode(v, d->children[i]);
    }
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
    if(this->debug) printf("\nRESTRUCTION >>> R:%2d O:%2d E:%2d\n", this->cnt_r, this->cnt_o, this->cnt_e);
    cout << cnt << " of " << this->node_max << " nodes joined in the Tree." << endl;
    if(cnt == this->node_max) cout << "perfect !!!111" << endl;
}
