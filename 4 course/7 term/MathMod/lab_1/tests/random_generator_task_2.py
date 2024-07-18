import random
from random_generator import generator

def generator_test_2(weights):
    print(f"--- Test 2. Results ---\n")
    for weight in weights:
        zero = 0
        one = 0
        for i in range(0, 10000):
            result = generator([1, 0], [weight, 1-weight])
            if result == 1:
                one += 1
            else:
                zero += 1
        
        print(f"For item {weight} (my generator):\nzero: {zero}\n one: {one}\n")
        
        zero = 0
        one = 0
        for i in range(0, 10000):
            result = random.choices([1, 0], [weight, 1-weight])
            if result == [1]:
                one += 1
            else:
                zero += 1
        
        print(f"For item {weight} (python generator):\nzero: {zero}\n one: {one}\n\n")
        