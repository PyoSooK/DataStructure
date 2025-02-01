#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int Element;
Element data[MAX_QUEUE_SIZE]; // 요소의 배열
int front;                    // 전단
int rear;                     // 후단

void error(char *str)
{
    printf("%s\n", str);
    exit(1);
}

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Element val)
{
    if (is_full())
        error("큐 포화 에러");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

Element dequeue()
{
    if (is_empty())
        error("큐 공백 에러");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}

Element peek()
{
    if (is_empty())
        error("큐 공백 에러");
    return data[(front + 1) % MAX_QUEUE_SIZE];
}

// 큐 테스트를 위한 코드 : 요소 종류마다 수정 필요
void print_queue(char msg[])
{
    int i, maxi = rear;
    if (front >= rear)
        maxi += MAX_QUEUE_SIZE;
    printf("* %s\n", msg);
    printf("Queue[%d] = ", size());
    for (i = front + 1; i <= maxi; i++)
        printf("%2d ", data[i % MAX_QUEUE_SIZE]);
    printf("\n");
}

int main(void)
{
    int i;

    init_queue();
    for (i = 1; i < 10; i++)
        enqueue(i);

    print_queue("Enqueue 9회");
    printf("* dequeue() --> %d\n", dequeue());
    printf("* dequeue() --> %d\n", dequeue());
    printf("* dequeue() --> %d\n", dequeue());
    print_queue("Dequeue 3회");

    return 0;
}