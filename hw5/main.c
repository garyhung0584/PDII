#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int rent;
    int free_inner_call, free_outer_call, free_landline_call;
    int free_inner_sms, free_outer_sms;
    double rate_inner_call, rate_outer_call, rate_landline_call;
    double rate_inner_sms, rate_outer_sms;
} Plan;

Plan plans[] = {
    {183, 500, 400, 300, 10, 15, 0.08, 0.1393, 0.1349, 1.1287, 1.4803},
    {383, 600, 500, 400, 20, 25, 0.07, 0.1304, 0.1217, 1.1127, 1.2458},
    {983, 700, 600, 500, 30, 35, 0.06, 0.1087, 0.1018, 0.9572, 1.1243}
};

void calculate_best_plan(int inner_call, int outer_call, int landline_call, int inner_sms, int outer_sms) {
    int best_cost = __INT_MAX__;
    int best_plan = -1;

    for (int i = 0; i < 3; i++) {
        Plan p = plans[i];

        double extra_inner_call = fmax(0, inner_call - p.free_inner_call) * p.rate_inner_call;
        double extra_outer_call = fmax(0, outer_call - p.free_outer_call) * p.rate_outer_call;
        double extra_landline_call = fmax(0, landline_call - p.free_landline_call) * p.rate_landline_call;
        double extra_inner_sms = fmax(0, inner_sms - p.free_inner_sms) * p.rate_inner_sms;
        double extra_outer_sms = fmax(0, outer_sms - p.free_outer_sms) * p.rate_outer_sms;

        int total_cost = (int)(extra_inner_call + extra_outer_call + extra_landline_call + extra_inner_sms + extra_outer_sms);
        int final_cost = total_cost > p.rent ? total_cost : p.rent;

        if (final_cost < best_cost) {
            best_cost = final_cost;
            best_plan = p.rent;
        }
    }

    printf("%d\n%d\n", best_cost, best_plan);
}

int main(){
    int insec, outsec, telsec, msg, outmsg;

    int bestFee, currentPlan;

    scanf("%d %d %d %d %d", &insec, &outsec, &telsec, &msg, &outmsg);

    calculate_best_plan(insec, outsec, telsec, msg, outmsg);



    return 0;
}
