#!/bin/bash

# Function to clean and recreate QML file
clean_qml() {
    local file=$1
    local filename=$(basename "$file" .qml)
    local dir=$(dirname "$file")
    
    cat > "$file" << EOF
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 400
    height: 300
    color: "white"
    
    Text {
        text: "$filename"
        anchors.centerIn: parent
        font.pixelSize: 20
    }
}
EOF
    echo "Cleaned: $file"
}

# Clean all QML files
export -f clean_qml
find qml -name "*.qml" -type f -exec bash -c 'clean_qml "$0"' {} \;

echo "All QML files cleaned!"
