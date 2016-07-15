#pragma once
#ifndef _Eval_Visitor_H
#define _Eval_Visitor_H

#include <stack>
#include "Visitor.h"
#include "Typedefs.h"
#include "Component_Node.h"
#include "Leaf_Node.h"
#include "Composite_Negate_Node.h"
#include "Composite_Add_Node.h"
#include "Composite_Subtract_Node.h"
#include "Composite_Divide_Node.h"
#include "Composite_Multiply_Node.h"
#include "Tree.h"

/**
* @class Post_Order_Eval_Visitor is a subclass of Visitor
* @brief Defines a Expression Evaluator - evaluates the expression represented
by a tree in post order.
*/

template <typename T>
class Post_Order_Eval_Visitor : public Visitor
{
public:
	///Ctor
	Post_Order_Eval_Visitor(void)
		:stack_()
	{}

	///Dtor
	virtual ~Post_Order_Eval_Visitor(void){}

	/// Visit method for LEAF_NODE instances
	virtual void visit(const LEAF_NODE& node){
		stack_.push(node.item());
	}

	/// Visit method for COMPOSITE_NEGATE_NODE instances
	virtual void visit(const COMPOSITE_NEGATE_NODE& node){
		T temp = stack_.top();
		stack_.pop();
		stack_.push(-1 * temp);
	}

	/// Visit method for COMPOSITE_ADD_NODE instances
	virtual void visit(const COMPOSITE_ADD_NODE& node) {
		T rightOperand = stack_.top();
		stack_.pop();

		T leftOperand = stack_.top();
		stack_.pop();

		stack_.push(leftOperand + rightOperand);
	}

	/// Visit method for COMPOSITE_SUBTRACT_NODE instances
	virtual void visit(const COMPOSITE_SUBTRACT_NODE& node) {
		T rightOperand = stack_.top();
		stack_.pop();

		T leftOperand = stack_.top();
		stack_.pop();

		stack_.push(leftOperand - rightOperand);
	}

	/// Visit method for COMPOSITE_MULTIPLY_NODE instances
	virtual void visit(const COMPOSITE_MULTIPLY_NODE& node) {
		T rightOperand = stack_.top();
		stack_.pop();

		T leftOperand = stack_.top();
		stack_.pop();

		stack_.push(leftOperand * rightOperand);
	}

	/// Visit method for COMPOSITE_DIVIDE_NODE instances
	virtual void visit(const COMPOSITE_DIVIDE_NODE& node) {
		T rightOperand = stack_.top();
		stack_.pop();

		T leftOperand = stack_.top();
		stack_.pop();

		stack_.push(leftOperand / rightOperand);
	}

	T yield() {
		return stack_.top();
	}

protected:
	std::stack<T> stack_;
};

/**
* @class Post_Order_Eval_Visitor is a subclass of Post_Order_Eval_Visitor
* @brief Defines a Expression Evaluator - evaluates the expression represented
by a tree in reverse pre order.
*/

template <typename T>
class Pre_Order_Eval_Visitor : public Post_Order_Eval_Visitor<T>
{
public:

	///Ctor
	Pre_Order_Eval_Visitor(void)
	{}

	///Dtor
	virtual ~Pre_Order_Eval_Visitor(void)
	{}

	/// Visit method for COMPOSITE_SUBTRACT_NODE instances
	virtual void visit(const COMPOSITE_SUBTRACT_NODE& node) {
		T leftOperand = stack_.top();
		stack_.pop();

		T rightOperand = stack_.top();
		stack_.pop();

		stack_.push(leftOperand - rightOperand);
	}

	/// Visit method for COMPOSITE_DIVIDE_NODE instances
	virtual void visit(const COMPOSITE_DIVIDE_NODE& node) {
		T leftOperand = stack_.top();
		stack_.pop();

		T rightOperand = stack_.top();
		stack_.pop();

		stack_.push(leftOperand / rightOperand);
	}
};

#endif /* _Eval_Visitor_H */