from typing import List, Union
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from datetime import datetime 

app = FastAPI()

class persona(BaseModel):
    id_persona: int
    nombre:str
    apellido: str
    cargo: str
    departamento: str
    tipo_de_usuario: str
    id_organizacion: int

class registro(BaseModel):
    IdRegister: int
    id_registro: int
    fecha: datetime  
    entrada_salida: str
    id_persona: int
    id_espacio: int

@app.get("/")
def read_root():
    return {"MESO API"}

@app.get("/persona", response_model=List[dict])
def read_persona():

    return persona.persona_schema(db_persona.read())