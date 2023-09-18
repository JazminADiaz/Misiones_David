import random
import random

sum_total = 0
dictionary_lists = {}

list_counter = 0
initial_word = random.choice(["con\"", "sec\""])
previous_word = initial_word

while sum_total != 20:
    random_number = random.randint(1, 20)
    if sum_total + random_number <= 20:
        sum_total += random_number
    else:
        continue

    if previous_word == "con\"":
        current_word = "sec\""
    else:
        current_word = "con\""

    key = f"\"{list_counter}_{current_word}"
    
    # Generate unique random numbers for each lista
    random_numbers = set()
    while len(random_numbers) < max(2, random_number):
        new_number = random.randint(1, 60)
        random_numbers.add(new_number)
    
    dictionary_lists[key] = list(random_numbers)
    list_counter += 1
    previous_word = current_word

print("Total sum:", sum_total)
print("Dictionary of lists:")
for key, lista in dictionary_lists.items():
    print(f'"{key}": {lista}')
print("Total sum:", sum_total)
print("Dictionary of lists:")
for key, lista in dictionary_lists.items():
    print(f'"{key}": {lista}')
