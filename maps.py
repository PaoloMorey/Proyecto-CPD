import urllib.request
from urllib.parse import urlencode
import datetime as dt
import json

file = open("key.txt", "r")
key = file.read().strip()

total_ciudades = int(input("Ingrese el numero de ciudades: "))
origin_list = []

e = 0
while e < total_ciudades:
    city = input("Ingrese ciudad " + str(e + 1) + ": ")
    origin_list.append(city)
    e += 1


"""origin_list = [
    "Cercado, Lima, Peru",
    "Lince, Lima, Peru",
    "Miraflores, Lima, Peru",
    "Barranco, Lima, Peru",
    "Rimac, Lima, Peru",
    "Los Olivos, Lima, Peru",
    "La Molina, Lima, Peru",
    "La Victoria, Lima, Peru",
    "Magdalena, Lima, Peru",
    "San Borja, Lima, Peru",
]"""

# save each element in origin_list with a \n
ol = "\n".join(origin_list)
# save ol to file
file = open("matrix/cities.txt", "w")
file.write(ol)
file.close()
destination_list = origin_list
origin_dict = {}
destination_dict = {}
for index, value in enumerate(origin_list):
    origin_dict[index] = value
for index, value in enumerate(destination_list):
    destination_dict[index] = value

origin = "|".join(origin_list)
destination = "|".join(destination_list)

# departure_time = str(round(dt.datetime(2022, 7, 9, 12, 30).timestamp()))
endpoint = "https://maps.googleapis.com/maps/api/distancematrix/json"
params = {
    "origins": origin,
    "destinations": destination,
    "mode": "driving",  # "walking","bicycling"
    # departure_time": departure_time,
    "key": key,
}
url_params = urlencode(params)
# print(url_params)
url = f"{endpoint}?{url_params}"
# print(url)
response = urllib.request.urlopen(url)
response_json = json.loads(response.read())
with open("response.json", "w") as f:
    json.dump(response_json, f)


dist_matrix = [[] for x in range(len(origin_dict))]
time_matrix = [[] for x in range(len(origin_dict))]
for i in range(len(origin_dict)):
    for j in range(len(destination_dict)):
        if response_json["rows"][i]["elements"][j]["status"] == "OK":
            dist_matrix[i].append(
                response_json["rows"][i]["elements"][j]["distance"]["value"]
            )
            time_matrix[i].append(
                response_json["rows"][i]["elements"][j]["duration"]["value"]
            )
        else:
            dist_matrix[i].append(0)
            time_matrix[i].append(0)

# convert dist_matrix to list of lists
dist_matrix = [list(x) for x in dist_matrix]
time_matrix = [list(x) for x in time_matrix]
for i in range(len(dist_matrix)):
    for j in range(len(dist_matrix[0])):
        if i == j or dist_matrix[i][j] == 0:
            dist_matrix[i][j] = -1
            time_matrix[i][j] = -1
with open("matrix/dist.txt", "w") as f:
    for row in dist_matrix:
        # convert row to string
        row = str(row)
        row = row[1:-1]
        row = row.replace(",", " ")
        f.write(row + "\n")
with open("matrix/time.txt", "w") as f:
    for row in time_matrix:
        # convert row to string
        row = str(row)
        row = row[1:-1]
        row = row.replace(",", " ")
        f.write(row + "\n")
