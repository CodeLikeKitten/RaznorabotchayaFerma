from sqlalchemy import Column, Integer, Float, String
from .database import Base

class Record(Base):
    __tablename__ = 'records'
    id = Column(Integer, primary_key=True, index=True)
    Farm_Name = Column(String, index=True)
    Air_Temperature = Column(Float)
    Pressure = Column(Float)
    Humidity = Column(Float)
    CO2 = Column(Integer)
    TVOC = Column(Integer)
    Soil_Temperature = Column(Float)
    Soil_Humidity = Column(Float)
    Illumination = Column(Float)
    Time = Column(String)
    Date = Column(String)
