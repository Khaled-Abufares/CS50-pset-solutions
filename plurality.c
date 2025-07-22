// Inspired by ChatGPT & Copilot – written after understanding.
#include<stdio.h>
#include<cs50.h>
#include<string.h>
#define max 9
bool vote(string name);
void print_winner(void);
int candidate_count;
typedef struct
    {
        string name;
        int votes;
    } candidate;
    candidate candidates[max];
int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > max)
    {
        printf("Maximum number of candidates is %d\n", max);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    int voter_count = get_int("Number of voters: ");
    for(int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    print_winner();

}
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}
void print_winner(void)
{
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == max_votes)
            {
                printf("%s\n", candidates[i].name);
            }
        }

}
