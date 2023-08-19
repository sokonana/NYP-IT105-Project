# Import all required libraries
import pickle
import numpy as np
import pandas as pd


# Import model selection and data preparation libraries
from sklearn.preprocessing import StandardScaler, LabelEncoder

# Load model and encoder from pickled files
filename1 = 'encoder.sav'
filename2 = 'finalized_model.sav'

le = pickle.load(open(filename1, 'rb'))
clf = pickle.load(open(filename2,'rb'))

# Load test data for Allen
dataset = pd.read_csv('Allen.csv')
print(dataset)

# Test predictions
y_pred = clf.predict(dataset[:10])
y_prob = clf.predict_proba(dataset[:10])

# Print results
print(le.inverse_transform(y_pred))

for m in y_prob:
    print("Prediction Probability:", np.max(m))
