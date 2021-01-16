#!/bin/bash

if [[ -z "${MUSIKCUBE_BUILD_HOST_IP}" ]]; then
    echo "no build host ip specified"
    exit
fi

if [[ -z "${MUSIKCUBE_BUILD_HOST_PW}" ]]; then
    echo "no build host pw specified"
    exit
fi

# echo sshpass -p ${MUSIKCUBE_BUILD_HOST_PW} scp "$1/*" build@${MUSIKCUBE_BUILD_HOST_IP}:/home/build/ 2> /dev/null
# sshpass -p ${MUSIKCUBE_BUILD_HOST_PW} scp -o StrictHostKeyChecking=no "$1/*" build@${MUSIKCUBE_BUILD_HOST_IP}:/home/build/ 2> /dev/null

touch foo.bar.baz
sshpass -p ${MUSIKCUBE_BUILD_HOST_PW} scp -o StrictHostKeyChecking=no foo.bar.baz build@${MUSIKCUBE_BUILD_HOST_IP}:/home/build/ 2> /dev/null
