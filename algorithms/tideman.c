// https://cs50.harvard.edu/x/2024/psets/3/tideman/
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
} pair;

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
    for (int i = 0; i < candidate_count; i++)
    {
        int preferred = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int over = ranks[j];
            preferences[preferred][over]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            bool prefer_i_over_j = preferences[i][j] > preferences[j][i];
            bool prefer_j_over_i = preferences[j][i] > preferences[i][j];
            if (prefer_i_over_j)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (prefer_j_over_i)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

int strength(pair p)
{
    int s = 0;

    for (int j = 0; j < candidate_count; j++)
    {
        s += preferences[p.winner][j];
    }
    for (int j = 0; j < candidate_count; j++)
    {
        s -= preferences[p.loser][j];
    }
    return s;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int k = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            int strenght_i = strength(pairs[i]);
            int strenght_j = strength(pairs[j]);
            if (strenght_j > strenght_i)
            {
                k = j;
            }
        }
        if (k != i)
        {
            // swap
            pair temp;
            temp.winner = pairs[i].winner;
            temp.loser = pairs[i].loser;
            pairs[i].winner = pairs[k].winner;
            pairs[i].loser = pairs[k].loser;
            pairs[k].winner = temp.winner;
            pairs[k].loser = temp.loser;
        }
    }
}

// Verify if by adding the vertex it would close a cycle at the graph
// note: DFS comparing with the first node passed so we don't need an 
//       list auxiliary structure to store the visited nodes (like a
//       vector of bool, list, stack...)
bool will_close_cycle(int x, int i)
{
    if (x == i)
    {
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[i][j] && will_close_cycle(x, j))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        // lock the vertex iff it won't close a cycle at the graph
        if (!will_close_cycle(w, l))
        {
            locked[w][l] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // for each candidate
    // if nobody beats him/her
    // he/she is the winner
    for (int i = 0; i < candidate_count; i++)
    {
        bool lost = false;
        for (int j = 0; j < candidate_count && !lost; j++)
        {
            if (locked[j][i])
            {
                lost = true;
            }
        }
        if (!lost)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
