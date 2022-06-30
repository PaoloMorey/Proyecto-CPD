import urllib.request
from urllib.parse import urlencode
import datetime as dt
import json

file = open("key.txt", "r")
key = file.read().strip()

origin_list = [
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
]
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
print(url_params)
url = f"{endpoint}?{url_params}"
print(url)
response = urllib.request.urlopen(url)
response_json = json.loads(response.read())
with open("response.json", "w") as f:
    json.dump(response_json, f)

for origen in range(len(response_json["origin_addresses"])):
    print("Desde:", response_json["origin_addresses"][origen])
    for destino in range(len(response_json["destination_addresses"])):
        print("\tHacia", response_json["destination_addresses"][destino] + ":")
        print(
            "\t\tDistancia (m):",
            response_json["rows"][origen]["elements"][destino]["distance"]["value"],
        )
        print(
            "\t\tTiempo (s):",
            response_json["rows"][origen]["elements"][destino]["duration"]["value"],
        )

dist_matrix = [[] for x in range(len(origin_dict))]
time_matrix = [[] for x in range(len(origin_dict))]
for i in range(len(origin_dict)):
    for j in range(len(destination_dict)):
        dist_matrix[i].append(
            response_json["rows"][i]["elements"][j]["distance"]["value"]
        )
        time_matrix[i].append(
            response_json["rows"][i]["elements"][j]["duration"]["value"]
        )

# save dist_matrix and time_matrix to json
with open("matrix/dist_matrix.json", "w") as f:
    json.dump({"matrix": dist_matrix, "map": origin_dict}, f)
with open("matrix/time_matrix.json", "w") as f:
    json.dump({"matrix": time_matrix, "map": origin_dict}, f)
