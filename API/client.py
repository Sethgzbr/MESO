import psycopg2

def db_client():
    try:
        dbname = "alumnat"  
        user = "seth"  
        password = "dam"  
        host = "192.168.53.2" 
        port = "5432"  

        conn = psycopg2.connect(
            host=host,
            port=port,
            user=user,
            password=password,
            database=dbname
        )

        return conn 

    except Exception as e:
        return {"status": -1, "message": f"Error de conexión: {e}"}