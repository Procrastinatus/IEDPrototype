#!/bin/bash
iface="lo";
ied_id=1;

	sudo ./iedprototype -p 101 -i lo -z 4096  -c 4096 -x PLACEHOLDER/LLN0\$GO\$Meas
	ied_id=$((ied_id+1))

echo "IED has started\n"

${OUTPUT_PATH} 
#-x LIED10CTRL/LLN0\$GO\$Status -x LIED10PROT/LLN0\$GO\$Alarm -x LIED10MEAS/LLN0\$GO\$Meas
