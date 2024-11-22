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

@app.get("/persona", response_model=List[dict])
def read_persona():

    return persona.persona_schema(db_persona.read())

@app.post("/create_persona")
async def create_human(data: human):
    IdPersona = data.IdPersona
    nomPersona = data.nomPersona
    cognomPersona = data.cognomPersona 
    cargo = data.cargo
    departamento = data.departamento 
    tipoUsuario = data.tipoUsuario 
    if db_persona.aula_existeix(IdAula):
        l_student_id = db_persona.create(IdAula, nompersona,cicle,curs,grup)
    else:
        raise HTTPException(status_code = 404, detail = "Aula no trobada, sisplau afegeix un que existeixi,")
    
    return {
        "msg": "“S’ha afegit correctement",
        "id student": l_student_id,
        "Nom persona": nompersona
    }