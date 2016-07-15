#include "stdafx.h"

#if !defined (_Print_Visitor_CPP)
#define _Print_Visitor_CPP

#include <iostream>

#include "Component_Node.h"
#include "Leaf_Node.h"
#include "Composite_Negate_Node.h"
#include "Composite_Add_Node.h"
#include "Composite_Subtract_Node.h"
#include "Composite_Divide_Node.h"
#include "Composite_Multiply_Node.h"
#include "Tree.h"

#include "Print_Visitor.h"

/// visit method for Leaf_Node<int> instance
void Print_Visitor::visit(const LEAF_NODE& node)
{
	std::cout << node.item() <<",";
}

/// visit method for Composite_Negate_Node<int> instance
void Print_Visitor::visit(const COMPOSITE_NEGATE_NODE& node)
{
	std::cout << "-,";
}

/// visit method for Composite_Add_Node<int> instance
void Print_Visitor::visit(const COMPOSITE_ADD_NODE& node)
{
	std::cout << "+,";
}

/// visit method for Composite_Subtract_Node<int> instance
void Print_Visitor::visit(const COMPOSITE_SUBTRACT_NODE& node)
{
	std::cout << "-,";
}

/// visit method for Composite_Multiply_Node<int> instance
void Print_Visitor::visit(const COMPOSITE_MULTIPLY_NODE& node)
{
	std::cout << "*,";
}

/// visit method for Composite_Divide_Node<int> instance
void Print_Visitor::visit(const COMPOSITE_DIVIDE_NODE& node)
{
	std::cout << "/,";
}

#endif /* _Print_Visitor_CPP */