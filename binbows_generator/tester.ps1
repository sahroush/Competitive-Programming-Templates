touch main.txt
touch naive.txt
rm tests -r
mkdir tests
mkdir tests/in
mkdir tests/out
g++ -std=c++17 -o main.exe main.cpp
g++ -std=c++17 -o naive.exe naive.cpp
g++ -std=c++17 -o gen.exe gen.cpp
$AC = 0
$WA = 0
$i = 200
while ($i){
  .\gen.exe
  .\main.exe
  .\naive.exe
  if(diff (cat main.txt) (cat naive.txt)){
    $WA ++
    cp test.txt tests/in/input$WA.txt
    cp naive.txt tests/out/output$WA.txt
  }
  else{
    AC ++
  }
  $i--
  echo "WA: $WA, AC: $AC"
}
rm main.txt
rm naive.txt

