import random

from random_generator import generator

def generator_4(probabilities):
    variants = [x for x in range(0, len(probabilities))]
    count = [0 for x in range(0, len(probabilities))]
    my_count = [0 for x in range(0, len(probabilities))]
    
    for i in range(0, 100000):
        result = random.choices(variants, weights=probabilities)
        count[result[0]] += 1
    
    for i in range(0, 100000):
        result = generator(variants, probabilities)
        my_count[result] += 1
        
    print(f"--- Test 4. Results ---")
    for i in range(0, len(variants)):
        print(f"\nVariant {variants[i]} (my generator): {my_count[i]}")
        print(f"Variant {variants[i]} (python generator): {count[i]}")