# Game of Life – C Implementation

This project simulates **Conway's Game of Life** using different strategies in C, each implemented as a separate task. It supports matrix evolution using classical rules, stack-based tracking, and binary tree expansion.
Details: https://site-pa.netlify.app/proiecte/game_of_life/

## Features

- Handles matrix-based simulation of life and death of cells.
- Supports **3 distinct evolution strategies**:
  - Task 1: Classic generation evolution (Rule A)
  - Task 2: Stack-based storage of modified cells
  - Task 3: Binary tree of evolving states using Rule A and Rule B
- Efficient use of dynamic memory and custom data structures.
- Input and output through files.
- Fully written in portable C (C99+).

---

## ✅ Task 1: Classic Evolution (Rule A)

Simulates the Game of Life by applying the standard rules (Rule A) over `k` generations.

### Description

For each generation:
- Apply classic Conway rules.
- Update matrix in-place.
- Write the current matrix state to the output file.

### Example Output

```
+++++
++X++
+++X+
+XXX+
+++++

+++++
+++++
+X+X+
++XX+
++X+

...
```

---

## 📦 Task 2: Stack of Modifications

Tracks modified cells during each generation and stores them in a **stack**.

### Description

- At each generation, the coordinates of changed cells are stored in a list.
- The list is pushed onto a stack associated with the generation number.
- After all generations, the stack is printed in reverse chronological order.

### Example Output

```
3 1 2 2 3
2 1 3 3 3 4 2
1 1 1 2 2 1
```

---

## 🌳 Task 3: Binary Tree of Generations

Constructs a binary tree where:
- **Left subtree** applies Rule B (birth on exactly 2 neighbors).
- **Right subtree** applies Rule A (classic Game of Life rules).

### Description

- Initial state is the root.
- Each node branches into left (Rule B) and right (Rule A) child nodes.
- Recursively constructs the tree up to depth `k`.
- Matrix state is printed in preorder (DFS) traversal.

### Example Output (Preorder)

```
+++++
++X++
+++X+
+XXX+
+++++

+++++
+++++
+X+X+
++XX+
++X+

+++++
++X++
+X+X+
+XX++
+++++

...
```

---

## 🔧 Compilation

```bash
gcc task_1.c functii.c -o game_of_life
```

## ▶️ Usage

```bash
./game_of_life input.txt output.txt
```

### Input Format

```
<task_number>
<n> <m>
<k>
<initial matrix>
```

### Matrix Format

- Characters: `'X'` for alive, `'+'` for dead.
- Size: `n x m`

### Output

- For Task 1 and 3: Matrix states over generations.
- For Task 2: Stack dump with modified cell coordinates per generation.

---

## 🧱 Data Structures

```c
typedef struct List {
    int linie, coloana;
    struct List *next;
} List;

typedef struct Stack {
    int nr_gen;
    List *head;
    struct Stack *next;
} Stack;

typedef struct Tree {
    List *head;
    struct Tree *left, *right;
} Tree;
```

## 🔍 Task 4: Hamiltonian Path in Game of Life

Finds the **longest Hamiltonian path** among the living cells in the matrix after applying evolution rules.

### Description

- Builds a binary evolution tree as in Task 3 (Rule A and B branches).
- For each matrix, constructs an undirected graph:
  - Each **alive cell** is a node.
  - Edges exist between neighboring cells (max 8 directions).
- Finds the **largest connected component** and computes the longest Hamiltonian path inside it.
- The Hamiltonian path is printed as a list of coordinates.

### Example Output

```
3
(1,2) (2,3) (3,3)
```

- If no Hamiltonian path of length > 1 exists, output `-1`.

### Algorithm Notes

- Uses DFS to find the longest path visiting each cell once within the largest connected component.
- Backtracking and adjacency matrix representation for efficient traversal.

---

## 📄 License

This project is intended for educational and personal use.


---
