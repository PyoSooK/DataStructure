#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 10

int *stack;
int top;
int size; // 스택 크기 (size * STACK_SIZE)

int is_empty() { return (top == -1); }
int is_full() { return ((top % 10) == STACK_SIZE - 1); }
void stack_init()
{
    top = -1;
    size = 1;
}

// top 원소를 삭제 및 반환
int pop()
{
    if (is_empty())
    {
        printf("* Stack is Empty!!\n");
        return 0;
    }
    else
    {
        // pop으로 안해 size가 줄어드는 경우 (예. top : 10 -> 9)
        if (top % 10 == 0)
        {
            int i, value, *temp;
            value = stack[top];
            temp = (int *)malloc(STACK_SIZE * (size - 1) * sizeof(int));

            printf("* CHANGE STACK\n");
            for (i = 0; i < top; i++)
                temp[i] = stack[i];
            free(stack);
            stack = (int *)malloc(STACK_SIZE * (size - 1) * sizeof(int));

            for (i = 0; i < top; i++)
                stack[i] = temp[i];

            free(temp);

            top--;
            size--;
            return value;
        }
        // size 변화가 없는 경우
        else
            return stack[top--];
    }
}

// 원하는 위치의 원소를 삭제 및 반환
int pop_at(int index)
{
    if (is_empty())
    {
        printf("* Stack is Empty!!\n");
        return 0;
    }
    else
    {
        // 인덱스가 스택 범위 내에 없는 경우
        if (index < 0 || index > top)
        {
            printf("* POP INDEX ERROR\n");
            return 0;
        }

        int value = stack[index];

        if (top % 10 == 0)
        {
            int i, *temp;
            temp = (int *)malloc(STACK_SIZE * (size - 1) * sizeof(int));

            printf("* CHANGE STACK\n");
            for (int i = index; i < top; i++)
                stack[i] = stack[i + 1];
            for (i = 0; i < top; i++)
                temp[i] = stack[i];
            free(stack);

            stack = (int *)malloc(STACK_SIZE * (size - 1) * sizeof(int));
            for (i = 0; i < top; i++)
                stack[i] = temp[i];
            free(temp);

            top--;
            size--;
        }
        else
        {
            for (int i = index; i < top; i++)
                stack[i] = stack[i + 1];
            top--;
        }
        return value;
    }
}

// top 원소를 삽입
void push(int item)
{
    // 포화상태일 경우 size 증가 후 원소 삽입
    if (is_full())
    {
        printf("* Full STACK\n");
        int *temp;
        temp = (int *)malloc((STACK_SIZE * size) * sizeof(int));

        for (int i = 0; i < (top + 1); i++)
            temp[i] = stack[i];
        free(stack);
        stack = (int *)malloc((STACK_SIZE * (size + 1)) * sizeof(int));

        for (int i = 0; i < (top + 1); i++)
            stack[i] = temp[i];
        stack[++top] = item;

        size++;

        free(temp);
    }
    else
        stack[++top] = item;
}

// 원하는 위치에 원소를 삽입
void push_at(int index, int item)
{
    // 인덱스가 스택의 범위 내에 없는 경우
    if (index >= (top + 2))
    {
        printf("* Previous index is EMPTY.\n");
        return;
    }
    else
    {
        if (is_full())
        {
            printf("* Full STACK\n");
            int *temp;
            temp = (int *)malloc((STACK_SIZE * size) * sizeof(int));

            for (int i = 0; i < (top + 1); i++)
                temp[i] = stack[i];
            free(stack);
            stack = (int *)malloc((STACK_SIZE * (size + 1)) * sizeof(int));

            for (int i = 0; i < (top + 1); i++)
                stack[i] = temp[i];

            if (index < top)
            {
                int i;
                for (i = top; i >= index; i--)
                    stack[i + 1] = stack[i];
                stack[index] = item;
                top++;
            }
            else
                stack[++top] = item;

            size++;

            free(temp);
        }
        else
        {
            if (index < top)
            {
                int i;
                for (i = top; i >= index; i--)
                    stack[i + 1] = stack[i];
                stack[index] = item;
                top++;
            }
            else
                stack[++top] = item;
        }
    }
}

// 스택의 원소 출력
void print_stack()
{
    int i;
    printf("\nSTACK SIZE [%d]\n", (STACK_SIZE * size));
    printf("STACK\n");
    for (i = 0; i <= top; i++)
    {
        if (i != 0 && (i % 10) == 0)
            printf("\n");
        printf("%2d ", stack[i]);
    }
    printf("\n\n");
}

int main(void)
{
    stack_init();
    int i;
    stack = (int *)malloc(STACK_SIZE * sizeof(int));

    for (i = 0; i < 38; i++)
        push(i + 1);

    print_stack();

    push_at(1, 40);
    push_at(3, 77);
    printf("top : %d\n", top);
    print_stack();

    push_at(5, 66);
    print_stack();

    push_at(44, 100);

    pop_at(1);
    pop_at(3);
    print_stack();

    free(stack);

    getchar();
}