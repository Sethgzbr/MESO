from typing import List, Union
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel

app = FastAPI()

class persona(BaseModel):
    id_persona: int
    nombre:str
    apellido: str
    cargo: str
    departamento: str
    tipo_de_usuario: str
    id_organizacion: int

class organization(BaseModel):
    id_organizacion: int
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
    id_persona = data.id_persona
    nombre = data.nombre
    apellido = data.apellido 
    cargo = data.cargo
    departamento = data.departamento 
    tipo_de_usuario = data.tipo_de_usuario 
    id_organizacion = data.id_organizacion
    if db_persona.organization_existeix(id_organizacion):
        l_student_id = db_persona.create(nombre,apellido,cargo,departamento, tipo_de_usuario, id_organizacion)
    else:
        raise HTTPException(status_code = 404, detail = "Aula no trobada, sisplau afegeix un que existeixi,")
    
    return {
        "msg": "“S’ha afegit correctement",
        "id human": l_human_id,
        "Nom persona": nombre
    }

@app.put("/update/{id}")
def update(id_organizacion: int,nombre: str,apellido: str,cargo: str,departamento: str,tipo_de_usuario: str):
    updated_records = db_alumne.update(id_organizacion, nombre, apellido, cargo, departamento, tipo_de_usuario)
    if updated_records == 0:
       raise HTTPException(status_code=404, detail="Items to update not found") 