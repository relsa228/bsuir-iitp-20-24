import math
import random 

def main_module(max_val):
    num_of_cycle = random.randrange(1, 1000000)
    mod = random.randrange(1, 1000000)
    k = random.randrange(0, mod)
    b = random.randrange(0, mod)
    r = random.randrange(0, mod)
    
    for i in range(0, num_of_cycle):
        r = (k * r + b) % mod
        
    return r % max_val

def generator(variants, probabilities):
    segments = []
    acc = 0
    
    for i in range(0, len(variants)):
        segments.append([acc, acc + probabilities[i]])
        acc += probabilities[i]
    
    prob_sum = sum(probabilities)
    
    dec_coeff = 0
    
    while True:
        if prob_sum * dec_coeff >= 1:
            break
        else:
            dec_coeff += 10
            
    prob_sum *= dec_coeff
    
    choice = main_module(prob_sum) / dec_coeff
    
    for i in range(0, len(variants)):
        if choice < segments[i][1] and choice >= segments[i][0]:
            return variants[i]
        
    return -100500 