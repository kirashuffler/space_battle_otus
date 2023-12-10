let
  pkgs = import <nixpkgs> { config.replaceStdenv = ( {pkgs} : pkgs.gcc13Stdenv ); };
in
  import ./default.nix {
    inherit (pkgs) stdenv gcc13 gtest lib;
}
