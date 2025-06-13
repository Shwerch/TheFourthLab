find com -name "*.java" > sources.txt
javac -d build -encoding UTF-8 @sources.txt
rm sources.txt
java -cp build com.example.Main
