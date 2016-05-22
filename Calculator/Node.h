#ifndef NODE_H
#define NODE_H

enum enum_NodeType
{
    tAdd,
    tSubstract,
    tMultiply,
    tDivision,
    tNumber,
    tVariable,
};

/// 节点：
typedef struct Node_t
{
    enum_NodeType type;  /// 节点类型
    Node_t* next1;
    Node_t* next2;

    float value;     /// 值

    bool is_var;
    bool sign;       /// 正负号 + 用true -用false
    char symbol;     /// 变量
	float index=1;   /// 指数
}Node;



/// 运算：
float Node_Add(Node* node);
float Node_Substract(Node* node);
float Node_Multiply(Node* node);
float Node_Division(Node* node);
float Node_Calulate(Node* node);


#endif // NODE_H
