import random
numbers_total = list(range(2, 60 + 1))
numbers_list=list(range(2, 30 + 1))
weights_t = [1] * len(numbers_total)
weights_l = [1] * len(numbers_list)

max_total_values = random.choices(numbers_total, weights_t)[0]
print(f"max: {max_total_values}" )


sum_total = 0
dictionary_lists = {}

list_counter = 0
initial_word = random.choice(["con\"", "sec\""])
previous_word = initial_word

while sum_total != max_total_values:
    # Genera una lista de números sin repetición
    minimo=min(30, max_total_values - sum_total)
    if (minimo==1):
        break
    numbers_random = list(range(2, min( 30, max_total_values - sum_total) + 1))
    print(f"numer: {numbers_random}")
    # Asigna el mismo peso a cada número (en este caso, 1)
    weights_n = [1] * len(numbers_random)

    # Elige un número aleatorio con igual probabilidad
    random_number = random.choices(numbers_random, weights_n)[0]

    if sum_total + random_number <= max_total_values:
        sum_total += random_number
    else:
        continue

    if previous_word == "con\"":
        current_word = "sec\""
    else:
        current_word = "con\""

    key = f"\"{list_counter}_{current_word}"

    # Genera números aleatorios con igual probabilidad utilizando random.choices
    if current_word == "con\"":
        # Crear población excluyendo valores ya seleccionados en "con\""
        population = set(range(60)) - set(dictionary_lists.get(f"\"{list_counter}_con\"", []))
        random_numbers = random.choices(list(population), k=random_number)
    else:
        random_numbers = random.choices(range(60), k=random_number)

    dictionary_lists[key] = random_numbers
    list_counter += 1
    previous_word = current_word


print("Total sum:", sum_total)
print("Dictionary of lists:")
for key, lista in dictionary_lists.items():
    print(key, lista)
"""
file=dir_tutti+"/log/Tesis/mision_variables/activities.txt"
with open(file, "a") as f:        
    for key, lista in dictionary_lists.items():
        print(f'{key}: {lista}')  
        lista_str = ', '.join(map(str, lista))
        f.write("\n") 
        f.write("activities[" + key + "] = {" + lista_str + "};")
"""
