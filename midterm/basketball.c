#include <stdio.h>
#include <string.h>

#define MAX_TEAMS 3

typedef struct {
    char name;
    int wins;
    int total_score;
} Team;

void update_team(Team teams[], char team, int score) {
    for (int i = 0; i < MAX_TEAMS; i++) {
        if (teams[i].name == team) {
            teams[i].wins++;
        }
    }
}

void update_score(Team teams[], char team, int score) {
    for (int i = 0; i < MAX_TEAMS; i++) {
        if (teams[i].name == team) {
            teams[i].total_score += score;
        }
    }
}

int main() {
    int M;
    scanf("%d", &M);

    Team teams[MAX_TEAMS] = { {'A', 0, 0}, {'B', 0, 0}, {'C', 0, 0} };

    for (int i = 0; i < M; i++) {
        char team1, team2;
        int score1 = 0, score2 = 0;

        scanf(" %c %c", &team1, &team2);

        for (int j = 0; j < 4; j++) {
            int s1, s2;
            scanf("%d %d", &s1, &s2);
            score1 += s1;
            score2 += s2;
        }

        update_score(teams, team1, score1);
        update_score(teams, team2, score2);

        if (score1 > score2) {
            update_team(teams, team1, score1);
        } else {
            update_team(teams, team2, score2);
        }
    }

    Team *best_team = &teams[0];
    for (int i = 1; i < MAX_TEAMS; i++) {
        if (teams[i].wins > best_team->wins) {
            best_team = &teams[i];
        }
    }

    printf("%c %d\n", best_team->name, best_team->total_score);

    return 0;
}
