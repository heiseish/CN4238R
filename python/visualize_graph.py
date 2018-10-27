from bokeh.plotting import figure, output_file, show
from bokeh.io import export_png
import json

with open('vertices.json', 'r') as v:
	v = json.load(v)
	dataX = []
	dataY = []
	for i in range(len(v)):
		x = v[i][0]
		y = v[i][1]
		dataY.append(x)
		dataX.append(y)
	pl = figure(plot_width=1500, plot_height=800)
	pl.circle(x=dataX, y=dataY, size=5,
                  color="#031e7c")

	export_png(pl, filename="graph.png")