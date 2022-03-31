function getData() {

    firebase.database().ref('/test').once('value').then(function (snapshot) {
        var float = snapshot.val().float;
        var int = snapshot.val().int;
        var string = snapshot.val().string;
    
        document.getElementById("float").innerHTML = float;
        document.getElementById("int").innerHTML = int;
        document.getElementById("string").innerHTML = string;
    })
}