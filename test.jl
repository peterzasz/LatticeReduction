using LinearAlgebra, StaticArrays

include("lattice_algorithms.jl")

u = MVector{2}([5,0])
v = MVector{2}([9,1])

LagrangeGauss_2d!(u,v)

println(u)
println(v)