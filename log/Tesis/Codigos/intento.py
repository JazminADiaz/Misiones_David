import random

sumatoria = 0  # Inicializa la sumatoria en 0
diccionario_listas = {}  # Inicializa un diccionario para almacenar las listas

contador_listas = 1  # Inicializa un contador para las claves del diccionario

while sumatoria != 20:
    numero_aleatorio = random.randint(1, 20)
    if sumatoria + numero_aleatorio <= 20:
        sumatoria += numero_aleatorio
    else:
        continue  # Evita que se agregue una lista si supera 20
    
    palabra_inicial = random.choice(["con", "sec"])
    clave = f"{contador_listas}_{palabra_inicial}"  # Formato de la clave
    numeros_aleatorios = [random.randint(1, 60) for _ in range(numero_aleatorio)]
    diccionario_listas[clave] = numeros_aleatorios
    contador_listas += 1

print("Sumatoria total:", sumatoria)
print("Diccionario de listas:")
for clave, lista in diccionario_listas.items():
    print(f'"{clave}": {lista}')