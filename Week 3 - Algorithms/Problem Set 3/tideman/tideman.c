#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_path(int source, int dest);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (i == ranks[k])
                {
                    preferences[i][j] += 1;
                    break;
                }
                if (j == ranks[k])
                {
                    preferences[j][i] += 1;
                    break;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair tmpPair;
                tmpPair.winner = i;
                tmpPair.loser = j;

                pairs[pair_count] = tmpPair;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pair tmpPair;
                tmpPair.winner = j;
                tmpPair.loser = i;

                pairs[pair_count] = tmpPair;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] \
                < preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner])
            {
                pair tmpPair;
                tmpPair.winner = pairs[j].winner;
                tmpPair.loser = pairs[j].loser;

                pairs[j] = pairs[j + 1];
                pairs[j + 1] = tmpPair;
            }
        }
    }

    // for (int i=0; i<pair_count; i++)
    // {
    //     printf("%i\n", i);
    //     printf("%s\n", candidates[pairs[i].winner]);
    //     printf("%s\n", candidates[pairs[i].loser]);
    //     printf("vic %i\n", preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
    // }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_path(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    // for (int i=0; i<MAX; i++){
    //     for (int j=0; j<MAX; j++){
    //         printf("%i ", locked[i][j]);
    //     }
    //     printf("\n");
    // }
    // return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool flag = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                flag = false;
                break;
            }
        }

        if (flag)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}

bool is_path(int source, int dest)
{
    if (locked[source][dest] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[source][i] == true)
        {
            // WRONG: return is_path(i, dest);
            // if false, cannot dive into next loop

            if (is_path(i, dest))
            {
                return true;
            }
        }
    }
    return false;
}