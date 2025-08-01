#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int compute_score(string word);
int main(void)
{
    string word1 = get_string("player 1: ");
    string word2 = get_string("player 2: ");
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    if (score1 > score2)
    {
        printf("player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
int compute_score(string word)
{
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {
            char lower = tolower(word[i]);
            int index = lower - 'a';
            score += POINTS[index];
        }
    }

    return score;
}
