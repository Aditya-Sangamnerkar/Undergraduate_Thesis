import serial
import pymongo
import time


def push_to_db(bin_id, bin_fill_level):
    with pymongo.MongoClient('mongodb://localhost:27017/') as client:
        db = client['bin_db']
        collection = db['bin_collection']
        response = collection.update_one({'bin_id': bin_id}, {'$set': {'fill_level': bin_fill_level}}, upsert=True)


def check_payload(payload):
    empty_check = True if len(payload) > 0 else False
    if empty_check:
        check_start_byte = payload[0] == '*'
        check_stop_byte = payload[-1] == '#'
        if check_start_byte and check_stop_byte:
            bin_id = payload[1]
            bin_fill_level = payload[2:-1]
            return {'status': 200, 'data': [bin_id, bin_fill_level]}
        return {'status': 500}
    return {'status': 500}


def read_serial_port():
    with serial.Serial(port="COM3", baudrate=19200, timeout=2) as serial_port:
        payload = str()
        while True:
            if serial_port.in_waiting > 0:
                # utf 8 + strip to remove the two spaces for \n,\r
                payload = serial_port.readline().decode('utf-8').strip()
                result = check_payload(payload)
                print(result)
                if result['status'] == 200:
                    push_to_db(result['data'][0], result['data'][1])
                time.sleep(0.05)


if __name__ == '__main__':
    read_serial_port()
