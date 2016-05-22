#ifndef SCAN_H
#define SCAN_H


//表达式中信息
enum enum_symbol
{
    eAdd,
    eSubtract,
    eLeftBracket,
    eRightBracket,
    eNumber,
    eVariable,
    eMultiply,
    eDivision,
    eIndex,
    eAssign,
	eTerm,
    eEnd,
    eError
};


//表达式阅读器：
void Scanner_Init(const char* expression);  //将表达式载入阅读器
enum_symbol Scan_Result();               //阅读结果反馈器
void Scan_Forward();                     //阅读进度推进器
void Scan_Backward();                     //阅读进度回退器

extern char current_symbol;              //当前读到的符号
extern char current_charactor;           //当前读到的字符
extern float current_number;             //当前读到的数字
extern bool current_assign;              //当前读到的符号 （正true 负false）
extern enum_symbol current_result;       //当前反馈器的结果
extern const char* Scan_pos;             //字符遍历器

#endif // SCAN_H
