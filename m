#!/bin/bash
M_PATH=$(dirname "$(readlink -f "$0")")
cd "$M_PATH"
make || exit 1
echo
echo "RUNNING ./jpeglevel $@"
echo "---"
./jpeglevel "$@"
RC=$?
echo "---"
echo "RETURNED $RC"
