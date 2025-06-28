import pandas as pd


i=27
print(i)
df=pd.read_csv(f'procesados/video{i}_Lab_sliced.csv')

df = df[92:]

df['t']=df['t']-df['t'].iloc[0]
df['t'] = df['t'].round(2)

df.to_csv(f'procesados/video{i}_Lab_sliced_cut.csv',index=False)