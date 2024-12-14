import json
import requests

# URL вашего API
API_URL = "http://127.0.0.1:8000/records/"

# Путь к JSON файлу
JSON_FILE_PATH = "C:/Users/User/Desktop/project_main/backend/app/parsed_kekws.json"

def transform_keys(record):
    return {
        "Farm_Name": record["Farm_Name"],
        "Air_Temperature": record["Air_Temperature"],
        "Pressure": record["Pressure"],
        "Humidity": record["Humidity"],
        "CO2": record["CO2"],
        "TVOC": record["TVOC"],
        "Soil_Temperature": record["Soil_Temperature"],
        "Soil_Humidity": record["Soil_Humidity"],
        "Illumination": record["Illumination"],
        "Time": record["time"],
        "Date": record["date"],
    }


# Функция для загрузки данных из JSON файла
def load_data_from_json(file_path):
    with open(file_path, "r", encoding="utf-8") as file:
        data = json.load(file)
    return data

def send_data_to_api(data):
    for record in data:
        transformed_record = transform_keys(record)
        response = requests.post(API_URL, json=transformed_record)
        if response.status_code == 200:
            print(f"Record added successfully: {transformed_record}")
        else:
            print(f"Failed to add record: {transformed_record}. Error: {response.text}")


if __name__ == "__main__":
    # Загружаем данные из файла
    records = load_data_from_json(JSON_FILE_PATH)

    # Отправляем данные в API
    send_data_to_api(records)
