#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THRESHOLD 1.0   // Threshold for neuron firing
#define LEAK_RATE 0.1  // Leak rate for membrane potential
#define RESET_V 0.0     // Reset potential after neuron fires

// Weights for different questions
#define WEIGHT_QUESTION_1 1.0
#define WEIGHT_QUESTION_2 1.2
#define WEIGHT_QUESTION_3 1.5
#define WEIGHT_QUESTION_4 1.1
#define WEIGHT_QUESTION_5 1.0

// LeakyIntegrate-Fire Neuron model
typedef struct {
    float membrane_potential; // Current membrane potential
    int fired;                // Whether the neuron fired
} LIFNeuron;

// Initialize neuron
void init_neuron(LIFNeuron *neuron) {
    neuron->membrane_potential = 0.0;
    neuron->fired = 0;
}

// Update neuron state based on input
void update_neuron(LIFNeuron *neuron, float input) {
    if (neuron->fired) {
        neuron->membrane_potential = RESET_V; // Reset after firing
    } else {
        neuron->membrane_potential += input - LEAK_RATE; // Integrate input and leak
    }

    if (neuron->membrane_potential >= THRESHOLD) {
        neuron->fired = 1; // Fire the neuron
    }
}

// Logical gate functions using LIF neurons

// AND gate (both inputs must fire for output)
int lif_and(int input1, int input2) {
    LIFNeuron n1, n2, output;
    init_neuron(&n1);
    init_neuron(&n2);
    init_neuron(&output);

    update_neuron(&n1, input1);
    update_neuron(&n2, input2);
    
    update_neuron(&output, n1.fired && n2.fired ? 1.0 : 0.0);
    return output.fired;
}

// OR gate (either input can fire for output)
int lif_or(int input1, int input2) {
    LIFNeuron n1, n2, output;
    init_neuron(&n1);
    init_neuron(&n2);
    init_neuron(&output);

    update_neuron(&n1, input1);
    update_neuron(&n2, input2);
    
    update_neuron(&output, n1.fired || n2.fired ? 1.0 : 0.0);
    return output.fired;
}

// NAND gate (negation of AND gate)
int lif_nand(int input1, int input2) {
    return !lif_and(input1, input2);
}

// NOT gate (inverts input)
int lif_not(int input) {
    return !input;
}

// Simulate Quantum Superposition using Hadamard Gate (H)
int hadamard_gate_adjusted(int input) {
    float prob = rand() % 100 / 100.0;  // Generate a random float between 0 and 1

    if (input == 2) { // If user answered YES
        if (prob < 0.7) {
            return 0;  // 70% chance to return Yes
        } else {
            return 1;  // 30% chance to return Confused
        }
    }
    else if (input == 1) { // If user answered Confused
        if (prob < 0.5) {
            return 1;  // 50% chance to return Confused
        } else {
            return 2;  // 50% chance to return No
        }
    }
    else { // If user answered NO
        return 2; // Return No
    }
}

// Simulate Quantum Entanglement using CNOT Gate (controlled-NOT)
int cnot_gate(int control, int target) {
    return (control == 1) ? !target : target;
}

// Probabilistic decision-making based on weighted sum of answers
int probabilistic_decision(int q1, int q2, int q3, int q4, int q5) {
    // Calculate the weighted sum of the inputs
    float weighted_sum = q1 * WEIGHT_QUESTION_1 + q2 * WEIGHT_QUESTION_2 +
                         q3 * WEIGHT_QUESTION_3 + q4 * WEIGHT_QUESTION_4 + 
                         q5 * WEIGHT_QUESTION_5;

    // Determine the outcome based on the weighted sum
    if (weighted_sum > 8) {  // High confidence for YES
        return 0; // Yes
    } else if (weighted_sum > 3) {  // Moderate confidence for Confused
        return 1; // Confused
    } else {  // Low confidence for NO
        return 2; // No
    }
}

// Main function for user input and decision-making
int main() {
    int q1, q2, q3, q4, q5;

    srand(time(NULL));  // Initialize random seed for simulating quantum behavior

    // Ask user for answers to questions
    printf("Question 1: Is this decision aligned with my long-term goals and values? (0 for NO, 1 for Confused, 2 for YES): ");
    scanf("%d", &q1);

    printf("Question 2: Have I considered the possible positive and negative outcomes of this decision? (0 for NO, 1 for Confused, 2 for YES): ");
    scanf("%d", &q2);

    printf("Question 3: Am I feeling emotionally calm and clear-headed about this decision? (0 for NO, 1 for Confused, 2 for YES): ");
    scanf("%d", &q3);

    printf("Question 4: Is this decision reversible or flexible, or is it a one-time decision? (0 for NO, 1 for Confused, 2 for YES): ");
    scanf("%d", &q4);

    printf("Question 5: Have I allowed myself enough time to think through this decision carefully? (0 for NO, 1 for Confused, 2 for YES): ");
    scanf("%d", &q5);

    // Apply decision-making logic using quantum-inspired LIF neurons and probabilistic decision
    int final_decision = probabilistic_decision(q1, q2, q3, q4, q5);

    if (final_decision == 0) {
        printf("Recommended decision: YES\n");
    } else if (final_decision == 1) {
        printf("Recommended decision: Confused (Quantum Superposition)\n");
        printf("Take a break and reconsider.\n");
    } else {
        printf("Recommended decision: NO\n");
    }

    return 0;
}
