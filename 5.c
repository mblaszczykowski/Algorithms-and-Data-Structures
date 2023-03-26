#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

// dodawanie do stosu
void push(int val) {
    // alokacja pamieci
    struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));

    // dodanie danej
    newnode->data = val;

    newnode->next = top;
    top = newnode;
}

// usuwanie ze stosu
void pop() {
    if (top == NULL)
        printf("Stos jest pusty\n");
    else
        top = top->next;
}

// wyswietlanie stosu
void display() {
    // pomocniczy node
    struct Node *ptr;

    if (top == NULL)
        printf("Stos jest pusty\n");
    else {
        // ustawienie pomocniczego node na top
        ptr = top;

        // petla przez wszystkie elementy
        while (ptr != NULL) {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
    }

    printf("\n");
}

// zwroc top
int showTop() {
    return top->data;
}

// czy lista jest pusta
int empty() {
    if (top == NULL)
        return 1;
    return 0;
}

// zwroc priorytet
int priorytety(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// algorytm ONP
void ONP(char *s) {
    char result[100] = "";

    // petla przez wszystkie elementy stringa z inputu
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];

        // jesli zeskanowany znak jest litera badz liczba, dodaj do wynikowego stringa
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9')) {
            char temp[2] = {c, '\0'};
            strcat(result, temp);
        }

        // jesli zeskanowany znak jest '(', dodaj go do stosu
        else if (c == '(')
            push('(');

        // jesli zeskanowany znak to ')', petla do momentu napotkania '(' jako top i dodawanie top do rezultatu wynikowego oraz usuwanie elementu
        else if (c == ')') {
            while (showTop() != '(') {
                char temp[2] = {showTop(), '\0'};
                strcat(result, temp);
                pop();
            }
            pop();
        }

        // Jesli zeskanowany jest operator, ustalamy priorytet
        else {
            while (!empty() && priorytety(s[i]) <= priorytety(showTop())) {
                char temp[2] = {showTop(), '\0'};
                strcat(result, temp);
                pop();
            }
            push(c);
        }
    }

    // Dodaj top do stringa wynikowego i usun wszystkie elementy ze stosu
    while (!empty()) {
        char temp[2] = {showTop(), '\0'};
        strcat(result, temp);
        pop();
    }

    // wypisz rezultat
    printf("%s\n", result);
}

int main() {
    char rownanie[100];

    // input bez spacji
    printf("Wpisz rownanie bez spacji np. '12+a*(b*c+d/e)' : ");
    scanf("%s", rownanie);

    printf("Rownanie po zastosowaniu ONP: ");
    // wywolanie funkcji ONP
    ONP(rownanie);

    return 0;
}