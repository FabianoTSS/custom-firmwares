DIR=$(pwd)
mkdir -p root
tar -xf www.tar.gz -C $DIR/root
tar -xf usr.tar.gz -C $DIR/root
tar -xf system.tar.gz -C $DIR/root
tar -xf sys.tar.gz -C $DIR/root
tar -xf sbin.tar.gz -C $DIR/root
tar -xf root.tar.gz -C $DIR/root
tar -xf proc.tar.gz -C $DIR/root
tar -xf overlay.tar.gz -C $DIR/root
tar -xf mnt.tar.gz -C $DIR/root
tar -xf lib.tar.gz -C $DIR/root
tar -xf files.tar.gz -C $DIR/root
tar -xf etc.tar.gz -C $DIR/root
tar -xf dev.tar.gz -C $DIR/root
tar -xf cp.tar.gz -C $DIR/root
tar -xf chroot.tar.gz -C $DIR/root
tar -xf bin.tar.gz -C $DIR/root