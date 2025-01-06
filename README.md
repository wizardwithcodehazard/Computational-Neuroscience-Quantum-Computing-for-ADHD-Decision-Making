# Computational Neuroscience + Quantum Computing for ADHD Decision-Making

This project combines computational neuroscience, quantum computing, and probabilistic decision-making to help individuals with ADHD (Attention-Deficit/Hyperactivity Disorder) make decisions more effectively. By utilizing a Leaky Integrate-and-Fire (LIF) neuron model and quantum-inspired gates, this project simulates cognitive decision-making processes, helping to simulate impulsivity and ADHD-like behaviors while also offering a probabilistic framework to improve decision accuracy.

## Project Overview

The project is designed to simulate decision-making in individuals with ADHD by integrating the following:

- **Computational Neuroscience**: Using a Leaky Integrate-and-Fire (LIF) neuron model to simulate decision-making and cognitive processes.
- **Quantum Computing**: Implementing quantum-inspired gates such as the Hadamard and CNOT gates to simulate quantum superposition and entanglement in decision-making.
- **Probabilistic Decision-Making**: Using a weighted sum of user responses to make decisions based on the input provided, simulating cognitive processes and offering recommendations.

The goal of this project is to provide a foundational model that can be extended to real-time decision-making systems for ADHD patients, with potential applications in therapy, decision assistance, and behavioral studies.

## Features

- **Leaky Integrate-and-Fire Neuron Model**: Simulates how neurons integrate inputs over time and fire once the membrane potential exceeds a threshold. This model is used to simulate logical operations (AND, OR, NAND, NOT gates).
- **Quantum-Inspired Gates**: Simulates quantum behaviors such as superposition and entanglement using Hadamard and CNOT gates.
- **Weighted Probabilistic Decision-Making**: Uses weighted answers to five questions to calculate a weighted sum and recommend a decision (YES, Confused, or NO).
- **Interactive Decision Flow**: Users answer questions, and based on their responses, the system provides a decision recommendation.

## How It Works

1. **Leaky Integrate-and-Fire (LIF) Neurons**: LIF neurons accumulate input over time and "fire" when their membrane potential exceeds a set threshold. The system uses these neurons to simulate logical operations (AND, OR, NAND, NOT).
2. **Quantum-Inspired Gates**: Using quantum-like behavior, the Hadamard gate introduces a probabilistic approach to decisions by applying superposition and the CNOT gate allows entanglement, influencing the output based on the user's prior input.
3. **Probabilistic Decision-Making**: The project calculates a weighted sum based on five user-provided answers to decision-related questions. This sum determines the recommendation (YES, Confused, or NO).

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/wizardwithcodehazard/Computational-Neuroscience-Quantum-Computing-for-ADHD-Decision-Making.git
   cd Computational-Neuroscience-Quantum-Computing-for-ADHD-Decision-Making
   ```

2. Compile the C code:
   ```bash
   gcc -o adhd.c
   ```

3. Run the program:
   ```bash
   ./adhd
   ```

## Usage

Upon running the program, users will be prompted to answer five questions related to a decision they are trying to make. Each answer is weighted and contributes to the final decision-making process.

Example questions:
- Is this decision aligned with my long-term goals and values?
- Have I considered the possible positive and negative outcomes of this decision?
- Am I feeling emotionally calm and clear-headed about this decision?
- Is this decision reversible or flexible, or is it a one-time decision?
- Have I allowed myself enough time to think through this decision carefully?

Based on the weighted sum of answers, the system will provide one of the following recommendations:
- **YES**: The decision is considered a good choice.
- **Confused**: The system is unsure, and the user should take a break and reconsider.
- **NO**: The decision is not recommended.

## Contributing

We welcome contributions to improve this project, especially in the following areas:

- Integrating more sophisticated machine learning models to improve decision-making accuracy.
- Expanding the probabilistic decision-making model with additional inputs and factors.
- Incorporating more advanced quantum algorithms and neuroscience models.

To contribute, please follow the steps below:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

- This project was inspired by research in computational neuroscience, quantum computing, and decision theory.
- Special thanks to the open-source community for providing tools and resources for neuroscience modeling and quantum computing.

# Code Explanation
### 1. **Includes and Definitions**

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
```

- `stdio.h`: This header provides standard input/output functions like `printf` (to display output) and `scanf` (to take user input).
- `stdlib.h`: This library contains functions such as `rand()` for generating random numbers, which we'll use later for simulating quantum behavior.
- `time.h`: Provides functions like `time()`, which is used to seed the random number generator for the quantum-like randomness in our decision-making system.

```c
#define THRESHOLD 1.0   // Threshold for neuron firing
#define LEAK_RATE 0.1   // Leak rate for membrane potential
#define RESET_V 0.0     // Reset potential after neuron fires
```

- `THRESHOLD`: The membrane potential must exceed this value for a neuron to fire. It represents the point at which the neuron becomes active.
- `LEAK_RATE`: Simulates the "leak" in a neuron’s membrane potential. Over time, the membrane potential gradually decreases if the neuron isn't receiving stimuli.
- `RESET_V`: After the neuron fires, its membrane potential is reset to this value, simulating the neuron returning to an "inactive" state.

```c
#define WEIGHT_QUESTION_1 1.0
#define WEIGHT_QUESTION_2 1.2
#define WEIGHT_QUESTION_3 1.5
#define WEIGHT_QUESTION_4 1.1
#define WEIGHT_QUESTION_5 1.0
```

- These constants represent the **weights** assigned to each of the five input questions. Each question has a different weight, meaning some questions are more important than others when calculating the final decision.

---

### 2. **LIFNeuron Struct**

```c
typedef struct {
    float membrane_potential; // Current membrane potential
    int fired;                // Whether the neuron fired
} LIFNeuron;
```

- This `LIFNeuron` struct represents a single **Leaky Integrate-and-Fire neuron**.
- `membrane_potential`: This is the current value of the neuron's membrane potential, which accumulates over time as the neuron receives input.
- `fired`: A boolean flag that indicates whether the neuron has fired (reached the threshold). If this value is `1`, the neuron has fired; if it's `0`, it hasn't.

---

### 3. **init_neuron Function**

```c
void init_neuron(LIFNeuron *neuron) {
    neuron->membrane_potential = 0.0;
    neuron->fired = 0;
}
```

- This function **initializes** a neuron by setting its membrane potential to `0.0` and marking it as not fired (`fired = 0`).
- This is the starting state for each neuron before it starts processing any input.

---

### 4. **update_neuron Function**

```c
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
```

- This function simulates the process of updating the neuron's membrane potential.
- If the neuron has already fired, its potential is reset to `RESET_V`.
- If the neuron hasn't fired yet, it **integrates** the input (i.e., the input value is added to the membrane potential) and accounts for the leakage by subtracting `LEAK_RATE`.
- If the membrane potential exceeds the `THRESHOLD`, the neuron **fires**, and its `fired` flag is set to `1`.

---

### 5. **Logical Gates Using LIF Neurons**

The functions `lif_and`, `lif_or`, `lif_nand`, and `lif_not` represent **logical gates** simulated using LIF neurons. These gates use the binary inputs (0, 1, or 2) to calculate an output.

- **AND Gate**: The output will fire only if both inputs fire.
- **OR Gate**: The output will fire if at least one of the inputs fires.
- **NAND Gate**: This is the negation of the AND gate (it fires if both inputs don’t fire).
- **NOT Gate**: The output will fire if the input doesn't fire (it inverts the input).

These gates are based on the behavior of LIF neurons but simulate basic logical operations.

---

### 6. **Quantum-Inspired Functions**

#### Hadamard Gate (`hadamard_gate_adjusted`)

```c
void hadamard_gate_adjusted(float *input) {
    *input = (*input == 2) ? 1.5 : (*input == 1) ? 2 : 0;
}
```

- The **Hadamard Gate** applies a **quantum-like transformation** to an input (e.g., a decision such as YES, Confused, or NO). It alters the probability of the decision outcome, simulating quantum **superposition**.

#### CNOT Gate (`cnot_gate`)

```c
void cnot_gate(int *control_bit, int *target_bit) {
    if (*control_bit == 1) {
        *target_bit = !(*target_bit);
    }
}
```

- The **CNOT (Controlled-NOT) Gate** is a basic **quantum gate** that applies a conditional operation: if the **control bit** is `1`, it inverts the **target bit**. This simulates quantum **entanglement**.

---

### 7. **probabilistic_decision Function**

```c
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
```

- This function calculates a **weighted sum** of the user's answers to five questions, with each question having a specific weight.
- If the sum is above a certain threshold, the decision is `YES`, indicating a high confidence level.
- If the sum is moderate, the system returns `Confused`, simulating quantum uncertainty.
- If the sum is low, the recommendation is `NO`, indicating low confidence in the decision.

---

### 8. **Main Function**

```c
int main() {
    int q1, q2, q3, q4, q5;

    srand(time(NULL));  // Initialize random seed for simulating quantum behavior

    // Ask user for answers to questions
    printf("Question 1: Is this decision aligned with my long-term goals and values? (0 for NO, 1 for Confused, 2 for YES): ");
    scanf("%d", &q1);
    // Repeat for other questions (q2, q3, q4, q5)
    
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
```

- This is the **entry point** of the program. It prompts the user to answer five questions, each representing a decision criterion.
- The user’s answers are processed using the **probabilistic decision-making** logic to produce a final recommendation.
- The program utilizes **quantum-inspired** logic and decision-making algorithms to produce outcomes like **YES**, **Confused**, or **NO**.
