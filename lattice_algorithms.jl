using LinearAlgebra, StaticArrays

#core functions
sq_norm(v) = v⋅v

#CVP

function CVP_solver() end

#SVP

function LagrangeGauss_2d!( u::MVector{2}, v::MVector{2} )
	
	s(u,v) = Int(round( u⋅v / sq_norm(u) )) # v - su

	v .-= s(u,v)*u
	
	while sq_norm(u) > sq_norm(v)

		u .-= s(v,u)*v

		if sq_norm(v) <= sq_norm(u)
			break
		end

		v .-= s(u,v)*u

	end
end

function SVP_Enum() end

function LagrangeGauss!() end