import pandas as pd
import pm4py
from datetime import date
import glob
today = date.today()

def alpha(event_log):
    net, initial_marking, final_marking = pm4py.discover_petri_net_alpha(event_log)
    pm4py.view_petri_net(net, initial_marking, final_marking)
def inductive(event_log):
    net, initial_marking, final_marking = pm4py.discover_petri_net_inductive(event_log)
    pm4py.view_petri_net(net, initial_marking, final_marking)

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
    heuristic(event_log)

def time_format(file_path, cont):
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
                else:
                    time_log.append('2023-01-'+str(cont)+' 0'+str(hi)+':'+str(mi)+':'+str(int(round(s))))
            else:
                if cont<10:
                    time_log.append('2023-01-0'+str(cont)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
                else:
                    time_log.append('2023-01-'+str(cont)+' 0'+str(hi)+':0'+str(mi)+':'+str(int(round(s))))
            case='mision'+str(cont)
            case_id.append(case)

        
        log['time'] = time_log
        log['time'] = pd.to_datetime(log['time'], format='%Y-%m-%d %H:%M:%S')
        log['case_id']=case_id
        log.to_csv('/home/jazmin/tuttifrutti/log/ideales_no_repetidos_1/time/data'+str(cont)+'.csv', sep=';', index=False)
        return '/home/jazmin/tuttifrutti/log/ideales_no_repetidos_1/time/data'+str(cont)+'.csv'

def logs_folder(folder):
    # Get data file names
    filenames = glob.glob(folder + "/*.csv")

    dfs = []
    cont=0
    for filename in filenames:
        cont+=1
        if cont<30:
            filename=time_format(filename, cont)
            dfs.append(pd.read_csv(filename))

    # Concatenate all data into one DataFrame
    big_frame = pd.concat(dfs, ignore_index=True)
    print(big_frame)
    big_frame.to_csv('/home/jazmin/tuttifrutti/log/ideales_no_repetidos_1/final_log/trial.csv', sep=';', index=False)
    
    import_csv("/home/jazmin/tuttifrutti/log/ideales_no_repetidos_1/final_log/trial.csv")



    



if __name__ == "__main__":
    logs_folder("/home/jazmin/Documents/Ubuntu_personal/TESIS/intento2023/ideales_no_repetidos_1")
