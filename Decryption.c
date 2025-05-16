#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // For atoi()

int main()
{
    int shift;
    int i = 0;
    char temp[100];
    char shift_buffer[10];

    //import the encrypted word
    FILE *fptr = fopen("Password.txt", "r");
    if (fptr == NULL) {
        perror("Error opening Password.txt");
        return 1;
    }
    fgets(temp, 100, fptr);
    fclose(fptr);

    //import the shift value
    FILE *fptr2 = fopen("Encryption.txt", "r");
    if (fptr2 == NULL) {
        perror("Error opening Encryption.txt");
        return 1;
    }
    fgets(shift_buffer, 10, fptr2);
    fclose(fptr2);

    //convert shift string to integer
    shift = atoi(shift_buffer);

    //decrypt the message
    while (temp[i] != '\0')
    {
        char c = temp[i];

        if (c >= 'a' && c <= 'z') {
            temp[i] = ((c - 'a' - shift + 26) % 26) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            temp[i] = ((c - 'A' - shift + 26) % 26) + 'A';
        }

        i++;
    }

    printf("Decrypted phrase: %s\n", temp);
    return 0;
}
