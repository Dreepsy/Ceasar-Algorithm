#include <stdio.h>
#include <string.h>

int main()
{
    char word [100];
    int shift;     //ceaser cipher shift amount
    int i = 0;

    printf("please select the shift size: \n" );
    scanf("%d", &shift);
    fflush(stdout);

    while (getchar() != '\n');


    //creation of shift file
    FILE *fptr2;
    fptr2 = fopen("Encryption.txt", "w");
    fprintf(fptr2, "%d", shift);
    fclose(fptr2);


    //creation of a file
    FILE *fptr;
    fptr = fopen("Password.txt", "w");

    //exception handling if file couldnt be created
    if(fptr == NULL)
    {
        perror("Error opening file");
        return -1;
    }


    printf("Please enter a phrase: \n");
    fflush(stdout);
    fgets(word, 100, stdin);
    

    //encrypting the user input
    while(word[i] != '\0')      //as long as word[i] is not at the end do.... '\0' tells the end of the array in C
    {
        char c = word[i];

        if(c >= 'a' && c <= 'z')
        {
            word[i] = ((c - 'a' + shift) %26) + 'a';
        } else if(c >= 'A' && c <= 'Z')
        {
            word[i] = ((c - 'A' + shift) %26) + 'A';
        }

        i++;
    }

    fprintf(fptr, "%s", word);
    fclose(fptr);
    printf("Encrypted phrase: %s\n", word);

    return 0;
}