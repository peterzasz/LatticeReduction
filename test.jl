using LinearAlgebra, Random

include("lattice_algorithms.jl")

#= LAGRANGE GAUSS 2d
u = MVector{2}([5,0])
v = MVector{2}([9,1])

LagrangeGauss_2d!(u,v)

println(u)
println(v)
=#

#=
A = [3 2 1; 
	 0 2 4; 
	 1 1 -1 ]
v = [3.005,-35.995, 15.005] # v = 3a_1 + 2a_2 - 10a_3 + [0.005, 0.005, 0.005], closest vector: [3,-36,15]

F = qr(A)

Matrix(F.Q) |> display
F.R |> display

greedy_CVP(Matrix(F.Q),F.R,v,Matrix(F.Q)\v)

@time A*greedy_CVP(Matrix(F.Q),F.R,v,Matrix(F.Q)\v) |> display
=#
#=
n = 10

for i in 1:10
	M = rand(-100:100,n,n)
	od = ort_deft(M,qr(M).R)

	while det(M) == 0
		M = rand(-100:100,n,n)
	end

	M2 = copy(M)

	println("var1:")

	@time counter = LagrangeGauss_var1!(M)

	(counter, od/counter) |> display

	println()

	counter = LagrangeGauss_var2!(M2)

	(counter, od, ort_deft(M2,qr(M2).R)) |> display

end =#
#=
function lalala()
	d = 5
	B = rand(d,d) .* 100
	B |> display

	while !is_invertible(B)
		B = rand(-range:range,d,d)
	end

	LagrangeGauss_var1!(B)

	ort_deft(B,qr(B).R) |> display

	for i in 1:size(B,2)
		nr = norm(B[:,i])

		for j in 1:size(B,1)
			B[j,i] = B[j,i] / nr
		end
	end

	ort_deft(B,qr(B).R) |> display

	LagrangeGauss_var1!(B)

	ort_deft(B,qr(B).R) |> display
end

lalala()=#
function bcal(n)
	x = 1

	for i = 2:n
		x = sqrt(1-((i-1)/i)^2*x^2)
		println(x)

	end
end

bcal(100000)