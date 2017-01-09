#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void showHelp();

using namespace std;

int main(int argc, char** argv) {

    if(argc == 0) {
        cout << "Usage:     ./analyze [0-9]\n";
        return 0;
    }
    vector<vector<int>> node_val_list;

    /* ========== 読み込み 開始 ========== */
    string mobile_ratio = argv[1];
    for(int i=0; i<100; i++) {
        vector<int> node_val;

        string empty = i < 10 ? "0" : "";
        string file_name = "../result/result." + mobile_ratio + "." + empty + std::to_string(i) + ".csv";

        ifstream ifs(file_name);
        if(!ifs) {
            cout << "入力エラー\n";
            return 0;
        }

        // csvファイルを1行ずつ読み込む
        string str;
        while(getline(ifs,str)){
            string node_num;
            string max_node_num;
            istringstream stream(str);

            getline(stream, node_num, ',');
            getline(stream, max_node_num, ',');

            node_val.push_back(stoi(node_num));
        }
        node_val_list.push_back(node_val);
    }
    /* ========== 読み込み 終了 ========== */



    /* ========== 書き込み 開始 ========== */

    vector<int> avg_list;
    for(int i=0; i<10; i++) {
        avg_list.push_back(0);
        for(int j=0; j<100; j++) {
            avg_list[i] += node_val_list[j][i];
        }
        printf("%.2f,", (double)avg_list[i]/100);
    }
    printf("\n");

    /* ========== 書き込み 終了 ========== */

    return 1;
}
