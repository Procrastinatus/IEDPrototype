#!/bin/bash
iface="lo";
ied_id=1;
for i in {102..132}
do
	sudo ./iedprototype -p $i -i $iface -n $ied_id &
	ied_id=$((ied_id+1))
done
echo "IEDs have started"
