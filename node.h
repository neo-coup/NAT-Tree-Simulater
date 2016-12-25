#ifndef __NODE_H__
#define __NODE_H__

#define CHILDREN_MAX 2

class Node
{
 private:
     int id;
     bool connect;
     int connection_type;
     int locate;
     bool mobile;

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
     int getLocate() { return this->locate; };
     void setLocate(int locate) { this->locate = locate; };
     bool getMobile() { return this->mobile; };
     void setMobile(bool mobile) { this->mobile = mobile; };
};

#endif
