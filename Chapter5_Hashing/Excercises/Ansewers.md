### 5.1

a. separate chaining hash table

0: 4371

1: 

2:

3: 1323 -> 6173

4: 4344

5:

6:

7:

8:

9: 4199 -> 9679 -> 1989

b. linear probing hash table

0: 9679

1: 4371

2: 1989

3: 1323

4: 6173

5: 4344

6:

7:

8:

9: 4199

c. quadratic probing hash table

0: 9679

1: 4371

2:

3: 1323

4: 6173

5: 4344

6:

7:

8: 1989

9: 4199

d. double hash table

0:

1: 4371

2:

3: 1323

4: 6173

5: 9679

6:

7: 4344

8: 

9: 4199

rehash

0:

1:

2:

3: 1323

4: 4344

5:

6:

7:

8:

9: 1989

10:

11: 4371

12:

13: 6173

14:

15:

16:

17:

18:

19: 9679

### 5.2

a. separate chaining hash table

0:

1:

2:

3: 1323

4: 4344

5:

6:

7:

8:

9: 1989

10:

11: 4371

12:

13: 1673

14:

15:

16:

17:

18:

19: 4199 -> 9679

b. linear probing hash table

0:

1:

2:

3:

4:

5:

6:

7:

8:

9:

10:

11:

12:

13:

14:

15:

16:

17:

18:

19:

c. quadratic probing hash table

0: 4199

1:

2:

3: 1323

4: 4344

5:

6:

7:

8:

9: 1989

10:

11: 4371

12:

13: 6173

14:

15:

16:

17:

18:

19: 9679

### 5.3

./Ex_5_3_number_of_collisions.cpp

### 5.4

currentSize <= tableSize / 2

### 5.5

that is same with the implementation in the book.

### 5.6

```
template<typename HashedObj>
bool QuadraticProbingHashTable<HashedObj>::isEmpty() {
    return currentSize == 0;
}
```

### 5.7

a. 

```
int findPos(const HashedObj &x, int& firstInactivePos);
```

b.

When deletion is frequent