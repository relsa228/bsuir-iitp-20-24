import random

from random_generator import generator

def generator_test_3(probability_a, conditional_probability):
    ab = probability_a * conditional_probability
    a_no_b = probability_a * (1 - conditional_probability)
    no_a_b = (1 - probability_a) * (1 - conditional_probability)
    no_a_no_b = 1 - ab - a_no_b - no_a_b
    
    ab = round(ab, 3)
    a_no_b = round(a_no_b, 3)
    no_a_b = round(no_a_b, 3)
    no_a_no_b = round(no_a_no_b, 3)
    
    print(f"Probabilities:\n0. {ab},\n1. {a_no_b},\n2. {no_a_b},\n3. {no_a_no_b}\n")

    my_zero = 0
    my_one = 0
    my_two = 0
    my_three = 0
    error = 0
    
    for i in range(0, 100000):
        result = generator([0, 1, 2, 3], [ab, a_no_b, no_a_b, no_a_no_b])    
        match result:
            case 0:
                my_zero += 1
            case 1:
                my_one += 1
            case 2:
                my_two += 1
            case 3:
                my_three += 1
            case -100500:
                error += 1


    zero = 0
    one = 0
    two = 0
    three = 0
    
    for i in range(0, 100000):
        result = random.choices([0, 1, 2, 3], weights=[ab, a_no_b, no_a_b, no_a_no_b])    
        match result:
            case [0]:
                zero += 1
            case [1]:
                one += 1
            case [2]:
                two += 1
            case [3]:
                three += 1
                
    print(f"--- Test 3. Results ---" +
          f"\n\nVariant 0 (my generator): {my_zero}\nVariant 0 (python generator): {zero}" +
          f"\n\nVariant 1 (my generator): {my_one}\nVariant 1 (python generator): {one}" +
          f"\n\nVariant 2 (my generator): {my_two}\nVariant 2 (python generator): {two}" +
          f"\n\nVariant 3 (my generator): {my_three}\nVariant 3 (python generator): {three}")
    