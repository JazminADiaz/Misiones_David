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
today = date.today()
fitness1=[]
precision1=[]
generalization1=[]
simplicity1=[]

#choose the mision
mision="secuencial_paralela"
mision_folder="/home/jazmin/tuttifrutti/log/Tesis/"+mision
trials_folder=mision_folder+"/trial_folder"


if mision=="secuencial_paralela":
    check=26

if mision=="secuencial":
    check=17

if mision=="paralela":
    check=9

def graphic(fitness1, precision1, generalization1, simplicity1, models):
    d1 = {'Simplicidad': simplicity1}
    d2 = {'Fitness': fitness1}
    d3 = {'Generalización':generalization1}
    d4 = {'Precisión': precision1}
    #print(len(fitness1), len(precision1))
    df1 = pd.DataFrame(data=d1)
    df1['# de repeticiones para creación de modelo'] = pd.Series(models)
    df1.boxplot(column=['Simplicidad'], by=['# de repeticiones para creación de modelo'])
    if mision=="secuencial_paralela":
        plot.suptitle('Mision Secuencial Paralela')
    if mision=="paralela":
        plot.suptitle('Mision Paralela')
    if mision=="secuencial":
        plot.suptitle('Mision Secuencial')
    plot.savefig("/home/jazmin/tuttifrutti/log/"+mision+"/final_log/BoxPlot_"+mision+"_Simplicidad.png")
    plot.show()

    df2 = pd.DataFrame(data=d2)
    df2['# de repeticiones para creación de modelo'] = pd.Series(models)
    df2.boxplot(column=['Fitness'], by=['# de repeticiones para creación de modelo'])

    if mision=="secuencial_paralela":
        plot.suptitle('Mision Secuencial Paralela')
    if mision=="paralela":
        plot.suptitle('Mision Paralela')
    if mision=="secuencial":
        plot.suptitle('Mision Secuencial')
    plot.savefig("/home/jazmin/tuttifrutti/log/"+mision+"/final_log/BoxPlot_"+mision+"_Fitness.png")
    plot.show()

    df3 = pd.DataFrame(data=d3)
    df3['# de repeticiones para creación de modelo'] = pd.Series(models)
    df3.boxplot(column=['Generalización'], by=['# de repeticiones para creación de modelo'])

    if mision=="secuencial_paralela":
        plot.suptitle('Mision Secuencial Paralela')
    if mision=="paralela":
        plot.suptitle('Mision Paralela')
    if mision=="secuencial":
        plot.suptitle('Mision Secuencial')
    plot.savefig("/home/jazmin/tuttifrutti/log/"+mision+"/final_log/BoxPlot_"+mision+"_Generalización.png")
    plot.show()

    df4 = pd.DataFrame(data=d4)
    df4['# de repeticiones para creación de modelo'] = pd.Series(models)
    df4.boxplot(column=['Precisión'], by=['# de repeticiones para creación de modelo'])

    if mision=="secuencial_paralela":
        plot.suptitle('Mision Secuencial Paralela')
    if mision=="paralela":
        plot.suptitle('Mision Paralela')
    if mision=="secuencial":
        plot.suptitle('Mision Secuencial')
    plot.savefig("/home/jazmin/tuttifrutti/log/"+mision+"/final_log/BoxPlot_"+mision+"_Precisión.png")
    plot.show()





def model_evaluation(net, im, fm):
    choice=2
    #read all the names for the folder chosen with the logs to compare with the model
    filenames_2 = glob.glob(trials_folder + "/*.csv")
    fitness=[]
    precision=[]
    generalization=[]
    simplicity=[]


    for filename_2 in filenames_2:
        log_t = time_format(filename_2,1,choice)
        log_t = pm4py.format_dataframe(log_t, case_id='case_id', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')    
        fitness_t = pm4py.fitness_token_based_replay(log_t, net, im, fm)
        #fitness_a = pm4py.fitness_alignments(log_t, net, im, fm)
        #ETConformance method
        prec_t = pm4py.precision_token_based_replay(log_t, net, im, fm)
        #Align-ETConformance method
        #prec_a = pm4py.precision_alignments(log_t, net, im, fm)
        #generalization
        gen = generalization_evaluator.apply(log_t, net, im, fm)
        #simplicity
        simp = simplicity_evaluator.apply(net)
        
        #store the values of the metrics for all 10 logs to compare
        fitness.append(fitness_t["average_trace_fitness"])
        precision.append(prec_t)
        generalization.append(gen)
        simplicity.append(simp)
        #print(len(fitness))
        #
        '''
        if len(fitness)==107:
            pm4py.view_petri_net(net, im, fm)
            print(fitness)
        '''

    models.extend([model,model,model,model,model,model,model,model,model,model])
    #store for all 5 models 
    fitness1.extend(fitness)
    precision1.extend(precision)
    generalization1.extend(generalization)
    simplicity1.extend(simplicity)
    print(len(fitness1))
    if len(fitness1)==10:
        pm4py.view_petri_net(net, im, fm)
        pm4py.save_vis_petri_net(net, im, fm,  "/home/jazmin/tuttifrutti/log/"+mision+"/final_log/PetriNet.png")

        graphic(fitness1, precision1, generalization1, simplicity1, models)

        print(precision1)
        #print(models)
        #print(len(models))


def alpha(event_log):

    net, initial_marking, final_marking = pm4py.discover_petri_net_alpha(event_log)
    pm4py.view_petri_net(net, initial_marking, final_marking)

def inductive(event_log):
    #create the petri net
    net, initial_marking, final_marking = pm4py.discover_petri_net_inductive(event_log)


    
    #pm4py.view_petri_net(net, initial_marking, final_marking)
    model_evaluation(net, initial_marking, final_marking)








def heuristic(event_log):
    map = pm4py.discover_heuristics_net(event_log)
    pm4py.view_heuristics_net(map)
    #net, im, fm = pm4py.discover_petri_net_heuristics(event_log, dependency_threshold=0.99)

    #pm4py.view_petri_net(net, im, fm)

def import_csv(file_path):
    #when using concatenate pandas "," get included, here we open the file, delete the comas, and close the file
    fin = open(file_path, "rt")
    data = fin.read()
    data = data.replace('"', '')
    fin.close()
    fin = open(file_path, "wt")
    fin.write(data)
    fin.close()
    #read the log
    event_log = pd.read_csv(file_path, sep=';')
    event_log = pm4py.format_dataframe(event_log, case_id='case_id', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')
    log_start = pm4py.get_start_activities(event_log)

    #choose the algorithm

    #alpha(event_log)
    inductive(event_log)
    #heuristic(event_log)

def time_format(file_path, cont,choice):
        log = pd.read_csv(file_path, sep=';')
        case_id=[]
        case_id += len(log.time) * ["mision"+str(cont)]
        log['case_id']=case_id
        #used at the beginning for the logs used to create the model
        if choice==1:
            log.to_csv(mision_folder+'/time/data'+str(cont)+'.csv', sep=';', index=False)
            return mision_folder+'/time/data'+str(cont)+'.csv', len(log.time)
        #used for the logs to compare with the log
        if choice==2:
            return log


def logs_folder():
    #Read all the csv files cotain in the folder or the chosen mision
    filenames = glob.glob(mision_folder + "/*.csv")
    dfs = []
    cont=0
    choice=1
    for filename in filenames:
        cont+=1
        #change the seconds for a date_format:
        [filename, log]=time_format(filename, cont,choice)
        #Make sure only complete logs are used
        if (log>=check):
            global model
            model+=1
            #max 50 logs for final model
            if model<=50:
                dfs.append(pd.read_csv(filename))
                #if (len(dfs)<=10):

                # Concatenate all data into one DataFrame
                big_frame = pd.concat(dfs, ignore_index=True)
                #print(big_frame)

                big_frame.to_csv(mision_folder+'/final_log/final_log.csv', sep=';', index=False)
                #create a model every 10 repetitions stored in the log
                if model%50==0:
                    import_csv(mision_folder+"/final_log/final_log.csv")


if __name__ == "__main__":

    logs_folder()
