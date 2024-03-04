import { initializeApp} from "https://www.gstatic.com/firebasejs/10.7.1/firebase-app.js";
import { getDatabase, push, get, update, set} from "https://www.gstatic.com/firebasejs/10.7.1/firebase-database.js";
import { ref } from "https://www.gstatic.com/firebasejs/10.7.1/firebase-database.js";

const firebaseConfig = {
    apiKey: "AIzaSyDm0cssgEIVfy77wLs3nCffl7YkOm_jqoc",
    authDomain: "opnelab.firebaseapp.com",
    databaseURL: "https://opnelab-default-rtdb.firebaseio.com",
    projectId: "opnelab",
    storageBucket: "opnelab.appspot.com",
    messagingSenderId: "69956560633",
    appId: "1:69956560633:web:35dd82b1ec2b217faaa428",
    measurementId: "G-FT564ZQQ57"
  };

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

const temperatureElem = document.getElementById("ftemp");
const pressureElem = document.getElementById("fpres");
const humidityElem = document.getElementById("fhum");
const moistureElem = document.getElementById("fmoi");
const phElem = document.getElementById("fph");

const dataRef = ref(database, 'DHT');

// Get data once from Firebase Realtime Database
get(dataRef).then((snapshot) => {
    const data = snapshot.val();
    
    // Display the data in the corresponding elements
    temperatureElem.textContent = `${data.temperature}`;
    humidityElem.textContent = `${data.humidity}`;
}).catch((error) => {
    console.error(error);
});