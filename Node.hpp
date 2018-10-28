#ifndef NODE_HPP
#define NODE_HPP

#include "Vector2.hpp"

//Node type to determine if the node is passable or not
enum class ENodeType
{
    Passable,
    Obstacle
};

//Header only as the node is only a container
class Node
{
public:
    Node(int id, Vector2f& worldPosition, Vector2i& gridPosition, ENodeType nodeType = ENodeType::Passable)
     : m_id(id), m_worldPosition(worldPosition), m_gridPosition(gridPosition), m_nodeType(nodeType){}
    Node(){}
    ~Node(){}

    //Set the node type to a new type
    void SetNodetype(ENodeType type){m_nodeType = type;}
    //Set the parent to a node
    void SetParent(Node* node) {m_parent = node;}
    //Get the node
    ENodeType GetNodeType() const { return m_nodeType;}
    //Get the world position of the node
    const Vector2f& GetWorldPos() { return m_worldPosition; }
    //Get the grid position of the node
    const Vector2i& GetGridPos() { return m_gridPosition; }
    //Get the parent of the node (Returns nullptr if no parent)
    Node* GetParent() const {return m_parent;}

    //Set GCost and HCost to 0 by default
    int GCost {0};
    int HCost {0};
    //To get the fcost just add the G and H costs together
    int FCost(){return GCost + HCost;}
    //Get the node ID
    int GetID() const {return m_id;}
private:
    //Hold a unique ID of the node
    int m_id;

    Vector2f m_worldPosition;
    Vector2i m_gridPosition;
    ENodeType m_nodeType;
    Node* m_parent{nullptr};
};

inline bool operator==(const Node& lhs, const Node& rhs)
{
     return lhs.GetID() == rhs.GetID();
}

inline bool operator!=(const Node& lhs, const Node& rhs)
{
     return lhs.GetID() != rhs.GetID();
}

inline bool operator<(const Node& lhs, const Node& rhs)
{
     return lhs.GetID() < rhs.GetID();
}

#endif // NODE_HPP
