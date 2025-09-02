const ip = "http://192.168.150.41/";
document.getElementById("up_button").addEventListener("click",()=>{
    console.log("Up");
    fetch(`${ip}up`, {
  mode: 'cors',
  headers: {
    'Access-Control-Allow-Origin':'*'
  }
});
});

document.getElementById("down_button").addEventListener("click",()=>{
    console.log("Down");
    fetch(`${ip}down`, {
  mode: 'cors',
  headers: {
    'Access-Control-Allow-Origin':'*'
  }
});
});


document.getElementById("stop_button").addEventListener("click",()=>{
    console.log("Stop");
    fetch(`${ip}stop`, {
  mode: 'cors',
  headers: {
    'Access-Control-Allow-Origin':'*'
  }
});
});
