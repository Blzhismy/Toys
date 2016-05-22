#ifndef PARSE_H
#define PARSE_H


#include "Node.h"


//表达式解析器：
Node* Expr();
Node* Term();

void Parser_Init(const char* expression);
void Parse();
float Parse_Result();
bool Error_Happened ();

/// 解析错误抛出
extern bool error_happened_;

extern float Result_;

extern bool assigned;                //检测到等号


#endif // PARSE_H
