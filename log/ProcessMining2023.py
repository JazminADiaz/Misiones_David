import matplotlib.pyplot as plot
import pandas as pd
import numpy as np
import pm4py
import glob
import seaborn as sns
from pm4py.algo.evaluation.generalization import algorithm as generalization_evaluator
from pm4py.algo.evaluation.simplicity import algorithm as simplicity_evaluator

# Imports
models=[]
fitness1=[]
precision1=[]
generalization1=[]
simplicity1=[]
model_n=60
samples=10

#choose the mision
mision="Compuertas"
mision_folder="/home/jazmin/tuttifrutti/log/Tesis/"+mision
trial_folder=mision_folder+"/trial_folder"


if mision=="secuencial_paralela":
    check=26

if mision=="secuencial":
    check=17

if mision=="paralela":
    check=9
def preparation(data_frame):
    #calculate the relative time of each activity
    # Create a pivot table of the start (minimum) and end (maximum) timestamps associated with each case:
    events=data_frame
    case_starts_ends = events.pivot_table(index='mision', aggfunc={'time': ['min', 'max']}) 
    case_starts_ends = case_starts_ends.reset_index() 
    case_starts_ends.columns = ['mision', 'caseend', 'casestart'] 
    # Merge with the main event log data so that for each row we have the start and end times.
    events = events.merge(case_starts_ends, on='mision')
    print(events['mision'])

    # Calculate the relative time by subtracting the process start time from the event timestamp
    events['relativetime'] = events['time'] - events['casestart']
    # Convert relative times to more friendly measures
    ## seconds
    events['relativetime_s'] = events['relativetime'].dt.seconds
    print(events['relativetime_s'])
    ## Get an array of patient labels for the y axis - for graph labelling purposes
    misionnums = [int(e) for e in events['mision'].apply(lambda x: x.strip('mision'))]
    ## Plot a scatter plot of patient events over relative time
    ax = sns.scatterplot(x=events['relativetime_s'],
    y=events['mision'], hue=events['activity'])
    ## Set y axis ticks so that you only show every 5th patient - for readability
    plot.yticks(np.arange(min(misionnums), max(misionnums)+1, 5))
    plot.show()
    events['caselength'] = events['caseend'] - events['casestart']
    #order the cases by overall process lengths
    ## Order by the case length
    ordered = events.sort_values(by=['caselength', 'mision', 'relativetime_s'])
    ax = sns.scatterplot(x=ordered['relativetime_s'], y=ordered['mision'], hue=ordered['activity']) 
    plot.yticks(np.arange(min(misionnums), max(misionnums)+1, 5))
    #plot.show()


    #check for a stady work flow
    ax = sns.scatterplot(x=events['time'], y=events['mision'], hue=events['activity']) 
    plot.yticks(np.arange(min(misionnums), max(misionnums)+1, 5))
    #plot.show()

    #plotting with resource
    ax = sns.scatterplot(x=events['time'], y=events['robot'], hue=events['activity'])
    #plot.show()



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
        plot.savefig(mision_folder+"/final_log/BoxPlot_"+mision+key+".png")
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
        case_id += len(log.time) * ["mision 0"]
        log['mision']=case_id
        log= pm4py.format_dataframe(log, case_id='mision', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')    
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
    model=0
    for filename in filenames:
        log = pd.read_csv(filename, sep=';')
        case_id=[]
        case_id += len(log.time) * ["mision "+str(model)]
        log['mision']=case_id
        #Make sure only complete logs are used

#       if (len(log.mision)>=check):
        model+=1

        #max 50 logs for final model
#            if model<=model_n:
        dfs.append(log)
        # Concatenate all data into one DataFrame
        big_frame = pd.concat(dfs, ignore_index=True)
        if model==model_n:
            big_frame.to_csv(mision_folder+'/final_log/final_log_2.csv', sep=';', index=False)
            big_frame = pm4py.format_dataframe(big_frame, case_id='mision', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')

            #preparation(big_frame)

            #create a model every 10 repetitions stored in the log
#                if model%samples==0:
#                    inductive(big_frame)
            


if __name__ == "__main__":

    logs_folder()
