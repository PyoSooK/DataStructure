#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char Element;

Element data[MAX_STACK_SIZE];

int stack_top;

void init_stack() { stack_top = -1; }
int size() { return stack_top + 1; }
int is_empty() { return (stack_top == -1); }
int is_full() { return (stack_top == MAX_STACK_SIZE - 1); }

void push(Element e)
{
    if (is_full())
        printf("스택 포화 에러");
    else
        data[++stack_top] = e;
}

Element pop()
{
    if (is_empty())
    {
        printf("스택 공백 에러");
        return '\0';
    }
    return data[stack_top--];
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

int precedence(char op)
{
    switch (op)
    {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

void infix_to_postfix(char expr[])
{
    int i = 0;
    char c, op;

    init_stack();
    while (expr[i] != '\0')
    {
        c = expr[i++];
        if (c >= '0' && c <= '9')
            printf("%c ", c);
        else if (c == '(')
            push(c);
        else if (c == ')')
        {
            while (is_empty() == 0)
            {
                op = pop();
                if (op == '(')
                    break;
                else
                    printf("%c ", op);
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            while (is_empty() == 0)
            {
                op = peek();
                if (precedence(c) <= precedence(op))
                {
                    printf("%c ", op);
                    pop();
                }
                else
                    break;
            }
            push(c);
        }
    }
    while (is_empty() == 0)
        printf("%c ", pop());
    printf("\n");
}

int main(void)
{
    char expr[2][80] = {"8 / 2 - 3 + (3 * 2)", "1 / 2 * 4 * 4 (1 / 4)"};

    printf("중위수식 : %s ==> 후위수식 : ", expr[0]);
    infix_to_postfix(expr[0]);
    printf("중위수식 : %s ==> 후위수식 : ", expr[1]);
    infix_to_postfix(expr[1]);

    return 0;
}
