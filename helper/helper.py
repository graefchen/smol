# █░█ █▀▀ █░░ █▀█ █▀▀ █▀█
# █▀█ ██▄ █▄▄ █▀▀ ██▄ █▀▄
# a small script that helps you when you are undecided
#
# inspired by my (@graechen) stupidness and Myrallia's small input over discord
# with the message to my small minimum "proof of work":
# ```
# import random
# if random.randint(0,1) == 1:
#   print("yes")
# else:
#   print("no")
# ```
# the input:
# > needs, try again. Repeat the question. Maybe. Definitely
# 
# resulting in this stupid program

import random

rnd = random.randint(0,5)

match rnd:
    case 0: print("no")
    case 1: print("yes")
    case 2: print("try again later")
    case 3: print("repeat the question")
    case 4: print("maybe")
    case 5: print("definitely")
