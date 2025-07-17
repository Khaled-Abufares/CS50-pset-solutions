#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("key must contain 26 characters\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("key must contain only alphabetic characters\n");
            return 1;
        }
        for (int j = i + 1; j < 26; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("key must not contain repeated characters\n");
                return 1;
            }
        }
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            if (isupper(c))
            {
                int index = c - 'A';
                printf("%c", toupper(key[index]));
            }
            else
            {
                int index = c - 'a';
                printf("%c", tolower(key[index]));
            }
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}
