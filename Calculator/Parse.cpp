#include <iostream>
#include "Parse.h"
#include "Scanner.h"
#include "Variable.h"
#include <assert.h>

bool error_happened_ = false;
float parse_result_ = 0;
bool parse_assigned_active = false;          

void Parser_Init(const char* expression)
{
	assert(expression);
	assert(*expression != '\0');
	Scanner_Init (expression);

	error_happened_ = false;
	parse_assigned_active = false;
}

bool Error_Happened ()
{
	return error_happened_;
}

void Parse()
{
	Node* Big_Node = Expr ();
	if (Big_Node == NULL)
	{
		parse_result_ = 0;
	}
	parse_result_ = Node_Calulate (Big_Node);
}

float Parse_Result()
{
	return parse_result_;
}

Node* Expr()
{
	enum_symbol result;
	enum_symbol last_result = eEnd;
	Node* PreviousNode = NULL;

	do
	{
		result = Scan_Result();

		if (result == eAdd)
		{
			if (last_result == eEnd)
			{
				Scan_Forward ();
				result = Scan_Result ();
				Node* node = Term();
				if( node == NULL )
				{
					return NULL;
				}
				node->sign = true;
				PreviousNode = node;
				last_result = result;
				continue; 
			}
			Node* AddNode = (Node*)malloc(sizeof(Node));
			AddNode->type = tAdd; 
			AddNode->sign = true;
			AddNode->sign = true;
			AddNode->index = 1;

			if (last_result == eAdd or last_result == eSubtract)
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}
			else
			{
				AddNode->next1 = PreviousNode;
				PreviousNode = AddNode;  

			}
		}
		else if (result == eSubtract)
		{

			if (last_result == eEnd)
			{
				Scan_Forward ();
				result = Scan_Result ();
				Node* node = Term();
				if( node == NULL )
				{
					return NULL;
				}
				node->sign = false;
				PreviousNode = node;
				last_result = result;
				continue;
			}

			Node* SubNode = (Node*)malloc(sizeof(Node));
			SubNode->type = tSubstract; 
			SubNode->sign = true;
			SubNode->index = 1;

			if (last_result == eAdd or last_result == eSubtract)
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}
			else
			{
				SubNode->next1 = PreviousNode;
				PreviousNode = SubNode;

			}
		}
		else if (result == eNumber or result == eVariable)
		{
			if (last_result == eNumber and last_result == eVariable)
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}

			Node* TermNode = Term();
			if (TermNode == NULL)
			{
				return NULL;
			}

			if (last_result == eEnd)
			{
				PreviousNode = TermNode;
			}
			else
			{
				PreviousNode->next2 = TermNode;
			}
			last_result = result;
			continue;
		}
		else if (result == eLeftBracket)
		{
			if (last_result == eRightBracket or last_result == eNumber or last_result == eVariable)
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}

			Node* node = Term();
			if (node == NULL)
			{
				return NULL;
			}
			if (last_result == eEnd)
			{
				PreviousNode = node;
			}
			else
			{
				PreviousNode->next2 = node;
			} 
			last_result = eTerm;
			continue;
		}
		else if (result == eAssign)
		{
			if (PreviousNode->type != tVariable or parse_assigned_active )
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;    
			}

			parse_assigned_active= true;
			char symbol = current_symbol;

			Scan_Forward ();
			float val = Node_Calulate (Expr());

			if (find_var (symbol))
			{
				set_value (symbol, val);
			}
			else
			{
				add_var (symbol,val);
			}
			PreviousNode->value = val;

			return PreviousNode;
		}
		else if (result == eEnd or result == eRightBracket)
		{
			if (last_result == eEnd or (PreviousNode->next1 != NULL and PreviousNode->next2 == NULL))
			{
				std::cout << "Syntax Error."<< std::endl;
				error_happened_ = true;
			}
			return PreviousNode;
		}
		else
		{
			std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
			error_happened_ = true;
			return NULL;
		}

		last_result = result;
		Scan_Forward ();

	}while(1);

	return PreviousNode;
}





Node* Term()
{
	enum_symbol result = current_result;
	enum_symbol last_result = eEnd;
	Node* PreviousNode = NULL;

	do
	{

		if (result == eNumber)
		{
			if (last_result == eNumber or last_result == eVariable)
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}

			Node* node = (Node*)malloc(sizeof(Node));
			node->type = tNumber;
			node->sign = true;
			node->index = 1;
			node->value = current_number;

			if (last_result == eEnd)
			{
				PreviousNode = node;
			}
			else
			{
				PreviousNode->next2 = node;
			}
		}
		else if (result == eVariable)
		{
			if (last_result == eNumber or last_result == eVariable)
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}

			Node* node = NULL;

			if(find_var(current_symbol))
			{
				node = (Node*)malloc(sizeof(Node));
				node->type = tVariable; 
				node->sign = true;
				node->index = 1;
				node->symbol = current_symbol; 
				node->value = value_var(current_symbol);
			}
			else
			{
				char symbol = current_symbol;
				Scan_Forward ();
				enum_symbol next = Scan_Result ();
				if (next == eAssign)
				{
					node = (Node*)malloc(sizeof(Node));
					node->type = tVariable; 
					node->sign = true;
					node->index = 1;
					node->symbol = symbol;      
					return node;
				}
				else
				{
					if (next != eAdd and next != eSubtract and next != eMultiply and next != eDivision and next != eEnd and next != eRightBracket)
					{
						std::cout << "Syntax Error."<< std::endl;
					}
					else
					{
						printf ("Variable %c hasn't been assigned yet.\n",symbol);
					}

					error_happened_ = true; 
					return NULL;
				}           
			}

			if (last_result == eEnd)
			{
				PreviousNode = node;
			}
			else
			{
				PreviousNode->next2 = node;
			}

		}
		else if (result == eMultiply)
		{
			if (last_result == eEnd or last_result == eMultiply or last_result == eMultiply)
			{
				std::cout << __FILE__ << " " << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}

			Node* node = (Node*)malloc(sizeof(Node));
			node->type = tMultiply;
			node->sign = true;
			node->index = 1;

			node->next1 = PreviousNode;
			node->next2 = NULL;
			PreviousNode = node;
		}
		else if (result == eDivision)
		{
			if (last_result == eEnd or last_result == eMultiply or last_result == eDivision)
			{
				std::cout << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}

			Node* node = (Node*)malloc(sizeof(Node));
			node->type = tDivision;
			node->sign = true;
			node->index = 1;

			node->next1 = PreviousNode;
			node->next2 = NULL;
			PreviousNode = node;
		}
		else if (result == eLeftBracket)
		{
			if (last_result == eRightBracket or last_result == eNumber or last_result == eVariable)
			{
				std::cout << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;
			}

			Scan_Forward ();
			Node* node = Expr();
			result = Scan_Result ();
			if (result != eRightBracket )
			{
				std::cout << __LINE__ << " " << "Syntax Error."<< std::endl;
				error_happened_ = true;
				return NULL;  
			}
			if (node == NULL)
			{
				return NULL;
			}

			if (last_result == eEnd)
			{
				PreviousNode = node;
			}
			else
			{
				PreviousNode->next2 = node;
			}
		}
		//  else if (result == eIndex)
		//  {
		//  	if (last_result != eNumber and last_result != eVariable and last_result != eRightBracket)
		//  	{
		//  		std::cout << __LINE__ << " " << "Syntax Error."<< std::endl;
		//  		error_happened_ = true;
		//  		return NULL;  
		//  	}

		//  	Scan_Forward ();
		//  	enum_symbol temp = Scan_Result ();
		//  	Node* node = NULL;
		//  	if (temp == eNumber) 
		//  	{
		//  		node->type = tNumber;
		//  		node->sign = true;
		//  		node->value = current_number;
		//  		node->index = 1;
		//  	}
		//  	else if (temp == eVariable)
		//  	{
		//  		if (find_var (current_symbol))
		//  		{
		//  			node->type = tVariable;
		//  			node->sign = true;
		//  			node->value = value_var (current_symbol);
		//  			node->index = 1;
		//  		}
		//  		else
		//  		{
		//  			printf ("Variable %c hasn't been assigned yet.\n",current_symbol);
		//  			error_happened_ = true;
		//  			return NULL;    			    
		//  		}
		//  	}
		//  	//else if (temp == eLeftBracket)
		//  	//{
		//  	//   node = Expr (); 
		//  	//}
		//  	else
		//  	{
		//  		std::cout << __LINE__ << " " << "Syntax Error."<< std::endl;
		//  		error_happened_ = true;
		//  		return NULL;   
		//  	}

		//  	if (node == NULL)
		//  	{
		//  		std::cout << __LINE__ << " " << "Syntax Error."<< std::endl;
		//  		error_happened_ = true;
		//  		return NULL;       
		//  	}
		//  	PreviousNode->index = Node_Calulate (node);

		//  	result = Scan_Result ();
		//  	continue;
		//  }
		else
		{
			if (last_result == eEnd or (PreviousNode->next1 != NULL and PreviousNode->next2 == NULL))
			{
				std::cout << "Syntax Error." << std::endl;
				error_happened_ = true;
				return NULL;
			}
			return PreviousNode;
		}

		last_result = result;
		Scan_Forward ();
		result = Scan_Result ();

	}while(1);
}
