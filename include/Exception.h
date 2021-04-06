#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(std::string msg) :m_msg(msg) {};
	~Exception() = default;
	void show() { std::cout << m_msg << std::endl; };

private:
	std::string m_msg;
};