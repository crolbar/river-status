{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = inputs: let
    system = "x86_64-linux";
    pkgs = import inputs.nixpkgs {inherit system;};
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = with pkgs; [
        wayland-scanner
        wayland
        pkg-config
        clang-tools
      ];
    };

    packages.${system}.default = pkgs.stdenv.mkDerivation {
      pname = "river-status";
      version = "0.1";
      src = ./.;

      buildInputs = with pkgs; [
        wayland-scanner
        wayland
        pkg-config
      ];

      makeFlags = ["PREFIX=$(out)"];
    };
  };
}
