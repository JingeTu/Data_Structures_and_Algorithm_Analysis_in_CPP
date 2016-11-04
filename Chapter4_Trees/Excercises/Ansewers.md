### 4.1

a. root: A

b. leaves: G, H, I, L, M, K

### 4.2

a.

A is the parent node for B, C.

B is the parent node for D, E.

C is the parent node for F.

D is the parent node for G, H.

E is the parent node for I, J.

F is the parent node for K.

J is the parent node for L, M.

b.

refer to a.

c.

refer to a.

d.

Depth 0 node(s): A.

Depth 1 node(s): B, C.

Depth 2 node(s): D, E, F.

Depth 3 node(s): G, H, I, J, K.

Depth 4 node(s): L, M.

e.

Height 0 node(s): G, H, I, L, M, K.

Height 1 node(s): D, J, F.

Height 2 node(s): E, C.

Height 3 node(s): B.

Height 4 node(s): A.

### 4.3

The depth of the tree is 4.

### 4.4

Every node except root is a child of another node in the tree.
A child-parent relation consumes a link.
N nodes have 2N links. The number of used links is N - 1.
So the `nullptr` links number is 2N-(N-1) = N + 1.

### 4.5

$2^0 + 2^1 + 2^2 + \cdot + 2^h = 2^{h+1} - 1$

### 4.6

Use the Conclusion from 4.4.

Set #(full nodes) = x, #(leaves) = y, #(nodes with one link) = z, #(all the nodes) = N.

Sum all the nodes, we get x+y+z = N.

Then sum all the `nullptr`, we get 2*y+z = N+1.

We get x+1 = y.

### 4.7

### 4.8

prefix: `-**ab+cde`

infix: `a*b*(c+d)-e`

postfix: `ab*cd+*e-`

a. 
```
after insertion
           9
               7
       6
           5
   4
3
       2
   1
```

b.
```
after deletion
       9
           7
   6
       5
4
       2
   1
```

### 4.11

./Ex_4_11_set.cpp