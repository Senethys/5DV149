# Givna datatyper

Här återfinns implementationer av några av de datatyper som kommer användas
under denna kurs. Nedan följer information om hur dessa kompileras och hur
`minimal working examples` körs för varje datatyp.

## Headerfiler

Headerfilerna för de givna datatyperna är alla samlade i mappen `include`. Dessa
kan inkluderas med hjälp av `-I`-flaggan till `gcc`, se exempel nedan.

## undefined reference

Det är möjligt att du får t.ex. följande felmeddelande:

```bash
/tmp/ccLd0e5H.o: In function `queue_empty':
queue.c:(.text+0x14): undefined reference to `list_empty'
```

Detta innebär att du inte anget alla nödvändiga C-filer till kompilatorn. I
fallet ovan saknas `list.c`.

# En-dimensionellt fält

```bash
dali@kvicksand:~/datastructures/src$ gcc -std=c99 -Wall -I../include/ array_1d/array_1d.c array_1d/array_1d_mwe.c -o array_1d_mwe
dali@kvicksand:~/datastructures/src$ ./array_1d_mwe
[ [1], [4], [9], [16], [25], [36] ]
[ [(Jan, 31)], [(Feb, 28)], [(Mar, 31)], [(Apr, 30)], [(May, 31)], [(Jun, 30)], [(Jul, 31)], [(Aug, 31)], [(Sep, 30)], [(Oct, 31)], [(Nov, 30)], [(Dec, 31)] ]
```
# Två-dimensionellt fält

```bash
dali@kvicksand:~/datastructures/src$ gcc -std=c99 -Wall -I../include/ array_2d/array_2d.c array_2d/array_2d_mwe.c -o array_2d_mwe
dali@kvicksand:~/datastructures/src$ ./array_2d_mwe
[ [ [11], [12], [13] [ [21], [22], [23] [ [31], [32], [33] [ [41], [42], [43] ]
```
# Dubbellänkad lista

```bash
dali@kvicksand:~/datastructures/src$ gcc -std=c99 -Wall -I../include/ list/list.c list/list_mwe.c -o list_mwe
dali@kvicksand:~/datastructures/src$ ./list_mwe
List after inserting one value:
( [5] )
List after inserting second value at the end:
( [5], [8] )
List after inserting a third value in the middle:
( [5], [2], [8] )
Free'ing [5]
List after removing first element:
( [2], [8] )
Free'ing [2]
Free'ing [8]
```

# Riktad lista

```bash
dali@kvicksand:~/datastructures/src$ gcc -std=c99 -Wall -I../include/ dlist/dlist.c dlist/dlist_mwe.c -o dlist_mwe
dali@kvicksand:~/datastructures/src$ ./dlist_mwe
("Alfons", "Bengt", "Cia", "David", "Florian", "Gunnar")
```

# Kö

```bash
dali@kvicksand:~/datastructures/src$ gcc -std=c99 -Wall -I../include/ queue/queue.c queue/queue_mwe.c list/list.c -o queue_mwe
dali@kvicksand:~/datastructures/src$ ./queue_mwe
QUEUE before dequeuing:
{ [1], [2], [3] }
QUEUE after dequeuing:
{ [2], [3] }
--QUEUE before dequeueing--
{ [1], [2], [3] }
--QUEUE after dequeueing--
{ [2], [3] }
```


# Stack

```bash
dali@kvicksand:~/datastructures/src$ gcc -std=c99 -Wall -I../include/ stack/stack.c stack/stack_mwe.c -o stack_mwe
dali@kvicksand:~/datastructures/src$ ./stack_mwe
--STACK before popping--
{ [3], [2], [1] }
--STACK after popping--
{ [2], [1] }
--STACK before popping--
{ [3], [2], [1] }
--STACK after popping--
{ [2], [1] }
```

# Tabell (aktuell senare)

```bash
dali@kvicksand:~/datastructures/src$ gcc -std=c99 -Wall -I../include/ table/table.c table/table_mwe.c dlist/dlist.c -o table_mwe
dali@kvicksand:~/datastructures/src$ ./table_mwe
[5, test]
```
