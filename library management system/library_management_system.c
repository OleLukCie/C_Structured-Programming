#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct bookInfo {
    char name[20];
    float price;
    int num;
};


struct Node {
    struct bookInfo data;
    struct Node* next;
};


struct Node* listBook = NULL;


struct Node* createNode(struct bookInfo data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void insertNodeByHead(struct Node* headNode, struct bookInfo data) {
    struct Node* newNode = createNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}


void deleteNodeByName(struct Node* headNode, const char* bookName) {
    struct Node* posLeftNode = headNode;
    struct Node* posNode = headNode->next;
    
    while (posNode != NULL && strcmp(posNode->data.name, bookName) != 0) {
        posLeftNode = posNode;
        posNode = posNode->next;
    }

    if (posNode == NULL) {
        printf("Books not found!\n");
        return;
    }
    
    printf("Successfully delete the book:%s\n", posNode->data.name);
    posLeftNode->next = posNode->next;
    free(posNode);
}


struct Node* searchByName(struct Node* headNode, const char* bookName) {
    struct Node* posNode = headNode->next;
    while (posNode != NULL) {
        if (strcmp(posNode->data.name, bookName) == 0) {
            return posNode;
        }
        posNode = posNode->next;
    }
    return NULL;
}


void printList(struct Node* headNode) {
    struct Node* pMove = headNode->next;
    printf("Title\tPrice\tAmount\n");
    while (pMove != NULL) {
        printf("%s\t%.2f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
        pMove = pMove->next;
    }
}


void makeMenu() {
    printf("--------------------------------------------------\n");
    printf("**************************************************\n");
    printf("       <-*-Library management system-*->\n");
    printf("**************************************************\n");
    printf("		 Welcome!\n\n");
    printf("\t\t0.Log out of the system\n");
    printf("\t\t1.Register books\n");
    printf("\t\t2.Browse books\n");
    printf("\t\t3.Borrow books\n");
    printf("\t\t4.Return the books\n");
    printf("\t\t5.Book sorting\n");
    printf("\t\t6.Delete the book\n");
    printf("\t\t7.Find books\n");
    printf("--------------------------------------------------\n");
    printf("Please enter (0-7):");
}


void saveInfoToFile(const char* fileName, struct Node* headNode) {
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    struct Node* pMove = headNode->next;
    while (pMove != NULL) {
        fprintf(fp, "%s\t%.1f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
        pMove = pMove->next;
    }
    fclose(fp);
}


void readInfoFromFile(const char* fileName, struct Node* headNode) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("No files found, list of books that started empty.\n");
        return;
    }

    struct bookInfo tempData;
    while (fscanf(fp, "%s\t%f\t%d\n", tempData.name, &tempData.price, &tempData.num) != EOF) {
        insertNodeByHead(headNode, tempData);
    }
    fclose(fp);
}


void bubbleSortList(struct Node* headNode) {
    if (headNode == NULL) return;
    
    for (struct Node* p = headNode->next; p != NULL; p = p->next) {
        for (struct Node* q = headNode->next; q->next != NULL; q = q->next) {
            if (q->data.price > q->next->data.price) {
                struct bookInfo tempData = q->data;
                q->data = q->next->data;
                q->next->data = tempData;
            }
        }
    }
    printList(headNode);
}


void keyDown() {
    int userKey = 0;
    struct bookInfo tempBook;
    
    scanf("%d", &userKey);
    switch (userKey) {
        case 0:
            printf("Are you sure you want to quit? (Yes[1] No[0])\n");
            int k;
            scanf("%d", &k);
            if (k == 1) {
                printf("Exit Successful!\n");
                exit(0);
            }
            return;
        case 1:
            printf("Register book information (name price amount): ");
            scanf("%s %f %d", tempBook.name, &tempBook.price, &tempBook.num);
            insertNodeByHead(listBook, tempBook);
            saveInfoToFile("bookinfo.txt", listBook);
            break;
        case 2:
            printList(listBook);
            break;
        case 3:
            printf("Please enter the title of the book to borrow: ");
            scanf("%s", tempBook.name);
            struct Node* result = searchByName(listBook, tempBook.name);
            if (result == NULL) {
                printf("Unable to borrow, no related books\n");
            } else {
                if (result->data.num > 0) {
                    result->data.num--;
                    printf("The borrowing was successful!\n");
                } else {
                    printf("The current book is out of stock, and the borrowing has failed!\n");
                }
            }
            break;
        case 4:
            printf("Please enter the title of the book to be returned: ");
            scanf("%s", tempBook.name);
            result = searchByName(listBook, tempBook.name);
            if (result == NULL) {
                printf("The source of the book is illegal!\n");
            } else {
                result->data.num++;
                printf("The book was returned!\n");
            }
            break;
        case 5:
            bubbleSortList(listBook);
            break;
        case 6:
            printf("Please enter the title of the book you want to delete: ");
            scanf("%s", tempBook.name);
            deleteNodeByName(listBook, tempBook.name);
            saveInfoToFile("bookinfo.txt", listBook);
            break;
        case 7:
            printf("Please enter the title of the book you want to query: ");
            scanf("%s", tempBook.name);
            result = searchByName(listBook, tempBook.name);
            if (result == NULL) {
                printf("No information found!\n");
            } else {
                printf("Title\tPrice\tAmount\n");
                printf("%s\t%.1f\t%d\n", result->data.name, result->data.price, result->data.num);
            }
            break;
        default:
            printf("Invalid option, please re-enter.\n");
            break;
    }
}


int main() {
    listBook = (struct Node*)malloc(sizeof(struct Node));
    if (!listBook) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }
    listBook->next = NULL;  

    readInfoFromFile("bookinfo.txt", listBook);

    while (1) {
        makeMenu();            
        keyDown();            
        printf("Press any key to continue...\n");
        getchar();            
        getchar();            
        system("cls");       
    }

    
    saveInfoToFile("bookinfo.txt", listBook);
    return 0;
}

