#include <stdio.h>
#include <stdlib.h>

// struktura node
struct node {
    int data;
    struct node * left;
    struct node * right;
};

struct node * root = NULL;

// tworzenie nowego node
struct node * create_node(int data) {
    struct node * new_node = (struct node * ) malloc(sizeof(struct node));

    if (new_node == NULL) {
        printf("\nPamiec nie mogla zostac zarezerwowana");
        return NULL;
    }

    new_node -> data = data;
    new_node -> left = NULL;
    new_node -> right = NULL;

    return new_node;
}

// dodawanie elementu do drzewa
void insert(int data) {
    struct node * new_node = create_node(data);

    if (new_node != NULL) {
        // jesli root jest pusty, utworz nowy node jako root node
        if (root == NULL) {
            root = new_node;
            printf("Node z daną %d zostal dodany\n", data);
            return;
        }

        struct node * temp = root;
        struct node * prev = NULL;

        // W pętli while przeszukiwane są kolejne węzły drzewa, dopóki nie zostanie znaleziony węzeł, który nie ma lewego lub prawego dziecka
        while (temp != NULL) {
            prev = temp;
            if (data > temp -> data) {
                temp = temp -> right;
            } else {
                temp = temp -> left;
            }
        }

        // znajdz ostatni node gdzie nowy node powinien byc dodany
        if (data > prev -> data) {
            prev -> right = new_node;
        } else {
            prev -> left = new_node;
        }

        printf("Node z daną %d zostal dodany\n", data);
    }
}
                                                        
// znajdz node o najmniejszej wartosci w drzewie
struct node * smallest_node(struct node * root) {
    struct node * curr = root;
    while (curr != NULL && curr -> left != NULL) {
        curr = curr -> left;
    }
    return curr;
}

// usun node o podanym kluczu z drzewa
struct node * delete(struct node * root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root -> data) {
        root -> left = delete(root -> left, key);
    } else if (key > root -> data) {
        root -> right = delete(root -> right, key);
    } else {
        if (root -> left == NULL) {
            struct node * temp = root -> right;
            free(root);
            return temp;
        } else if (root -> right == NULL) {
            struct node * temp = root -> left;
            free(root);
            return temp;
        }
        struct node * temp = smallest_node(root -> right);
        root -> data = temp -> data;
        root -> right = delete(root -> right, temp -> data);
    }
    return root;

}

// znajdz node o podanym kluczu
int search(int key) {
    struct node * temp = root;

    while (temp != NULL) {
        if (key == temp -> data) {
            return 1;
        } else if (key > temp -> data) {
            temp = temp -> right;
        } else {
            temp = temp -> left;
        }
    }
    return 0;
}



// znajdz node o najwiekszej wartosci w drzewie
struct node * largest_node(struct node * root) {
    struct node * curr = root;
    while (curr != NULL && curr -> right != NULL) {
        curr = curr -> right;
    }
    return curr;
}

// wypisanie wezlow drzewa w kolejnosci inorder
void inorder(struct node * root) {
    if (root == NULL) {
        return;
    }
    inorder(root -> left);
    printf("%d ", root -> data);
    inorder(root -> right);
}

// wypisanie wezlow drzewa w kolejnosci preorder
void preorder(struct node * root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root -> data);
    preorder(root -> left);
    preorder(root -> right);
}

// wypisanie wezlow drzewa w kolejnosci postorder
void postorder(struct node * root) {
    if (root == NULL) {
        return;
    }
    postorder(root -> left);
    postorder(root -> right);
    printf("%d ", root -> data);
}

//wyswietlanie 2d
void print2DUtil(struct node * root, int space) {
    if (root == NULL)
        return;

    // zwieksz dystans pomiedzy poziomami
    space += 10;

    // zajmij sie prawym potomkiem najpierw
    print2DUtil(root -> right, space);

    // wypisz aktualny node po spacji
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root -> data);

    // zajmij sie lewym potomkiem
    print2DUtil(root -> left, space);
}

void deleteTree(struct node * node) {
    if (node == NULL) return;

    // najpierw usun oba subdrzewa
    deleteTree(node -> left);
    deleteTree(node -> right);

    // potem usun node
    printf("   Usuwanie wezla: %d\n", node -> data);
    free(node);
}

// usun drzewo i nastepnie ustaw root jako NULL
void deleteTreeMain(struct node ** node_ref) {
    printf("\nUsuwanie calego drzewa:\n");
    deleteTree( * node_ref);
    * node_ref = NULL;
}

int main() {
    int data;
    struct node * result = NULL;

    // dodawanie wezlow
    insert(10);
    insert(5);
    insert(20);
    insert(3);
    insert(4);
    insert(1);
    insert(75);
    insert(24);
    insert(13);

    // rysowanie drzewa
    printf("\nRysunek drzewa:\n");
    print2DUtil(root, 0);;
    printf("\n");

    // kasowanie wezla o konkretnej wartosci
    root = delete(root, 24);
    printf("Usuwam node z daną %d\n", 24);
    root = delete(root, 4);
    printf("Usuwam node z daną %d\n", 4);
    root = delete(root, 10);
    printf("Usuwam node z daną %d\n", 10);

    // rysowanie drzewa
    printf("\nRysunek drzewa po usunieciu kilku wezlow:\n");
    print2DUtil(root, 0);;
    printf("\n");

    //szukanie wezla 75
    int doWyszukania = 75;
    if (search(doWyszukania) == 1) {
        printf("\n%d zostalo znalezione!\n", doWyszukania);
        printf("Sciezka:\n");
        print2DUtil(root, 0); // wyswietlanie sciezki jesli znaleziono
    } else {
        printf("\n%d nie zostalo znalezione!\n", doWyszukania);
    }

    printf("\n");

    // wyswietlenie wezlow w odpowiedniej kolejnosci
    printf("\n");
    printf("Wyswietlanie wezlow w odpowiedniej kolejnosci przechodzenia: \n");
    printf("VLR: ");
    preorder(root);
    printf("\n");
    printf("LVR: ");
    inorder(root);
    printf("\n");
    printf("LRV: ");
    postorder(root);
    printf("\n");

    // kasowanie calego drzewa
    deleteTreeMain( & root);
    printf("\n");

    return 0;
}