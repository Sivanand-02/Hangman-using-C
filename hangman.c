#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
    char data;
    struct Node *next;
};

struct Node *createNode(char data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addNode(struct Node **head, char data) {
    struct Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void displayList(struct Node *head) {
    struct Node *current = head;
    int cnt=0;
    while (current != NULL) {
        if (current->data == ' ') {
            printf("  "); // Print spaces as is
        } else {
            printf("%c ", current->data);
            cnt++;
        }
        current = current->next;
    }
    printf("\n");
    printf("Total characters : %d\n",cnt);
}

int main() {
    srand(time(NULL));
    int i,allLettersGuessed,found;
    char inputWord[100];
    printf("Enter the word to be guessed (letters and spaces allowed): ");
    scanf(" %[^\n]s", inputWord);

    int wordLength = strlen(inputWord);

    struct Node *guessedWord = NULL;
    for (i = 0; i < wordLength; i++) {
        char character = (inputWord[i] == ' ') ? ' ' : '_'; // Preserve spaces
        addNode(&guessedWord, character);
    }

    int maxAttempts = 6;
    int attemptsLeft = maxAttempts;

    char guessedLetters[26];
    int numGuessedLetters = 0;

    printf("Welcome to Hangman!\n");

    while (attemptsLeft > 0) {
        printf("Word: ");
        displayList(guessedWord);
        printf("Attempts left: %d\n", attemptsLeft);

        char guess;
        printf("Enter your guess: ");
        scanf(" %c", &guess);

        int alreadyGuessed = 0;
        for ( i = 0; i < numGuessedLetters; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("You already guessed '%c'.\n", guess);
            continue;
        }

        guessedLetters[numGuessedLetters++] = guess;

        found = 0;
        struct Node *current = guessedWord;
        for ( i = 0; i < wordLength; i++) {
            if (inputWord[i] == guess) {
                current->data = guess;
                found = 1;
            }
            current = current->next;
        }

        if (!found) {
            attemptsLeft--;
            printf("Incorrect guess!\n");
        } else {
            printf("Correct guess!\n");
        }

        allLettersGuessed = 1;
        current = guessedWord;
        while (current != NULL) {
            if (current->data == '_') {
                allLettersGuessed = 0;
                break;
            }
            current = current->next;
        }

        if (allLettersGuessed) {
            printf("Congratulations! You guessed the word: %s\n", inputWord);
            getch();
            break;
        }
    }

    if (attemptsLeft == 0) {
        printf("Sorry, you've run out of attempts. The word was: %s\n", inputWord);
        getch();
    }

    struct Node *current = guessedWord;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}
