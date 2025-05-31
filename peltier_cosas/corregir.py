import pandas as pd



for i in range(1,5):
    df=pd.read_csv(f'peltier_cosas/peltier_{i}.csv')
    df.columns=['t','temp','_']
    # Convert to datetime
    df['t'] = pd.to_datetime(df['t'].str.strip(), format='%H:%M:%S').dt.time
    df = df.drop(columns=['_'])
    df.to_csv(f'peltier_cosas/peltiermod{i}.csv',index=False)

# i=1


