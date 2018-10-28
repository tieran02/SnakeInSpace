#include "Node.hpp"


Node::Node(int ID, Vector2f& worldPosition, Vector2i& gridPosition, ENodeType nodeType) : m_nodeType(nodeType), m_worldPosition(worldPosition), m_id(ID), m_gridPosition(gridPosition)
{
    //ctor
}

Node::~Node()
{
    //dtor
}
