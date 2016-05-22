#include <stdio.h>
#include <math.h>
#include "Node.h"
#include "Variable.h"


float Node_Add(Node* node)
{
    return Node_Calulate(node->next1) +  Node_Calulate(node->next2);
}

float Node_Substract(Node* node)
{
    return Node_Calulate(node->next1) - Node_Calulate(node->next2);
}

float Node_Multiply(Node* node)
{
    return Node_Calulate(node->next1) * Node_Calulate(node->next2);
}

float Node_Division(Node* node)
{
    return Node_Calulate(node->next1) / Node_Calulate(node->next2);
}


float Node_Calulate(Node *node)
{
	if (node == NULL)
	{
		return 0;
	}

	if(node->type == tNumber)
	{
		float num = node->sign ? node->value : (-node->value); 
		return pow (num,node->index);
	}
	if(node->type == tVariable)
	{
		float num = node->sign ? node->value : (-node->value); 
		return pow (num,node->index);
	}
	if(node->type == tAdd)
	{
		float num = Node_Add (node);
		num = node->sign ? num : (-num);
		return pow (num,node->index);
	}
	if(node->type == tSubstract)
	{
		float num =  Node_Substract (node);
		num = node->sign ? num : (-num);
		return pow (num,node->index);
	}
	if(node->type == tMultiply)
	{
		float num = Node_Multiply (node);  
		num = node->sign ? num : (-num); 
		return pow (num,node->index);
	}
	if(node->type == tDivision)
	{
		float num = Node_Division (node); 
		num = node->sign ? num : (-num);
		return pow (num,node->index);
	}

	return 0;
}



