# Cryptographic Algorithms in C


This project implements fundamental cryptographic primitives and number theory algorithms from scratch in C. It includes demonstrations of key concepts such as modular arithmetic, public-key cryptography, and stream ciphers. The system is fully modular, with each algorithm implemented in its own header (`.h`) and source (`.c`) files.

1. [Greatest Common Divisor](#greatest-common-divisor)
2. [Modular Inverse](#modular-inverse)
4. [Chinese Remainder Theorem](#chinese-remainder-theorem)
5. [Modular Exponentiation](#modular-exponentiation)
6. [Primality Testing](#primality-testing)
7. [Diffie Hellman Key Exchange](#diffie-hellman-key-exchange)
8. [Elliptic Curve Arithmetic](#elliptic-curve-arithmetic)
9. [Discrete Logarithm Solvers](#discrete-logarithm-solvers)
10. [Rivest–Shamir–Adleman (RSA)](#rivestshamiradleman-rsa)
11. [Digital Signature Algorithm (DSA)](#digital-signature-algorithm-dsa)
12. [RC4 Stream Cipher](#rc4-stream-cipher)


## Greatest Common Divisor


This module provides functions to compute the greatest common divisor (GCD) and perform the Extended Euclidean Algorithm.

### Mathematical Background

The **Euclidean algorithm** computes the GCD of two numbers by repeated division:
$$\gcd(a, b) = \gcd(b, a \bmod b)$$

Example:

$$\gcd(30, 12) = \gcd(12, 6) = \gcd(6, 0) = 6$$

The **Extended Euclidean Algorithm** also finds integers $x$ and $y$ such that:
$$ax + by = \gcd(a, b)$$
### Functions
```c
void scan_for_gcd(int *a, int *b);
```
Prompts the user to input two integers for GCD computation.

**Parameters:**
- `int *a`: Pointer to the first integer.
- `int *b`: Pointer to the second integer.

---
```c
void print_gcd(int64_t a, int64_t b);
```
Uses the Extended Euclidean Algorithm to compute and print $\gcd(a, b) = ax + by$ along with the coefficients $x$ and $y$.

**Parameters:**

- `int64_t a`: First integer.
- `int64_t b`: Second integer.

---
```c
uint64_t gcd(uint64_t a, uint64_t b);
```
Recursively computes: $\gcd(a, b) = \gcd(b, a \bmod b)$

**Parameters:**

- `uint64_t a`: First non-negative integer.
- `uint64_t b`: Second non-negative integer.

**Returns:**

- `uint64_t`: The greatest common divisor $\gcd(a, b)$.

---
```c
void extended_gcd(int64_t a, int64_t b, int64_t *gcd, int64_t *x, int64_t *y);
```
Finds integers $x$, $y$ such that $ax + by = \gcd(a, b)$. This is used in computing modular inverses.

**Parameters:**

- `int64_t a`: First integer.
- `int64_t b`: Second integer.
- `int64_t *gcd`: Output pointer to store the computed GCD.
- `int64_t *x`: Output pointer to store the coefficient of `a`.
- `int64_t *y`: Output pointer to store the coefficient of `b`.

---

## Modular Inverse

This module provides functions to compute the modular inverse of an integer, i.e., finding an integer $x$ such that:

$$a \cdot x \equiv 1 \pmod{n}$$

This is only possible when $\gcd(a, n) = 1$. The Extended Euclidean Algorithm is used to compute the inverse.

### Mathematical Background

The modular inverse of $a$ modulo $n$ is an integer $x$ such that $a \cdot x \equiv 1 \pmod{n}$.
This is commonly denoted as $a^{-1} \equiv x \pmod{n}$.

That is, $x$ is the value which, when multiplied by $a$, gives $1$ modulo $n$.
Such an inverse exists **if and only if** $\gcd(a, n) = 1$.

To compute $a^{-1} \mod n$, we use the **Extended Euclidean Algorithm**, which finds integers $x$ and $y$ such that:

$$a \cdot x + n \cdot y = \gcd(a, n)$$

When $\gcd(a, n) = 1$, this becomes $a \cdot x + n \cdot y = 1$.
Taking both sides modulo $n$, we get $a \cdot x \equiv 1 \pmod{n}$, so $a^{-1} \equiv x \pmod{n}$.

If $\gcd(a, n) \ne 1$, then $a^{-1} \mod n$ does not exist.

### Functions
```c
void scan_for_inverse(int *a, int *n)
```
Prompts the user to input two integers $a$ and $n$ to be used for modular inverse computation.

**Parameters:**

- `int a`: Pointer to store the base integer
- `int n`: Pointer to store the modulus

---
```c
void print_inverse(int a, int n)
```
Computes and prints the modular inverse of $x \equiv a \mod n$ if it exists.
If no inverse exists (i.e., $\gcd(a, n) \neq 1$), an error message explaining that the inverse is undefined.

**Parameters:**

- `int a`: The base integer
- `int n` The modulus

---
```c
int64_t *inverse(int64_t a, int64_t n)
```
Computes the modular inverse of `a` modulo `n`, i.e., finds an integer `x` such that:

$$a \cdot x \equiv 1 \pmod{n}$$

This is done using the Extended Euclidean Algorithm.
If no inverse exists (i.e., when $\gcd(a, n) \ne 1$), the function returns `NULL`.

**Parameters:**

- `int64_t a`: The number for which the inverse is to be found.
- `int64_t n`: The modulus.

**Returns:**

- `int64_t *`: Pointer to the inverse value if it exists, or `NULL` if no inverse exists.

---



## Chinese Remainder Theorem

This module provides a way to solve systems of linear congruences using the Chinese Remainder Theorem (CRT).
It includes a data structure to represent each modular equation and functions to compute the unique solution when the moduli are pairwise coprime.

### Mathematical Background
The CRT solves a system of congruences of the form:

$$
\begin{cases}
x \equiv b_1 \pmod{n_1} \\
x \equiv b_2 \pmod{n_2} \\
\vdots \\
x \equiv b_k \pmod{n_k}
\end{cases}
$$

If the moduli $n_1, n_2, \dots, n_k$ are pairwise coprime, then there exists a **unique solution modulo** $N$, where: $N = n_1 \cdot n_2 \cdots n_k$

To construct the solution:
- For each $i$, compute $N_i = \frac{N}{n_i}$
- Find the modular inverse $y_i = N_i^{-1} \pmod {n_i}$
- Then the solution is:

$$x = \sum_{i=0}^{k-1} b_i \cdot N_i \cdot y_i \pmod N$$

This $x$ satisfies all the original congruences and is unique modulo $N$.

### Data Structure
```c
typedef struct ModularEquation {
    // Represents x ≡ b (mod n)
    uint64_t b;
    uint64_t n;
} ModularEquation;
```

### Functions
```c
ModularEquation *initModularEquation(uint64_t b, uint64_t n);
```
Initializes a `ModularEquation` with the form $x \equiv b \pmod n$.

**Parameters:**

- `int b`: The remainder
- `int n`: The modulus

**Returns:**

- `ModularEquation *`: Pointer to the created `ModularEquation` instance.

---
```c
void printModularEquation(ModularEquation *modularEquation);
```
Prints the modular equation in the format $x \equiv b \pmod n$.

**Parameters:**

- `modularEquation *`: Pointer to the modular equation to print

---
```c
ModularEquation *crt(ModularEquation *modularEquations[], size_t size);
```
Solves a system of congruences using the Chinese Remainder Theorem.

**Parameters:**

- `ModularEquation *modularEquations[]`: An array of pointers to `ModularEquation` structs, each representing an equation of the form $x \equiv b_i \pmod n_i$
- `size_t size`: The number of equations in the system

**Returns:**

A pointer to a new `ModularEquation` representing the combined solution $x \equiv r \pmod N$,
where $N = n_1 \cdot n_2 \cdots n_k$ and $r$ is the unique solution modulo $N$ that satisfies all given congruences.
> Assumes all moduli $n_i$ are pairwise coprime. If this condition is not met, the result is undefined.

---
### Example Usage

Suppose we want to solve the following system:

$$
\begin{cases}
x \equiv 2 \pmod{5} \\
x \equiv 3 \pmod{7} \\
x \equiv 10 \pmod{11}
\end{cases}
$$

Here's how you can represent and solve this using the CRT module:

```c
#include "crt.h"

ModularEquation *eq1 = initModularEquation(2, 5);
ModularEquation *eq2 = initModularEquation(3, 7);
ModularEquation *eq3 = initModularEquation(10, 11);

ModularEquation *equations[] = { eq1, eq2, eq3 };
size_t size = sizeof(equations) / sizeof(equations[0]);

ModularEquation *result = crt(equations, size);
printModularEquation(result);

free(equations[0]);
free(equations[1]);
free(equations[2]);
free(result);
```
**Output:** `x ≡ 87 (mod 385)`

This means $x \equiv 87 \pmod {385}$ is the unique solution that satisfies all the original equations.

## Modular Exponentiation

This module implements efficient exponentiation of the form $x^e \pmod p$ using the square-and-multiply algorithm.
This is essential in cryptography, especially in RSA, DSA, and Diffie–Hellman protocols.

### Mathematical Background

Modular exponentiation computes $x^e \pmod p$ efficiently.
Rather than multiplying $x$ by itself $e$ times which its time complexity is $O(e)$, we use the square-and-multiply method to reduce the time complexity to $O(\log e)$.

- $\text{Let } e_{10} \text{ in decimal be } (e_0 e_1 \ldots e_k)_2 \text{ in binary}$
  - $\text{Initialize } result = 1$
  - $\text{For each } e_i \text{ in } {e_0} \text{ to } e_{k}$:
    - Square: $result = ({result}^2) \mod p$
    - $\text{if } e_i = 1:$
	    - Multiply: $result = (result \cdot x) \mod p$
  - $\text{return result}$

This allows efficient exponentiation even for very large $e$.

### Example

$$3^{13} \mod 11$$

Let $x = 3$

Let $e = 13_{10} = 1101_{2}$

Let $p = 7$

$\text{Initialize } result = 1$:

|$e_i$|    op    |         result        |value of result|
|-----|----------|------------------------|---------------|
| $1$ |  Square  |$result = 1 ^ 2 \mod 11$|      $1$      |
|     | Multiply |$result = 1 * 3 \mod 11$|      $3$      |
| $1$ |  Square  |$result = 3 ^ 2 \mod 11$|      $9$      |
|     | Multiply |$result = 9 * 3 \mod 11$|      $5$      |
| $0$ |  Square  |$result = 5 ^ 2 \mod 11$|      $3$      |
| $1$ |  Square  |$result = 3 ^ 2 \mod 11$|      $9$      |
|     | Multiply |$result = 9 * 3 \mod 11$|      $5$      |




$$3^{13} \pmod {11} = 5$$

### Functions
```c
void print_for_exponent(int x, int e, int p);
```
Computes and prints the result of $x^e \pmod p$.

**Parameters:**

- `int x`: The base
- `int e`: The exponent
- `int p`: The modulus
---
```c
uint64_t exponent(uint64_t x, uint64_t y, uint64_t mod);
```
Performs modular exponentiation using the square-and-multiply method.

**Parameters:**

- `uint64_t x`: The base
- `uint64_t y`: The exponent
- `uint64_t mod`: The modulus

**Returns:**

- `uint64_t`: The computed value of $x^y \pmod p$ as a 64-bit unsigned integer.

---
## Primality Testing


This module implements probabilistic primality testing based on Fermat's little theorem and a simplified version of the Miller–Rabin test. It also includes Carmichael number detection and utilities for generating random prime numbers.

### Mathematical Background

Primality testing relies on number-theoretic properties that primes satisfy and composites usually do not.

#### Fermat’s Little Theorem

If $p$ is prime and $\gcd(a, p) = 1$, then:

$$a^{p-1} \equiv 1 \pmod{p}$$

This gives a basic test: if $a^{n-1} \not\equiv 1 \pmod{n}$, then $n$ is composite.
If it holds for many $a$, $n$ is probably prime.

#### Carmichael Numbers

These are composite numbers like $561$, $1105$, and $1729$ that satisfy:

$$a^{n-1} \equiv 1 \pmod{n}$$

For all $a$ coprime to $n$ $\text{ e.i.} \gcd(a, n)=1$,
They fool Fermat's test, so stronger tests are needed.

**Example:**
$561$ is a Carmichael number. It is composite: $561 = 3 \cdot 11 \cdot 17$.
Yet for any $a$ coprime to 561 (e.g., $a = 2, 4, 5, 10, 13, \dots$), we have:

$$a^{560} \equiv 1 \pmod{561}$$

Try $a = 2$:

$$2^{560} \equiv 1 \pmod {561}$$

This makes 561 appear prime in Fermat's test, even though it is not.

#### Miller–Rabin Test

Probabilistic algorithm used to determine whether a number is likely to be prime. It builds upon **Fermat’s Little Theorem**, which states:

If $p$ is prime and $\gcd(a, p) = 1$, then
$a^{p-1} \equiv 1 \pmod{p}$

However, as we seen some **composite numbers** called **Carmichael Numbers** can pass this test for all bases $a \text{ coprime to } n \text{ i.e. } gcd(a, n) = 1$.
To address this, Miller–Rabin applies a stronger check.

#### Step-by-step Process

Let $n$ be an **odd** integer greater than 3. We write:

$$n - 1 = 2^r \cdot m \quad | \quad \text{with } m \text{ odd}$$

To extract this form, we repeatedly divide $n - 1$ by $2$ until the result becomes odd.
This step ensures we can express $n - 1$ as a product of a power of $2$ and an odd number.
This structure required for the repeated squaring test that follows.

Now, pick a random base $a$ such that $2 \le a \le n - 2$ and compute:

$$x = a^m \mod n$$

The base $a$ **passes** the test if:

- $x \equiv 1 \pmod{n}$
- $x \equiv -1 \pmod{n}$ at some step during repeated squaring, i.e.,
  $$a^{2^j m} \equiv -1 \pmod{n} \quad \text{for some } 0 \le j < r$$

If neither condition holds, then $n$ is definitely **composite**.

#### Probabilistic Guarantee

If $n$ passes this test for multiple random values of $a$, then it's **probably prime**.
The probability that a composite number passes **all** $k$ rounds is at most $(\frac{1}{4})^k$
This makes the test highly reliable even with a small number of rounds (e.g., $k = 20$).

### Functions
```c
bool is_carmichael_number(int n)
```
Checks if the number is a Carmichael number by verifying whether $a^{n-1} \equiv 1 \pmod n$ for all $a$ coprime to $n$.

**Parameters:**

- `int n`: The number to check

**Returns:**

- `bool`: True if $n$ is a Carmichael number; otherwise false.

---

```c
bool single_test(uint32_t m, uint32_t n);
```
Performs a single round of the Miller–Rabin test for a random base $a$.

**Parameters:**

- `int m`: The odd part of $n - 1$, i.e., $n - 1 = 2^r \cdot m$
- `int n`: The number being tested for primality

**Returns:**

`bool`: True if $n$ passes the round; otherwise false.

---
```c
bool check_primility(uint32_t n);
```
Performs 20 iterations of the Miller–Rabin test to determine whether a number is probably prime.

**Parameters:**

- `int n`: The number to test

**Returns:**

- `bool`: True if $n$ is probably prime; otherwise false.

---
```c
uint16_t rand_16_bits_number(void);
```
Generates a random 16-bit **odd** number with the first and last bit set to 1.

**Returns:**

- `uint16_t`: A random 16-bit odd number.

---
```c
uint16_t generate_16bits_prime(int *attempts);
```
Generates a 16-bit prime number using probabilistic testing.

**Parameters:**

- `int *attempts`: Pointer to an integer that will store how many attempts it took to find a prime (can be `NULL`)

**Returns:**

- `int uint16_t`: A 16-bit prime number.

---
```c
uint32_t rand_32_bits_number(void);
```
Generates a random 32-bit **odd** number with the first and last bit set to 1.

**Returns:**
- `int uint32_t`: A random 32-bit odd number.

---
```c
uint32_t generate_32bits_prime(int *attempts);
```
Generates a 32-bit prime number using probabilistic testing.

**Parameters:**

- `int *attempts`: A pointer to an integer that will store how many attempts it took to find a prime (can be `NULL`)

**Returns:**

- `uint32_t`: A 32-bit prime number.

---
## Diffie Hellman Key Exchange


This module implements a basic version of the Diffie Hellman key exchange protocol, including key pair generation, encryption, and decryption.

### Mathematical Background

Diffie–Hellman allows two parties to agree on a shared secret over an insecure channel.

Given:

- A large prime number $p$
- A generator $\alpha$ (primitive root modulo $p$)

Each party picks a **private key** (say $a$ and $b$), and computes their **public key**:

- $A = \alpha^a \pmod p$
- $B = \alpha^b \pmod p$

The shared secret is then computed as:

- Party A: $K = B^a \pmod p$
- Party B: $K = A^b \pmod p$

Since $A = \alpha^a$
We have: $A^b \equiv (\alpha^a)^b \equiv \alpha^{ab} \equiv \alpha^{ba} \equiv (\alpha^b)^a \equiv B^a\pmod{p}$
So both get the same result.

This shared secret can then be used to encrypt/decrypt messages.

---
### Functions
```c
uint64_t DH_generate_keyPair(int64_t p, int alpha);
```
Generates a public key using a random private key and the generator α modulo a large prime $p$.

**Parameters:**

- `int64_t p`: A large prime number used as the modulus.
- `int alpha`: A primitive root modulo $p` (the generator).

**Returns:**

- `uint64_t`: The generated public key.
---
```c
void DH_encrypt(int64_t p, int alpha, int64_t Kpub, int message, uint64_t *ephemeral_key, int64_t *cipher);
```
Encrypts a message using the recipient's public key and a randomly generated ephemeral key.

**Parameters:**

- `int64_t p`: The shared large prime modulus.
- `int alpha`: The generator used in key exchange.
- `int64_t Kpub`: The recipient's public key.
- `int message`: The message to encrypt.
- `uint64_t *ephemeral_key`: Output parameter for the generated ephemeral key.
- `int64_t *cipher`: Output parameter for the encrypted message.
---
```c
void DH_decrypt(int64_t p, int alpha, int64_t Keph, int64_t cipher, int64_t *message);
```
Decrypts a message using the received ephemeral key and the receiver's private key.

**Parameters:**

- `int64_t p`: The shared large prime modulus.
- `int alpha`: The generator used in key exchange.
- `int64_t Keph`: The received ephemeral key.
- `int64_t cipher`: The encrypted message.
- `int64_t *message`: Output parameter for the decrypted message.
---

## Elliptic Curve Arithmetic


This module implements elliptic curve arithmetic over a finite field. It supports point initialization, printing, and point addition using modular arithmetic.

### Mathematical Background

An **elliptic curve** over a finite field $\mathbb{F}_p$ (where $p$ is prime) is defined by an equation of the form:

$$y^2 \equiv x^3 + ax + b \pmod{p}$$

The set of points $(x, y)$ satisfying the curve equation, together with a special **point at infinity**, form an **abelian group** under a defined addition rule.

To add two points $P = (x_1, y_1)$ and $Q = (x_2, y_2)$ on the curve:

- If $P = Q$, use the tangent method:
  $$s = \frac{3x_1^2 + a}{2y_1} \mod p$$
- If $P \ne Q$, use the chord method:
  $$s = \frac{y_2 - y_1}{x_2 - x_1} \mod p$$

Then compute the resulting point $R = (x_3, y_3)$ using:
- $x_3 = s^2 - x_1 - x_2 \pmod p$
- $y_3 = s(x_1 - x_3) - y_1 \pmod p$

All divisions are performed using **modular inverses**.

Elliptic curves are widely used in cryptography, particularly in schemes like ECDH and ECDSA, because they offer strong security with smaller key sizes.

### Data Structures
```c
typedef struct EllipticCurve {
	int a;
	int b;
	int m;
} EllipticCurve;
```
Represents an elliptic curve defined over a finite field modulo `m`, using the equation:
$$y^2 \equiv x^3 + ax + b \pmod{m}$$

**Fields:**
- `int a`: Coefficient of the linear term $a \cdot x$
- `int b`: Constant term $b$
- `int m`: Modulus for the finite field arithmetic
---
```c
typedef struct EllipticCurvePoint {
	int x;
	int y;
} EllipticCurvePoint;
```
Represents a point $(x, y)$ on an elliptic curve.

**Fields:**

- `int x`: x-coordinate
- `int y`: y-coordinate

## Functions
```c
EllipticCurve *initEllipticCurve(int a, int b, int m);
```
Initializes a new elliptic curve defined by the equation:

$$y^2 \equiv x^3 + ax + b \pmod{m}$$

**Parameters:**

- `int a`: coefficient of the linear term.
- `int b`: constant term.
- `int m`: modulus of the finite field.

**Returns:**

- `EllipticCurve *`: A pointer to a newly allocated `EllipticCurve` structure.

---
```c
EllipticCurvePoint *initEllipticCurvePoint(int x, int y);
```
Creates and returns a point on the elliptic curve.

**Parameters:**

- `int x`: x-coordinate.
- `int y`: y-coordinate.

**Returns:**

- `EllipticCurvePoint *`: A pointer to a new `EllipticCurvePoint` structure.

---
```c
EllipticCurvePoint *copyEllipticCurvePoint(EllipticCurvePoint *point);
```
Returns a copy of the given point.

**Parameters:**

- `EllipticCurvePoint *point`: pointer to an existing `EllipticCurvePoint`.

**Returns:**

- `EllipticCurvePoint *`: New dynamically allocated point with the same coordinates.
 
---
```c
EllipticCurvePoint *add_two_point_on_curve(EllipticCurvePoint *point1, EllipticCurvePoint *point2, EllipticCurve *curve);
```
Adds two points on an elliptic curve using modular arithmetic.

**Parameters:**

- `EllipticCurvePoint *point1`: first point.
- `EllipticCurvePoint *point2`: second point.
- `EllipticCurve *curve`: the elliptic curve over which the addition is performed.

**Returns:**

- `EllipticCurvePoint *`: Pointer to the resulting point, or `NULL` if the denominator is zero or the result is the point at infinity.

---
```c
bool isPointsEqual(EllipticCurvePoint *point1, EllipticCurvePoint *point2);
```
Checks if two points have the same coordinates.

**Parameters:**

- `EllipticCurvePoint *point1`: first point.
- `EllipticCurvePoint *point2`: second point.

**Returns:**

`bool`: `true` if the points are equal, `false` otherwise.

---
```c
void printEllipticCurve(EllipticCurve *curve);
```
Prints the equation of the elliptic curve in readable form.

**Parameters:**

- `EllipticCurve *curve`: pointer to the elliptic curve.

---
```c
void printEllipticCurvePoint(EllipticCurvePoint *point);
```
Prints the coordinates of a point.

**Parameters:**

- `EllipticCurvePoint *point`: pointer to the elliptic curve point.

---

## Discrete Logarithm Solvers

This module provides algorithms to solve the Discrete Logarithm Problem (DLP) using Baby-Step Giant-Step (BSGS) and Pollard's Rho methods. It also includes a helper for solving linear congruences.

### Mathematical Background

#### Baby-Step Giant-Step (BSGS)

The DLP is:
**Given** integers $g$, $y$, and prime $p$, **find** $x$ such that:

$$g^x \equiv y \pmod p$$

Let $m = \left\lceil \sqrt p \right\rceil$

Then any exponent $x$ can be written as $x = im + j$.
Rewriting:

$$
g^{im} * g^j \equiv y \pmod p \\
$$
Can be written as:
$$
g^j \equiv y * (g^{-m})^i \pmod p
$$

Which motivates the algorithm to:

1. Compute all **baby steps**: $g^j \pmod p \text{ for } j = 0 \text{ to } m-1$
2. Compute all **giant steps**: $y * (g^{-m})^i \pmod p \text{ for } i = 0 \text{ to } m-1$.
3. Match values to recover $x = im + j$.

- **Time complexity:** $O(\sqrt{p})$
- **Space complexity:** $O(\sqrt{p})$

---
#### Pollard's Rho for DLP

Pollard’s Rho is a **probabilistic** method for solving:

$$g^x \equiv y \pmod p$$

It generates a sequence of the form:

$$r_{k} \equiv g^{a_k} * y^{b_k} \pmod p$$

The sequence is partitioned into 3 regions based on $r \mod 3$.
Each region updates `(a, b)` differently:

- If `r % 3 == 0`: `a += 1`
- If `r % 3 == 1`: `b += 1`
- If `r % 3 == 2`: `a *= 2`, `b *= 2`

When a cycle is detected (like Floyd’s algorithm), we solve:

$g^{a_1} * y^{b_1} ≡ g^{a_2} * y^{b_2} \pmod p \implies$ Reduce to a linear congruence: $B \cdot x \equiv A \mod (p − 1)$

- **Time complexity:** $O(\sqrt p)$
- **Space complexity:** $O(1)$
---

## Functions

```c
int64_t *linearCongruence(int64_t a, int64_t b, int64_t n, int64_t *size);
```
Solves the linear congruence:
$a \cdot x ≡ b \pmod n$

**Parameters:**

- `int64_t a`: multiplier on x
- `int64_t b`: target value
- `int64_t n`: modulus
- `int64_t *size`: output parameter for number of solutions

**Returns:**

- `int64_t *`: array of all solutions (length given by `*size`)

---

```c
uint64_t *BSGS_solve(int g, int y, int p);
```

Solves the discrete logarithm using Baby-Step Giant-Step:
$g^x \equiv y \pmod p$

**Parameters:**

- `int g`: generator
- `int y`: target value
- `int p`: prime modulus

**Returns:**

- `uint64_t *`: pointer to `x` if a solution exists, otherwise `NULL`

---
```c
int64_t *pollard_solve(int g, int y, int p);
```
Solves the discrete logarithm using Pollard’s Rho:
$g^x ≡ y \pmod p$

**Parameters:**

- `int g`: generator
- `int y`: target value
- `int p`: prime modulus

**Returns:**

- `int64_t *`: pointer to `x` if a solution is found, otherwise `NULL`

---

## Rivest–Shamir–Adleman (RSA)

This module implements RSA key generation, encryption, and decryption using modular exponentiation, modular inverse, and the Chinese Remainder Theorem for optimization.

### Mathematical Background

RSA is based on the difficulty of factoring large numbers. The steps are:

1. Choose two distinct large primes: $p$ and $q$
2. Compute $n = p \cdot q$
3. Compute $\varphi(n) = (p - 1)(q - 1)$
   - **Euler’s Totient Function** $\varphi(n)$ counts the number of integers in $\{1, 2, ..., n - 1\}$ that are coprime to $n$. i.e. $\gcd(\varphi(i),n) = 1$.
   - If $p$ is prime, then $\varphi(p)$ is calculated to be $p - 1$
4. Choose public key $e$ such that $\gcd(e, \varphi(n)) = 1$
5. Compute private key $d$ such that:
   $$d \cdot e \equiv 1 \pmod{\varphi(n)}$$

**Encryption:**
Given public key $(e, n)$ and message $m$:
$$\text{cipher} \equiv m^e \pmod{n}$$

**Decryption:**
Using private key $d$:
$$\text{message} \equiv \text{cipher}^d \pmod{n}$$

To improve efficiency, decryption is performed using the **Chinese Remainder Theorem (CRT)**:

$$
m_p = c^{d \bmod (p-1)} \bmod p
$$
$$
m_q = c^{d \bmod (q-1)} \bmod q
$$

Then combine $m_p$ and $m_q$ using CRT to recover the message modulo $n$.

## Functions

```c
void RSA_generate_keyPair(uint32_t *e, uint32_t *n);
```
Generates RSA key pair: public exponent $e$ and modulus $n$.
Internally chooses random 16-bit primes $p$, $q$ and ensures $\gcd(e, \varphi(n)) = 1$.

**Parameters:**
- `uint32_t *e`: output parameter for the public exponent
- `uint32_t *n`: output parameter for the modulus $n = p \cdot q$

---
```c
void RSA_encrypt(uint64_t n, uint64_t Kpub, uint64_t message, uint64_t *cipher);
```
Encrypts a message using RSA public key.

**Parameters:**

- `uint64_t n`: RSA modulus
- `uint64_t Kpub`: RSA public exponent (e)
- `uint64_t message`: plaintext message to encrypt
- `uint64_t *cipher`: output parameter to store the ciphertext

---
```c
void RSA_decrypt(int64_t Kpub, uint64_t cipher, int64_t *message);
```

Decrypts the RSA ciphertext using the stored primes and Chinese Remainder Theorem (CRT).

**Parameters:**

- `int64_t Kpub`: public exponent (used to compute private key)
- `uint64_t cipher`: ciphertext to decrypt
- `int64_t *message`: output parameter to store the decrypted message

---


## Digital Signature Algorithm (DSA)

This module implements the DSA key generation, signature, and verification process over a finite field using modular arithmetic.

### Mathematical Background

DSA is used to produce and verify digital signatures. It is based on the hardness of the discrete logarithm problem.

To set up:

1. Choose a **safe prime** $p$ and a prime $q$ such that:
   $$p = 2q + 1$$
2. Choose a generator $\alpha$ of the subgroup of order $q$ in $\mathbb{Z}_p^*$
3. Generate a private key $d \in \{1, ..., q - 1\}$
4. Compute the public key:
   $$\beta = \alpha^d \mod p$$

---

**Signature Generation** for a message $m$:

1. Select a random ephemeral key $k \in \{1, ..., q - 1\}$
2. Compute: $r = (\alpha^k \mod p) \mod q$
3. Compute: $s = k^{-1}(\text{message} + d \cdot r) \mod q$

---

**Signature Verification** for $(r, s)$:

1. Compute: $w = s^{-1} \mod q$
2. Compute: 
	- $u_1 = \text{message} \cdot w \mod q$
	- $u_2 = r \cdot w \mod q$
4. Compute: $v = ((\alpha^{u_1} \cdot \beta^{u_2}) \mod p) \mod q$
5. The signature is valid if: $v = r$

---

## Functions

```c
void DSA_sign_and_verify(uint64_t p, uint64_t q, int alpha, int message);
```
Generates keypair, signs the message, and verifies the signature.

**Parameters:**

- `uint64_t p`: safe prime modulus
- `uint64_t q`: prime such that `p = 2q + 1`
- `int alpha`: generator of subgroup of order `q`
- `int message`: message to sign

---
```c
uint64_t DSA_generate_keyPair(uint64_t p, uint64_t q, int alpha);
```

Generates a random private key and returns the corresponding public key.

**Parameters:**

- `uint64_t p`: safe prime
- `uint64_t q`: prime divisor of `p-1`
- `int alpha`: generator

**Returns:**

- `uint64_t`: public key (beta = alpha^d mod p)

---
```c
void DSA_sign(uint64_t p, uint64_t q, int alpha, int message, uint64_t *r, uint64_t *s);
```
Signs a message using the DSA private key.

**Parameters:**

- `uint64_t p`: prime modulus
- `uint64_t q`: prime divisor
- `int alpha`: generator
- `int message`: message to sign
- `uint64_t *r`: output parameter for signature part r
- `uint64_t *s`: output parameter for signature part s

---
```c
bool DSA_verify(uint64_t p, uint64_t q, int alpha, uint64_t public_key, uint64_t r, uint64_t s, int message);
```
Verifies a DSA signature.

**Parameters:**

- `uint64_t p`: prime modulus
- `uint64_t q`: prime divisor
- `int alpha`: generator
- `uint64_t public_key`: public key $\beta$
- `uint64_t r`: signature component
- `uint64_t s`: signature component
- `int message`: original message

**Returns:**
- `bool`: `true` if signature is valid, otherwise `false`

---

## RC4 Stream Cipher

This module implements the RC4 stream cipher, a symmetric key encryption algorithm known for its simplicity and speed. It includes key scheduling, keystream generation, encryption, and decryption.

### Mathematical Background

RC4 generates a **keystream** by initializing a permutation of the numbers $0$ through $255$ (i.e., $S[0 \ldots 255]$ using a **key scheduling algorithm (KSA)**. Then, it produces a pseudorandom keystream using the **pseudo-random generation algorithm (PRGA)**.

Encryption and decryption are symmetric and use the XOR operation:

- **Encryption:** $C_i = P_i \oplus K_i$
- **Decryption:** $P_i = C_i \oplus K_i$

Where:
- $C_i$ is the ciphertext byte
- $P_i$ is the plaintext byte
- $K_i$ is the keystream byte
- $\oplus$ denotes bitwise XOR

---

### Functions

```c
void print_key_stream(uint8_t *keystream);
```
Prints the 256-byte keystream as hexadecimal values.

**Parameters:**

- `uint8_t *keystream`: pointer to the keystream array.

---

```c
uint8_t *RC4_init(char *key);
```
Initializes the RC4 cipher and generates a 256-byte keystream using the provided key.

**Parameters:**

- `char *key`: null-terminated string used as the key.

**Returns:**

- `uint8_t *`: pointer to a dynamically allocated keystream array.

---

```c
uint8_t *RC4_encrypt(char *string, uint8_t *keyStream);
```
Encrypts a string using the RC4 keystream.

**Parameters:**

- `char *string`: null-terminated plaintext string.
- `uint8_t *keyStream`: the 256-byte keystream.

**Returns:**

- `uint8_t *`: pointer to the dynamically allocated ciphertext.

---

```c
char *RC4_decrypt(char *cipher, uint8_t *keyStream);
```
Decrypts a ciphertext using the RC4 keystream. This is functionally the same as encryption.

**Parameters:**

- `char *cipher`: ciphertext data (as char pointer).
- `uint8_t *keyStream`: the 256-byte keystream.

**Returns:**

- `char *`: pointer to the decrypted plaintext.

---