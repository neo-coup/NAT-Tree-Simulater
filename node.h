#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>

// #define TYPE0_RATIO
// #define TYPE1_RATIO
// #define TYPE2_RATIO
// #define TYPE3_RATIO
// #define TYPE4_RATIO
// #define TYPE5_RATIO
#define CHILDREN_MAX 2

class Node
{
 private:
     int id;
     int connection_type;
     bool connect;

 public:
     Node *parent;
     Node *children[CHILDREN_MAX];

     Node() {
         this->connect = false;
         this->parent = NULL;
         for(int i=0; i<CHILDREN_MAX; i++) this->children[i] = NULL;
      };
     int getId() { return this->id; };
     void setId(int id) { this->id = id; };
     int getConnectionType() { return this->connection_type; };
     void setConnectionType(int connection_type) { this->connection_type = connection_type; }
     void setConnect(bool connect) { this->connect = connect; };
     bool isConnect() { return this->connect; };
};

#endif
