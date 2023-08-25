import matplotlib.pyplot as plot
import pandas as pd
import numpy as np
import pm4py
import glob
import seaborn as sns
from pm4py.algo.evaluation.generalization import algorithm as generalization_evaluator
from pm4py.algo.evaluation.simplicity import algorithm as simplicity_evaluator
mision="secuencial_paralela"
mision_folder="/home/jazmin/tuttifrutti/log/Tesis/"+mision

big_frame = pd.read_csv(mision_folder+'/final_log/final_log.csv', sep=';')
big_frame = pm4py.format_dataframe(big_frame, case_id='mision', activity_key='activity', timestamp_key='time', timest_format='%Y-%m-%d %H:%M:%S')

preparation(big_frame)
