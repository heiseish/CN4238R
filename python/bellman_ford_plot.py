from bokeh.plotting import figure, output_file, show
from bokeh.io import export_png
import json

with open('bellmanford_path.json', 'r') as p, open('vertices.json', 'r') as v:
	v = json.load(v)
	p = json.load(p)
	
	dataX = []
	dataY = []
	for i in range(len(p)):
		if p[i] is -1:
			continue
		v1 = v[i]
		v2 = v[p[i]]
		dataY.append([ v1[1], v2[1]])
		dataX.append([ v1[0], v2[0] ])
	pl = figure(plot_width=1500, plot_height=800)
	pl.multi_line(xs=dataX, ys=dataY)
	pl.circle_cross(x=[103.7694386], y=[1.294731], size=20,
                  color="#FB8072", fill_alpha=0.2, line_width=2)
	export_png(pl, filename="bellman_ford_path.png")