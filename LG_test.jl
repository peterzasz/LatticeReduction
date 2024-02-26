using LinearAlgebra, Random, Logging

include("lattice_algorithms.jl")

# searching for occasions where de number of greedy steps is bigger than the dimension

function onerun_test(d::Int)
	
	B = rand(-100:100,d,d)
	B .= sortslices(B, dims=2, by=norm)

	@info "Start base:" B

	Q,R = qr(B)
	Q = Matrix(Q)

	counter = 0
	while greedy_step!(B,d,Q,R) == 1
		counter += 1
		Q,R = qr(B)
		Q = Matrix(Q)

		@info "step $counter:" B
	end

	@info "End base:" B
end

d = 10 # dimensions

onrun_test(d)