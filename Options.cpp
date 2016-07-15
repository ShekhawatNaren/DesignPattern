#include "stdafx.h"
#if !defined (_Options_CPP)
#define _Options_CPP

#include <iostream>
#include <cstdio>

#include "Options.h"
#include "getopt.h"
#include "LQueue.h"
#include "Tree.h"
#include "Typedefs.h"

// Initialize the singleton.
Options *Options::options_impl_ = nullptr;

Options*
Options::instance()
{
	// You fill in here.
	if (Options::options_impl_ == nullptr) {
		Options::options_impl_ = new Options();
	}

	return Options::options_impl_;
}

// Ctor
Options::Options()
	: traversal_strategy_("Levelorder"),
	queue_type_("LQueue")
{
}

//Dtor
Options::~Options()
{
	// release the freelist if we used an LQueue
	if (queue_type_ == "LQueue")
	{
		LQueue_Node<TREE>::free_list_release();
	}
}

// Return queue type.
std::string
Options::queue_type()
{
	return queue_type_;
}

// Return traversal strategy.
std::string
Options::traversal_strategy()
{
	return traversal_strategy_;
}

// Parse the command line arguments.
bool
Options::parse_args(int argc, char *argv[])
{
	// You may need to use the getopt() function in the assignment4 directory.
	for (int c;
		(c = parsing::getopt(argc, argv, "t:q:h?")) != EOF;
		)
		switch (c)
		{
			// Parse the traversal strategy option
		case 't':
			switch (parsing::optarg[0])
			{
				// Level order traversal
			case 'L':
				this->traversal_strategy_ = "Levelorder";
				break;
				// Preorder traversal
			case 'P':
				this->traversal_strategy_ = "Preorder";
				break;
				// Postorder traversal
			case 'O':
				this->traversal_strategy_ = "Postorder";
				break;
				// Inorder traversal
			case 'I':
			default:
				this->traversal_strategy_ = "Inorder";
				break;
			}
			break;
			// Parse the queue type option
		case 'q':
			this->queue_type_ = parsing::optarg[0] == 'L'
				? "LQueue"
				: "STLQueue";
			break;
		case 'h':
		case '?':
			print_usage();
			return false;
			break;
		default:
			std::cerr << "Queue type " << char(c) << " unknown" << std::endl;
		}

	return true;
};

// Parse the command line arguments.
void
Options::print_usage(void)
{
	std::cout << "Usage: Adapter_test [-t L|p|P|I] [-q S|L]" << std::endl;
	std::cout << "    where -t specifies the tree traversal strategy:" << std::endl;
	std::cout << "       L = Levelorder (default)" << std::endl;
	std::cout << "       P = Preorder" << std::endl;
	std::cout << "       O = Postorder" << std::endl;
	std::cout << "       I = Inorder" << std::endl << std::endl;
	std::cout << "    where -q specifies the queue type:" << std::endl;
	std::cout << "       L = LQueue (default)" << std::endl;
	std::cout << "       S = STLQueue" << std::endl;
}

#endif /* _OptionsXS_CPP */