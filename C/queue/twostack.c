/*
    제목 : 스택을 두 개 사용해서 큐 구현하기
    작성일자 : 2023.04.02
*/

#include <stdio.h>
#define MAX_SIZE 5

typedef int Element;

int Stack1[MAX_SIZE], Stack2[MAX_SIZE];

int Stack1_top;
int Stack2_top;

int count = 0;

void init_queue()
{
    Stack1_top = -1;
    Stack2_top = -1;
}

void push_S1(Element e)
{
    if (Stack1_top == MAX_SIZE - 1)
        printf("큐 포화 에러");
    Stack1_top++;
    Stack1[Stack1_top] = e;
}

void push_S2(Element e)
{
    if (Stack2_top == MAX_SIZE - 1)
        printf("큐 포화 에러");
    Stack2_top++;
    Stack2[Stack2_top] = e;
}

int pop_S1()
{
    if (Stack1_top == -1)
        printf("큐 공백 에러");
    return Stack1[Stack1_top--];
}

int pop_S2()
{
    if (Stack2_top == -1)
        printf("큐 공백 에러");
    return Stack2[Stack2_top--];
}

// Stack1을 enqueue할 때, Stack2를 dequeue할 때 주로 사용

void enqueue(Element val)
{
    push_S1(val); // 입력 값을 Stack1 맨 위에 추가
    printf("enaueue() : %dn", val);
    count++;
}

void dequeue()
{
    int i;

    if (Stack1_top == -1 && Stack2_top == -1)
        printf("큐 공백 에러\n"); // Stack1과 Stack2 모두 초기화 상태일때 에러가 뜸
    else
    {
        // Stack2에 Stack1의 값과 반대로 위치로 값을 입력
        for (i = 0; i < count; i++)
        {
            int temp;

            temp = pop_S1(); // Stack1의 pop결과를 변수 temp에 자징
            push_S2(temp);   // temp에 저장된 값을 Stack2 맨 위에 추가
        }

        int x;
        x = pop_S2();

        printf("ttdequeue() --> %dn", x); // Stack2 멘위 값을 출력
        count--;

        // 출력된 값을 제외하고 Stack1에 enqueue한 순서대로 다시 입력
        for (i = 0; i < count; i++)
        {
            int temp;

            temp = pop_S2();
            push_S1(temp);
        }
    }
}

int main(void)
{
    int i;

    init_queue(); // Stack1과 Stack2 top값을 -1로 초기화

    for (i = 1; i <= 4; i++)
        enqueue(i); // Stack1[0] ~ Stack1[3]에 1~4를 순서대로 추가

    dequeue(); // Stack2에 4, 3, 2, 1 입력 후 1 반환 -> Stack1에 2, 3, 4 입력
    dequeue(); // Stack2에 4, 3, 2 입력 후 2 반환 -> Stack1에 3, 4 입력
    dequeue(); // Stack2에 4, 3 입력 후 3 반환 -> Stack1에 4 입력

    enqueue(11); // Stack1 = {4, 11}

    dequeue(); // Stack2에 11, 4 입력 후 4 반환 -> Stack1에 11 입력
    dequeue(); // Stack2에 11 입력 후 11 반환 -> Stack1 입력 값 없음
    dequeue(); // Stack1과 Stack2 모두 초기화 상태이므로 에러

    return 0;
}
