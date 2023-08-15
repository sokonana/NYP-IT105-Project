from flask import Flask
from flask import request, jsonify

# Import all required libraries
import pickle
import numpy as np
import pandas as pd


# Import model selection and data preparation libraries
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn import preprocessing

# Import algorithm libraries
from sklearn.svm import SVC

app = Flask(__name__)

@app.route('/keystroke', methods=['POST'])
def detect_keystroke():
    inputdata = request.get_json()
   
    # forming an array
    # input = np.array([inputdata['H.period'], inputdata['UD.period.t'] ])
    input = np.array(inputdata['input']).reshape(1,-1)


    # Load scaler and model from file
    filename = 'encoder.sav'
    filename1 = 'scaler.sav'
    filename2 = 'finalized_model.sav'

    # Load from saved serialised format
    le = pickle.load(open(filename, 'rb'))
    scaler = pickle.load(open(filename1,'rb'))
    model = pickle.load(open(filename2,'rb'))

    # Apply scaling to input parameters
    input_scaled = scaler.transform(input)
    y_pred = model.predict(input_scaled)
    y_class = le.inverse_transform(y_pred)

    return jsonify({'predict_code' : str(y_pred), 'predict_class': y_class[0]})
    

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001, debug=True)