#!/bin/bash
#
# Build Nusacoin-Qt.dmg locally on macOS (Intel or Apple Silicon).
#
# Mirrors .github/workflows/build-macos.yml (branch remy/build-macos-dmg),
# including all toolchain-compatibility shims. Run from the repo root:
#
#   git clone https://github.com/TaobotX11/nusacoin.git
#   cd nusacoin
#   bash /path/to/build-macos-local.sh
#
# Prerequisites: Xcode Command Line Tools (xcode-select --install) and Homebrew.
#
set -euo pipefail
cd "$(dirname "$0")"

echo "==> Installing dependencies with Homebrew..."
brew install automake berkeley-db@5 boost ccache libevent librsvg \
  libtool miniupnpc pkg-config python qrencode qt@5 zeromq

export PATH="$(brew --prefix qt@5)/bin:$PATH"
BDB_PREFIX="$(brew --prefix berkeley-db@5)"
export PKG_CONFIG_PATH="$(brew --prefix qt@5)/lib/pkgconfig:${PKG_CONFIG_PATH:-}"

echo "==> Creating dummy libboost_system.a (Boost >= 1.89 is header-only,"
echo "    but this old configure script still probes for the library)..."
echo "int boost_system_stub;" | c++ -x c++ -c -o /tmp/boost_system_stub.o -
ar rcs "$(brew --prefix boost)/lib/libboost_system.a" /tmp/boost_system_stub.o

echo "==> Applying macOS toolchain compatibility patches (working tree only)..."
sed -i '' 's/uint16_t short randv/uint16_t randv/' src/addrdb.cpp
sed -i '' 's/UPNP_GetValidIGD(devlist, &urls, &data, lanaddr, sizeof(lanaddr));/UPNP_GetValidIGD(devlist, \&urls, \&data, lanaddr, sizeof(lanaddr), nullptr, 0);/' src/net.cpp
sed -i '' 's/fs::copy_option::overwrite_if_exists/fs::copy_options::overwrite_existing/' src/wallet/bdb.cpp
sed -i '' 's/it.level()/it.depth()/' src/wallet/walletutil.cpp
cat > contrib/macdeploy/fancy.plist <<'PLIST'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>window_bounds</key>
	<array>
		<integer>100</integer>
		<integer>100</integer>
		<integer>540</integer>
		<integer>380</integer>
	</array>
	<key>icon_size</key>
	<integer>128</integer>
	<key>applications_symlink</key>
	<true/>
	<key>items_position</key>
	<dict>
		<key>Nusacoin-Qt.app</key>
		<array>
			<integer>120</integer>
			<integer>150</integer>
		</array>
		<key>Applications</key>
		<array>
			<integer>420</integer>
			<integer>150</integer>
		</array>
	</dict>
</dict>
</plist>
PLIST
sed -i '' 's/plistlib.readPlist(p)/plistlib.load(open(p, "rb"))/' contrib/macdeploy/macdeployqtplus

echo "==> Configuring..."
./autogen.sh
./configure --with-incompatible-bdb --with-boost="$(brew --prefix boost)" \
  --disable-tests --disable-bench --disable-gui-tests \
  BDB_LIBS="-L${BDB_PREFIX}/lib -ldb_cxx-5.3" \
  BDB_CFLAGS="-I${BDB_PREFIX}/include" \
  CPPFLAGS="-I$(brew --prefix)/include" \
  LDFLAGS="-L$(brew --prefix)/lib"

echo "==> Building (this takes a while)..."
make -j"$(sysctl -n hw.ncpu)"

echo "==> Creating DMG..."
export PYTHONUNBUFFERED=1
QT_TR_DIR="$($(brew --prefix qt@5)/bin/qmake -query QT_INSTALL_TRANSLATIONS)"
test -d "$QT_TR_DIR"
AVAIL=""
for lng in ar bg ca cs da de es fa fi fr gd gl he hu id it ja ko lt lv pl pt ru sk sl sv uk zh_CN zh_TW; do
  if [ -f "$QT_TR_DIR/qt_${lng}.qm" ]; then
    AVAIL="${AVAIL:+$AVAIL,}$lng"
  fi
done
echo "Qt translations dir: $QT_TR_DIR (available: ${AVAIL:-none})"
make deploy QT_TRANSLATION_DIR="$QT_TR_DIR" OSX_QT_TRANSLATIONS="$AVAIL"

echo ""
echo "==> Done!"
ls -la ./*.dmg
