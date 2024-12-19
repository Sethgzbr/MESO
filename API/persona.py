def persona_schema(reg) -> dict:
    return {
        "fecha": reg[0],
        "nombre": reg[1],
        "id_persona": reg[2]
    }

def personas_schema(personas) -> list:
    return [persona_schema(reg) for reg in personas]
