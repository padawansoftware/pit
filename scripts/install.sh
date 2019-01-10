INSTALL_DIR=/usr/share/pit

# Create directory
[ -d $INSTALL_DIR ] || mkdir $INSTALL_DIR

# Copy content
cp -r pit commands $INSTALL_DIR
