import pandas as pd



for i in range(5,5):
    df=pd.read_csv(f'peltier_cosas/peltier_{i}.csv')
    df.columns=['t','temp','_']
    # Convert to datetime
    df['t'] = pd.to_datetime(df['t'].str.strip(), format='%H:%M:%S').dt.time
    df = df.drop(columns=['_'])
    df.to_csv(f'peltier_cosas/peltiermod{i}.csv',index=False)

# i=1

for i in range(8,9):
    df=pd.read_csv(f'peltier_cosas/peltier_{i}.csv')
    df.columns=['t','temp']
    # Convert to datetime
    # df['t'] = pd.to_datetime(df['t'].str.strip(), format='%H:%M:%S').dt.time
    df['t'] = range(len(df))
    # df = df.drop(columns=['_'])
    df.to_csv(f'peltier_cosas/peltiermod{i}.csv',index=False)

