#!/usr/bin/env python
# coding: utf-8

# ```
# pip install xlrd
# ```

import os
import operator
import time
import itertools
import pandas as pd

def maybeMakeNumber(s):
    try:
        return s if float(s) == int(s) else 0
    except ValueError:
        return 0


files = [f for f in os.listdir('.') if os.path.isfile(f) and f.endswith('xlsx')]

dfs = []
for f in files:
    df = pd.read_excel(f, engine = 'openpyxl', header=1)
    df = df.fillna(0)
    dfs.append(df)


uniqID = set()
Qnums = []
for df in dfs:
    Qnums.append(df.shape[1]//5)
    ids = df.iloc[:,1].to_list()
    uniqID = uniqID | set([x for x in list(map(maybeMakeNumber, ids)) if x])

colName = []
for hw,q in enumerate(Qnums):
    for i in range(q):
        colName.append( f"HW{hw+1}_Q{i+1}" )
    colName.append( f"HW{hw+1}_total" )
colName.append( f"Sum" )

Final = pd.DataFrame(index=uniqID, columns=colName)


for p, df in enumerate(dfs):
    QCount = []
    for i in range(1, Qnums[p]+1):
        QCount.append(df[df.iloc[:,5*i+2]==100.0 ].shape[0])
    QWeight = [ 19+981/(1+c**1.21) for c in QCount ]
    #print(QCount, QWeight)
    
    filter_col = [col for col in colName if col.startswith(f'HW{p+1}')]
    for StuId in uniqID:
        c = df[ df.iloc[:,1]==StuId ].iloc[:, [5*i+2 for i in range(1, Qnums[p]+1)]].values
        res = [*map(operator.mul, QWeight, c[0]/100)]
        #print(StuId, c[0], res, sum(res))
        Final.loc[StuId][filter_col] = res + [sum(res)]

total_col = [col for col in colName if col.endswith(f'_total')]
Final['Sum'] = Final[total_col].sum(axis=1)


Final.to_csv('Final.csv')


