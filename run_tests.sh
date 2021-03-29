#1 /bin/bash

make main

SECONDS=0

for i in $(seq 1 10)
do
	make run-test ARGS="test$i.txt"
done

duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed."