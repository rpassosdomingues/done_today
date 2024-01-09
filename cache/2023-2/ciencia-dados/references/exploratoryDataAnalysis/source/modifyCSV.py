import csv

def modifyCSV(file_path):
    modified_data = []

    with open(file_path, 'r') as csvfile:
        csvreader = csv.reader(csvfile)
        
        for row in csvreader:
            cleaned_row = [value.replace(',', '.') if ',' in value else value for value in row]
            modified_data.append(cleaned_row)

    with open(file_path, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerows(modified_data)

# Example usage
file_path = 'input.csv'
modifyCSV(file_path)
