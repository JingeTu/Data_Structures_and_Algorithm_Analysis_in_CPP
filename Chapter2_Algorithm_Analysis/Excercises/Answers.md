### 2.1

$ 2/N, 37, \sqrt{N}, N, N\log{\log{N}}, N\log{N}, N\log{N^2}, N\log^2{N}, N^{1.5}, N^2, N^2\log{N}, N^3, 2^{N/2}, 2^N $

### 2.2

a T
b F
c T
d F

### 2.3

$\lim_{n\to+\infty}{\epsilon\over\sqrt{\log{N}}} = 0$
$\therefore N\log{N}$ grows faster.

### 2.4

use L'Hopital rule
$\lim_{n\to+\infty}{N\over\log^k{N}} = \lim_{n\to+\infty}{N\over{k\log^{k-1}{N}\log{e}}} = \lim_{n\to+\infty}{N\over{k(k-1)(k-2)\cdots1\log^{k}{e}}} = +\infty$
$\therefore \log^k{N}=o(N)$

### 2.5

We can get $f(N)\leq{g(N)}$ and $g(N)\leq{f(N)}$ are false.
$\therefore$ There is not specific relation between $f(N), g(N)$.
Set $f(N) = \sin{N}, g(N) = \cos{N}$.

### 2.6

a. $2^{2^{N-1}}$
b. $\log{\log{D}} + 1$

### 2.7

a.
(1) $O(N)$
(2) $O(N^2)$
(3) $O(N^3)$
(4) $\sum_{i=0}^{n-1}i = {(n-1)n\over{2}} = O(N^2)$
(5) $\sum_{i=0}^{n-1}\sum_{j=0}^{i^2-1}j = \sum_{i=0}^{n-1}{{i^4-i^2}\over{2}} = O(N^5)$
(6) $\sum_{i=1}^{n-1}(\sum_{j=1}^{i-1}j*i+\sum_{j=1}^{i^2-1}1) = \sum_{i=1}^{n-1}({i^2(i^2-1)\over{2}}+{i^2(i^2-1)\over{2}}) = \sum_{i=1}^{n-1}{i^2(i^2-1)}=O(N^5)$

### 2.8

a.

a.1.

{a[0], a[1]} are distinct.

{a[0], a[1], a[2]} are distinct.

...

{a[0], a[1], ..., a[N - 1]} are distinct.

So alg1. generate legal permutations.

a.2.

{a[0], a[1], ..., a[N - 1]} are N numbers.

{used[0], used[1], ..., used[N - 1]} are all true, then suggesting [1, N] are in the a array. 
[1, N] are N distinct numbers, so {a[0], a[1], ..., a[N - 1]} is legal permutation.

a.3.

b.

b.1.

In one random generation, the probability of get a number in a[0:i-1] is i/N and get a legal number is (N-i)/N.

There is equal probability of randomly generating a[j] (j = 0, 1, ..., i - 1), when we have know it's in a[0:i-1].

And the probability is 1/i.

The time cost expectation in one failure in finding the legal number is set to A. A is a function of i, so write A as A(i). We can get A(i):

$A(i) = {1 \over i}\sum_{j=1}^{i}{j} = {i(i+1)} \over {2i}$

The expectation in generating a[i] is a sum of mathematical progression.

$B(i) = \sum_{k=1}^{\infty}({N - i \over N})^k({N \over N})^{k-1}(k*A+1)$

So the final time cost expectation of alg1. is C:

$C = \sum_{i=0}^{N-1}B(i)$

b.2.

Like alg1. set A(i) to a constant, becasue we have constant cost for finding if a number has been used.

$A(i) = 1$

b.3.

O(3N)

c.

./2_8_c.cpp

### 2.9

### 2.10