#!/bin/bash

echo "" > results.log

for seed in {0..10}
do
        for SodaCost in 1 5 10 100
        do
                for NumStudents in {1..5}
                do
                	for MaxPurchases in 1 2 5 10 100
                	do
                	        for NumVendingMachines in {1..5}
                	        do
                	                for MaxStockPerFlavour in 1 5 20 50
                	                do
                	                        for MaxShippedPerFlavour in 1 2 5 10 20 100
                	                        do
                	                                for TimeBetweenShipments in 1 2 10 50 100
                	                                do
                	                                        for ParentalDelay in 1 2 5 10 20 30 50 100
                	                                        do
                	                                                for NumCouriers in {1..5}
                	                                                do
                                                                                random_seed=$(( $seed * 9001 + 1 ))

                                                                                # generate configuration file
                                                                        	echo "SodaCost $SodaCost #comments" > manual_input.txt
                                                                        	echo "NumStudents $NumStudents #comments" >> manual_input.txt
                                                                        	echo "MaxPurchases $MaxPurchases #comments" >> manual_input.txt
                                                                        	echo "NumVendingMachines $NumVendingMachines #comments" >> manual_input.txt
                                                                        	echo "MaxStockPerFlavour $MaxStockPerFlavour #comments" >> manual_input.txt
                                                                        	echo "MaxShippedPerFlavour $MaxShippedPerFlavour #comments" >> manual_input.txt
                                                                        	echo "TimeBetweenShipments $TimeBetweenShipments #comments" >> manual_input.txt
                                                                        	echo "ParentalDelay $ParentalDelay #comments" >> manual_input.txt
                                                                        	echo "NumCouriers $NumCouriers #comments" >> manual_input.txt

                        	                                        	./soda_32 manual_input.txt $random_seed > output1.txt
                        	                                        	./soda manual_input.txt $random_seed > output2.txt
                        	                                        	#diff output1.txt output2.txt
                                                                                if [ `echo $?` -ne 0 ]   # make sure it does not deadlock
                                                                                then
                                                                                	cat manual_input.txt >> results.log
                                                                                	echo "with random seed: $random_seed" >> results.log
                                                                                	exit 1
                                                                                fi
                                                                        done
                                                                done
                                                        done
                                                done
                                        done
                                done
                        done
                done
        done
done

rm output1.txt output2.txt

exit 0


