from bs4 import BeautifulSoup as bs

import os, glob

import shutil
from IPython.utils.io import capture_output
import random
import matplotlib.pyplot as plot
import pandas as pd
import numpy as np
import glob
import os
import seaborn as sns
from datetime import date
from IPython.display import Markdown, display
import matplotlib.pyplot as plt
import pm4py
from pm4py.objects.conversion.log import converter as log_converter
from pm4py.visualization.petri_net import visualizer as pn_visualizer
from pm4py.objects.petri_net.utils.decomposition import decompose
from pm4py.objects.petri_net.utils import reachability_graph
from pm4py.visualization.transition_system import visualizer as ts_visualizer


def activities():
    if mision_activities=="manual":   
        ################################ ADD THE ACTIVITIES #######################################################     #delete previos content
        file=dir_tutti+"/log/Tesis/mision_variables/activities.txt"
        with open(file, "w") as f:
            f.write("activities[\"0_sec\"] = {0,22,23};")
            f.write("\n") 
            f.write("activities[\"1_con\"] = {31,25,26};")

            ################################ ADD THE ACTIVITIES #######################################################

    if mision_activities=="random":
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

        file=dir_tutti+"/log/Tesis/mision_variables/activities.txt"
        with open(file, "a") as f:        
            for key, lista in dictionary_lists.items():
                print(f'{key}: {lista}')  
                lista_str = ', '.join(map(str, lista))
                f.write("\n") 
                f.write("activities[" + key + "] = {" + lista_str + "};")


def simulacion(directorio, repetition, time):
    filelist = glob.glob(os.path.join(directorio, "*"))
    for f in filelist:
        os.remove(f)

    for b in range(1, repetition + 1):
        with open(f"/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/tuttiTamT.argos") as fp:
            soup = bs(fp, 'html.parser')
        
        tag = soup.experiment
        tag['random_seed'] = b
        
        with open("/home/jazmin/tuttifrutti/log/Tesis/mision_variables/seed.txt", "w"):
            pass
        
        with open("/home/jazmin/tuttifrutti/log/Tesis/mision_variables/seed.txt", "a") as f:
            f.write("\n")
            f.write(f"s= \"{b}\";\n")
            f.write(f"events_folder= \"{directorio}\";\n")
            f.write(f"timer_simulation= {time};\n")
        
        with open(f"/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/tuttiTamT.argos", "w") as outf:
            outf.write(str(soup))
        
        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/build')
        os.system('make')
        os.chdir('/home/jazmin/tuttifrutti/experiments-loop-functions/scenarios/tuttifrutti/')
        #os.system("cd ~/tuttifrutti/experiments-loop-functions/build")
        os.system("argos3 -c tuttiTamT.argos")

def copy_folder(source, destination):
    try:
        # Create the new folder if it doesn't exist
        if not os.path.exists(destination):
            os.mkdir(destination)
        # Use the `copytree` function from shutil to copy the folder and its contents
        shutil.copytree(source, os.path.join(destination, os.path.basename(source)))
        print(f"Folder '{os.path.basename(source)}' copied to {destination}")
    except Exception as e:
        print(f"Unable to copy the folder: {e}")

def copy_file(source, destination):
    try:
        # Use the `copy` function from shutil to copy the file
        shutil.copy(source, destination)
        print(f"File copied from {source} to {destination}")
    except Exception as e:
        print(f"Unable to copy the file: {e}")


def concatenate(folder):
    filenames = glob.glob(folder + "/*.csv")
    dfs = []
    model=0
    for filename in filenames:
        log = pd.read_csv(filename, sep=',')
        case_id=[]
        case_id += len(log.mision) * ["mision "+str(model)]
        log['mision']=case_id
        model+=1
        dfs.append(log)
        big_frame = pd.concat(dfs, ignore_index=True)
        if model==len(filenames):
            big_frame.to_csv(dir_tutti+'/log/Tesis/LogFinal/final_log_2.csv', sep=',', index=False)

#from my_simulation import simulacion  

#This is the only line for the directory you should need to change
dir_tutti="/home/jazmin/tuttifrutti"

#use the word "manual" or "random"
mision_activities="random"

#probability from 0 to 1
fixed_prob="probability=0.8;"

#number of times the mision is repeated to be stored in one log
repetition_numer=20

#duration of the simulation in seconds
timer=80000

file=dir_tutti+"/log/Tesis/mision_variables/activities.txt"
file_send=dir_tutti+"/log/Tesis/EventLogs/"
with open(file, "w") as f:
    f.write("probability=1;")
activities()

simulacion(file_send, repetition_numer, timer)
print("Simulación completada.")


file=dir_tutti+"/log/Tesis/mision_variables/activities.txt"
file_send=dir_tutti+"/log/Tesis/EventLogs_fail/"
with open(file, "r") as archivo:
    lineas = archivo.readlines()
lineas[0] = fixed_prob+"\n"
with open(file, "w") as archivo:
    archivo.writelines(lineas)

simulacion(file_send, repetition_numer, timer)

# Directory where you want to search for folders
directory = dir_tutti+"/log/Tesis/"

# Prefix that should be in the folder names
prefix = "example"

# Find all folders with the "example" prefix in the name
folders = [name for name in os.listdir(directory) if prefix in name]

# Find the highest number in the folder names
numbers = [int(name.replace(prefix, "")) for name in folders]
highest_number = max(numbers) if numbers else 0

# Create the name for the new folder
new_name = f"{prefix}{highest_number + 1}"

# Full path of the new folder
new_folder = os.path.join(directory, new_name)

event_log = dir_tutti+"/log/Tesis/EventLogs"
event_log_fail =dir_tutti+"/log/Tesis/EventLogs_fail"
variables=dir_tutti+"/log/Tesis/mision_variables/activities.txt"

copy_folder(event_log, new_folder)
copy_folder(event_log_fail, new_folder)
copy_file(variables, new_folder)

fn = dir_tutti+'/log/Tesis/LogFinal/final_log_2.csv'
concatenate(new_folder+"/EventLogs")
events = pd.read_csv(fn)
events.columns = ['mision', 'action', 'datetime', 'resource', 'random_seed']
events['datetime'] = pd.to_datetime(events['datetime'])
events


concatenate(new_folder+"/EventLogs_fail")
events_fail = pd.read_csv(fn)
events_fail.columns = ['mision', 'action', 'datetime', 'resource', 'random_seed']
events_fail['datetime'] = pd.to_datetime(events_fail['datetime'])
events_fail


events.rename(columns={'datetime': 'time:timestamp', 'mision': 'case:concept:name', 'action': 'concept:name', 'random_seed': 'org:resource'}, inplace=True)
events_fail.rename(columns={'datetime': 'time:timestamp', 'mision': 'case:concept:name', 'action': 'concept:name', 'random_seed': 'org:resource'}, inplace=True)

## Convert to log format the events without fail probability
log_inicial = log_converter.apply(events)
## Convert to log format the events with fail probability
log_fail = log_converter.apply(events_fail)

variants = pm4py.get_variants(log_fail)
len(variants)
variants

#log_no_timeout = pm4py.filter_activities_rework(log_inicial, "time_out", 1)
log_no_timeout = pm4py.filter_event_attribute_values(log_inicial, "concept:name", ["time_out"], level="case", retain=False)
log_no_timeout


#alpha
net, im, fm = pm4py.discover_petri_net_alpha(log_no_timeout)

parameters = {pn_visualizer.Variants.FREQUENCY.value.Parameters.FORMAT: "png"}
gviz = pn_visualizer.apply(net, im, fm , parameters=parameters, variant=pn_visualizer.Variants.FREQUENCY, log=log_no_timeout)
pn_visualizer.save(gviz, new_folder+"/Alpha_miner_frequency_IDEAL.png")
pm4py.view_petri_net(net, im, fm)


#Petri net
net, im, fm = pm4py.discover_petri_net_heuristics(log_no_timeout, dependency_threshold=0.99)
parameters = {pn_visualizer.Variants.FREQUENCY.value.Parameters.FORMAT: "png"}
gviz = pn_visualizer.apply(net, im, fm , parameters=parameters, variant=pn_visualizer.Variants.FREQUENCY, log=log_no_timeout)
pn_visualizer.save(gviz, new_folder+"/Heuristic_miner_frequency_IDEAL.png")
#pm4py.view_petri_net(net, im, fm)

net, im, fm = pm4py.discovery.discover_petri_net_ilp(log_inicial)
parameters = {pn_visualizer.Variants.FREQUENCY.value.Parameters.FORMAT: "png"}
gviz = pn_visualizer.apply(net, im, fm, parameters=parameters, variant=pn_visualizer.Variants.FREQUENCY, log=log_inicial)
pn_visualizer.save(gviz, new_folder+"/ILP_miner_frequency_IDEAL.png")
#pm4py.view_petri_net(net, im, fm)

net, initial_marking, final_marking = pm4py.discover_petri_net_inductive(log_inicial)

#we can add frequency and performance, change the word to FREQUENCY or PERFORMANCE accordingly
parameters = {pn_visualizer.Variants.FREQUENCY.value.Parameters.FORMAT: "png"}
gviz = pn_visualizer.apply(net, initial_marking, final_marking, parameters=parameters, variant=pn_visualizer.Variants.FREQUENCY, log=log_inicial)
pn_visualizer.save(gviz, new_folder+"/Inductive_miner_frequency_IDEAL.png")
pn_visualizer.view(gviz)


net, initial_marking, final_marking = pm4py.discover_petri_net_inductive(log_no_timeout)

#we can add frequency and performance, change the word to FREQUENCY or PERFORMANCE accordingly
parameters = {pn_visualizer.Variants.PERFORMANCE.value.Parameters.FORMAT: "png"}
gviz = pn_visualizer.apply(net, initial_marking, final_marking, parameters=parameters, variant=pn_visualizer.Variants.FREQUENCY, log=log_no_timeout)
pn_visualizer.save(gviz, new_folder+"/Inductive_miner_frequency_IDEAL_not_time_out.png")
pn_visualizer.view(gviz)

