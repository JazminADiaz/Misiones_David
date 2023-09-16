import random

sum_total = 0  # Initialize the sum to 0
dictionary_lists = {}  # Initialize a dictionary to store the lists

list_counter = 1  # Initialize a counter for dictionary keys

while sum_total != 20:
    random_number = random.randint(1, 20)
    if sum_total + random_number <= 20:
        sum_total += random_number
    else:
        continue  # Skip adding a list if it exceeds 20
    
    initial_word = random.choice(["con", "sec"])
    key = f"{list_counter}_{initial_word}"  # Key format
    random_numbers = [random.randint(1, 60) for _ in range(random_number)]
    dictionary_lists[key] = random_numbers
    list_counter += 1

print("Total sum:", sum_total)
print("Dictionary of lists:")
for key, lista in dictionary_lists.items():
    print(f'"{key}": {lista}')