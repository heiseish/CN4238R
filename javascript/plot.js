'use-strict';
var plotly = require('plotly')("heiseish", "UkxgQPWwLND2Q1e1hDsf")
var clusters = require('./clusters.json')
var vertices = require('./vertices.json')
var special = ['zeroth','first', 'second', 'third', 'fourth', 'fifth', 'sixth', 'seventh', 'eighth', 'ninth', 'tenth', 'eleventh', 'twelfth', 'thirteenth', 'fourteenth', 'fifteenth', 'sixteenth', 'seventeenth', 'eighteenth', 'nineteenth'];
var deca = ['twent', 'thirt', 'fort', 'fift', 'sixt', 'sevent', 'eight', 'ninet'];

const stringifyNumber = (n) => {
	if (n < 20) return special[n];
	if (n%10 === 0) return deca[Math.floor(n/10)-2] + 'ieth';
	return deca[Math.floor(n/10)-2] + 'y-' + special[n%10];
}


const random_rgba = () => {
	var o = Math.round, r = Math.random, s = 255;
	return 'rgba(' + o(r()*s) + ',' + o(r()*s) + ',' + o(r()*s) + ',' + r().toFixed(1) + ')';
}

let data = []
for (let i = 0; i < 10; i++) {
	var trace = {
		x: clusters[i].map(idx => vertices[idx][0]),
		y: clusters[i].map(idx => vertices[idx][1]),
		mode: "markers",
		name: stringifyNumber(i)  + " clusters",
		text: [stringifyNumber(i)],
		marker: {
			color: random_rgba(),
			size: 12,
			line: {
				color: "white",
				width: 0.5
			}
		},
		type: "scatter"
	};
	data.push(trace)
}

var layout = {
	title: "k-means algorithm",
	xaxis: {
		title: "Longitude",
		showgrid: false,
		zeroline: false
	},
	yaxis: {
		title: "Latitude",
		showline: false
	}
};
  var graphOptions = {layout: layout, filename: "line-style", fileopt: "overwrite"};
  plotly.plot(data, graphOptions, function (err, msg) {
	  console.log(msg);
  });
