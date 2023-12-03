let 
  pkgs = import <nixpkgs> {};
in 
pkgs.mkShell {
  buildInputs = with pkgs; [
    stdenv
    cmake
    gcc
    gtest
  ];
}
