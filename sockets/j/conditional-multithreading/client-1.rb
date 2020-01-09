require 'socket'

s = TCPSocket.new '127.0.0.1',8989

s.write("/tmp/testfiles/#{ARGV[0]}.c\n")

s.each_line do |line|
    puts line
end


s.close
