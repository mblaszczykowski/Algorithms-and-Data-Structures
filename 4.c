#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// zdefiniowanie struktury
typedef struct Stack {
    int size;
    int top;
    int * arr;
} Stack_Node;

// funkcja do utworzenia struktury zwracajaca ją
Stack_Node * Create_stack(int size) {
    Stack_Node * stack = (Stack_Node*)malloc(sizeof(Stack_Node));
    stack -> size = size;
    stack -> top = -1;
    stack -> arr = (int*)malloc(size*sizeof(int));
    return stack;
}

// funkcja do sprawdzenia czy stos jest pelen
int Check_Full(Stack_Node * stack) {
    if (stack -> top == stack -> size - 1)
        return 1;
    else
        return 0;
}

// funkcja do sprawdzenia czy stos jest pusty
int Check_Empty(Stack_Node * stack) {
    if (stack -> top == -1)
        return 1;
    else
        return 0;
}
// funkcja do dodawania elementow
void push(Stack_Node * stack, int element) {
    if (Check_Full(stack))
        return;
    stack -> arr[++stack -> top] = element;
}

// funkcja do usuwania elementu i zwracania go
int pop(Stack_Node * stack) {
    if (Check_Empty(stack))
        return -1;

    return (stack -> arr[stack -> top--]);
}

// funkcja do wypisywania ruchu dyskow
void Move_Disc(int disc, char from_Rod, char to_Rod)
{
    printf("Przeniesiono dysk %d z '%c' do '%c'\n", disc, from_Rod, to_Rod);
}

void Move_Disc_Helper(Stack_Node * source, Stack_Node * dest, char s, char d) {
    int top1 = pop(source);
    int top2 = pop(dest);

    if (top1 == -1) {
        push(source, top2);
        Move_Disc(top2, d, s);
    } else if (top2 == -1) {
        push(dest, top1);
        Move_Disc(top1, s, d);
    } else if (top1 > top2) {
        push(source, top1);
        push(source, top2);
        Move_Disc(top2, d, s);
    } else {
        push(dest, top2);
        push(dest, top1);
        Move_Disc(top1, s, d);
    }
}

void TowerOfHanoi(int number_of_discs, Stack_Node * source, Stack_Node * aux, Stack_Node * dest) {
    char s = 'S', d = 'D', a = 'A';

    if (number_of_discs % 2 == 0) {
        char var = d;
        d = a;
        a = var;
    }

    int number_of_moves = pow(2, number_of_discs) - 1;
    for (int i = number_of_discs; i >= 1; i--) {
        push(source, i);
    }

    // iteracja przez kazde i az do liczby ruchow
    for (int i = 1; i <= number_of_moves; i++) {
        if (i % 3 == 0)
            Move_Disc_Helper(aux, dest, a, d);
        else if (i % 3 == 2)
            Move_Disc_Helper(source, aux, s, a);
        else if (i % 3 == 1)
            Move_Disc_Helper(source, dest, s, d);
    }
}

int main() {
    int number_of_discs;

    printf("Podaj liczbe dyskow: ");
    scanf("%d", &number_of_discs);

    Stack_Node * source;
    Stack_Node * dest;
    Stack_Node * aux;

    // utworzenie 3 stosow      
    source = Create_stack(number_of_discs);
    aux = Create_stack(number_of_discs);
    dest = Create_stack(number_of_discs);

    TowerOfHanoi(number_of_discs, source, aux, dest);

    // delete dynamically allocated memory stacks
    free(source);
    free(aux);
    free(dest);

    return 0;
}