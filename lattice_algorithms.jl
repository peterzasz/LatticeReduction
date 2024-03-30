using LinearAlgebra

# A FEW IMPORTANT LATTICES
 
 triangle_2 = [1 1/2;
 			   0 sqrt(3)/2]

 triangle_3 = [1 1/2 0;
 			   0 sqrt(3)/2 1/sqrt(3);
 			   0 0 sqrt(2)/sqrt(3)]



# BASIC FUNCTIONS

"""
	sq_norm(v)

	This function recives a vector v, and returns the squared of the standard euclidian norm of that vector.
"""
sq_norm(v::Vector) = v⋅v

"""
	ort_deft(B,R)

	This function recieves two matrices B and R. B should be nonsingular,
	and R should be the matrix from the qr decomposition of B (B=QR).
	
	If these conditions hold the function returns the ortogonality defect of
	the linearly independent vectrors that are the columns of B.
"""
ort_deft(B::Matrix,R::Matrix) = prod(norm(B[:,i])/abs(diag(R)[i]) for i in 1:size(B,2))

"""
	is_invertible(A)

	This function recieves a matrix A. In the case that a is nonsingular,
	the function returns true, otherwise it returns false.
"""
is_invertible(A::Matrix) = !isapprox(det(BigFloat.(A)), 0, atol = 1e-18)



# CVP, SVP solvers

"""
	greedy_CVP(Q,R,v,v_comp)
	
	This function recieves two matrices Q and R, and two vectors v and v_comp.
	It can be used to find the closest lattice vector to v, in a lattice L
	generated by the columns of the nonsingular matrice B.

	Q and R should be the matrices given by the qr decomposition of the matrice B (B=QR), 
	and v_comp should be a vector such that Q*v_comp=v.

	This function returns a vector called comp, such that B*comp is the closest vector to the
	vector v in the lattice L.
"""
function greedy_CVP( Q::Matrix, R::Matrix, v::Vector, v_comp::Vector )

	r = norm( diag(R) ./ 2 ) # radius of ball to search trough

	lower = v_comp .- r
	upper = v_comp .+ r

	position = zeros(size(lower))
	base_comp = zeros(Int,size(lower))

	# setting up start position

	for i in size(lower,1):-1:1
		dist = ceil(Int,(lower[i]-position[i])/diag(R)[i])
		position = position + R[:,i].*dist
		base_comp[i] += dist
	end

	# minsearch trough lattice vectors of cube

	min_len = Inf
	min_base_comp = zeros(Int,size(lower))

	at = 1
	while at <= size(position,1)

		back_len = sq_norm(position[2:end]-v_comp[2:end])

		while position[1] < upper[1]

			len = back_len + (position[1]-v_comp[1])^2

			if len < min_len
				min_len = len
				min_base_comp = copy(base_comp)
			end

			if R[1,1] < 0
				position += -R[:,1]
				base_comp[1] -= 1
			else
				position += R[:,1]
				base_comp[1] += 1
			end
		end

		at = 2
		if R[2,2] < 0
			position += -R[:,2]
			base_comp[2] -= 1
		else
			position += R[:,2]
			base_comp[2] += 1
		end

		while position[at] > upper[at]

			at += 1

			if at > size(position,1)
				break
			else
				if R[at,at] < 0
					position += -R[:,at]
					base_comp[at] -= 1
				else
					position += R[:,at]
					base_comp[at] += 1
				end
			end
		end

		if at <= size(position,1)

			for i in at-1:-1:1

				dist = ceil(Int,(lower[i]-position[i])/diag(R)[i])
				position = position + R[:,i].*dist
				base_comp[i] += dist

			end
		end
	end

	return min_base_comp
end

function greedy_SVP(Q::Matrix,R::Matrix) # returns shortest vector
	# todo
end



# BASIS REDUCTION ALGORITHMS

"""
	LagrangeGauss_2d!(u,v)

	This function is the implementation of the classical lattice reduction algorithm of
	Lagrange on the plane.

	The function should recieve two linearly independent vectors of the same dimension, and it changes
	these vectors in such a way that they still generate the same lattice but are LG reduced.

	The function returns the number of times a change has been made to the vectors u and v, or equivalently
	the number of week reductions the algorythm does.
"""
function LagrangeGauss_2d!(u::Vector,v::Vector)

	counter = 0

	s(u,v) = Int(round( u⋅v / sq_norm(u) )) # v - su

	ss = s(u,v)

	if ss != 0
		counter += 1
		v .-= s(u,v)*u # weak reduction 
	end
	
	while sq_norm(u) > sq_norm(v)

		ss = s(v,u)

		if ss != 0
			counter += 1
			u .-= ss*v # weak reduction
		end

		if sq_norm(v) <= sq_norm(u)
			break
		end

		ss = s(u,v)

		if ss != 0
			counter += 1
			v .-= ss*u # weak reduction
		end
	end

	return counter
end

"""
	LagrangeGauss_var1!(B)

	This function implements a variant of the generalization of Lagranges lattice reduction in arbitrary
	dimensions. This is a variant of the greedy reduction algorythm given by ... in ... 

	The function should recieve a nonsingular matrice B, where the columns of B are the basis of the lattice L.
	The function changes the matrice B, in such a way that its columns still generate the same lattice, but
	the basis is LG reduced.

	The function returns the number of times a change has been made to the columns of B or equivalently the
	number of strong reduction steps in the algorythm.
"""
function LagrangeGauss_var1!(B::Matrix)

	counter = 0

	s(u,v) = Int(round( u⋅v / sq_norm(u) )) # as in 2dim

	if size(B,2) == 2
		@views u,v = B[:,1], B[:,2]
		return LagrangeGauss_2d!(u,v)
	else
	
		smaller = true

		while smaller

			B .= sortslices(B, dims=2, by=norm)
			Q,R = qr(B)
			Q = Matrix(Q)

			smaller = false
			for i in size(B,2):-1:3

				comp = greedy_CVP(Q[:,1:i-1],R[1:i-1,1:i-1],Q[:,1:i-1]*R[1:i-1,i],R[1:i-1,i])
				new_vec = B[:,i] - B[:,1:i-1]*comp 

				if norm(new_vec) < norm(B[:,i])
					B[:,i] = new_vec
					smaller = true
					counter += 1
				end
			end

			new_vec = B[:,2] - s(B[:,1],B[:,2])*B[:,1]

			if norm(new_vec) < norm(B[:,2])
				B[:,2] = new_vec
				smaller = true
				counter += 1
			end

		end

		B .= sortslices(B, dims=2, by=norm)
	end

	return counter
end


function greedy_step!(B::Matrix,at::Int,Q::Matrix,R::Matrix) # returns -1 - length not decreased; 0 - length decrased, but vector positions not; 1 - length decrased, vector positions changed

	comp = greedy_CVP(Q[:,1:at-1],R[1:at-1,1:at-1],Q[:,1:at-1]*R[1:at-1,at],R[1:at-1,at])
	new_vec = B[:,at] - B[:,1:at-1]*comp

	new_norm = norm(new_vec)
	index = at

	while index > 0 && new_norm < norm(B[:,index])
		index -= 1
	end

	if index == at
		return -1
	elseif index == at-1
		B[:,at] = new_vec
		return 0
	else
		for i in at:-1:index+2
			B[:,i] = B[:,i-1]
		end

		B[:,index+1] = new_vec

		return 1
	end
end

function LagrangeGauss_var2!(B::Matrix) # gives back number of times it decrased length of a vector

	counter = 0

	if size(B,2) == 2
		@views u,v = B[:,1], B[:,2]
		LagrangeGauss_2d!(u,v)
	else

		B .= sortslices(B, dims=2, by=norm)
		at = size(B,2)

		while at > 2

			step = 1
			while step == 1
				Q,R = qr(B)
				Q = Matrix(Q)
				
				step = greedy_step!(B,at,Q,R)
				
				if step == 1 || step == 0
					counter += 1
				end
			end

			at -= 1
		end

		@views u,v = B[:,1], B[:,2]
		counter += LagrangeGauss_2d!(u,v)
	end

	return counter
end


