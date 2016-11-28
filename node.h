#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

// #define TYPE0_RATIO
// #define TYPE1_RATIO
// #define TYPE2_RATIO
// #define TYPE3_RATIO
// #define TYPE4_RATIO
// #define TYPE5_RATIO

class Node
{
 private:
     int id;
     int connection_type;
     bool connect;
     Node *parent;
     Node *children;

 public:
     Node(int id) {
         this->id = id;

         // connection_type is decised here

     };
     int getId() { return this->id; };
     int getConnectionType() { return this->connection_type; };
     void setConnectionType(int connection_type) { this->connection_type = connection_type; }
     bool isConnect() { return this->connect; };
};

#endif
