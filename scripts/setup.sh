#!/bin/bash

PROJECT_ROOT=$(dirname "$(dirname "$(realpath "$0")")")

mkdir -p "$PROJECT_ROOT/keys"
sudo chown -R $USER:$USER "$PROJECT_ROOT/keys"
ssh-keygen -t rsa -b 2048 -f "$PROJECT_ROOT/keys/ssh_host_rsa_key" -N ""
chmod 644 "$PROJECT_ROOT/keys/ssh_host_rsa_key"
echo "Host key generated !"
