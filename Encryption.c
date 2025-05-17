#include <stdio.h>
#include <string.h>

int main()
{
    char word[100];
    int shift;
    int i = 0;

    printf("please select the shift size: \n" );
    scanf("%d", &shift);
    fflush(stdout);

    while (getchar() != '\n'); // clear input buffer

    printf("Please enter a phrase: \n");
    fflush(stdout);
    fgets(word, 100, stdin);

    // Save plain text before encrypting
    FILE *fptr1 = fopen("PlainText.txt", "w");
    if (fptr1 == NULL) {
        perror("Error opening PlainText.txt");
        return -1;
    }
    fprintf(fptr1, "%s", word);
    fclose(fptr1);

    // Save shift size (optional, unused by cracker)
    FILE *fptr2 = fopen("Encryption.txt", "w");
    fprintf(fptr2, "%d", shift);
    fclose(fptr2);

    // Encrypt the input
    i = 0;
    while(word[i] != '\0') {
        char c = word[i];

        if(c >= 'a' && c <= 'z') {
            word[i] = ((c - 'a' + shift) % 26) + 'a';
        } else if(c >= 'A' && c <= 'Z') {
            word[i] = ((c - 'A' + shift) % 26) + 'A';
        }
        i++;
    }

    // Save encrypted password
    FILE *fptr = fopen("Password.txt", "w");
    if(fptr == NULL) {
        perror("Error opening Password.txt");
        return -1;
    }

    fprintf(fptr, "%s", word);
    fclose(fptr);

    printf("Encrypted phrase: %s\n", word);

    return 0;
}
