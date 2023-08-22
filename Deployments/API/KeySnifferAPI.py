from flask import Flask
from flask import request, jsonify

# Import all required libraries
import pickle
import numpy as np
import pandas as pd


# Import model selection and data preparation 
from sklearn.preprocessing import StandardScaler, LabelEncoder

app = Flask(__name__)

@app.route('/keystroke', methods=['POST'])
def detect_keystroke():
    inputdata = request.get_json()
   
    print(inputdata)
    # forming an array
    # This checking for dict data type is to make sure it works with Postman 
    # and web client call
    # Postman will send data as dict, other clients web call might just send an array
    if isinstance(inputdata, dict):
        input = np.array([inputdata['input']])
    else:
        input = np.array([inputdata])

    # Load scaler and model from file
    filename1 = 'encoder.sav'
    filename2 = 'finalized_model.sav'

    # Load from saved serialised format
    le = pickle.load(open(filename1, 'rb'))
    model = pickle.load(open(filename2,'rb'))

    # Apply scaling to input parameters
    y_pred = model.predict(input)
    y_class = le.inverse_transform(y_pred)
    y_prob = round(np.max(model.predict_proba(input)),4)

    return jsonify({'pred_code' : str(y_pred), 'pred_class': y_class[0], 'pred_prob': str(y_prob)})
    

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001, debug=True)