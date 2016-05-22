#include "Scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>


char current_symbol=0;
char current_charactor=0;
float current_number=0;
float current_variable=0;
enum_symbol current_result;
const char* Scan_pos = NULL;
const char* begin_pos_ = NULL;


void Scanner_Init(const char* expression) 
{
	begin_pos_ = expression;
	Scan_pos = begin_pos_;
}


void Scan_Forward()
{
	assert (Scan_pos);
	if (*Scan_pos=='\0')
	{
		return ;
	}
	++Scan_pos;
}


enum_symbol Scan_Result()
{

	do
	{

		current_charactor = *Scan_pos;

		switch (current_charactor)
		{
			case '0' : case '1': case '2': case '3': case '4':
			case '5' : case '6': case '7': case '8': case '9':
				char *p;
				current_number = strtod(Scan_pos,&p);
				Scan_pos = --p;
				current_result = eNumber;
				return eNumber;
				break;
			case '+':
				current_result = eAdd;
				return eAdd;
				break;
			case '-':
				current_result = eSubtract;
				return eSubtract;
				break;
			case '*':
				current_result = eMultiply;
				return eMultiply;
				break;
			case '/':
				current_result = eDivision;
				return eDivision;
				break;
			case '^':
				current_result = eIndex;
				return eIndex;
				break;
			case '=':
				current_result = eAssign;
				return eAssign;
				break;
			case '(':
				current_result = eLeftBracket;
				return eLeftBracket;
				break;
			case ')':
				current_result = eRightBracket;
				return eRightBracket;
				break;
			//case '^':
			//	current_result = eIndex;
			//	return eIndex;
			//	break;
			case '\0': case EOF:
				current_result = eEnd;
				return eEnd;
				break;
			case '\n' : case '\r' : case ' ':
				++Scan_pos;
				continue;
				break;
			default:
				if (isupper(*Scan_pos) or islower (*Scan_pos))
				{
					current_symbol = *Scan_pos;
					current_result = eVariable;
					return eVariable;
				}
				else
				{
					current_result = eError;
					return eError;
				}
				break;
		}

		break;

	}while (1);

	return eEnd;
}


