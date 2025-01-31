# stack ADT

## data
- 문자형 배열

## operation
- init_stack() : 스택을 초기화한다.
- is_empty() : 스택이 비어있으면 True, 아니면 False를 반환한다.
- is_full() : 스택이 가득차있으면 True, 아니면 False를 반환한다.
- size() : 스택 내의 모든 요소들의 개수들을 반환한다.
- push(x) : 주어진 요소 x를 스택 상단에 삽입한다.
- pop() : 스택 상단에 있는 요소를 삭제하고 반환한다.
- peek() : 스택 상단에 있는 요소를 삭제하지 않고 반환한다.

# stack_dynamicMemory 
stack을 동적 메모리를 활용해서 구현했습니다.

# stack_dynamicMemory  ADT

## data
- 정수형 동적메모리

## operation
- init_stack() : 스택을 초기화한다.
- is_empty() : 스택이 비어있으면 True, 아니면 False를 반환한다.
- is_full() : 스택이 가득차있으면 True, 아니면 False를 반환한다.
- print_stack() : 스택의 크기와 모든 요소를 출력한다. 
- push(x) : 주어진 요소 x를 스택 상단에 삽입한다.
- push_at(index, x) : 주어진 요소 x를 index에 삽입한다.
- pop() : 스택 상단에 있는 요소를 삭제하고 반환한다.
- pop_at(index) : index에 있는 요소를 삭제하고 반환한다.
