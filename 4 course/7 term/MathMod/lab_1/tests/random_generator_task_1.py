import random
from random_generator import generator

def generator_test_1(weight):
    
    my_one = 0
    my_zero = 0
    
    for i in range(0, 1000000):
        result = generator([1, 0], [weight, 1-weight])
        if result == 1:
            my_one += 1
        else:
            my_zero += 1
    
    one = 0
    zero = 0
    
    for i in range(0, 1000000):
        result = random.choices([1, 0], [weight, 1-weight])
        if result == [1]:
            one += 1
        else:
            zero += 1
        
    print(f"--- Test 1. Results ---" +
          f"\nZero (my generator): {my_zero}" +
          f"\nZero (python generator): {zero}" +
          f"\n\nOne (my generator): {my_one}" +
          f"\nOne (python generator): {one}")