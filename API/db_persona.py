from client import db_client

def read():
    try:
        conn = db_client()
        cur = conn.cursor()
        cur.execute("SELECT registro.fecha, persona.nombre FROM registro JOIN persona ON registro.id_persona = persona.id_persona;")
    
        human = cur.fetchall()
    
    except Exception as e:
        print("ERROR", e)
        return {"status": -1, "message": f"Error de connexió:{e}" }
    
    finally:
        conn.close()
    
    return human