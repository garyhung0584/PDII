#include <stdio.h>
#include <string.h>

#define GATEVALUE(Gate) int (*GateValue)(struct _Gate *)

typedef struct _Gate {
    int input1;
    int input2;
    GATEVALUE(Gate);
} Gate;

int trim3bit(int value) {
    return value & 0x7;
}

int GateNOTValue(Gate *gate) {
    return trim3bit(~gate->input1);
}

int GateBUFFERValue(Gate *gate) {
    return trim3bit(gate->input1);
}

int GateANDValue(Gate *gate) {
    return trim3bit(gate->input1 & gate->input2);
}

int GateORValue(Gate *gate) {
    return trim3bit(gate->input1 | gate->input2);
}

int GateNANDValue(Gate *gate) {
    return trim3bit(~(gate->input1 & gate->input2));
}

int GateNORValue(Gate *gate) {
    return trim3bit(~(gate->input1 | gate->input2));
}

void CreateGate(Gate *obj, const char *type, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;

    if (strcmp(type, "N") == 0) {
        obj->GateValue = GateNOTValue;
    } else if (strcmp(type, "B") == 0) {
        obj->GateValue = GateBUFFERValue;
    } else if (strcmp(type, "A") == 0) {
        obj->GateValue = GateANDValue;
    } else if (strcmp(type, "O") == 0) {
        obj->GateValue = GateORValue;
    } else if (strcmp(type, "NA") == 0) {
        obj->GateValue = GateNANDValue;
    } else if (strcmp(type, "NO") == 0) {
        obj->GateValue = GateNORValue;
    }
}

void printBinary3(int val) {
    for (int i = 2; i >= 0; i--) {
        printf("%d", (val >> i) & 1);
    }
    printf("\n");
}

int main() {
    int X1, X2, X3;
    char op1[3], op2[3], op3[3], op4[3], op5[3];

    scanf("%d %d %d", &X1, &X2, &X3);
    scanf("%s %s %s %s %s", op1, op2, op3, op4, op5);

    Gate g1, g2, g3;
    CreateGate(&g1, op1, X1, 0);
    CreateGate(&g2, op2, X2, 0);
    CreateGate(&g3, op3, X3, 0);

    int val1 = g1.GateValue(&g1);
    int val2 = g2.GateValue(&g2);
    int val3 = g3.GateValue(&g3);

    Gate g4;
    CreateGate(&g4, op4, val1, val2);
    int y = g4.GateValue(&g4);

    Gate g5;
    CreateGate(&g5, op5, y, val3);
    int output = g5.GateValue(&g5);

    printBinary3(output);
    return 0;
}
