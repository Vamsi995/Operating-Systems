#!/bin/bash

## Modify the above line to point to bash executable in your system

## ROLL NUMBERS OF THE TEAM-MATES ##
#    1.111801002
#    2.111801026
#    3.111801010
#    4.111601004
###

## Write your script below this line ##

make
touch master.csv
./input_generator 100000000 111801002 [111801026 111601004 111801010] > master.csv
touch cse.csv
touch me.csv
touch ce.csv
touch ee.csv
touch test1.csv
touch test3.csv
mkdir courses

COURSES=`cut -d',' -f2 master.csv | sort -u` ## all unique courses
STUDENTS=`cut -d',' -f1 master.csv | sort -u` ## all unique student rolls

# time for 10000000 records:
# real	1m21.040s
# user	1m24.143s
# sys	0m4.139s
#
# time for 100000000 records:
# real  16m13.755s
# user  14m57.615s
# sys   3m18.840s

awk -F, '{print $1","$3> "courses/"$2".csv" }' master.csv #Splitting the master file to individual subject-wise csv file using awk command and print only rollno and marks of the student

for i in $COURSES
do
	sort -k1,1n -k2,2nr -t ',' "courses/${i}.csv"| sort -u -t, -k1,1 >temp
	mv temp "courses/${i}.csv" 
done
# getting the respective students for respective stream
CSE=`grep "^111" master.csv`
ME=`grep "^131" master.csv`
EE=`grep "^121" master.csv`
CE=`grep "^101" master.csv`

# Getting Courses for each respective streams
CSEID=`cut -d',' -f2 <<< $CSE | sort -u`
MEID=`cut -d',' -f2 <<< $ME | sort -u`
EEID=`cut -d',' -f2 <<< $EE | sort -u`
CEID=`cut -d',' -f2 <<< $CE | sort -u`

#CSEcourses=`cut -d',' -f2  master.csv | grep "CS"|sort -u | tr -s '\n' ',' | sed "s/,$//g"`
# addding all rolls of students of each branch to a branch csv file
cut -d',' -f1  master.csv | grep "^111"|sort -u | sed "s/,$//g"> ./cse.csv
cut -d',' -f1  master.csv | grep "^121"|sort -u | sed "s/,$//g"> ./ee.csv
cut -d',' -f1  master.csv | grep "^131"|sort -u | sed "s/,$//g"> ./me.csv
cut -d',' -f1  master.csv | grep "^101"|sort -u | sed "s/,$//g"> ./ce.csv
cd courses
#generating the header for each of the csv files
TempCs="Rollno"
for i in $CSEID
do
	TempCs+=",${i}"
done
TempEe="Rollno"
for i in $EEID
do
	TempEe+=",${i}"
done
TempMe="Rollno"
for i in $MEID
do
	TempMe+=",${i}"
done
TempCe="Rollno"
for i in $CEID
do
	TempCe+=",${i}"
done
#joining the all courses of respective branches to single branch csv file
for i in $CSEID
do
	join -t, -e - -a1 -a2 -o 0 2.2  ../cse.csv "./${i}.csv" > ../test1.csv # '-' is added in case mark of the student is missing in a particular course
	join -t,  ../cse.csv ../test1.csv > ../test3.csv
	mv ../test3.csv ../cse.csv
done
echo $TempCs | cat - ../cse.csv > temp && mv temp ../cse.csv # adding the header
for i in $MEID
do
	join -t, -e - -a1 -a2 -o 0 2.2  ../me.csv "./${i}.csv" > ../test1.csv # '-' is added in case mark of the student is missing in a particular course
	join -t,  ../me.csv ../test1.csv > ../test3.csv
	mv ../test3.csv ../me.csv
done
echo $TempMe | cat - ../me.csv > temp && mv temp ../me.csv # adding the header
for i in $EEID
do
	join -t, -e - -a1 -a2 -o 0 2.2  ../ee.csv "./${i}.csv" > ../test1.csv # '-' is added in case mark of the student is missing in a particular course
	join -t,  ../ee.csv ../test1.csv > ../test3.csv
	mv ../test3.csv ../ee.csv
done
echo $TempEe | cat - ../ee.csv > temp && mv temp ../ee.csv # adding the header
for i in $CEID
do
	join -t, -e - -a1 -a2 -o 0 2.2  ../ce.csv "./${i}.csv" > ../test1.csv # '-' is added in case mark of the student is missing in a particular course
	join -t,  ../ce.csv ../test1.csv > ../test3.csv
	cp ../test3.csv ../ce.csv
done 
echo $TempCe | cat - ../ce.csv > temp && mv temp ../ce.csv # adding the header