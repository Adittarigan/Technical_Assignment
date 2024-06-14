from flask import Flask, request, jsonify
import time
import pandas as pd

app = Flask('Flask_Testing')

AirQuality = []
timestamp = []

@app.route('/', methods=['GET'])
def hello_world():
    if len(AirQuality) > 0:
        data_dict = {'timestamp': timestamp, 'Air Quality': AirQuality}
        df = pd.DataFrame(data_dict)
        return df.to_html()
    else:
        return 'No Data Received'

@app.route('/data', methods=['POST'])
def data():
    if request.is_json:
        data = request.json
        AQ = data.get('Air Quality')
    else:
        AQ = request.form.get('Air Quality')

    timing = time.time()
    AirQuality.append(AQ)
    timestamp.append(timing)

    return jsonify({'Air Quality': AQ, 'timestamp': timing})

if __name__ == '__main__':
    app.run(host='0.0.0.0')
