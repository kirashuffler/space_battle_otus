let
  pkgs = import <nixpkgs> {};
in
  import ./default.nix {
    inherit (pkgs) stdenv gcc gtest lib;
}
