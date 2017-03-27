#pragma once
class InitialisationError : std::exception
{
public:
	InitialisationError(const std::string& msg);

	const char* what() { return message.c_str(); }

private:
	std::string message;
};

