import psycopg2
from psycopg2 import sql

def db_client():
    
    try:
        dbname = "meso"
        user = "marcos"
        password = "asix"
        host = "192.168.53.2"
        port = "5432"
        
        return psycopg2.connect(
            host = host,
            port = port,
            user = user,
            password = password,
            database = dbname,
        ) 
            
    except Exception as e:
            return {"status": -1, "message": f"Error de connexió:{e}" }