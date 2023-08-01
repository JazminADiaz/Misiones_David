import pandas as pd
import pm4py
from datetime import date
import glob
from pm4py.algo.evaluation.generalization import algorithm as generalization_evaluator
from pm4py.algo.evaluation.simplicity import algorithm as simplicity_evaluator
import numpy as np

today = date.today()
fitness1=[]
precision1=[]

generalization1=[]
simplicity1=[]

mision="secuencial_paralela"
mision_folder="/home/jazmin/tuttifrutti/log/"+mision
trials_folder=mision_folder+"/trial_folder"
trial="/home/jazmin/tuttifrutti/log/secuencial_paralela/trial_folder/1690908573data.csv"

def model_evaluation(net, im, fm):
    choice=2
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

        fitness.append(fitness_t["log_fitness"])
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


    fitness1.append(fitness)
    precision1.append(precision)
    generalization1.append(generalization)
    simplicity1.append(simplicity)
    print(len(fitness1))
    if len(fitness1)==97:
        pm4py.view_petri_net(net, im, fm)
        print(fitness1[1])

        #print(fitness)


def alpha(event_log):

    net, initial_marking, final_marking = pm4py.discover_petri_net_alpha(event_log)
    pm4py.view_petri_net(net, initial_marking, final_marking)

def inductive(event_log):
    net, initial_marking, final_marking = pm4py.discover_petri_net_inductive(event_log)
    #pm4py.view_petri_net(net, initial_marking, final_marking)
    model_evaluation(net, initial_marking, final_marking)

def heuristic(event_log):
    map = pm4py.discover_heuristics_net(event_log)
    pm4py.view_heuristics_net(map)
    #net, im, fm = pm4py.discover_petri_net_heuristics(event_log, dependency_threshold=0.99)

    #pm4py.view_petri_net(net, im, fm)

def import_csv(file_path):
    fin = open(file_path, "rt")
    data = fin.read()
    data = data.replace('"', '')
    fin.close()
    fin = open(file_path, "wt")
    fin.write(data)
    fin.close()

    event_log = pd.read_csv(file_path, sep=';')
    event_log = pm4py.format_dataframe(event_log, case_id='case_id', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')
    log_start = pm4py.get_start_activities(event_log)


    print(log_start)
    #alpha(event_log)
    inductive(event_log)
    #heuristic(event_log)

def time_format(file_path, cont,choice):
        log = pd.read_csv(file_path, sep=';')
        time_log=[]
        case_id=[]
        for i in range(0, len(log.time)):
            t=log.time[i]
            c=log.case_id[i]
            #print("t="+str(t))
            h=t/3600
            hi= int(t/3600)
            m=(h-hi)*60
            mi=int(m)
            s=(m-mi)*60
            if mi>=10:
                if cont<10:
                    time_log.append('2023-01-0'+str(cont)+' 0'+str(hi)+':'+str(mi)+':'+str(int(round(s))))
                if 10<=cont<=30:
                    time_log.append('2023-01-'+str(cont)+' 0'+str(hi)+':'+str(mi)+':'+str(int(round(s))))
                if 30<cont<=58:
                    time_log.append('2023-02-'+str(cont-30)+' 0'+str(hi)+':'+str(mi)+':'+str(int(round(s))))
                if 58<cont<=88:
                    time_log.append('2023-03-'+str(cont-57)+' 0'+str(hi)+':'+str(mi)+':'+str(int(round(s))))
                if 88<cont<=119:
                    time_log.append('2023-04-'+str(cont-88)+' 0'+str(hi)+':'+str(mi)+':'+str(int(round(s))))
                if 120<cont<=150:
                    time_log.append('2023-05-'+str(cont-119)+' 0'+str(hi)+':'+str(mi)+':'+str(int(round(s))))
            else:
                if cont<10:
                    time_log.append('2023-01-0'+str(cont)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
                if 10<=cont<=31:
                    time_log.append('2023-01-'+str(cont)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
                if 31<cont<=58:
                    time_log.append('2023-02-'+str(cont-30)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
                if 58<cont<=88:
                    time_log.append('2023-03-'+str(cont-57)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
                if 88<cont<=119:
                    time_log.append('2023-04-'+str(cont-88)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
                if 120<cont<=150:
                    time_log.append('2023-05-'+str(cont-119)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
            case='mision'+str(cont)
            case_id.append(case)

        
        log['time'] = time_log
        log['time'] = pd.to_datetime(log['time'], format='%Y-%m-%d %H:%M:%S')
        log['case_id']=case_id
        if choice==1:
            log.to_csv(mision_folder+'/time/data'+str(cont)+'.csv', sep=';', index=False)
            return mision_folder+'/time/data'+str(cont)+'.csv'
        if choice==2:
            return log


def logs_folder():
    # Get data file names
    filenames = glob.glob(mision_folder + "/*.csv")

    dfs = []
    logs=[]
    cont=0
    choice=1
    for filename in filenames:
        cont+=1
        logs.append(cont)
        filename=time_format(filename, cont,choice)
        dfs.append(pd.read_csv(filename))

        # Concatenate all data into one DataFrame
        big_frame = pd.concat(dfs, ignore_index=True)
        #print(big_frame)
        big_frame.to_csv(mision_folder+'/final_log/final_log.csv', sep=';', index=False)
        
        import_csv(mision_folder+"/final_log/final_log.csv")


if __name__ == "__main__":

    logs_folder()
