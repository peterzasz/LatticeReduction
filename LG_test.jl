using LinearAlgebra, Random, Logging

include("lattice_algorithms.jl")

# searching for occasions where de number of greedy steps is bigger than the dimension

function standard_test(d::Int,n::Int,range::Int) # d - dimensions; n - number of times to run the test
	
	D = Dict{Int,Int}()

	for i = 1:n
		B = rand(-range:range,d,d)
		while !is_invertible(B)
			B = rand(-range:range,d,d)
		end

		B .= sortslices(B, dims=2, by=norm)

		@info "$i. Start base:" B

		Q,R = qr(B)
		Q = Matrix(Q)

		counter = 0
		while greedy_step!(B,d,Q,R) == 1
			counter += 1
			Q,R = qr(B)
			Q = Matrix(Q)

			@info "$i.$counter:" B
		end

		@info "$i.End base:" B num_of_steps = counter

		D[counter] = get(D,counter,0) + 1
	end

	@info "number with number:" D
end


function ort_deft_test(d::Int,n::Int,range::Int)

	maximal = 0

	for i = 1:n
		B = rand(-range:range,d,d)
		while !is_invertible(B)
			B = rand(-range:range,d,d)
		end

		LagrangeGauss_var1!(B)

		od = ort_deft(B,qr(B).R)

		if od > maximal
			maximal = od
		end

	end

	@info maximal
end

d = 3 # dimensions

io = open("log.txt", "w+")
logger = SimpleLogger(io)

with_logger(logger) do
	ort_deft_test(d,100000,1000)
end

flush(io)
close(io)