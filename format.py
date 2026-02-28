import csv
import sys

csv.field_size_limit(sys.maxsize)
if len(sys.argv) != 3:
    print("Usage: python format_dict.py input.csv output.txt")
    sys.exit(1)

input_file = sys.argv[1]
output_file = sys.argv[2]

with open(input_file, newline='', encoding='utf-8') as infile, \
     open(output_file, 'w', encoding='utf-8') as outfile:

    reader = csv.reader(infile)

    for row in reader:
        if not row:
            continue

        key = row[0].strip()

        # La définition est généralement dans la dernière colonne
        value = row[-1].strip()

        outfile.write(key + "\n")
        outfile.write(value + "\n")
