import csv

fileinput = '0x4003.csv'
fileoutput = '0x4003.parsed.csv'

fin = open(fileinput,"r")
fout = open(fileoutput, "w")

with open(fileinput) as csvfile:
    data_list=list(csv.reader(csvfile))
data = [str(x[0]) for x in data_list]
