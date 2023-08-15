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

# Load dataset and extract first 20 subjects
whole_dataset = pd.read_csv('Train_Data.csv')

first_10subject = (whole_dataset.groupby(by='subject', axis=0).count().index[:10])
selected_dataset = whole_dataset[whole_dataset['subject'].isin(first_10subject)]

# The DD and UD timings of each key have been showed to be highly correlated to each other 
# in a separate analysis. Hence, we will drop all features starting with 'DD'
all_features = selected_dataset.columns[3:34]
selected_features = [x for x in all_features if not x.startswith('DD')]

# Get a copy of dataset with selected feature columns
df = selected_dataset[selected_features].copy()

# Encode target data
le = LabelEncoder()
target = le.fit_transform(selected_dataset['subject'])

# Split into training and testing data
X_train, X_test, y_train, y_test = train_test_split(df, target,test_size=0.20, random_state=42, stratify=target)

# Perform scaling
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)

# Model instantiation
clf = SVC(random_state=42, C=1, gamma=0.08, kernel='rbf')

# Train and fit model
clf.fit(X_train_scaled, y_train)

# Save LabelEncode
filename = 'encoder.sav'
pickle.dump(le, open(filename,'wb'))

# Save scaler
filename1 = 'scaler.sav'
pickle.dump(scaler, open(filename1, 'wb'))

# Save model
filename2 = 'finalized_model.sav'
pickle.dump(clf, open(filename2, 'wb'))


