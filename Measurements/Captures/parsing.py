cat 4003_reles.csv | awk -F"," '{print $2;}'> 0x4003.csv
cat 0x4003.csv | awk -F"0x" '{print $2;}' > 0x4003.raw.csv

cat 4330_reles.csv | awk -F"," '{print $2;}'> 0x4330.csv
cat 0x4330.csv | awk -F"0x" '{print $2;}' > 0x4330.raw.csv

import csv
import re
import os

fileinput = '0x4330.raw.csv'
fileoutput = '0x4330.parsed.csv'
n=64
data_list=[]
with open(fileinput) as csvfile:
    data_list=list(csv.reader(csvfile))


data_list.pop(0)
data = [str(x[0]) for x in data_list]

def get_pattern(data,n,fout):
    for i in range(len(data)):
        if(data[i]=='FE'):
            x=[]
            #x.append(data[i-1])
            for j in range(n):
                x.append(data[i+j])
            print(x)
            fout.write(str(x)+'\n')
    fout.close()

fout = open(fileoutput,'w')
get_pattern(data,n,fout)

7EDFFFFFDEEFBFFFBFF7E
7EBDFFFF7FFFFFFFFFFFFFFF39F7E
7EBDFFFF7FFFFFFFFFFFFFFF39F7E
7EBDFFFF7FFFFFFFFFFFFFFF39F7E
7EFFFF7FFFFFFFFFFFFFEFFFA317E
7E19ABF5FFFFFFFFFFFFFFFFFF7F72A85AF7E
7E7CB12914AEDFFFFFFFEFFEFFBFFFFFF7F7FFFFFFFFFDFFFFB77E


