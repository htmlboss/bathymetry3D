#pragma once

#include <memory>
#include <queue>

class Command {

public:
	virtual ~Command() = default;

	Command(Command&&) = default;
	Command& operator=(Command&&) = default;

	virtual void execute() = 0;
};

using CommandPtr = std::unique_ptr<Command>;
using CommandQueue = std::queue<CommandPtr>;