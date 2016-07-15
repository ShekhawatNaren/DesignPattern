#pragma once
#ifndef _Options_H
#define _Options_H

// This header defines "size_t"
#include <stdlib.h>
#include <string>
#include <stdexcept>

/**
* @class Factory_Bridge
* @brief Defines a singleton class to handle command line option processing.
*/
class Options
{
public:
	/// Method to return the one and only instance.
	static Options *instance(void);

	/// Dtor
	~Options();

	/// This returns the queue type specified on the command line.
	std::string queue_type();

	/// This returns the traversal strategy specified on the command line.
	std::string traversal_strategy();

	/// Parse command-line arguments and set the appropriate values as
	/// follows:
	/// 't' - Traversal strategy, i.e., 'P' for pre-order, 'O' for
	/// post-order, 'I' for in-order, and 'L' for level-order.
	/// 'q' - Type of queue, i.e., either 'L' for LQeuue or 'A' for AQueue.
	bool parse_args(int argc, char *argv[]);

	/// Print out usage and default values.
	void print_usage(void);

private:
	/// Make the constructor private for a singleton.
	Options();

	/// Values for parameters passed in on the command line.
	std::string traversal_strategy_;
	std::string queue_type_;

	/// Pointer to the one and only Options object
	static Options* options_impl_;
};

#endif /* _Options_H */