#pragma once
#if !defined (_Typedefs_H)
#define _Typedefs_H

template <typename T>
class Array;

template <typename T>
class Queue;

template <typename T>
class LQueue_Node;

template <typename T, typename QUEUE>
class Queue_Adapter;

template <typename T, typename LQUEUE_NODE>
class LQueue;

template <typename T, typename ARRAY>
class AQueue;

template <typename T>
class Node;

template <typename T>
class Tree;

typedef Node<int> NODE;
typedef Tree<int> TREE;

// This part of the solution uses the Adapter pattern.  Note that
// LQUEUE_ADAPTER and AQUEUE_ADAPTER are both children of the Queue
// class.  
typedef Queue_Adapter<TREE, LQueue <TREE, LQueue_Node<TREE> > > LQUEUE_ADAPTER;
typedef Queue_Adapter<TREE, AQueue <TREE, Array<TREE> > > AQUEUE_ADAPTER;

typedef Queue<TREE> QUEUE;

template <typename T>
class Component_Node;

template <typename T>
class Leaf_Node;

template <typename T>
class Composite_Unary_Node;

template <typename T>
class Composite_Negate_Node;

template <typename T>
class Composite_Binary_Node;

template <typename T>
class Composite_Add_Node;

template <typename T>
class Composite_Subtract_Node;

template <typename T>
class Composite_Multiply_Node;

template <typename T>
class Composite_Divide_Node;

typedef Component_Node<int> COMPONENT_NODE;

typedef Leaf_Node<int> LEAF_NODE;

typedef Composite_Unary_Node<int> COMPONENT_UNARY_NODE;

typedef Composite_Negate_Node<int> COMPOSITE_NEGATE_NODE;

typedef Composite_Binary_Node<int> COMPONENT_BINARY_NODE;

typedef Composite_Add_Node<int> COMPOSITE_ADD_NODE;

typedef Composite_Subtract_Node<int> COMPOSITE_SUBTRACT_NODE;

typedef Composite_Multiply_Node<int> COMPOSITE_MULTIPLY_NODE;

typedef Composite_Divide_Node<int> COMPOSITE_DIVIDE_NODE;

#endif /* _Typedefs_H */