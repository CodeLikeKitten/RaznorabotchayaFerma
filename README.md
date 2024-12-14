# RaznorabotchayaFerma
Проект выполнен для Хакатона "КиберVavilov"

# Низкий уровень

## Зависимости для Иотика
- ESPmDNS;
- BME280I2C;
- SparkFun_SGP30_Arduino_Library;
- ArduinoJson;
- BH1750.

Зависимости необходимы для работы с датчиками и работы с сетью. ArduinoJson отвечает за упаковку данных.

## Файлы
- iotik.ino - основной файл со всеми инклудами и основным кодом;
- pinout.h - распиновка;
- consts.h - константы;
- settings.h - настройки

# Высокий уровень

## Описание

Web-приложение, позволяющее отображать и искать записи в таблице по дате и времени снятия измерения или по названию сити-фермы. 
Проект включает фронтенд, написанный на Vue.js, и бэкенд на FastAPI. В качестве базы данных используется SQLite с SQLAlchemy.

## Структура проекта

project-main/

├── backend/

│   ├── app/

│   │   ├── __init__.py

│   │   ├── main.py

│   │   ├── models.py

│   │   ├── database.py

│   │   ├── crud.py

│   │   └── schemas.py

│   ├── data/

│   │   └── data.json

│   ├── test.db

│   └── requirements.txt

├── frontend/

│   ├── public/

│   │   └── index.html

│   ├── src/

│   │   ├── assets/

│   │   ├── components/

│   │   │   ├── TableComponent.vue

│   │   │   ├── PaginationComponent.vue

│   │   │   └── SearchComponent.vue

│   │   ├── App.vue

│   │   ├── main.js

│   │   └── router.js

│   └── package.json


# Принцип работы
Иотик опрашивает датчики и формирует JSON. Затем JSON передаётся на сервер, откуда его скрапит скрипт на python. Скрипт сохраняет данные в json файл и отправляет на сервер, где api принимает значения и пушит их в базу данных.
________________________________
# Как начать работу
## Подготовка низкого уровня
1. Скачать прошивку (папка lowLevel);
2. Установить зависимости (поиск по GitHub и менеджеру библиотек Arduino);
3. Установить (ESP32 для Arduino IDE)[https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html]; 
4. Выбрать ESP32-WROOM в менеджере плат;
5. Поменять параметры в файле setting.h на необходимые (Хостнейм, настройки подключения к Wi-Fi, адрес сервера);
6. Загрузить прошивку в плату.

Сервер и ферма должны быть подключены к одной точке доступа Wi-Fi;
## Запуск приложения
1. Скачать папку project_main
2. Открыть терминал и перейти в папку проекта
3. Перейти в папку backend (cd backend)
4. Запустить API (uvicorn app.main:app --host 192.168.0.102 --port 8000)
5. Перейти в папку frontend (cd .. | cd frontend)
6. Запустить фронтенд (npm run serve)
7. Перейти на сайт web-приложения (http://192.168.0.102:8080/records/)
