{
  lib,
  libX11,
  libinput,
  libxcb,
  libxkbcommon,
  pcre2,
  pixman,
  pkg-config,
  stdenv,
  wayland,
  wayland-protocols,
  wayland-scanner,
  xcbutilwm,
  xwayland,
  meson,
  ninja,
  scenefx,
  wlroots_0_19,
  libGL,
  fetchFromGitLab,
  enableXWayland ? true,
  debug ? false,
}:
stdenv.mkDerivation {
  pname = "mango";
  version = "nightly";

  src = builtins.path {
    path = ../.;
    name = "source";
  };

  mesonFlags = [
    (lib.mesonEnable "xwayland" enableXWayland)
    (lib.mesonBool "asan" debug)
  ];

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
    wayland-scanner
  ];

  buildInputs = [
    libinput
    libxcb
    libxkbcommon
    pcre2
    pixman
    wayland
    wayland-protocols
    (wlroots_0_19.overrideAttrs (old: {
      version = "0.20-unstable";
      src = fetchFromGitLab {
        domain = "gitlab.freedesktop.org";
        owner = "wlroots";
        repo = "wlroots";
        rev = "884d29e5f31b5dec41fdbaa7876458e1b88a28be";
        hash = "sha256-486jjsRhj9uv/3Or1zdU5Aw472NHOJPdosYvGl+vGQw=";
      };
    }))
    libGL
  ]
  ++ lib.optionals enableXWayland [
    libX11
    xcbutilwm
    xwayland
  ];

  passthru = {
    providedSessions = [ "mango" ];
  };

  meta = {
    mainProgram = "mango";
    description = "A streamlined but feature-rich Wayland compositor";
    homepage = "https://github.com/DreamMaoMao/mango";
    license = lib.licenses.gpl3Plus;
    maintainers = [ ];
    platforms = lib.platforms.unix;
  };
}
