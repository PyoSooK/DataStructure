#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 10

int *queue;
int front; // 전단
int rear;  // 후단
int size = 1;

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % (QUEUE_SIZE * size); }
int queue_size() { return (rear - front + (QUEUE_SIZE * size)) % (QUEUE_SIZE * size); }

void enqueue(int item)
{
    // queue 크기 증가해야 하는 경우
    if (is_full())
    {
        printf("* Full QUEUE\n");
        int *temp = (int *)malloc((QUEUE_SIZE * size) * sizeof(int));

        if (rear > front)
        {
            for (int i = 0; i < (rear + 1); i++)
                temp[i] = queue[i];
        }
        else
        {
            for (int i = front; i < (QUEUE_SIZE * size); i++)
                temp[i - front] = queue[i];
            for (int i = 0; i < (rear + 1); i++)
                temp[QUEUE_SIZE * size - (rear + 1) + i] = queue[i];
            front = 0;
            rear = QUEUE_SIZE * size - 1;
        }
        free(queue);

        queue = (int *)malloc((QUEUE_SIZE * (size + 1)) * sizeof(int));
        for (int i = 0; i < (QUEUE_SIZE * size); i++)
            queue[i] = temp[i];
        rear = (rear + 1) % (QUEUE_SIZE * (size + 1));
        queue[rear] = item;
        size++;
        free(temp);
    }
    else
    {
        rear = (rear + 1) % (QUEUE_SIZE * size);
        queue[rear] = item;
    }
}

void enqueue_at(int index, int item)
{
    if (index < 1 || index > queue_size() + 1)
    {
        printf("* ENQUEUE INDEX ERROR!!\n");
        return;
    }

    if (is_full())
    {
        printf("* Full QUEUE\n");
        int *temp = (int *)malloc((QUEUE_SIZE * size) * sizeof(int));

        if (rear > front)
            for (int i = 0; i < (rear + 1); i++)
                temp[i] = queue[i];
        else
        {
            for (int i = front; i < (QUEUE_SIZE * size); i++)
                temp[i - front] = queue[i];
            for (int i = 0; i < (rear + 1); i++)
                temp[QUEUE_SIZE * size - (rear + 1) + i] = queue[i];
            front = 0;
            rear = QUEUE_SIZE * size - 1;
        }
        free(queue);

        queue = (int *)malloc((QUEUE_SIZE * (size + 1)) * sizeof(int));
        for (int i = 0; i < (rear + 1); i++)
            queue[i] = temp[i];
        for (int i = rear; i >= index; i--)
            queue[i + 1] = queue[i];
        rear = (rear + 1) % (QUEUE_SIZE * (size + 1));
        queue[index] = item;
        size++;
        free(temp);
    }
    else
    {
        index = (index + front) % (QUEUE_SIZE * size);
        if ((rear + 1) % (QUEUE_SIZE * size) != index)
        {
            if (rear < front && index > front)
            {
                for (int i = rear; i >= 0; i--)
                    queue[i + 1] = queue[i];
                queue[0] = queue[(QUEUE_SIZE * size) - 1];
                for (int i = QUEUE_SIZE - 2; i >= index; i--)
                    queue[i + 1] = queue[i];
            }
            else
            {
                for (int i = rear; i >= index; i--)
                    queue[(i + 1) % (QUEUE_SIZE * size)] = queue[i];
            }
        }
        rear = (rear + 1) % (QUEUE_SIZE * size);
        queue[index] = item;
    }
}

void enqueue2(int item)
{
    if (is_full())
    {
        printf("* Full QUEUE\n");
        int *temp = (int *)malloc((QUEUE_SIZE * size) * sizeof(int));

        if (rear > front)
            for (int i = 0; i < (rear + 1); i++)
                temp[i] = queue[i];
        else
        {
            for (int i = 0; i < (rear + 1); i++)
                temp[i] = queue[i];
            for (int i = (QUEUE_SIZE * size) - 1; i > front; i--)
                temp[i] = queue[i];
            front = front + QUEUE_SIZE;
        }

        free(queue);
        queue = (int *)malloc((QUEUE_SIZE * (size + 1)) * sizeof(int));
        if (rear > front)
        {
            for (int i = 0; i < (rear + 1); i++)
                queue[i] = temp[i];
        }
        else
        {
            for (int i = 0; i < (rear + 1); i++)
                queue[i] = temp[i];
            for (int i = rear + 2; i < QUEUE_SIZE; i++)
                queue[i + QUEUE_SIZE] = temp[i];
        }
        rear = (rear + 1) % (QUEUE_SIZE * (size + 1));
        queue[rear] = item;
        size++;
        free(temp);
    }
    else
    {
        rear = (rear + 1) % (QUEUE_SIZE * size);
        queue[rear] = item;
    }
}

int dequeue()
{
    if (is_empty())
    { // 큐가 공백 상태인 경우
        printf("* Queue is Empty!!\n");
        return 0;
    }
    else
    {
        if (queue_size() % QUEUE_SIZE == 0)
        {
            printf("* CHANGE DEQUEUE\n");
            int re;
            int *temp = (int *)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));

            re = queue[front + 1];

            if (rear > front)
                for (int i = front + 1; i < rear + 1; i++)
                    temp[i - (front + 1)] = queue[i];
            else
            {
                for (int i = front + 1; i < QUEUE_SIZE * size; i++)
                    temp[i - (front + 1)] = queue[i];
                for (int i = 0; i < (rear + 1); i++)
                    temp[QUEUE_SIZE * (size - 1) - (rear + 1) + i] = queue[i]; // front ~ 값이 몇 개 들어가 있는지
            }

            free(queue);

            queue = (int *)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));

            for (int i = 0; i < QUEUE_SIZE * (size - 1); i++)
                queue[i] = temp[i];

            front = 0;
            rear = QUEUE_SIZE * (size - 1) - 1;
            size--;

            free(temp);
            return re;
        }
        else
        {
            front = (front + 1) % (QUEUE_SIZE * size);
            return queue[front];
        }
    }
    return 0;
}

int dequeue_at(int index)
{
    if (is_empty())
    { // 큐가 공백 상태인 경우
        printf("* Queue is Empty!!\n");
        return 0;
    }
    else
    {
        if (index < 1 || index > queue_size())
        {
            printf("* DEQUEUE INDEX ERROR!!\n");
            return 0;
        }

        int re;
        index = (index + front) % (QUEUE_SIZE * size);
        re = queue[index];

        if (queue_size() % QUEUE_SIZE == 0)
        {
            printf("* CHANGE DEQUEUE\n");
            int *temp = (int *)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));

            if (rear > front)
            {
                for (int i = front; i < index; i++)
                    temp[i - front] = queue[i];
                for (int i = index; i < rear; i++)
                    temp[i - front] = queue[i + 1];
            }
            else
            {
                if (index > front && index < (QUEUE_SIZE * size))
                {
                    for (int i = front; i < index; i++)
                        temp[i - front] = queue[i];
                    for (int i = index; i < QUEUE_SIZE * size - 1; i++)
                        temp[i - front] = queue[i + 1];
                    for (int i = 0; i < (rear + 1); i++)
                        temp[QUEUE_SIZE * (size - 1) - (rear + 1) + i] = queue[i];
                }
                else if (index >= 0 && index < rear + 1)
                {
                    for (int i = front; i < QUEUE_SIZE * size; i++)
                        temp[i - front] = queue[i];
                    for (int i = 0; i < index; i++)
                        temp[QUEUE_SIZE * (size - 1) - rear + i] = queue[i];
                    for (int i = index; i < rear; i++)
                        temp[QUEUE_SIZE * (size - 1) - rear + i] = queue[i + 1];
                }
            }
            free(queue);

            queue = (int *)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));

            for (int i = 0; i < QUEUE_SIZE * (size - 1); i++)
                queue[i] = temp[i];

            front = 0;
            rear = QUEUE_SIZE * (size - 1) - 1;
            size--;

            free(temp);
        }
        else
        {
            if (rear < front && index < rear + 1)
            {
                for (int i = index; i > 0; i--)
                    queue[i] = queue[i - 1];
                queue[0] = queue[(QUEUE_SIZE * size) - 1];
                for (int i = (QUEUE_SIZE * size); i > front; i--)
                    queue[i] = queue[i - 1];
            }
            else
            {
                for (int i = index; i > front; i--)
                    queue[i] = queue[i - 1];
            }
            front = (front + 1) % (QUEUE_SIZE * size);
        }
        return re;
    }

    return 0;
}

// 큐의 원소를 출력하는 연산
void printQueue()
{
    int i, maxi = rear;
    if (front >= rear)
        maxi += (QUEUE_SIZE * size);
    printf("QUEUE SIZE [%d]\n", (QUEUE_SIZE * size));
    printf("\n QUEUE [ ");
    for (i = front + 1; i <= maxi; i++)
        printf("%d ", queue[i % (QUEUE_SIZE * size)]);
    printf("]\n");
}

void printQueue2()
{
    int i, maxi;
    maxi = (QUEUE_SIZE * size);
    printf("QUEUE SIZE [%d]\n", (QUEUE_SIZE * size));
    printf("\n QUEUE [ ");
    for (i = 0; i < maxi; i++)
        printf("%d ", queue[i]);
    printf("]\n");
}

int main(void)
{
    int i;
    init_queue();
    queue = (int *)malloc(QUEUE_SIZE * sizeof(int));

    for (i = 1; i < 20; i++)
        enqueue(i);
    printQueue();
    for (i = 1; i < 8; i++)
        dequeue();
    for (i = 10; i < 13; i++)
        enqueue(i);
    printQueue();

    dequeue_at(4);
    printQueue();

    free(queue);
    getchar();
}
