#!/bin/bash
iface="lo";

# -f flag is to simulate cb fail
sudo ./LIED11 -f -p 103 -i $iface -z 0x1000 -z 0x1001 -z 0x1002 -x LIED10CTRL/LLN0\$GO\$Status -x LIED10PROT/LLN0\$GO\$Alarm -x LIED10MEAS/LLN0\$GO\$Meas -c 4001

#echo "LIED11 has started\n"

#${OUTPUT_PATH} -p 102 -i lo -z 0x1000 -z 0x1001 -z 0x1002 -x LIED10CTRL/LLN0\$GO\$Status -x LIED10PROT/LLN0\$GO\$Alarm -x LIED10MEAS/LLN0\$GO\$Meas -c 4000
