# NTS
NAT-TREE-SIMULATER

## オプション
使い方:  
./[file name] [node file] [result file] [options]

[node file]              
eg. ### nodes/nodes.0.00.csv ###          
指定されなければ、上記のノードファイルが使用される

[result file]            
eg. ### result/result.0.00.csv ###        
指定されなければ、いずれのファイルにも書き込まれない(標準出力のみ)

 [options]  
-h, --help                ヘルプ表示   
-d, --debug               実行時のノード情報表示   
-e, --extend              組み合わせの拡張
-m, --mobile              モバイルノードの有効化  
-pe, --pEmpty             空き優先再構築     
-ps, --pShallow           浅さ優先再構築

## 実行環境
linux

## 実行方法
1. 初期化
```
cd ns
make allclean
```

2. ノードファイル生成
```
cd create
make
bash create.sh
```
nodesフォルダにノードファイルが生成される。

3. 実行  
### 単体実行
```
cd ns
make
./main [options]
```
### バッチ処理
```
cd ns
make
bash run.sh
```
resultフォルダにリザルトファイルが生成される。
4. 平均算出
```
cd analyze
make
bash analyze.sh
```
avgフォルダavgファイルが生成される。

### nodesファイル
nodes.モバイル割合.番号.csv

ID,タイプ,モバイルフラグ
