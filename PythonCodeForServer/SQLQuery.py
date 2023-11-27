import mysql.connector

db_config = {
    'host': 'localhost',
    'user': 'root',
    'password': 'NTH23122',
    'database': 'dtb_et'
}

def InsertData(locationID, temp, hud, lux, time):
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()
    query = "INSERT INTO tbl_tracker VALUES (%s, %s, %s, %s, %s)"
    values = [(locationID, temp, hud, lux, time)]

    cursor.executemany(query, values)
    conn.commit()
    conn.close()

def QueryData():
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()
    query = "SELECT * FROM tbl_tracker"
    cursor.execute(query)
    results = cursor.fetchall()
    return results
