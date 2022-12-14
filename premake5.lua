workspace "glsl-fractal"
    location "build"
    architecture "x64"
    configurations {"Release", "Debug"} 

project "glsl-fractal"
    kind "ConsoleApp"
    language "C++"
    location "build"

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp",
        "libraries/lib/glad.c",
        "shaders/**",
        "libraries/include/ImGui/*.h",
        "libraries/include/ImGui/*.cpp"
    }    

    includedirs {"libraries/*"}
    libdirs "libraries/lib"
    links {"opengl32", "glfw3"}

    filter "configurations:Release"
        defines "RELEASE"
        optimize "Speed"
        
    filter "configurations:Debug"
        defines "DEBUG" 
        symbols "On" 