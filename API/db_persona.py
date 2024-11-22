from client import db_client

def read():
    try:
        conn = db_client()
        cur = conn.cursor()
        cur.execute("select * from persona")
    
        human = cur.fetchall()
    
    except Exception as e:
        print("ERROR", se)
        return {"status": -1, "message": f"Error de connexió:{e}" }
    
    finally:
        conn.close()
    
    return human