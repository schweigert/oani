files = Dir.glob "*.cpp"
f = File.new "makefile", "w"
f.puts "all:"
f.puts "\t g++ \\"

for i in files
	f.puts "\t #{i} \\"
end


f.puts "-o AniV7.o -lGL -lGLU -lglut -O3"
