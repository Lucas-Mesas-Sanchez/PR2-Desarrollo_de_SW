import random
import psycopg

reemplazos = [
    ("NIC001", "RBOT01", "Fallo en puerto 10GbE", "2024-01-10 08:30", "2024-01-12 14:45"),
    ("NIC002", "RBOT02", "Reinicio inesperado del adaptador", "2024-01-15 09:10", "2024-01-16 11:20"),
    ("NIC003", "RBOT03", "Pérdida de enlace intermitente", "2024-02-01 07:50", "2024-02-03 13:40"),
    ("NIC004", "RBOT04", "Temperatura excesiva en NIC", "2024-02-10 10:00", "2024-02-11 09:30"),
    ("NIC005", "RBOT05", "Sustitución preventiva", "2024-02-20 11:00", "2024-02-21 16:45"),
    ("NIC006", "RBOT01", "Fallo en módulo óptico", "2024-03-01 08:15", "2024-03-03 12:10"),
    ("NIC007", "RBOT02", "Errores CRC en tráfico 100GbE", "2024-03-05 09:00", "2024-03-06 14:30"),
    ("NIC008", "RBOT03", "Firmware corrupto", "2024-03-12 07:45", "2024-03-13 15:00"),
    ("NIC009", "RBOT04", "Conector dañado", "2024-03-20 10:20", "2024-03-22 17:10"),
    ("NIC010", "RBOT05", "Interrupciones en tráfico Ceph", "2024-04-01 08:00", "2024-04-02 13:30"),
    ("NIC011", "RBOT01", "Pérdida de enlace total", "2024-04-05 09:40", "2024-04-07 18:25"),
    ("NIC012", "RBOT02", "Latencia anómala en 10GbE", "2024-04-10 11:15", "2024-04-11 12:50"),
    ("NIC013", "RBOT03", "Fallo en transceptor QSFP", "2024-04-15 07:30", "2024-04-16 16:00"),
    ("NIC014", "RBOT04", "Errores de negociación de velocidad", "2024-04-20 10:10", "2024-04-21 14:55"),
    ("NIC015", "RBOT05", "Problemas de compatibilidad con switch", "2024-04-25 08:45", "2024-04-26 13:20"),
    ("NIC016", "RBOT01", "Fallo en controlador interno", "2024-05-01 09:00", "2024-05-02 15:40"),
    ("NIC017", "RBOT02", "Sustitución programada", "2024-05-05 07:55", "2024-05-06 11:30"),
    ("NIC018", "RBOT03", "Conector QSFP flojo", "2024-05-10 10:25", "2024-05-11 17:00"),
    ("NIC019", "RBOT04", "Fallo en módulo óptico 25GbE", "2024-05-15 08:10", "2024-05-16 12:45"),
    ("NIC020", "RBOT05", "Errores de checksum persistentes", "2024-05-20 09:50", "2024-05-21 14:35")
]

   #FUNCION PARA INSERTAR REEMPLAZO CON CONEXION 

def insertar_reemplazo_aleatorio(reemplazos):
    sql = """
        INSERT INTO reemplazo
            (tarjeta, robot, descripcion, fecha_inicio, fecha_fin)
        VALUES (%s, %s, %s, %s, %s)
    """

    reemplazo = random.choice(reemplazos)
    conn = None

    try:
        conn = psycopg.connect(
            dbname="datacenter",
            user="postgres",
            password="postgres",
            host="localhost",
            port="5432"
        )
        print("Conexion realizada")

        with conn.cursor() as cur:
            cur.execute(sql, reemplazo)

        conn.commit()
        print(f"Reemplazo insertado: {reemplazo}")

    except Exception as e:
        print("Error al insertar:", e)

    finally:
        if conn:
            conn.close()


   #FUNCION PARA CONSULTAR STOCK CON CONEXION 

def consultar_stock(parametro):
    sql = "SELECT stock FROM stock WHERE tarjeta = %s"
    conn = None

    try:
        conn = psycopg.connect(
            dbname="datacenter",
            user="postgres",
            password="postgres",
            host="localhost",
            port="5432"
        )

        with conn.cursor() as cur:
            cur.execute(sql,(parametro,))
            resultados = cur.fetchone()

        print(f"Numero total de tarjetas de {(parametro)}:  {resultados[0]}")

    except Exception as e:
        print("Error en la consulta:", e)
        return None

    finally:
        if conn:
            conn.close()



insertar_reemplazo_aleatorio(reemplazos)
consultar_stock("Intel_X520")