add_rules("mode.debug", "mode.release")
add_requires("raylib 4.0.0")

target("ccd") do
    set_kind("binary")
    add_files("src/*.cpp")
	add_includedirs("include")

	set_warnings("all")
	set_optimize("fastest")
	
	add_packages("raylib")
end