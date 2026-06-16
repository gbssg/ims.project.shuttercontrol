// const ip = "http://espmicromod-001.cl04.ch/";

const ip = "http://10.5.8.6/";


document.getElementById("up_button").addEventListener("click", () => {
  console.log("Up");
  let sliderValue = parseInt(document.getElementById("slider-1").value)
  let url = `${ip}motor?id=1&cmd=up`;
  console.debug(sliderValue);
  if(sliderValue > 0){
    url += `&time=${sliderValue}`
  }
  fetch(
    url,{}
  );
});

document.getElementById("down_button").addEventListener("click", () => {
  console.log("Down");
  let sliderValue = parseInt(document.getElementById("slider-1").value)
  let url = `${ip}motor?id=1&cmd=down`;
  console.debug(sliderValue);
  if(sliderValue > 0){
    url += `&time=${sliderValue}`
  }
  fetch(
    url,{}
  );
});

document.getElementById("stop_button").addEventListener("click", () => {
  console.log("Stop");
  let sliderValue = parseInt(document.getElementById("slider-1").value)
  let url = `${ip}motor?id=1&cmd=stop`;
  console.debug(sliderValue);
  if(sliderValue > 0){
    url += `&time=${sliderValue}`
  }
  fetch(
    url,{}
  );
});

document.getElementById("up_button_2").addEventListener("click", () => {
  console.log("Up");
  let sliderValue = parseInt(document.getElementById("slider-2").value)
  let url = `${ip}motor?id=2&cmd=up`;
  if(sliderValue > 0){
    url += `&time=${sliderValue}`
  }
  fetch(
    url,{}
  );
});

document.getElementById("down_button_2").addEventListener("click", () => {
  console.log("Down");
  let sliderValue = parseInt(document.getElementById("slider-2").value)
  let url = `${ip}motor?id=2&cmd=down`;
  if(sliderValue > 0){
    url += `&time=${sliderValue}`
  }
  fetch(
    url,{}
  );
});

document.getElementById("stop_button_2").addEventListener("click", () => {
  console.log("Stop");
  let sliderValue = parseInt(document.getElementById("slider-2").value)
  let url = `${ip}motor?id=2&cmd=stop`;
  if(sliderValue > 0){
    url += `&time=${sliderValue}`
  }
  fetch(
    url,{}
  );
});

var output1 = document.getElementById("slider-output-1");
var output2 = document.getElementById("slider-output-2");
var input1 = document.getElementById("slider-1");
var input2 = document.getElementById("slider-2");

input1.oninput = function() {
  if (this.value > 0) {
    output1.innerHTML = (this.value / 1000).toFixed(2) + "s";
  }
  else {
    output1.innerHTML = "auto";
  }
}

input2.oninput = function() {
  if (this.value > 0) {
    output2.innerHTML = (this.value / 1000).toFixed(2) + "s";
  }
  else {
    output2.innerHTML = "auto";
  }
}