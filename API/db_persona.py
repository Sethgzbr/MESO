from client import db_client

def read():
    conn = None
    try:
        conn = db_client()
        if isinstance(conn, dict):  # Verificar si la conexión falló
            print("Conexión fallida:", conn)
            return []
        cur = conn.cursor()
        cur.execute("SELECT registro.fecha, persona.nombre FROM registro JOIN persona ON registro.id_persona = persona.id_persona;")
        
        # Recoger los resultados de la consulta
        result = cur.fetchall()
        print("Resultado de la consulta:", result)
        return result
    
    except Exception as e:
        print("ERROR", e)
        return []
    
    finally:
        if conn and not isinstance(conn, dict):
            conn.close()
