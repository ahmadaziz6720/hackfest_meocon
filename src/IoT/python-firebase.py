# referensi: https://github.com/RishabKattimani/FirebaseDBToPython.git
# pip install pyrebase4

import pyrebase

config = {
    "apiKey": "AIzaSyCTARMTNV8J6w24RJoR91RN8D07hZxkWZ0",
    "authDomain": "approkes.firebaseapp.com",
    "databaseURL": "https://approkes-default-rtdb.asia-southeast1.firebasedatabase.app",
    "projectId": "approkes",
    "storageBucket": "approkes.appspot.com",
    "messagingSenderId": "179843523866",
    "appId": "1:179843523866:web:52a90ac9dc0a7b952ff8a3"
}

firebase = pyrebase.initialize_app(config)
database = firebase.database()

data = {"Name": "liza", "MSG": "HAII LIZA", "Catatan": "Ini dari Python"}

database.child("test").set(data)

for i in database.child("test").get().each():
    print(i.val())


