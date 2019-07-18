#!/bin/bash
iface="lo";

sudo ./LIED10 -p 102 -i $iface -z 0x1003 -z 0x1004 -z 0x1005 -x LIED11CTRL/LLN0\$GO\$Status -x LIED11PROT/LLN0\$GO\$Alarm -x LIED11MEAS/LLN0\$GO\$Meas -c 4000

#echo "LIED10 has started\n"

#${OUTPUT_PATH} -p 102 -i lo -z 0x1000 -z 0x1001 -z 0x1002 -x LIED10CTRL/LLN0\$GO\$Status -x LIED10PROT/LLN0\$GO\$Alarm -x LIED10MEAS/LLN0\$GO\$Meas -c 4000
