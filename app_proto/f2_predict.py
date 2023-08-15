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

# Load scaler and model from file
filename = 'encoder.sav'
filename1 = 'scaler.sav'
filename2 = 'finalized_model.sav'

le = pickle.load(open(filename, 'rb'))
scaler = pickle.load(open(filename1,'rb'))
model = pickle.load(open(filename2,'rb'))

whole_dataset = pd.read_csv('Train_Data.csv')

# Load 10 subject not used in training to test performance
test_subject = whole_dataset[5000:5010]

# The DD and UD timings of each key have been showed to be highly correlated to each other 
# in a separate analysis. Hence, we will drop all features starting with 'DD'
all_features = test_subject.columns[3:34]
selected_features = [x for x in all_features if not x.startswith('DD')]

# Get a copy of dataset with selected feature columns
df = test_subject[selected_features].copy()

# display prediction
predictions = model.predict(df)

print("Results in codes:")
print(predictions)

print("Results in labels:")
print(le.inverse_transform(predictions))

