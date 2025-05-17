#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Trim and lowercase a string (used internally, not shown anymore)
void to_lower_trim(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!isspace((unsigned char)str[i])) {
            str[j++] = tolower((unsigned char)str[i]);
        }
        i++;
    }
    str[j] = '\0';
}

int main ()
{
    char choice;
    char word[100];
    char login[100];

    printf("Do you want to crack the password? (y/n): ");
    scanf(" %c", &choice);
    fflush(stdin); // Clear leftover newline

    // Load original plaintext
    FILE *fptr1 = fopen("PlainText.txt", "r");
    if (fptr1 == NULL) {
        perror("Error opening PlainText.txt");
        return 1;
    }
    fgets(login, sizeof(login), fptr1);
    fclose(fptr1);
    login[strcspn(login, "\n")] = 0;  // Remove newline

    // Prepare cleaned version for comparison
    char loginCleaned[100];
    strcpy(loginCleaned, login);
    to_lower_trim(loginCleaned);

    if (choice == 'y' || choice == 'Y') 
    {
        FILE *fptr = fopen("Password.txt", "r");
        if (fptr == NULL) {
            perror("Error opening Password.txt");
            return 1;
        }

        fgets(word, sizeof(word), fptr);
        fclose(fptr);
        word[strcspn(word, "\n")] = 0;  // Remove newline

        printf("🔐 Encrypted word from file: %s\n\n", word);

        int found = 0;
        char correctMatch[100];

        for (int shift = 1; shift < 26; shift++) {
            char decrypted[100];
            int i = 0;

            while (word[i] != '\0') {
                char c = word[i];
                if (c >= 'a' && c <= 'z') {
                    decrypted[i] = ((c - 'a' - shift + 26) % 26) + 'a';
                } else if (c >= 'A' && c <= 'Z') {
                    decrypted[i] = ((c - 'A' - shift + 26) % 26) + 'A';
                } else {
                    decrypted[i] = c;
                }
                i++;
            }
            decrypted[i] = '\0';

            char decryptedCleaned[100];
            strcpy(decryptedCleaned, decrypted);
            to_lower_trim(decryptedCleaned);

            printf("🔁 Trying shift %2d: %s\n", shift, decrypted);

            if (strcmp(decryptedCleaned, loginCleaned) == 0) {
                found = 1;
                strcpy(correctMatch, decrypted);
                break;
            }
        }

        if (found) {
            printf("\n✅ Match found! Decrypted password: %s\n", correctMatch);
        } else {
            printf("\n❌ No match found.\n");
        }

    } else {
        printf("Cracking skipped.\n");
    }

    return 0;
}
