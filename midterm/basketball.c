#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char name;
    int scores;
    int wins;
} Team;

void AddWins(Team teams[], char team){
    for(int i = 0; i < 3; i++){
        if(teams[i].name == team){
            teams[i].wins++;
            break;
        }
    }
}
void AddScore(Team teams[], char team, int score){
    for(int i = 0; i < 3; i++){
        if(teams[i].name == team){
            teams[i].scores += score;
            break;
        }
    }
}


int main()
{
    int m;
    Team teams[3] = {{'A', 0, 0}, {'B', 0, 0}, {'C', 0, 0} };

    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        char t1,t2;
        int score1 = 0, score2 = 0;
        scanf(" %c %c", &t1, &t2);

        for (int j = 0; j < 4; j++){
            int s1, s2;
            scanf("%d %d", &s1, &s2);
            score1 += s1;
            score2 += s2;
        }
        AddScore(teams, t1, score1);
        AddScore(teams, t2, score2);

        if (score1 > score2){
            AddWins(teams, t1);
        } else {
            AddWins(teams, t2);
        }
    }
    Team bestTeam = teams[0];
    for (int i = 0; i < 3; i++){
            if (teams[i].wins > bestTeam.wins){
                bestTeam = teams[i];
            }
    }

    printf("%c %d", bestTeam.name, bestTeam.scores);

    return 0;
}
