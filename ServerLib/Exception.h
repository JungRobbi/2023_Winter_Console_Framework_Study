#pragma once

class Exception : public std::exception
{
public:
	Exception(const std::string& str);
	~Exception();

	std::string text;

	const char* what() { return text.c_str(); }
};

