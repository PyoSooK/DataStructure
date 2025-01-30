#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

// 데이터 유형
typedef char Element;

Element data[MAX_STACK_SIZE];

int stack_top;

void init_stack() { stack_top = -1; }
int size() { return stack_top + 1; }
int is_empty() { return (stack_top == -1); }
int is_full() { return (stack_top == MAX_STACK_SIZE - 1); }

void push(Element e)
{
    if (is_full()) {
        printf("스택 포화 에러");
        return;
    }
    else
        data[++stack_top] = e; // top 증가 후 데이터 입력
}

Element pop()
{
    if (is_empty())
    {
        printf("스택 공백 에러");
        return '\0'; // char인 경우 null 문자 반환
    }
    return data[stack_top--]; // 논리적 삭제
}

Element peek()
{
    if (is_empty())
    {
        printf("스택 공백 에러");
        return '\0';
    }
    return data[stack_top];
}
