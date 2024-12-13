// откалиброванные значения АЦП
const float air_value    = 1587.0;
const float water_value  = 800.0;
const float moisture_0   = 0.0;
const float moisture_100 = 100.0;

const float k_voltage = 6.27; // коэффициент поправки напряжения АЦП ESP32 для ~4.45В

const float meausure_time = 1000 * 3; //раз в 3 секунды измеряем

const char* ssid = "Kvantotium";
const char* password = "1941194504";
const char* MyHostName = "raznorabotchiki";