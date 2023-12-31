{ stdenv, gcc, gtest, lib }:

stdenv.mkDerivation rec {
  pname = "space_battle";
  version = "0.1";

  src = ./.; 

  buildInputs = [ stdenv gcc gtest ];

  doCheck = true;
  buildPhase = ''
    ulimit -c unlimited
    g++ -std=c++20 -o tests test/main.cpp src/Init.cpp -lgtest -lpthread -g
  '';

  checkPhase = ''
    ./tests
  '';

  installPhase = ''
    install -Dm755 tests $out/bin/tests
  '';

  meta = with lib; {
    description = "Implementation of space battle game using C++ with Google Test and Nix";
    platforms = platforms.linux;
  };
}
