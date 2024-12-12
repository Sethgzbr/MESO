def persona_schema(persona) -> dict:
    return {
        "id_persona": persona[0],
        "nombre": persona[1],
        "apellido": persona[2],
        "cargo": persona[3],
        "departamento": persona[4],
        "tipo_de_usuario": persona[5],
        "id_organizacion": persona[6],
    }

def personas_schema(personas) -> list:
    return [persona_schema(persona) for persona in personas]
