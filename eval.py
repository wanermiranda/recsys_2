#!/usr/bin/python
import math 
import numpy as np
from scipy import stats
from sklearn.preprocessing import normalize
import matplotlib.pyplot as plt

OUTPUT_FILE = 'out.stat'
GROUND_TRUTH = 'ground_truth.txt' 

guesses = [line.rstrip('\n') for line in open(OUTPUT_FILE)]
ground = [line.rstrip('\n') for line in open(GROUND_TRUTH)]

error_sum = 0.0
n_items = 0.0
float_guesses = []
for idx in range(len(guesses)): 
	guess = float(guesses[idx])
	truth = float(ground[idx])
	float_guesses.append(guess)
	error = math.pow(truth - guess, 2)

	n_items += 1
	error_sum +=  error

n, min_max, mean, var, skew, kurt = stats.describe(float_guesses)

print "n"
print n
print "min_max"
print min_max
print "mean"
print mean
print "var"
print var
print "skew"
print skew
print "kurt"
print kurt


rmse = math.sqrt(error_sum / n_items)
mse = error_sum / n_items

print "RMSE ", rmse
print "MSE ", mse