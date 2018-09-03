filenames = Dir.glob "*.obj"

for fn in filenames
  puts "Removing Materials and uning all faces from "
  f = File.open(fn,"r")
  a = 0
  s = f.read
  lines = s.split "\n"
  fnorm = File.open(fn+"n"+a.to_s, "a+")
  for i in lines
    if i[0] == 'o'
      fnorm.close
      puts i.delete "o "
      a += 1
      fnorm = File.open((i.delete "o ")+".objn", "a+")
    end
    fnorm.puts i if i[0] == 'v' || i[0] == 'f'
  end
end
