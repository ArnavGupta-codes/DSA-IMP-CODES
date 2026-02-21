# Data Structures & Algorithms — Complete Lecture Notes
**Lectures 1–15  |  CLRS 4th Edition**

---

## Table of Contents
1. [Insertion Sort](#1-insertion-sort)
2. [Asymptotic Notation](#2-asymptotic-notation)
3. [Merge Sort](#3-merge-sort)
4. [Substitution Method](#4-solving-recurrences--substitution-method)
5. [Master Theorem](#5-the-master-theorem)
6. [Quicksort](#6-quicksort--lectures-78)
7. [Randomized Algorithms](#7-randomized-algorithms--lectures-8-10)
8. [Linear Time Sorting](#8-sorting-in-linear-time--lectures-8-12)
9. [Linear Data Structures](#9-linear-data-structures--lecture-13)
10. [Binary Search Trees — Basics](#10-binary-search-trees--lectures-1314)
11. [Binary Search Trees — Advanced](#11-advanced-bst-topics--lecture-15)
12. [Quick Reference](#12-quick-reference--complexity-summary)

---

## 1. Insertion Sort

### Algorithm

Insertion Sort builds a sorted array one element at a time by inserting each new element into its correct position within the already-sorted portion.

```
for i = 2 to n:
    key = A[i]
    j = i - 1
    while j > 0 AND A[j] > key:
        A[j+1] = A[j]
        j = j - 1
    A[j+1] = key
```

### Loop Invariant

> **A[1 : i−1] is sorted at the start of each iteration of the outer loop.**

- **Initialization:** A[1:1] is trivially sorted (single element).
- **Maintenance:** If A[1:i−1] is sorted, after inserting A[i] into the correct position, A[1:i] is sorted.
- **Termination:** When i = n+1, A[1:n] is fully sorted.

### Time Complexity

Each line has a cost. Let $t_i$ = number of times the while-loop condition is checked for iteration $i$.

$$T(n) \leq C_1 n + (C_2+C_4)(n-1) + \sum_{i=2}^{n} C_5 t_i + (C_6+C_7)\sum_{i=2}^{n}(t_i-1) + C_8(n-1)$$

| Case | Condition | Complexity |
|------|-----------|------------|
| Best Case | Already sorted ($t_i = 1$ for all $i$) | $\Theta(n)$ |
| Worst Case | Reverse sorted ($t_i = i$ for all $i$) | $\Theta(n^2)$ |

> **Key result:** $T(n) \leq c_1^* \cdot n + c_2^* \cdot n^2 \Rightarrow T(n) = O(n^2)$

---

## 2. Asymptotic Notation

Asymptotic notation describes the growth rate of functions and classifies algorithm efficiency.

### Big-O — Upper Bound

$$O(g(n)) = \{f(n) \mid \exists\, c > 0,\, n_0 > 0,\; \forall n \geq n_0 : 0 \leq f(n) \leq c \cdot g(n)\}$$

$f(n) = O(g(n))$ means $g(n)$ is an asymptotic upper bound. $f$ never grows faster than $c \cdot g(n)$ for large $n$.

### Big-Omega — Lower Bound

$$\Omega(g(n)) = \{f(n) \mid \exists\, c > 0,\, n_0 > 0,\; \forall n \geq n_0 : 0 \leq c \cdot g(n) \leq f(n)\}$$

### Big-Theta — Tight Bound

$$\Theta(g(n)) = \{f(n) \mid \exists\, c_1, c_2 > 0,\, n_0 > 0,\; \forall n \geq n_0 : 0 \leq c_1 g(n) \leq f(n) \leq c_2 g(n)\}$$

$f(n) = \Theta(g(n))$ is the strongest statement — it pins $f$ between two multiples of $g$.

### Little-o and Little-omega

- **$o(g(n))$:** $f$ grows *strictly slower* than $g$. $\forall c > 0,\; \exists n_0 : f(n) < c \cdot g(n)$. Equivalently: $\lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$.
- **$\omega(g(n))$:** $f$ grows *strictly faster* than $g$. $\lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$.

### Properties

| Property | Statement |
|----------|-----------|
| **Transitivity** | $f = O(g)$ and $g = O(h)$ $\Rightarrow$ $f = O(h)$  *(also for $\Omega, \Theta, o, \omega$)* |
| **Reflexivity** | $f = O(f)$ and $f = \Theta(f)$  *(but NOT $f = o(f)$ or $f = \omega(f)$)* |
| **Symmetry** | $f = \Theta(g) \Leftrightarrow g = \Theta(f)$ |
| **Transpose Symmetry** | $f = O(g) \Leftrightarrow g = \Omega(f)$ &nbsp;&nbsp; $\mid$ &nbsp;&nbsp; $f = o(g) \Leftrightarrow g = \omega(f)$ |

### Example

**Is $4n^2 + 100n + 500 = O(n^2)$?**

We need $c > 0, n_0$ such that $4n^2 + 100n + 500 \leq c \cdot n^2$ for all $n \geq n_0$.

$$4n^2 + 100n + 500 \leq 4n^2 + 100n^2 + 500n^2 = 604n^2 \quad \text{for } n \geq 1$$

> **Yes!** $4n^2 + 100n + 500 = O(n^2)$ with $c = 604$, $n_0 = 1$.

---

## 3. Merge Sort

### Strategy: Divide & Conquer

1. **Divide:** Split array A[1..n] at midpoint $q = \lfloor(p+r)/2\rfloor$
2. **Recurse:** Sort the two halves independently
3. **Merge:** Combine the two sorted halves

### Algorithm

```
MergeSort(A, p, r):
    if p >= r:  return        // base case: 1 element
    q = floor((p + r) / 2)
    MergeSort(A, p, q)
    MergeSort(A, q+1, r)
    Merge(A, p, q, r)
```

### Correctness Proof

Proof by induction on array length:

- **Base Step:** A[1:1] is trivially sorted.
- **Inductive Step:** If any array of length $\leq n/2$ is sorted correctly, then Merge Sort correctly sorts length $n$ — it sorts both halves (by IH), then merges two sorted halves.

### Merge Subroutine

Takes sorted A[p:q] and A[q+1:r] and combines into sorted A[p:r] using two pointers.

> **Worst and best case of merging $n$ elements is always $\Theta(n)$.**

### Time Complexity

Recurrence:

$$T(1) = \Theta(1) \qquad T(n) = 2T(n/2) + \Theta(n)$$

**Recursion Tree Analysis:**

| Level | # Subproblems | Work per subproblem | Total work |
|-------|---------------|---------------------|------------|
| 0 (root) | 1 | $cn$ | $cn$ |
| 1 | 2 | $cn/2$ | $cn$ |
| 2 | 4 | $cn/4$ | $cn$ |
| $\vdots$ | $\vdots$ | $\vdots$ | $cn$ |
| $\log n$ | $n$ | $c \cdot 1$ | $cn$ |

Number of levels = $\log_2 n + 1$

$$T(n) = (\log n + 1) \cdot cn = cn \log n + cn = \boxed{\Theta(n \log n)}$$

---

## 4. Solving Recurrences — Substitution Method

Guess the form of the solution, then verify by mathematical induction.

### Example: $T(n) = 2T(n/2) + n$

**Guess:** $T(n) \leq d \cdot n \log n$ (upper bound)

**Verify:**
```
T(n) ≤ 2 · d·(n/2)·log(n/2) + n
     = 2 · d·(n/2)·(log n - 1) + n
     = d·n·log n - d·n + n
     = d·n·log n - (d-1)·n
     ≤ d·n·log n    iff   d ≥ 1  ✓
```

### Example: $T(n) = 4T(n/2) + n$  (CLRS 4.3-2)

**Claim:** $T(n) = \Theta(n^2)$

**Upper Bound attempt — Guess $T(n) \leq cn^2$:**

$$T(n) \leq 4 \cdot c(n/2)^2 + n = cn^2 + n$$

This does **not** give $T(n) \leq cn^2$. We need to subtract something.

**Stronger guess: $T(n) \leq cn^2 - n$:**

$$T(n) \leq 4\left(c(n/2)^2 - n/2\right) + n = cn^2 - 2n + n = cn^2 - n \checkmark$$

> **Key trick:** When the guess doesn't work, strengthen it by subtracting a lower-order term.

### Common Pitfalls

- Getting $T(n) \leq (c+1)n$ does **not** prove $T(n) \leq cn$
- The result must satisfy the *exact form* of the guess, not just an upper bound
- For wrong guesses (e.g., guessing $O(n)$ for $T(n) = 4T(n/4) + n$), no valid $c$ will work — change the guess

---

## 5. The Master Theorem

For recurrences of the form:

$$T(n) = a \cdot T(n/b) + f(n), \quad a \geq 1,\; b > 1,\; f(n) \geq 0$$

Compare $f(n)$ against the **watershed function** $n^{\log_b a}$:

| Case | Condition on $f(n)$ | Result |
|------|---------------------|--------|
| **Case 1** | $f(n) = O(n^{\log_b a - \varepsilon})$ for some $\varepsilon > 0$ | $T(n) = \Theta(n^{\log_b a})$ |
| **Case 2** ($k=0$) | $f(n) = \Theta(n^{\log_b a})$ | $T(n) = \Theta(n^{\log_b a} \log n)$ |
| **Case 2** ($k \geq 1$) | $f(n) = \Theta(n^{\log_b a} \log^k n)$ | $T(n) = \Theta(n^{\log_b a} \log^{k+1} n)$ |
| **Case 3** | $f(n) = \Omega(n^{\log_b a + \varepsilon})$ AND regularity condition | $T(n) = \Theta(f(n))$ |

**Regularity condition for Case 3:** $a \cdot f(n/b) \leq c \cdot f(n)$ for some $c < 1$ and large $n$.

### Examples

**(a)** $T(n) = 2T(n/4) + 1$: $a=2, b=4 \Rightarrow n^{\log_4 2} = n^{1/2}$. $f(n) = 1 = O(n^{1/2 - \varepsilon})$ → **Case 1** → $T(n) = \Theta(\sqrt{n})$

**(b)** $T(n) = 2T(n/4) + \sqrt{n}$: $f(n) = \sqrt{n} = \Theta(n^{1/2})$ → **Case 2** → $T(n) = \Theta(\sqrt{n} \log n)$

**(c)** $T(n) = 2T(n/4) + \sqrt{n} \log^2 n$: $f(n) = \Theta(n^{1/2} \log^2 n)$ → **Case 2** ($k=2$) → $T(n) = \Theta(\sqrt{n} \log^3 n)$

**(d)** $T(n) = 2T(n/4) + n$: Check regularity: $2 \cdot (n/4) = n/2 \leq c \cdot n$ for $c = 1/2$ ✓ → **Case 3** → $T(n) = \Theta(n)$

**(e)** $T(n) = 2T(n/4) + n^2$: → **Case 3** → $T(n) = \Theta(n^2)$

**Binary Search** $T(n) = T(n/2) + \Theta(1)$: $a=1, b=2 \Rightarrow n^{\log_2 1} = 1$. $f(n) = \Theta(1)$ → **Case 2** → $T(n) = \Theta(\log n)$

---

## 6. Quicksort  (Lectures 7–8)

### Algorithm

```
QuickSort(A, p, r):
    if p < r:
        q = Partition(A, p, r)
        QuickSort(A, p, q-1)
        QuickSort(A, q+1, r)
```

### Partition

Selects last element `A[r]` as pivot $x$, rearranges so elements $\leq x$ come first.

```
Partition(A, p, r):
    x = A[r]           // pivot
    i = p - 1
    for j = p to r-1:
        if A[j] <= x:
            i = i + 1
            swap A[i] with A[j]
    swap A[i+1] with A[r]
    return i+1
```

### Loop Invariant for Partition

At each iteration of the for-loop:

| Region | Subarray | Property |
|--------|----------|----------|
| **LEFT** | A[p : i] | All elements $\leq$ pivot $x$ |
| **RIGHT** | A[i+1 : j−1] | All elements $>$ pivot $x$ |
| **UNKNOWN** | A[j : r−1] | Not yet processed |
| **PIVOT** | A[r] | The pivot $x$ |

- **Initialization:** LEFT = A[p:p−1] = ∅, RIGHT = A[p:p−1] = ∅ (trivially correct)
- **Termination:** $j = r$, so UNKNOWN = ∅. After final swap, pivot is in correct position.

### Correctness of Quicksort

Proof by induction on number of elements:

- **Base case:** $n=1$ — trivially sorted.
- **Inductive step:** For $n=k+1$: Partition places pivot A[q] in its correct final position (left ≤ A[q] < right). Both subarrays have size $\leq k$, so by IH they are sorted correctly. Result: fully sorted array.

### Time Complexity

**Worst case** (sorted/reverse-sorted input, pivot always at one end):

$$T(n) = T(0) + T(n-1) + \Theta(n) \Rightarrow T(n) = \Theta(n^2)$$

Verified by substitution: Guess $T(n) \leq cn^2$. Then $T(n) \leq c(n-1)^2 + \Theta(n) = cn^2 - c(2n-1) + dn \leq cn^2$ iff $c \geq d$ ✓

**Best case** (perfectly balanced splits):

$$T(n) = 2T(n/2) + \Theta(n) \Rightarrow T(n) = \Theta(n \log n)$$

### Decision Tree Lower Bound for Comparison Sorting

Any comparison-based sorting algorithm → model as a decision tree:
- Each internal node: comparison $a_i : a_j$
- Each leaf: a permutation (sorted output)
- Tree must have $\geq n!$ leaves
- Binary tree of height $h$ has $\leq 2^h$ leaves

$$n! \leq 2^h \Rightarrow h \geq \log(n!) \geq c \cdot n \log n$$

> **Any comparison-based sorting algorithm requires $\Omega(n \log n)$ comparisons in the worst case.**

---

## 7. Randomized Algorithms  (Lectures 8, 10)

### Deterministic vs. Randomized

| Type | Description |
|------|-------------|
| **Deterministic** | Same input → same sequence of decisions and output every time |
| **Randomized** | May make different decisions each run (due to random choices), but produces probabilistically correct output |

### Hiring Problem

Interview $n$ candidates in random order, hire each if better than the current best.

Cost = $n \cdot C_i + x \cdot C_h$ where $x$ = number hired.

**Using indicator random variables:**

$$X_i = \begin{cases} 1 & \text{if person } i \text{ is hired} \\ 0 & \text{otherwise} \end{cases}$$

$$\Pr[\text{person } i \text{ is hired}] = \frac{(i-1)!}{i!} = \frac{1}{i}$$

$$E[x] = E\left[\sum_{i=1}^n X_i\right] = \sum_{i=1}^n \frac{1}{i} = H_n \approx \ln n$$

> **Expected number of hires $\approx \ln n = O(\log n)$**

### Randomized Quicksort

Pick pivot uniformly at random instead of always using A[r].

**Expected comparisons:**

Assume distinct elements $a_1 < a_2 < \cdots < a_n$. Define:

$$X_{ij} = \begin{cases} 1 & \text{if } a_i \text{ and } a_j \text{ are compared} \\ 0 & \text{otherwise} \end{cases}$$

$a_i$ and $a_j$ are compared iff one of them is chosen as pivot before any element between them.

$$\Pr[X_{ij} = 1] = \frac{2}{j - i + 1}$$

$$E[X] = \sum_i \sum_{j > i} \frac{2}{j-i+1} \approx 2n \ln n$$

> **Expected time complexity of Randomized Quicksort = $\Theta(n \log n)$**

---

## 8. Sorting in Linear Time  (Lectures 8, 12)

Comparison-based sorting has a $\Omega(n \log n)$ lower bound. With extra structure on keys, we can do better.

### Counting Sort

Works when keys are integers in range $[0, k-1]$ for constant $k$.

1. Count[i] = number of times $i$ appears in A  — $O(n)$
2. Count[i] += Count[i−1]  (prefix sums → positions)  — $O(k)$
3. Place each element in output B at correct position (iterate backward for stability)  — $O(n)$

> $T(n) = \Theta(n + k)$. Space: $\Theta(n + k)$. **Stable sort.**

### Radix Sort

Sort $d$-digit numbers by sorting on each digit from **least significant to most significant**, using a stable sort each pass.

**Example:** 4-digit decimal → sort by units → tens → hundreds → thousands.

> ⚠️ **Must use a STABLE sort for each digit pass.** Ties must preserve relative ordering from previous passes.

With counting sort as subroutine: $T(n) = \Theta(d(n + k))$.
For $d = O(1)$ and $k = O(n)$: $T(n) = \Theta(n)$.

### Bucket Sort

Assumes input is uniformly distributed over $[0, 1)$. Divide into $n$ equal-sized buckets, sort each (with insertion sort), concatenate.

Let $n_i$ = elements in bucket $i$. Compute $E[n_i^2]$ using indicator variables:

$$E[n_i^2] = \sum_j E[X_{ji}^2] + \sum_j \sum_{k \neq j} E[X_{ji} X_{ki}] = 1 + n(n-1) \cdot \frac{1}{n^2} = 2 - \frac{1}{n} = O(1)$$

> **Expected time: $\Theta(n)$.** Requires uniform distribution assumption.

---

## 9. Linear Data Structures  (Lecture 13)

### Arrays
- Fixed size, $O(1)$ random access by index
- $O(n)$ insertion/deletion (shifting required)
- Contiguous memory, cache-friendly

### Linked Lists
- Dynamic size, $O(1)$ insert/delete at known position
- $O(n)$ search / index access
- Non-contiguous memory, extra pointer overhead

### Stacks (LIFO)

Last-In, First-Out. **Push** and **Pop**, both $O(1)$.

> **Catalan number result:** The number of stack-sortable permutations of $\{1, \ldots, n\}$ is:
> $$C_n = \frac{1}{n+1}\binom{2n}{n}$$
> This also equals the number of distinct BST shapes on $n$ nodes and the number of balanced parentheses strings of length $2n$.

A permutation is **not** stack-sortable iff it contains the pattern $(a_k, a_i, a_j)$ with $i < j < k$ as a subsequence.

### Queues (FIFO)

First-In, First-Out. **Enqueue** (insert at back) and **Dequeue** (remove from front), both $O(1)$.

---

## 10. Binary Search Trees  (Lectures 13–14)

### BST Property

Each node has: key, left pointer, right pointer.

> **For every node:** All keys in LEFT subtree < node.key < All keys in RIGHT subtree

### Operations

| Operation | Best Case | Worst Case | Notes |
|-----------|-----------|------------|-------|
| Search | $O(\log n)$ | $O(h)$ | $h$ = height of tree |
| Insert | $O(\log n)$ | $O(h)$ | Walk down to correct leaf |
| Delete | $O(\log n)$ | $O(h)$ | 3 cases (see below) |
| Inorder traversal | $\Theta(n)$ | $\Theta(n)$ | Always visits all $n$ nodes |

### Tree Traversals

| Traversal | Order | Result on tree (5,2,7,1,3,4,6,8) |
|-----------|-------|----------------------------------|
| **Preorder** | root → left → right | 5, 2, 1, 3, 4, 7, 6, 8 |
| **Inorder** | left → root → right | 1, 2, 3, 4, 5, 6, 7, 8 *(sorted!)* |
| **Postorder** | left → right → root | 1, 4, 3, 2, 6, 8, 7, 5 |

> **Inorder traversal of a BST always yields elements in sorted order — $O(n)$.**

### Delete Algorithm — 3 Cases

- **Case 1 — Leaf:** Simply remove it (return null)
- **Case 2 — One child:** Replace node with its only child
- **Case 3 — Two children:** Find in-order successor (minimum of right subtree), copy its key, delete successor from right subtree

```
Delete(root, key):
    if root == null: return null
    if key < root.data:  root.left = Delete(root.left, key)
    elif key > root.data: root.right = Delete(root.right, key)
    else:  // found node to delete
        if root.left == null AND root.right == null: return null
        elif root.left == null: return root.right
        elif root.right == null: return root.left
        else:  // two children
            temp = FindMin(root.right)   // in-order successor
            root.data = temp.data
            root.right = Delete(root.right, temp.data)
    return root

FindMin(node):
    while node.left != null:
        node = node.left
    return node
```

### Number of Distinct BSTs

$$C_n = \frac{1}{n+1}\binom{2n}{n} = 1, 1, 2, 5, 14, 42, \ldots$$

### Reconstructing BST from Preorder

Given a preorder sequence, we can **uniquely** reconstruct the BST:
- Root = first element
- Elements smaller than root → left subtree preorder
- Elements larger than root → right subtree preorder
- Recurse

*Example:* Preorder `4 1 2 3` → Root=4, left subtree: `1 2 3`

### Height and Time Complexity

- **Balanced BST:** $h = O(\log n)$ → all operations $O(\log n)$
- **Worst case (sorted insertion):** $h = n$ → operations $O(n)$ (degenerates to linked list!)

> Balanced BST variants (AVL, Red-Black Trees) maintain $h = O(\log n)$ always.

---

## 11. Advanced BST Topics  (Lecture 15)

*CLRS 12.1, 12.2, 12.3 | Lectures 15 (18/02)*

### Successor and Predecessor

**Successor of node $x$** = the node with the smallest key greater than $x$.key.

**Two cases:**
1. If $x$ has a **right subtree**: successor = minimum of right subtree (leftmost node in right subtree)
2. If $x$ has **no right subtree**: successor = lowest ancestor of $x$ whose left child is also an ancestor of $x$ — i.e., go up until you take a left turn.

```
Successor(x):
    if x.right != null:
        return FindMin(x.right)
    y = x.parent
    while y != null AND x == y.right:
        x = y
        y = y.parent
    return y        // y is the successor (or null if x has the max key)
```

> **CLRS 12.2-5:** If a node has two children, its successor has no left child, and its predecessor has no right child.

**Predecessor** is symmetric: largest key smaller than $x$.key.
- If $x$ has a left subtree: predecessor = maximum of left subtree
- Otherwise: go up until you take a right turn

### Inorder Walk Property (CLRS 12.1)

> **Theorem:** Inorder tree walk on a BST of $n$ nodes takes $\Theta(n)$ time.

- **Proof sketch:** Each node is visited exactly once (printed once). The recursion adds $O(1)$ work per node. Total = $\Theta(n)$.

> **CLRS 12.1-5:** Any comparison-based algorithm to build a BST from an unsorted list must take $\Omega(n \log n)$ time in the worst case (since we could use it to sort).

### BST Insert — Detailed

```
Insert(T, z):        // z is a new node with z.key set
    y = null
    x = T.root
    while x != null:
        y = x
        if z.key < x.key:  x = x.left
        else:              x = x.right
    z.parent = y
    if y == null:          T.root = z        // tree was empty
    elif z.key < y.key:    y.left = z
    else:                  y.right = z
```

Time complexity: $O(h)$ where $h$ = height.

### BST Delete — Full Case Analysis (CLRS 12.3)

The textbook uses a helper `Transplant(T, u, v)` that replaces subtree rooted at $u$ with subtree rooted at $v$:

```
Transplant(T, u, v):
    if u.parent == null:    T.root = v
    elif u == u.parent.left: u.parent.left = v
    else:                   u.parent.right = v
    if v != null:           v.parent = u.parent
```

Full delete:

```
Delete(T, z):
    if z.left == null:
        Transplant(T, z, z.right)          // Case 1 or 2
    elif z.right == null:
        Transplant(T, z, z.left)           // Case 2
    else:
        y = FindMin(z.right)               // y = successor of z
        if y.parent != z:
            Transplant(T, y, y.right)
            y.right = z.right
            y.right.parent = y
        Transplant(T, z, y)
        y.left = z.left
        y.left.parent = y
```

**CLRS 12.3-5:** An alternative delete uses the **predecessor** (max of left subtree) instead of successor — equally valid.

**CLRS 12.3-7:** If we delete a node with two children by replacing it with its successor, and then delete the successor, the resulting tree may differ from replacing directly. The BST property is maintained either way.

### Expected Height of a Random BST (CLRS 12.4 / Problem 12-4)

**Setup:** Insert $n$ distinct keys in a uniformly random order.

Let $h_n$ = expected height of a randomly built BST on $n$ keys.

**Result:**

$$E[h_n] = O(\log n)$$

More precisely, $E[h_n] \leq c \log n$ for some constant $c \approx 4.311$.

**Proof idea (exponential height analysis):**

- Define $Y_n = 2^{h_n}$ (exponential of height)
- Show $E[Y_n] = O(n^3)$ using recurrence on the rank of the root
- Since $Y_n = 2^{h_n}$, we get $h_n = \log Y_n \leq \log(n^3) = 3 \log n$ (in expectation)

**CLRS Problem 12-4 — Number of BSTs:**

The number of distinct BSTs on $n$ keys satisfies:

$$b(n) = \sum_{k=0}^{n-1} b(k) \cdot b(n-1-k), \quad b(0) = 1$$

This is the same recurrence as Catalan numbers, giving:

$$b(n) = C_n = \frac{1}{n+1}\binom{2n}{n} = \Theta\!\left(\frac{4^n}{n^{3/2}}\right)$$

### BST vs. Sorted Array vs. Linked List

| Operation | Sorted Array | Linked List | BST (balanced) | BST (worst) |
|-----------|-------------|-------------|----------------|-------------|
| Search | $O(\log n)$ | $O(n)$ | $O(\log n)$ | $O(n)$ |
| Insert | $O(n)$ | $O(1)^*$ | $O(\log n)$ | $O(n)$ |
| Delete | $O(n)$ | $O(1)^*$ | $O(\log n)$ | $O(n)$ |
| Successor | $O(1)$ | $O(n)$ | $O(\log n)$ | $O(n)$ |
| List all (sorted) | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |

*$O(1)$ assumes position is already known.

### Bijection: Preorder ↔ Balanced Parentheses (TAoCP 2.3.1)

There is a bijection between preorder sequences of BSTs on $n$ nodes and balanced parentheses strings of length $2n$.

**Encoding:** For each node visited in preorder:
- Output `(` when entering the node (visiting it)
- Output `)` when leaving the node (after visiting right subtree)

This gives a 1-to-1 correspondence, proving both are counted by Catalan numbers $C_n$.

**Example for $n=3$:** The 5 BSTs on $\{1,2,3\}$ correspond to the 5 balanced parentheses strings: `()()()`, `(())()`, `()(())`, `((()))`, `(()())`.

### Key Homework Problems

**CLRS 12.2-5:** Successor of a node with two children has no left child; predecessor has no right child.
- *Proof:* If successor $y$ had a left child $z$, then $z.key > x.key$ and $z.key < y.key$, contradicting $y$ being the successor.

**CLRS 12.2-6:** If the right subtree of $x$ is empty and $x$ has a successor $y$, then $y$ is the lowest ancestor of $x$ whose left child is also an ancestor of $x$.

**CLRS 12.2-9:** If $x$ is the smallest key in a BST and $y$ is its successor, then $y$ has no left child.

**CLRS 12.3-1:** A recursive version of BST insertion.

**CLRS 12.3-2:** Building a BST by successive insertion, then searching for each key — show the sequence of nodes examined is the same as in the original insertion path.

**CLRS 12.3-3:** Sort $n$ numbers by building a BST and reading out inorder. Worst case: $\Theta(n^2)$ (sorted input → chain). Best case: $\Theta(n \log n)$.

**TAoCP 2.3.1 Exercises:** Properties of tree traversals (preorder, inorder, postorder) and their relationships.

---

## 12. Quick Reference — Complexity Summary

### Sorting Algorithms

| Algorithm | Best Case | Average Case | Worst Case | Space | Stable? |
|-----------|-----------|--------------|------------|-------|---------|
| Insertion Sort | $\Theta(n)$ | $\Theta(n^2)$ | $\Theta(n^2)$ | $O(1)$ | Yes |
| Merge Sort | $\Theta(n \log n)$ | $\Theta(n \log n)$ | $\Theta(n \log n)$ | $O(n)$ | Yes |
| Quicksort | $\Theta(n \log n)$ | $\Theta(n \log n)$* | $\Theta(n^2)$ | $O(\log n)$ | No |
| Counting Sort | $\Theta(n+k)$ | $\Theta(n+k)$ | $\Theta(n+k)$ | $O(n+k)$ | Yes |
| Radix Sort | $\Theta(d(n+k))$ | $\Theta(d(n+k))$ | $\Theta(d(n+k))$ | $O(n+k)$ | Yes |
| Bucket Sort | $\Theta(n)$ | $\Theta(n)$** | $\Theta(n^2)$ | $O(n)$ | Yes |

\* Randomized Quicksort expected  
\*\* Requires uniform distribution

### Asymptotic Notation Summary

| Notation | Meaning | Formal definition |
|----------|---------|------------------|
| $O(g)$ | Upper bound | $f(n) \leq c \cdot g(n)$ for large $n$ |
| $\Omega(g)$ | Lower bound | $f(n) \geq c \cdot g(n)$ for large $n$ |
| $\Theta(g)$ | Tight bound | $c_1 g(n) \leq f(n) \leq c_2 g(n)$ for large $n$ |
| $o(g)$ | Strict upper | $\lim_{n \to \infty} f(n)/g(n) = 0$ |
| $\omega(g)$ | Strict lower | $\lim_{n \to \infty} f(n)/g(n) = \infty$ |

### Master Theorem Quick Lookup

| Recurrence | $n^{\log_b a}$ | Case | Result |
|------------|---------------|------|--------|
| $T(n) = T(n/2) + O(1)$ | $n^0 = 1$ | 2 | $\Theta(\log n)$ |
| $T(n) = 2T(n/2) + O(n)$ | $n^1$ | 2 | $\Theta(n \log n)$ |
| $T(n) = 4T(n/2) + O(n)$ | $n^2$ | 1 | $\Theta(n^2)$ |
| $T(n) = 4T(n/2) + O(n^2)$ | $n^2$ | 2 | $\Theta(n^2 \log n)$ |
| $T(n) = 4T(n/2) + O(n^3)$ | $n^2$ | 3 | $\Theta(n^3)$ |
| $T(n) = 2T(n/3) + O(n)$ | $n^{\log_3 2} \approx n^{0.63}$ | 3 | $\Theta(n)$ |

### BST Operations

| Operation | Average (random BST) | Worst Case |
|-----------|---------------------|------------|
| Search | $O(\log n)$ | $O(n)$ |
| Insert | $O(\log n)$ | $O(n)$ |
| Delete | $O(\log n)$ | $O(n)$ |
| Successor/Predecessor | $O(\log n)$ | $O(n)$ |
| Inorder Walk | $\Theta(n)$ | $\Theta(n)$ |
| Expected height | $O(\log n)$ | $n-1$ |

---

*End of Notes — Good luck!*
