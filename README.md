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
- consts.h - константы и некоторые настройки

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
