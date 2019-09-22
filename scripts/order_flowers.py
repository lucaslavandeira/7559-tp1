import sys

order_path = sys.argv[1]

with open(order_path, 'rb') as f:
    total_roses = 0
    total_tulips = 0
    for line in f:
        roses, tulips = line.split()
        total_roses += int(roses)
        total_tulips += int(tulips)

print(f'Count: {total_roses} roses, {total_tulips} tulips')
