skip_if(debug_mode)
kstep <- 0.1
order <- 4
deg <- order - 1
a <- sqrt(2)
pstep <- 0.01

x <- seq(pstep, 1 - pstep, pstep)

# Create desired knots:
knots <- make_knots(kstep = kstep, deg = deg, a = a)[, 1]

# Create the b-spline basis using splines
old <- splines::splineDesign(knots, x, deg + 1, derivs = 0L, outer.ok = TRUE)

# Create the b-spline basis using splines2
new <- splines2_basis(x, knots, deg, range(knots))

expect_equal(old, new, tolerance = 0.00001)

kstep <- 0.1
order <- 4
deg <- order - 1
a <- 0.2
pstep <- 0.01

x <- seq(pstep, 1 - pstep, pstep)

# Create desired knots:
knots <- make_knots(kstep = kstep, deg = deg, a = a)[, 1]

# Create the b-spline basis using splines
old <- splines::splineDesign(knots, x, deg + 1, derivs = 0L, outer.ok = TRUE)

# Create the b-spline basis using splines2
new <- splines2_basis(x, knots, deg, range(knots))

expect_equal(old, new, tolerance = 0.00001)

kstep <- 0.1
order <- 3
deg <- order - 1
a <- sqrt(2)
pstep <- 0.01
x <- seq(pstep, 1 - pstep, pstep)

# Create desired knots:
knots <- make_knots(kstep = kstep, deg = deg, a = a)[, 1]

# Create the b-spline basis using splines
old <- splines::splineDesign(knots, x, deg + 1, derivs = 0L, outer.ok = TRUE)

# Create the b-spline basis using splines2
new <- splines2_basis(x, knots, deg, range(knots))

expect_equal(old, new, tolerance = 0.00001)