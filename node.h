#ifndef __NODE_H__
#define __NODE_H__

#define TYPE_0 15
#define TYPE_1 15
#define TYPE_2 15
#define TYPE_3 15
#define TYPE_4 15
#define TYPE_5 20
#define CHILDREN_MAX 2

class Node
{
 private:
     int id;
     bool connect;
     int connection_type;

 public:
     Node *parent;
     Node *children[CHILDREN_MAX];

     Node();
     int getId() { return this->id; };
     void setId(int id) { this->id = id; };
     void setConnect(bool connect) { this->connect = connect; };
     bool getConnect() { return this->connect; };
     int getConnectionType() { return this->connection_type; };
     void setConnectionType(int connection_type) { this->connection_type = connection_type; }
     int selectConnectionType();
     bool canConnect(int);
};

#endif
