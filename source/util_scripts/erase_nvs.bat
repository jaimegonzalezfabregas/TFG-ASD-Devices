idf.py erase_flash

python nvs_partition_gen.py generate nvs.csv nvs.bin 0x4000

idf.py flash

python C:\Users\Jaime\esp\esp-idf\components\partition_table\parttool.py --port COM5 write_partition --partition-name=nvs --input "C:\Users\Jaime\Escritorio\sharedProjects\4to\TFG\TFG-ASD-Devices\source\util_scripts\nvs.bin"
