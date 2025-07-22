//This project was completed with personal understanding, with the help of ChatGPT for clarifying concepts and organizing logic, and Copilot for speeding up the process through autocomplete assistance.
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define MAX 9
typedef struct
{
    int winner;
    int loser;
} pair;
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int preferences[MAX][MAX];
bool locked[MAX][MAX];
int pair_count;
int candidate_count;
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool creates_cycle(int winner, int loser);
void print_winner(void);
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
           //printf("Vote recorded for %s at rank %d\n", name, rank);
             ranks[rank] = i;
           return true;
         }

    }

         //printf("Invalid vote for %s at rank %d\n", name, rank);
            return false;

}
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        for (int j = i +1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            //printf("Preference recorded: %s over %s\n", candidates[ranks[i]], candidates[ranks[j]]);
        }
    }
}
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                //printf("Pair added: %s over %s\n", candidates[i], candidates[j]);
                pair_count++;
            }

        }
    }
}
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if ( !creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //printf("Locking pair: %s over %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }
    }
}
bool creates_cycle(int winner, int loser)
{
    if (loser == winner)
    {
        //printf("Cycle detected: %s cannot win against itself\n", candidates[winner]);
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (creates_cycle(winner, i))
            {
                //printf("Cycle detected: %s cannot win against %s\n", candidates[winner], candidates[i]);
                return true;
            }
        }
    }

        //printf("No cycle detected for pair: %s over %s\n", candidates[winner], candidates[loser]);
        return false;


}
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming_edge = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_incoming_edge = true;
                break;
            }
        }
        if (!has_incoming_edge)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
int main(int argc, string argv[])
{
    if (argc < 2)
    {
        //printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        //printf("Maximum number of candidates is %d\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }
    int voter_count = get_int("Number of voters: ");
    if (voter_count > MAX)
    {
        //printf("Maximum number of voters is %d\n", MAX);
        return 3;
    }
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];

    for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        record_preferences(ranks);
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int strength2 = preferences[pairs[j+1].winner][pairs[j+1].loser] - preferences[pairs[j+1].loser][pairs[j+1].winner];


            if (strength1 < strength2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

