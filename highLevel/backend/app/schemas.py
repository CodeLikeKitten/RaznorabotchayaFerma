from pydantic import BaseModel

class RecordCreate(BaseModel):
    Farm_Name: str
    Air_Temperature: float
    Pressure: float
    Humidity: float
    CO2: int
    TVOC: int
    Soil_Temperature: float
    Soil_Humidity: int
    Illumination: float
    Time: str
    Date: str

class Record(RecordCreate):
    id: int

    class Config:
        from_attributes = True
