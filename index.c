#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct report {
    int timetaken;
    int accuracy;
    struct report *next;
} report;

report *head = NULL;

void calculate(int, int, int);
void begin();
void knowmore();
void nextwork();
void choices();
void store(report *);
void freemem();
void progress();

void store(report *ptr) {
    if (head == NULL) {
        head = ptr;
    } else {
        report *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = ptr;
    }
}

void freemem() {
    report *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("\nAll progress erased successfully!\n\n");
    choices();
}

void progress() {
    if (head == NULL) {
        printf("\nNo progress available! Try a test first.\n\n");
    } else {
        report *temp = head;
        int count = 1;
        printf("\nYour Typing Progress:\n");
        while (temp != NULL) {
            printf("Test %d -> Time taken: %d sec, Accuracy: %d%%\n",
                   count, temp->timetaken, temp->accuracy);
            temp = temp->next;
            count++;
        }
        printf("\n");
    }
    choices();
}

int homepage(void) {
    printf("WELCOME TO THE TYPING TUTOR!!");
    sleep(2);
    printf("\n\nHere, we will work on your typing speed and make you a better typist.");
    printf("\n\nLet's start our journey to rise as the best typist of all times.");
    printf("\n\nAre you ready to begin?\n");
    choices();
    return 0;
}

void choices() {
    int c;
    printf("\n\nPress 1 to begin.\nPress 2 to view your progress.\nPress 3 to erase all progress\nPress 4 to know more about our workspace.\nPress 0 to Exit.\n\n");
    scanf("%d", &c);

    switch (c) {
        case 1: begin(); break;
        case 2: progress(); break;
        case 3: freemem(); break;
        case 4: knowmore(); break;
        case 0: printf("Exiting... Goodbye!\n"); exit(0);
        default: printf("Please enter a valid option\n"); choices();
    }
}

void begin() {
    int correct = 0, wrong = 0, i, x, timetaken;
    clock_t start, end;
    char a[200];
    char b[] = "HELLO TYPING TUTOR";

    printf("\nType the following text as fast as you can:\n");
    sleep(1);
    getchar(); 
    printf("\n%s\n", b);

    start = clock();
    scanf("%[^\n]s", a);
    end = clock();

    x = strlen(b);
    for (i = 0; i < x; i++) {
        if (a[i] == b[i])
            correct++;
        else
            wrong++;
    }

    timetaken = (int)((end - start) / CLOCKS_PER_SEC);
    calculate(correct, wrong, timetaken);
    nextwork();
}

void calculate(int correct, int wrong, int timetaken) {
    report *ptr = (report *)malloc(sizeof(report));
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    ptr->timetaken = timetaken;
    ptr->accuracy = (100 * correct) / (correct + wrong);
    ptr->next = NULL;

    printf("\nRight letters: %d\n", correct);
    printf("Wrong letters: %d\n", wrong);
    printf("Time taken: %d sec\n", timetaken);
    printf("Accuracy: %d%%\n\n", ptr->accuracy);

    store(ptr);
}

void knowmore() {
    printf("\nAbout Typing Tutor:\n");
    printf("This program helps you improve typing speed and accuracy.\n");
    printf("You can track progress across multiple attempts.\n\n");
    choices();
}

void nextwork() {
    int c;
    printf("Do you want to continue? (1=Yes / 0=No): ");
    scanf("%d", &c);

    switch (c) {
        case 1: begin(); break;
        case 0: choices(); break;
        default: printf("Wrong input! Try again.\n"); nextwork();
    }
}

int main(void) {
    homepage();
    return 0;
}
