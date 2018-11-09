# Multiprocessing Producer-Consumer

Demonstration of multiprocessing using two programs, producer and consumer. Start producer first.

## Requirements

1. C++17 
1. POSIX shared memory, #include <sys/mman.h>
1. POSIX System V semaphores, #include <sys/sem.h>
1. CMakeLists.txt
1. README.txt file describing implementation 

## Producer

1. The producer produces a random floating point number (product) 
1. Products are made at random intervals between 0.5 and 1.5 seconds each
1. Products are numbered sequentially
1. Numbered products are printed and then passed to the consumer
1. For 1 out of 20 products, a product is dropped and not passed to the consumer.
1. Products are passed in a queue protected by semaphores
1. The queue can hold 5 products
1. If the queue is full when a product is produced, the producer outputs
"DROPPED <#>" and continues

## Consumer

1. The consumer consumes numbered products 
1. The consumer consumes products at a slower rate than the producer
produces them, there may be multiple products produced before the consumer
consumes the task. 
1. Products are consumed at random intervals between 1.0 and 3.0 seconds
1. Products are printed to the screen
1. If a product number is skipped in sequence, the consumer outputs 0.0 for that sequence number

## Producer Example Output

1 0.4395116517359974
2 0.07296093346964816
3 0.23989517451159492
4 0.9214004505330191
5 0.23692077473430806
6 0.5565227807496207
7 0.3635783890022559
9 0.8505558785920253
10 0.10421790588732671
12 0.3159450030396609
13 0.13638449049289925
DROPPED 13
14 0.8564636018393292
15 0.010106680565449055

## Consumer Example Output

1 0.4395116517359974
2 0.07296093346964816
3 0.23989517451159492
4 0.9214004505330191
5 0.23692077473430806
6 0.5565227807496207
7 0.3635783890022559
8 0.0
9 0.8505558785920253
10 0.10421790588732671
11 0.0
12 0.3159450030396609
13 0.0
14 0.8564636018393292
15 0.010106680565449055

