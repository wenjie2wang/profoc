Rcpp::compileAttributes()
devtools::document()
devtools::build()
devtools::check(cran = TRUE)
devtools::test()

# Release TODO:

# Bump Version Number in Description
# Update the Date field in Description
# Update the Date in NEWS.md

# CRAN Release checklist:

devtools::spell_check()
devtools::check_rhub()
devtools::release()

# Merge submitted_to_cran into main, without squashing commits, wihtout extra merge commit
# Create a tag on main

# Potential library unload problems can be solved by specifying
# CXXFLAGS=-fno-gnu-unique in ~/.R/Makevars
# or
# PKG_CXXFLAGS=-fno-gnu-unique in src/Makevars