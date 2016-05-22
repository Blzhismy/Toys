#ifndef VARIABLE_H
#define VARIABLE_H



typedef struct Variable_t
{
    char id;
    float value;
	bool is_init;
    Variable_t* next;
}Variable;

typedef struct VarListHead_t
{
     Variable* head;
     Variable* last;
}VarListHead;

bool find_var (const char id);
float value_var (const char id);
void add_var (const char id, float val);
void delete_var (const char id);
void set_value (const char id,float val);
VarListHead* create_var_list ();
void destroy_var_list ();

#endif // VARIABLE_H
