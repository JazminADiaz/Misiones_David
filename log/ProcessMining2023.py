import pandas as pd
import pm4py
from datetime import date
import glob
from pm4py.algo.evaluation.generalization import algorithm as generalization_evaluator
from pm4py.algo.evaluation.simplicity import algorithm as simplicity_evaluator

today = date.today()
def model_evaluation(log,net, im, fm):
    log_t = pd.read_csv(log, sep=';')
    log_t = pm4py.format_dataframe(log_t, case_id='case_id', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')    
    fitness_t = pm4py.fitness_token_based_replay(log_t, net, im, fm)
    fitness_a = pm4py.fitness_alignments(log_t, net, im, fm)
    #ETConformance method
    prec_t = pm4py.precision_token_based_replay(log_t, net, im, fm)
    #Align-ETConformance method
    prec_a = pm4py.precision_alignments(log_t, net, im, fm)
    #generalization
    gen = generalization_evaluator.apply(log_t, net, im, fm)
    #simplicity
    simp = simplicity_evaluator.apply(net)


    print("token replace fitness:")
    print(fitness_t)
    print("aligments fitness:")
    print(fitness_a)
    print("ETConformance")
    print(prec_t)
    print("Align-ETConformance")
    print(prec_a)
    print("Simplicity")
    print(simp)
    print("Generalization")
    print(gen)








def alpha(event_log):
    net, initial_marking, final_marking = pm4py.discover_petri_net_alpha(event_log)
    pm4py.view_petri_net(net, initial_marking, final_marking)
def inductive(event_log, trial_log):
    net, initial_marking, final_marking = pm4py.discover_petri_net_inductive(event_log)
    pm4py.view_petri_net(net, initial_marking, final_marking)
    model_evaluation(trial_log,net, initial_marking, final_marking)

def heuristic(event_log):
    map = pm4py.discover_heuristics_net(event_log)
    pm4py.view_heuristics_net(map)
    #net, im, fm = pm4py.discover_petri_net_heuristics(event_log, dependency_threshold=0.99)

    #pm4py.view_petri_net(net, im, fm)

def import_csv(file_path,trial_log):
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
    inductive(event_log, trial_log)
    #heuristic(event_log)

def time_format(file_path, cont, folder):
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
        log.to_csv(folder+'/time/data'+str(cont)+'.csv', sep=';', index=False)
        return folder+'/time/data'+str(cont)+'.csv'

def logs_folder(folder):
    # Get data file names
    filenames = glob.glob(folder + "/*.csv")

    dfs = []
    cont=0
    for filename in filenames:
        cont+=1
    
        filename=time_format(filename, cont, folder)
        dfs.append(pd.read_csv(filename))

    # Concatenate all data into one DataFrame
    big_frame = pd.concat(dfs, ignore_index=True)
    print(big_frame)
    big_frame.to_csv(folder+'/final_log/trial.csv', sep=';', index=False)
    
    import_csv(folder+"/final_log/trial.csv", folder+"/trial_folder/trial_log_t.csv")



    



if __name__ == "__main__":
    mision="secuencial"
    logs_folder("/home/jazmin/tuttifrutti/log/"+mision)
