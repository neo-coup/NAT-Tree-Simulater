#ifndef __NODE_H__
#define __NODE_H__

#define CHILDREN_MAX 2

const double TYPE_0 = 12.5;   // Open Internet
const double TYPE_1 = 12.5;   // Full cone NAT
const double TYPE_2 = 5.0;    // Restricted cone NAT
const double TYPE_3 = 40.0;   // Port Restricted cone NAT
const double TYPE_4 = 16.0;   // Symmetric NAT
const double TYPE_5 = 14.0;   // UDP Blocked

class Node
{
 private:
     int id;
     bool connect;
     int connection_type;

 public:
     Node* parent;
     Node* children[CHILDREN_MAX];

     Node();
     int getId() { return this->id; };
     void setId(int id) { this->id = id; };
     void setConnect(bool connect) { this->connect = connect; };
     bool getConnect() { return this->connect; };
     int getConnectionType() { return this->connection_type; };
     void setConnectionType(int connection_type) { this->connection_type = connection_type; }
     int selectConnectionType();
};

#endif
