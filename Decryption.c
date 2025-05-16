#include <stdio.h>
#include <string.h>

int main()
{
    int shift = 3;
    int i = 0;
    char temp [100];
    FILE *fptr;
    fptr = fopen("Password.txt", "r");
    fgets(temp, 100, fptr);
    fclose(fptr);

    //decrypt temp
    while (temp[i] != '\0')
    {
        char c = temp[i];

        if(c >= 'a' && c <= 'z')
        {
            temp[i] = ((c - 'a' - shift + 26) %26); + 'a'
        } else if(c >= 'A' && c <= 'Z')
        {
            temp[i] = ((c - 'A' - shift + 26) %26) + 'A';
        }

        i++;
    }

    printf("%s", temp);
    return 0;
}