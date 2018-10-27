from bokeh.plotting import figure, output_file, show
from bokeh.io import export_png
import json

with open('articulation_points.json', 'r') as a, open('non_articulation_points.json', 'r') as n:
	a = json.load(a)
	n = json.load(n)
	dataX2 = []
	dataY2 = []
	for i in range(len(n)):
		x = n[i][0]
		y = n[i][1]
		dataY2.append(x)
		dataX2.append(y)
	pl = figure(plot_width=1500, plot_height=800)
	pl.circle(x=dataX2, y=dataY2, size=5,
                  color="#028e0c")

	dataX = []
	dataY = []
	for i in range(len(a)):
		x = a[i][0]
		y = a[i][1]
		dataY.append(x)
		dataX.append(y)
	pl.circle(x=dataX, y=dataY, size=5,
                  color="#9b0303")

	export_png(pl, filename="articulation_points.png")