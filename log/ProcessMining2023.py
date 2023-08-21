import matplotlib.pyplot as plot
import pandas as pd
import numpy as np
import pm4py
from datetime import date
import glob
from pm4py.algo.evaluation.generalization import algorithm as generalization_evaluator
from pm4py.algo.evaluation.simplicity import algorithm as simplicity_evaluator

# Imports
model=0
models=[]
fitness1=[]
precision1=[]
generalization1=[]
simplicity1=[]
model_n=50
samples=10

#choose the mision
mision="secuencial_paralela"
mision_folder="/home/jazmin/tuttifrutti/log/Tesis/"+mision
trial_folder=mision_folder+"/trial_folder"


if mision=="secuencial_paralela":
    check=26

if mision=="secuencial":
    check=17

if mision=="paralela":
    check=9

def graphic(fitness1, precision1, generalization1, simplicity1, models):
    d1 = {'Simplicidad': simplicity1,
          'Fitness': fitness1,
          'Generalización':generalization1,
          'Precisión': precision1
          }
    for key, value in d1.items():
        df1 = pd.DataFrame(data= {key:value})
        df1['# de repeticiones para creación de modelo'] = pd.Series(models)
        df1.boxplot(column=[key], by=['# de repeticiones para creación de modelo'])
        plot.suptitle('Mision '+mision)
        plot.savefig("/home/jazmin/tuttifrutti/log/"+mision+"/final_log/BoxPlot_"+mision+key+".png")
        plot.show()

def model_evaluation(net, im, fm):
    #compare each trial file with each model
    filenames_2 = glob.glob(trial_folder + "/*.csv")
    fitness=[]
    precision=[]
    generalization=[]
    simplicity=[]
    
    for filename_2 in filenames_2:
        case_id=[]
        log = pd.read_csv(filename_2, sep=';')
        case_id += len(log.time) * ["mision0"]
        log['case_id']=case_id
        log= pm4py.format_dataframe(log, case_id='case_id', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')    
        fitness_t = pm4py.fitness_token_based_replay(log, net, im, fm)
        #ETConformance method
        prec_t = pm4py.precision_token_based_replay(log, net, im, fm)
        #generalization
        gen = generalization_evaluator.apply(log, net, im, fm)
        #simplicity
        simp = simplicity_evaluator.apply(net)
        
        #store the values of the metrics for each trial log in each model
        fitness.append(fitness_t["average_trace_fitness"])
        precision.append(prec_t)
        generalization.append(gen)
        simplicity.append(simp)
    #store all values together
    models.extend(len(filenames_2) * [model])
    fitness1.extend(fitness)
    precision1.extend(precision)
    generalization1.extend(generalization)
    simplicity1.extend(simplicity)
    print(len(fitness1))
    #once all models have been compared graphic the metrics
    if len(fitness1)==(model_n/samples)*len(filenames_2):
        pm4py.view_petri_net(net, im, fm)
        pm4py.save_vis_petri_net(net, im, fm,  mision_folder+"/final_log/PetriNet.png")
        graphic(fitness1, precision1, generalization1, simplicity1, models)

def alpha(event_log):
    net, initial_marking, final_marking = pm4py.discover_petri_net_alpha(event_log)
    pm4py.view_petri_net(net, initial_marking, final_marking)

def inductive(event_log):
    #create the petri net
    net, initial_marking, final_marking = pm4py.discover_petri_net_inductive(event_log)
    model_evaluation(net, initial_marking, final_marking)

def heuristic(event_log):
    map = pm4py.discover_heuristics_net(event_log)
    pm4py.view_heuristics_net(map)

def logs_folder():
    #Read all the csv files cotain in the folder if the choosen mision
    filenames = glob.glob(mision_folder + "/*.csv")
    dfs = []
    global model
    
    for filename in filenames:
        log = pd.read_csv(filename, sep=';')
        case_id=[]
        case_id += len(log.time) * ["mision"+str(model)]
        log['case_id']=case_id
        #Make sure only complete logs are used
        if (len(log.case_id)>=check):
            model+=1
            #max 50 logs for final model
            if model<=model_n:
                dfs.append(log)
                # Concatenate all data into one DataFrame
                big_frame = pd.concat(dfs, ignore_index=True)
                big_frame.to_csv(mision_folder+'/final_log/final_log.csv', sep=';', index=False)
                big_frame = pm4py.format_dataframe(big_frame, case_id='case_id', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')
                #create a model every 10 repetitions stored in the log
                if model%samples==0:
                    inductive(big_frame)


if __name__ == "__main__":

    logs_folder()
