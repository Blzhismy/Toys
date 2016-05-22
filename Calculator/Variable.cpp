#include "Variable.h"
#include <malloc.h>

VarListHead* list_head = create_var_list();

VarListHead* create_var_list()
{
    VarListHead* list_head = (VarListHead*)malloc(sizeof(VarListHead));
    list_head->head=NULL;
    list_head->last=NULL;
    return list_head;
}

bool find_var(const char id)
{
    Variable* pvar=list_head->head;
    if(pvar == NULL)
	{
		return false;
	}

	do
	{
		if(pvar->id == id)
		{
			return true;
		}
		pvar = pvar->next;

	}while(pvar!=NULL);

	return false;
}


void add_var (const char id, float val)
{
	Variable* var = (Variable*)malloc(sizeof(Variable));
	var->next=NULL;
	var->id = id;
	var->value = val; 

	if (list_head->head == NULL)
	{
		list_head->head = var;
		list_head->last = var;

		return ;
	}
	list_head->last->next = var;
	list_head->last = var;
}

void delete_var(const char id)
{
	Variable* pvar = list_head->head;
	while(pvar != NULL)
	{
		if(pvar->next->id == id)
		{
			Variable* temp = pvar->next;
			pvar->next = temp->next;
			free(temp);
			return;
		}
		pvar = pvar->next;
	}
}

bool is_var_init (const char id)
{
	Variable* pvar=list_head->head;

	do
	{
		if(pvar->id == id)
		{
			return pvar->is_init;
		}
		pvar = pvar->next;

	}while(pvar!=NULL);

	return false; 
}

void init_var (const char id)
{
	Variable* pvar=list_head->head;

	do
	{
        if(pvar->id == id)
        {
            pvar->is_init = true;
        }
        pvar = pvar->next;

    }while(pvar!=NULL);
}

void set_value (const char id,float val)
{
	Variable* pvar=list_head->head;
	while(pvar != NULL)
	{
		if(pvar->id == id)
		{
			pvar->value = val;
			return;
		}
		pvar = pvar->next;
	}
}

float value_var(const char id)
{
    Variable* pvar=list_head->head;
    while(pvar != NULL)
    {
        if(pvar->id == id)
        {
            return pvar->value;
        }
		pvar = pvar->next;
    }
}

void destroy_var_list()
{
    Variable* pvar = list_head->head;
    Variable* rubbish;
    while(pvar!=NULL)
    {
        rubbish = pvar;
        pvar = rubbish->next;
        free(rubbish);
    }
    free(list_head);
}
