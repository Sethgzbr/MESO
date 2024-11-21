from typing import List, Union
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel

app = FastAPI()

class persona(BaseModel):
    IdPersona: int
    nomPersona:str
    cognomPersona: str
    cargo: str
    departamento: str
    tipoUsuario: str

class organization(BaseModel):
    IdOrganization: int
    nomOrganization:str
    direccio: str
    tipoOrganization: str

class register(BaseModel):
    IdRegister: int

@app.get("/")
def read_root():
    return {"MESO API"}

