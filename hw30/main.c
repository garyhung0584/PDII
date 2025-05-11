#include <stdio.h>
#include <string.h>
// #include <stdlib.h> // Not strictly necessary for this problem

// Provided Union and Struct definitions
typedef enum { OUT, BASE_HIT } play_type_t;

typedef union {
    int base_hit; // 1~4: number of bases
    char out_kind; // 'F', 'S', 'G'
} play_result_t;

typedef struct {
    play_type_t type;
    play_result_t result;
} play_t;

typedef struct {
    int no; // Number of at-bats for this player
    play_t data[5]; // At-bat results for this player
} basePlayer_t;

// Global array to store data for 9 players
basePlayer_t players_data[9];
// Array to keep track of the current at-bat index for each player
int player_at_bat_counters[9];

int main() {
    // Read input for all 9 players
    for (int i = 0; i < 9; ++i) {
        scanf("%d", &players_data[i].no);
        player_at_bat_counters[i] = 0; // Initialize at-bat counter for this player

        for (int j = 0; j < players_data[i].no; ++j) {
            char play_str[3]; // Max 2 chars for play string (e.g., "1B", "HR") + null terminator
            scanf("%s", play_str);

            if (strcmp(play_str, "1B") == 0) {
                players_data[i].data[j].type = BASE_HIT;
                players_data[i].data[j].result.base_hit = 1;
            } else if (strcmp(play_str, "2B") == 0) {
                players_data[i].data[j].type = BASE_HIT;
                players_data[i].data[j].result.base_hit = 2;
            } else if (strcmp(play_str, "3B") == 0) {
                players_data[i].data[j].type = BASE_HIT;
                players_data[i].data[j].result.base_hit = 3;
            } else if (strcmp(play_str, "HR") == 0) {
                players_data[i].data[j].type = BASE_HIT;
                players_data[i].data[j].result.base_hit = 4;
            } else if (strcmp(play_str, "FO") == 0) {
                players_data[i].data[j].type = OUT;
                players_data[i].data[j].result.out_kind = 'F';
            } else if (strcmp(play_str, "SO") == 0) {
                players_data[i].data[j].type = OUT;
                players_data[i].data[j].result.out_kind = 'S';
            } else if (strcmp(play_str, "GO") == 0) {
                players_data[i].data[j].type = OUT;
                players_data[i].data[j].result.out_kind = 'G';
            }
        }
    }

    int target_total_outs;
    scanf("%d", &target_total_outs);

    // Initialize game state
    int current_score = 0;
    int current_total_outs = 0;
    // on_base[0] for 1st base, on_base[1] for 2nd, on_base[2] for 3rd. 1 if occupied, 0 if empty.
    int on_base[3] = {0, 0, 0};

    int current_batter_turn_idx = 0; // Global turn index to cycle through players

    // Game simulation loop
    while (current_total_outs < target_total_outs) {
        // Determine current player based on batting order
        int player_array_idx = current_batter_turn_idx % 9;

        // Get the current play for this player
        play_t current_play = players_data[player_array_idx].data[player_at_bat_counters[player_array_idx]];
        // Increment the at-bat counter for this player for their next turn
        player_at_bat_counters[player_array_idx]++;

        if (current_play.type == OUT) {
            current_total_outs++;
            // If 3 outs are reached (or a multiple of 3), clear bases
            // current_total_outs will be > 0 here if it's a multiple of 3 due to an out occurring
            if (current_total_outs % 3 == 0) {
                on_base[0] = 0;
                on_base[1] = 0;
                on_base[2] = 0;
            }
        } else { // BASE_HIT
            int k_bases = current_play.result.base_hit;
            int temp_on_base[3] = {0, 0, 0}; // Temporary array for next base state

            // Advance existing runners. Iterate from 3rd base down to 1st.
            // This order is crucial: if runners move simultaneously, we calculate their new positions
            // based on their old positions and store in temp_on_base to avoid interference.
            for (int i = 2; i >= 0; --i) { // i = 2 (3rd base), 1 (2nd base), 0 (1st base)
                if (on_base[i] == 1) { // If a runner is on base (i.e., base i+1)
                    int current_base_num_actual = i + 1; // Actual base number (1, 2, or 3)
                    int new_base_num_actual = current_base_num_actual + k_bases;

                    if (new_base_num_actual >= 4) { // Runner scores
                        current_score++;
                    } else { // Runner advances to a new base (1-indexed: 1, 2, or 3)
                        temp_on_base[new_base_num_actual - 1] = 1; // Mark new base as occupied
                    }
                }
            }

            // Advance the batter. Batter starts at home (conceptual base 0).
            int batter_new_base_num_actual = k_bases; // Batter moves k_bases from home.

            if (batter_new_base_num_actual >= 4) { // Batter scores (e.g., HR)
                current_score++;
            } else { // Batter lands on a base (1-indexed: 1, 2, or 3)
                temp_on_base[batter_new_base_num_actual - 1] = 1; // Mark batter's new base
            }

            // Update the actual on_base state from temp_on_base
            on_base[0] = temp_on_base[0];
            on_base[1] = temp_on_base[1];
            on_base[2] = temp_on_base[2];
        }

        // Move to the next batter in the order
        current_batter_turn_idx++;
    }

    // Output the total score when target_total_outs is reached
    printf("%d\n", current_score);

    return 0;
}
