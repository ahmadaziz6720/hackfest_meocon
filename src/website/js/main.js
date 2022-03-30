hilangkan("rules");
hilangkan("form");
hilangkan("edit");
hilangkan("notAvailable");

munculkan("realtime");

function munculkan(id){
    var elem = document.getElementById(id);
    if (elem.style.display === "none") {
        elem.style.display = "block";
    } else {
        elem.style.display = "none";
    }
}

function hilangkan(){
    var rules = document.getElementById("rules");
    var form = document.getElementById("form");
    var edit = document.getElementById("edit");
    var notAvailable = document.getElementById("notAvailable");
    var realtime = document.getElementById("realtime");

    rules.style.display = "none";
    form.style.display = "none";
    edit.style.display = "none";
    notAvailable.style.display = "none";
    realtime.style.display = "none";
}

function kirim() {
    munculkan("edit");
    munculkan("form");
    munculkan("rules");

    var nama = document.getElementById("people").value;
    var role = document.getElementById("tmp").value;

    document.getElementById("people2").innerHTML = nama;
    document.getElementById("tmp2").innerHTML = role;
}