var temp = [], hum = [], light = [], motion = [];
var firebase = new Firebase("esp-room-e42a9.firebaseio.com/");
firebase.on('value', function(snapshot) {
   for(let i in snapshot.val().temp){
     temp.push(snapshot.val().temp[i]);
   }
   for(let i in snapshot.val().hum){
     hum.push(snapshot.val().hum[i]);
   }
   for(let i in snapshot.val().light){
     light.push(snapshot.val().light[i]);
   }
   for(let i in snapshot.val().motion){
     motion.push(snapshot.val().motion[i]);
   }
  temp = temp.slice(temp.length- 20, temp.length);
  hum = hum.slice(hum.length- 20, hum.length);
  light = light.slice(light.length- 20, light.length);
  light.forEach((o, i, a) => a[i] = o*100/1024);
  motion = motion.slice(motion.length- 20, motion.length);
  drawGraph(temp, hum, light, motion);
});



function drawGraph(temp, hum, light, motion){
  var labels = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19];
  var ctx = document.getElementById("myChart").getContext('2d');
var myChart = new Chart(ctx, {
  type: 'line',
  data: {
    labels: labels,
    datasets: [{
    label: "temperature [°C]",
    labelString : "°C",
    borderColor: 'rgb(255, 99, 132)',
    backgroundColor: 'rgb(255, 99, 132)',
    fill: false,
    data: temp,
      yAxisID: "y-axis-temp",
    },
     {
            label: "humidity [%RH]",
           labelString : "hum",

    borderColor: 'rgb(0, 99, 132)',
    backgroundColor: 'rgb(0, 99, 132)',
    fill: false,
    data: hum,
      yAxisID: "y-axis-temp",         
               
  },
                 {
            label: "light [%]",
           labelString : "light",

    borderColor: 'rgb(145, 70, 65)',
    backgroundColor: 'rgb(145, 70, 65)',
    fill: false,
    data: light,
      yAxisID: "y-axis-temp",         
               
  },
                 {
            label: "motion [0-1]",
           labelString : "motion",

    borderColor: 'rgb(0, 21, 32)',
    backgroundColor: 'rgb(0, 21, 32)',
    fill: false,
    data: motion,
      yAxisID: "y-axis-temp",         
               
  }]
  },
            options: {
                responsive: true,
              maintainAspectRatio: false,
              hoverMode: 'index',
                stacked: false,
                title:{
                    display: true,
                    text:'Last 20 room measurements'
                },

                scales: {
                    yAxes: [{
                        type: "linear", 
                        display: true,
                        position: "left",
                        id: "y-axis-temp",
                        ticks: {
                          beginAtZero:true,
                          suggestedMax: 50
                        }
              
                    }],
                }
            }
});

}