import { initializeApp } from "https://www.gstatic.com/firebasejs/10.7.1/firebase-app.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/10.7.1/firebase-database.js";

const firebaseConfig = {
    apiKey: "AIzaSyBYqrAG5Yd332woLcWFOsk3jOAS-NuCTt4",
    authDomain: "openlab-44938.firebaseapp.com",
    databaseURL: "https://openlab-44938-default-rtdb.firebaseio.com",
    projectId: "openlab-44938",
    storageBucket: "openlab-44938.appspot.com",
    messagingSenderId: "103202189203",
    appId: "1:103202189203:web:94d7c05dcc2a54a7280266",
    measurementId: "G-YFLQSJCGP5"
  };

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

const temperatureElem = document.getElementById("ftemp");
const pressureElem = document.getElementById("fpres");
const humidityElem = document.getElementById("fhum");
const moistureElem = document.getElementById("fmoi");
const phElem = document.getElementById("fph");

const dataRef = ref(database, 'DHT');

// Listen for changes to data in Firebase Realtime Database
onValue(dataRef, (snapshot) => {
    const data = snapshot.val();
    
    // Display the data in the corresponding elements
    temperatureElem.textContent = `${data.temperature}`;
    humidityElem.textContent = `${data.humidity}`;
    pressureElem.textContent = `${data.pressure}`;
    moistureElem.textContent = `${data.moisture}`;
    phElem.textContent = `${data.ph}`;
}, {
    onlyOnce: false // This option ensures the callback runs every time the data changes
});
