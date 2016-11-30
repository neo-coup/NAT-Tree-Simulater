#ifndef __NODE_H__
#define __NODE_H__

#define TYPE_0 125   // Open Internet
#define TYPE_1 125   // Full cone NAT
#define TYPE_2 50    // Restricted cone NAT
#define TYPE_3 400   // Port Restricted cone NAT
#define TYPE_4 160   // Symmetric NAT
#define TYPE_5 140   // UDP Blocked
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
