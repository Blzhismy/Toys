#include <iostream>
#include "Parse.h"
#include "Cmd.h"


void input_expression (std::string& expr);

int main (int argc, const char** argv)
{
	std::string expression;

	while (1)
	{
		std::cout << "> ";
		input_expression (expression);
		if (expression.empty ())
		{
			continue;
		}
		//std::cout << expression << std::endl;

		CMD_EXIST (expression);

		Parser_Init (expression.data());
		Parse();

		if (Error_Happened ())
		{
			continue;
		}

		std::cout << Parse_Result() << std::endl;
	}
}


void input_expression (std::string& expr)
{
	std::istream& in = std::cin;
	std::getline (in,expr);
}

