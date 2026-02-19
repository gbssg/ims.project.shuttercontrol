const ip = "http://espmicromod-001.cl04.ch/";


document.getElementById("up_button").addEventListener("click", () => {
  console.log("Up");
  fetch(
    `${ip}motor?id=1&cmd=up`,{}
  );
});

document.getElementById("down_button").addEventListener("click", () => {
  console.log("Down");
  fetch(
    `${ip}motor?id=1&cmd=down`,{}
  );
});

document.getElementById("stop_button").addEventListener("click", () => {
  console.log("Stop");
  fetch(
    `${ip}motor?id=1&cmd=stop`,{}
  );
});

document.getElementById("up_button_2").addEventListener("click", () => {
  console.log("Up");
  fetch(
    `${ip}motor?id=2&cmd=up`,{}
  );
});

document.getElementById("down_button_2").addEventListener("click", () => {
  console.log("Down");
  fetch(
    `${ip}motor?id=2&cmd=down`,{}
  );
});

document.getElementById("stop_button_2").addEventListener("click", () => {
  console.log("Stop");
  fetch(
    `${ip}motor?id=2&cmd=stop`,{}
  );
});

document.getElementById("preset1").addEventListener("click", () => {
  fetch(`${ip}motor?id=1&cmd=down`);
  fetch(`${ip}motor?id=2&cmd=down`);
  console.log("preset1");
  setTimeout(() => {
    console.log("preset1");
    fetch(
      `${ip}motor?id=1&cmd=up`,{}
    );
    fetch(
      `${ip}motor?id=2&cmd=up`,{}
    );

    setTimeout(() => {
      console.log("preset1");
      fetch(
        `${ip}motor?id=1&cmd=stop`,{}
      );
      fetch(
        `${ip}motor?id=2&cmd=stop`,{}
      );
    }, 2000);

  }, 43000);
});

document.getElementById("preset2").addEventListener("click", () => {
  fetch(`${ip}motor?id=1&cmd=down`);
  fetch(`${ip}motor?id=2&cmd=down`);
  console.log("preset1");
  setTimeout(() => {
    fetch(
      `${ip}motor?id=1&cmd=stop`,{}
    );
    fetch(
      `${ip}motor?id=2&cmd=stop`,{}
    );
  }, 43000);
});

document.getElementById("preset3").addEventListener("click", () => {
  fetch(`${ip}motor?id=1&cmd=up`);
  fetch(`${ip}motor?id=2&cmd=up`);
  console.log("preset1");
  setTimeout(() => {
    fetch(
      `${ip}motor?id=1&cmd=stop`,{}
    );
    fetch(
      `${ip}motor?id=2&cmd=stop`,{}
    );
  }, 43000);
});


document.getElementById("preset4").addEventListener("click", () => {
  fetch(`${ip}motor?id=1&cmd=stop`);
  fetch(`${ip}motor?id=2&cmd=stop`);
});

document.getElementById("preset4").addEventListener("click", () => {
  fetch(`${ip}motor?id=1&cmd=up`);
  fetch(`${ip}motor?id=2&cmd=up`);
});

function updateHeight() {
    fetch(`${ip}motor?id=1&cmd=getHeight`)
        .then(response => { 
            return response.json();
        })
        .then(data => {
            console.log("Aktuelle Höhe:", data.height);
            document.getElementById("heightDisplay").innerText = data.height + " %";
        })
        .catch(error => {
            console.error("Fehler beim Abrufen der Daten:", error);
        });
        fetch(`${ip}motor?id=2&cmd=getHeight`)
        .then(response => { 
            return response.json();
        })
        .then(data => {
            console.log("Aktuelle Höhe 2:", data.height);
            document.getElementById("heightDisplay2").innerText = data.height + " %";
        })
        .catch(error => {
            console.error("Fehler beim Abrufen der Daten:", error);
        });
}

setInterval(updateHeight, 1000);


