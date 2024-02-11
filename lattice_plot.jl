using Plots

function plot_2dvec(v)
	plot!([0,v[1]],[0,v[2]], arrow = true)
end