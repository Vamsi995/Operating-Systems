#!bin/bash

#make
#touch master.csv
#./input_generator 1000000000 111801002 [111801026 111601004 111801010] > master.csv

CSE=`grep "^111" master.csv`
ME=`grep "^131" master.csv`
EE=`grep "^121" master.csv`
CE=`grep "^101" master.csv`

CSECOURSE=`cut -d',' -f2 <<< $CSE | sort -u | tr -s '\n' ',' | sed "s/,$//g"`
MECOURSE=`cut -d',' -f2 <<< $ME | sort -u | tr -s '\n' ',' | sed "s/,$//g"`
EECOURSE=`cut -d',' -f2 <<< $EE | sort -u | tr -s '\n' ',' | sed "s/,$//g"`
CECOURSE=`cut -d',' -f2 <<< $CE | sort -u | tr -s '\n' ',' | sed "s/,$//g"`


CSEID=`cut -d',' -f2 <<< $CSE | sort -u`
MEID=`cut -d',' -f2 <<< $ME | sort -u`
EEID=`cut -d',' -f2 <<< $EE | sort -u`
CEID=`cut -d',' -f2 <<< $CE | sort -u`


touch cse.csv me.csv ee.csv ce.csv


echo "Rollno,$CSECOURSE" > cse.csv
echo "Rollno,$MECOURSE" > me.csv
echo "Rollno,$EECOURSE" > ee.csv
echo "Rollno,$CECOURSE" > ce.csv


CSESTUDENT=`cut -d',' -f1 <<< $CSE | sort -u`
MESTUDENT=`cut -d',' -f1 <<< $ME | sort -u`
EESTUDENT=`cut -d',' -f1 <<< $EE | sort -u`
CESTUDENT=`cut -d',' -f1 <<< $CE | sort -u`


for i in $CSESTUDENT
do
	TEMP=""

	for j in $CSEID
	do
		RESULT=`grep "$i,$j" <<< $CSE | sort -k3,3nr -t ',' | head -n 1`
		MARK=`cut -d',' -f3 <<< $RESULT`
		TEMP+=",$MARK"
	done
	echo "$i$TEMP" >> cse.csv
done


for i in $MESTUDENT
do
	TEMP1=""

	for j in $MEID
	do
		RESULT=`grep "$i,$j" <<< $ME | sort -k3,3nr -t ',' | head -n 1`
		MARK=`cut -d',' -f3 <<< $RESULT`
		TEMP1+=",$MARK"
	done
	echo "$i$TEMP1" >> me.csv
done




for i in $EESTUDENT
do
	TEMP2=""

	for j in $EEID
	do
		RESULT=`grep "$i,$j" <<< $EE | sort -k3,3nr -t ',' | head -n 1`
		MARK=`cut -d',' -f3 <<< $RESULT`
		TEMP2+=",$MARK"
	done
	echo "$i$TEMP2" >> ee.csv
done



for i in $CESTUDENT
do
	TEMP3=""

	for j in $CEID
	do
		RESULT=`grep "$i,$j" <<< $CE | sort -k3,3nr -t ',' | head -n 1`
		#echo $RESULT
		MARK=`cut -d',' -f3 <<< $RESULT`
		TEMP3+=",$MARK"
	done
	echo "$i$TEMP3" >> ce.csv
done

# ======================================================================================


mkdir courses

COURSES=`cut -d',' -f2 master.csv | sort -u`
STUDENTS=`cut -d',' -f1 master.csv | sort -u`


for i in $COURSES
do 
	touch "courses/${i}.csv"
done



for i in $COURSES
do

	for j in $STUDENTS
	do
		RESULT=`grep "$j,$i" master.csv | sort -k3,3nr -t ',' | head -n 1`

		if [ -z "$RESULT" ]
		then
			RESULT=""
			continue
		else
			echo "$RESULT" >> "courses/${i}.csv"
		fi

		#echo "$RESULT" >> "courses/${i}.csv"
		#MARK=`cut -d',' -f3 <<< $RESULT`
		#TEMP3+=",$MARK"
	done
#	echo "$i$TEMP3" >> ce.csv
	sed -i "/^$/d" "courses/${i}.csv"
done






