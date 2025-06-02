#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int machine;
    int time;
} Operation;

typedef struct {
    Operation *ops;        // array of operations
    int *op_start_times;   // start times for each op
    int P;                 // number of operations
    int next_op;           // index of next op to schedule
    int finish_time;       // finish time of last op
} Job;

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) {
        fprintf(stderr, "Failed to read N and M\n");
        return 1;
    }

    Job *jobs = malloc(M * sizeof(Job));
    for (int i = 0; i < M; i++) {
        int P;
        scanf("%d", &P);
        jobs[i].P = P;
        jobs[i].next_op = 0;
        jobs[i].finish_time = 0;
        jobs[i].ops = malloc(P * sizeof(Operation));
        jobs[i].op_start_times = calloc(P, sizeof(int));
        for (int j = 0; j < P; j++) {
            scanf("%d %d",
                  &jobs[i].ops[j].machine,
                  &jobs[i].ops[j].time);
        }
    }

    // Track when each machine becomes available
    int *machine_available = calloc(N, sizeof(int));

    // Total number of operations across all jobs
    int total_ops = 0;
    for (int i = 0; i < M; i++) {
        total_ops += jobs[i].P;
    }

    // Schedule each operation one at a time
    for (int step = 0; step < total_ops; step++) {
        int sel_job = -1;
        int sel_finish = INT_MAX;

        // Find the job whose next operation will finish earliest
        for (int i = 0; i < M; i++) {
            Job *job = &jobs[i];
            if (job->next_op >= job->P) continue;

            Operation *op = &job->ops[job->next_op];
            int machine = op->machine;
            int dur     = op->time;

            int prev_finish = 0;
            if (job->next_op > 0) {
                Operation *prev_op = &job->ops[job->next_op - 1];
                prev_finish = job->op_start_times[job->next_op - 1]
                              + prev_op->time;
            }

            int start  = machine_available[machine] > prev_finish
                           ? machine_available[machine]
                           : prev_finish;
            int finish = start + dur;

            // select lowest finish time (tie break by smaller job index)
            if (finish < sel_finish ||
               (finish == sel_finish && (sel_job < 0 || i < sel_job))) {
                sel_finish = finish;
                sel_job    = i;
            }
        }

        // Actually schedule the selected operation
        Job *job = &jobs[sel_job];
        Operation *op = &job->ops[job->next_op];
        int machine = op->machine;
        int dur     = op->time;

        int prev_finish = 0;
        if (job->next_op > 0) {
            Operation *prev_op = &job->ops[job->next_op - 1];
            prev_finish = job->op_start_times[job->next_op - 1]
                          + prev_op->time;
        }

        int start = machine_available[machine] > prev_finish
                      ? machine_available[machine]
                      : prev_finish;
        int finish = start + dur;

        machine_available[machine] = finish;
        job->op_start_times[job->next_op] = start;
        job->next_op++;
        if (job->next_op == job->P) {
            job->finish_time = finish;
        }
    }

    // Sum of all job finish times
    long long total = 0;
    for (int i = 0; i < M; i++) {
        total += jobs[i].finish_time;
    }
    printf("%lld\n", total);

    // Cleanup
    for (int i = 0; i < M; i++) {
        free(jobs[i].ops);
        free(jobs[i].op_start_times);
    }
    free(jobs);
    free(machine_available);

    return 0;
}
