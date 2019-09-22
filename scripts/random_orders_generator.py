import random

ORDERS = 10000

for i in range(ORDERS):
    roses = random.randint(0, 20)
    tulips = random.randint(0, 20)
    print(f'{roses} {tulips}')
